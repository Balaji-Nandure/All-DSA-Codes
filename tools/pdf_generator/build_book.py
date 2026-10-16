import os
import sys
import glob
import re
import html
import subprocess
import pymupdf
from pygments import highlight
from pygments.lexers import CppLexer
from pygments.formatters import HtmlFormatter
from dsa_parser import parse_cpp_file

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', s)]

def format_inline_markdown(text):
    if not text:
        return ""
    t = html.escape(text)
    t = re.sub(r'\$([^\$]+)\$', r'<code class="inline-code">\1</code>', t)
    t = re.sub(r'`([^`]+)`', r'<code class="inline-code">\1</code>', t)
    return t

def build_book(base_dir=r"6. Love babbar sheet", output_pdf=None, filter_topics=None, book_title=None, book_subtitle=None, brand_title=None):
    base_dir = os.path.abspath(base_dir)
    dir_name = os.path.basename(base_dir)
    clean_dir_name = re.sub(r'^\d+\.\s*', '', dir_name).strip().title()

    if not book_title:
        book_title = f"{clean_dir_name} Handbook"
    if not book_subtitle:
        book_subtitle = f"Curated solutions, algorithmic intuition, step-by-step traces, and time/space complexity analysis formatted for maximum readability."
    if not brand_title:
        brand_title = clean_dir_name.upper()

    if not output_pdf:
        output_pdf = os.path.join(base_dir, f"{re.sub(r'[^a-zA-Z0-9]+', '_', clean_dir_name)}_Handbook.pdf")
    output_pdf = os.path.abspath(output_pdf)

    # 1. Discover all topics and questions
    topic_dirs = sorted([d for d in os.listdir(base_dir) if os.path.isdir(os.path.join(base_dir, d))], key=natural_sort_key)
    
    if filter_topics:
        topic_dirs = [d for d in topic_dirs if any(ft.lower() in d.lower() for ft in filter_topics)]

    book_data = []
    total_problems = 0

    print(f"Scanning '{base_dir}'...")

    # Check for direct .cpp files in base_dir
    direct_cpps = sorted([os.path.join(base_dir, f) for f in os.listdir(base_dir) if f.endswith('.cpp')], key=natural_sort_key)
    if direct_cpps and not topic_dirs:
        topic_item = {
            "folder": dir_name,
            "title": clean_dir_name,
            "slug": re.sub(r'[^a-zA-Z0-9]+', '-', clean_dir_name).lower(),
            "problems": []
        }
        for f in direct_cpps:
            p_data = parse_cpp_file(f)
            p_data["file_path"] = f
            p_data["topic_title"] = clean_dir_name
            p_data["topic_slug"] = topic_item["slug"]
            p_slug = f"{topic_item['slug']}-{p_data.get('problem_num', '00')}"
            p_data["anchor_id"] = f"prob-{p_slug}"
            topic_item["problems"].append(p_data)
            total_problems += 1
        book_data.append(topic_item)

    for t_dir in topic_dirs:
        full_tdir = os.path.join(base_dir, t_dir)
        # Find all cpp files recursively
        cpp_files = []
        for root_p, _, fnames in os.walk(full_tdir):
            for fn in fnames:
                if fn.endswith('.cpp'):
                    cpp_files.append(os.path.join(root_p, fn))
        cpp_files = sorted(cpp_files, key=natural_sort_key)
        if not cpp_files:
            continue
        
        t_clean = re.sub(r'^\d+\.\s*', '', t_dir).strip()
        topic_item = {
            "folder": t_dir,
            "title": t_clean,
            "slug": re.sub(r'[^a-zA-Z0-9]+', '-', t_clean).lower(),
            "problems": []
        }

        print(f"  Loading {t_dir} ({len(cpp_files)} files)...")
        for f in cpp_files:
            p_data = parse_cpp_file(f)
            p_data["file_path"] = f
            p_data["topic_title"] = t_clean
            p_data["topic_slug"] = topic_item["slug"]
            p_slug = f"{topic_item['slug']}-{p_data.get('problem_num', '00')}"
            p_data["anchor_id"] = f"prob-{p_slug}"
            topic_item["problems"].append(p_data)
            total_problems += 1

        book_data.append(topic_item)

    print(f"\nTotal chapters to compile: {len(book_data)} with {total_problems} problems.")

    if total_problems == 0:
        print("No C++ files found to compile.")
        return

    # Pygments styling
    formatter = HtmlFormatter(style="one-dark", linenos=True, cssclass="highlight")
    pygments_css = formatter.get_style_defs(".highlight")

    # 2. Build HTML Content
    html_parts = []

    # HTML Head & Base CSS
    html_parts.append(f'''<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>Love Babbar 450 DSA Sheet - Master Book</title>
<style>
    @import url('https://fonts.googleapis.com/css2?family=Plus+Jakarta+Sans:wght@400;500;600;700;800&family=JetBrains+Mono:wght@400;500;600;700&display=swap');

    @page {{
        size: A4 portrait;
        margin: 9mm 12mm 9mm 12mm;
    }}

    * {{
        box-sizing: border-box;
        margin: 0;
        padding: 0;
    }}

    body {{
        font-family: 'Plus Jakarta Sans', -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
        color: #1e293b;
        background: #ffffff;
        font-size: 13.5px;
        line-height: 1.6;
        -webkit-print-color-adjust: exact;
        print-color-adjust: exact;
    }}

    .inline-code {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 12px;
        background: #f1f5f9;
        color: #0f172a;
        padding: 2px 5px;
        border-radius: 4px;
        border: 1px solid #e2e8f0;
    }}

    .page-break {{
        page-break-before: always;
        break-before: page;
    }}

    .avoid-break {{
        break-inside: avoid;
        page-break-inside: avoid;
    }}

    /* ================= COVER PAGE ================= */
    .cover-page {{
        background: radial-gradient(circle at 80% 20%, #1e1b4b 0%, #0b0f19 70%, #030712 100%);
        color: #ffffff;
        padding: 30mm 15mm 20mm 15mm;
        display: flex;
        flex-direction: column;
        justify-content: space-between;
        min-height: 275mm;
        box-sizing: border-box;
        border-radius: 8px;
    }}
    .cover-top {{
        display: flex;
        align-items: center;
        gap: 8px;
        font-size: 13px;
        font-weight: 700;
        letter-spacing: 2px;
        color: #818cf8;
        text-transform: uppercase;
    }}
    .cover-center {{
        margin-top: 25mm;
    }}
    .cover-badge {{
        display: inline-block;
        background: rgba(99, 102, 241, 0.2);
        border: 1px solid #6366f1;
        color: #a5b4fc;
        padding: 4px 12px;
        border-radius: 20px;
        font-size: 12px;
        font-weight: 700;
        letter-spacing: 1px;
        margin-bottom: 15px;
    }}
    .cover-title {{
        font-size: 38px;
        font-weight: 800;
        line-height: 1.15;
        letter-spacing: -0.8px;
        background: linear-gradient(135deg, #ffffff 30%, #c7d2fe 70%, #38bdf8 100%);
        -webkit-background-clip: text;
        -webkit-text-fill-color: transparent;
        margin-bottom: 12px;
    }}
    .cover-subtitle {{
        font-size: 16px;
        color: #94a3b8;
        max-width: 520px;
        line-height: 1.5;
        margin-bottom: 30px;
    }}
    .cover-stats-grid {{
        display: grid;
        grid-template-columns: repeat(3, 1fr);
        gap: 12px;
        max-width: 480px;
    }}
    .cover-stat-box {{
        background: rgba(255, 255, 255, 0.05);
        border: 1px solid rgba(255, 255, 255, 0.1);
        border-radius: 8px;
        padding: 10px 14px;
    }}
    .cover-stat-num {{
        font-size: 24px;
        font-weight: 800;
        color: #38bdf8;
    }}
    .cover-stat-label {{
        font-size: 10px;
        color: #94a3b8;
        text-transform: uppercase;
        letter-spacing: 0.5px;
    }}
    .cover-footer {{
        border-top: 1px solid rgba(255, 255, 255, 0.1);
        padding-top: 15px;
        display: flex;
        justify-content: space-between;
        align-items: center;
        font-size: 11px;
        color: #64748b;
    }}

    /* ================= CHAPTER SPLASH PAGE ================= */
    .chapter-splash-page {{
        background: radial-gradient(circle at 80% 20%, #1e1b4b 0%, #0b0f19 75%, #030712 100%);
        color: #ffffff;
        padding: 30mm 15mm 20mm 15mm;
        display: flex;
        flex-direction: column;
        justify-content: space-between;
        min-height: 275mm;
        box-sizing: border-box;
        border-radius: 8px;
    }}
    .chap-splash-top {{
        display: flex;
        justify-content: space-between;
        align-items: center;
        font-size: 11px;
        font-weight: 700;
        letter-spacing: 2px;
        color: #818cf8;
        text-transform: uppercase;
    }}
    .chap-splash-hero {{
        margin: 20mm 0;
    }}
    .chap-badge {{
        display: inline-block;
        background: rgba(99, 102, 241, 0.2);
        border: 1px solid #6366f1;
        color: #a5b4fc;
        padding: 4px 12px;
        border-radius: 20px;
        font-size: 11px;
        font-weight: 700;
        letter-spacing: 1px;
        margin-bottom: 15px;
    }}
    .chap-title {{
        font-size: 34px;
        font-weight: 800;
        letter-spacing: -0.5px;
        background: linear-gradient(135deg, #ffffff 40%, #c7d2fe 80%, #38bdf8 100%);
        -webkit-background-clip: text;
        -webkit-text-fill-color: transparent;
        margin-bottom: 10px;
    }}
    .chap-subtitle {{
        font-size: 13px;
        color: #94a3b8;
        line-height: 1.5;
        max-width: 520px;
        margin-bottom: 25px;
    }}
    .chap-stats-grid {{
        display: flex;
        gap: 15px;
    }}
    .chap-stat-box {{
        background: rgba(255, 255, 255, 0.05);
        border: 1px solid rgba(255, 255, 255, 0.1);
        border-radius: 6px;
        padding: 8px 14px;
    }}
    .chap-stat-num {{
        font-size: 20px;
        font-weight: 800;
        color: #38bdf8;
    }}
    .chap-stat-lbl {{
        font-size: 9px;
        color: #94a3b8;
        text-transform: uppercase;
        letter-spacing: 0.5px;
    }}
    .chap-splash-footer {{
        border-top: 1px solid rgba(255, 255, 255, 0.1);
        padding-top: 12px;
        display: flex;
        justify-content: space-between;
        align-items: center;
        font-size: 10px;
        color: #64748b;
    }}

    /* ================= TABLE OF CONTENTS (MENU) ================= */
    .toc-container {{
        padding: 10px 0;
    }}
    .toc-header {{
        margin-bottom: 18px;
        border-bottom: 2px solid #e2e8f0;
        padding-bottom: 10px;
        display: flex;
        justify-content: space-between;
        align-items: flex-end;
    }}
    .toc-title {{
        font-size: 26px;
        font-weight: 800;
        color: #0f172a;
    }}
    .toc-subtitle {{
        font-size: 13px;
        color: #64748b;
        font-weight: 600;
    }}
    .toc-chapter-card {{
        background: #f8fafc;
        border: 1px solid #e2e8f0;
        border-radius: 8px;
        padding: 12px 16px;
        margin-bottom: 14px;
        break-inside: avoid;
        page-break-inside: avoid;
    }}
    .toc-chapter-title {{
        font-size: 15px;
        font-weight: 700;
        color: #4338ca;
        margin-bottom: 10px;
        display: flex;
        justify-content: space-between;
        align-items: center;
    }}
    .toc-prob-list {{
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 6px 14px;
        list-style: none;
    }}
    .toc-item a {{
        display: flex;
        align-items: center;
        gap: 8px;
        text-decoration: none;
        color: #1e293b;
        font-size: 12px;
        padding: 4px 8px;
        border-radius: 5px;
        transition: background 0.2s;
    }}
    .toc-item a:hover {{
        background: #e2e8f0;
    }}
    .toc-prob-num {{
        font-family: 'JetBrains Mono', monospace;
        font-weight: 700;
        color: #4f46e5;
        font-size: 11.5px;
    }}
    .toc-prob-name {{
        white-space: nowrap;
        overflow: hidden;
        text-overflow: ellipsis;
        flex: 1;
    }}
    .toc-diff-dot {{
        width: 7px;
        height: 7px;
        border-radius: 50%;
        display: inline-block;
    }}
    .dot-easy {{ background: #10b981; }}
    .dot-medium {{ background: #f59e0b; }}
    .dot-hard {{ background: #ef4444; }}

    /* ================= RUNNING HEADERS & FOOTERS ================= */
    .running-header {{
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-bottom: 5px;
        border-bottom: 1.5px solid #e2e8f0;
        margin-bottom: 9px;
        font-size: 10px;
        color: #64748b;
        font-weight: 700;
        letter-spacing: 0.5px;
        text-transform: uppercase;
    }}
    .running-header .brand {{
        display: flex;
        align-items: center;
        gap: 6px;
        color: #4f46e5;
    }}
    .running-header .badge-track {{
        background: #eef2ff;
        color: #4338ca;
        padding: 2px 7px;
        border-radius: 4px;
        font-size: 9.5px;
    }}
    .toc-jump-link {{
        text-decoration: none;
        color: #4f46e5;
        background: #eef2ff;
        padding: 2.5px 8px;
        border-radius: 4px;
        font-weight: 700;
        font-size: 9.5px;
        display: inline-flex;
        align-items: center;
        gap: 4px;
    }}

    .running-footer {{
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-top: 5px;
        border-top: 1.5px solid #e2e8f0;
        margin-top: 9px;
        font-size: 9.5px;
        color: #94a3b8;
    }}

    /* ================= PROBLEM CARDS & STYLES ================= */
    .problem-header {{
        background: linear-gradient(135deg, #f8fafc 0%, #f1f5f9 100%);
        border: 1px solid #e2e8f0;
        border-radius: 9px;
        padding: 10px 14px;
        margin-bottom: 9px;
    }}
    .title-row {{
        display: flex;
        align-items: center;
        gap: 9px;
        margin-bottom: 6px;
    }}
    .prob-num-pill {{
        background: linear-gradient(135deg, #4f46e5, #3b82f6);
        color: #ffffff;
        font-weight: 800;
        font-size: 12px;
        padding: 3px 9px;
        border-radius: 5px;
    }}
    .prob-title {{
        font-size: 18px;
        font-weight: 800;
        color: #0f172a;
        letter-spacing: -0.3px;
    }}
    .meta-bar {{
        display: flex;
        align-items: center;
        justify-content: space-between;
        gap: 8px;
    }}
    .meta-left {{
        display: flex;
        align-items: center;
        gap: 8px;
    }}
    .badge-diff {{
        display: inline-flex;
        align-items: center;
        gap: 5px;
        padding: 3px 8px;
        border-radius: 12px;
        font-size: 11px;
        font-weight: 700;
    }}
    .badge-diff::before {{
        content: "";
        width: 6px;
        height: 6px;
        border-radius: 50%;
    }}
    .badge-easy {{ background: #ecfdf5; color: #047857; border: 1px solid #a7f3d0; }}
    .badge-easy::before {{ background: #10b981; }}
    .badge-medium {{ background: #fffbeb; color: #b45309; border: 1px solid #fde68a; }}
    .badge-medium::before {{ background: #f59e0b; }}
    .badge-hard {{ background: #fef2f2; color: #b91c1c; border: 1px solid #fecaca; }}
    .badge-hard::before {{ background: #ef4444; }}

    .topic-tag {{
        background: #ffffff;
        border: 1px solid #cbd5e1;
        color: #334155;
        padding: 2px 7px;
        border-radius: 4px;
        font-size: 11px;
        font-weight: 600;
    }}
    .meta-links {{
        display: flex;
        gap: 6px;
    }}
    .link-btn {{
        display: inline-flex;
        align-items: center;
        gap: 4px;
        background: #ffffff;
        border: 1px solid #cbd5e1;
        color: #0f172a;
        text-decoration: none;
        padding: 2.5px 8px;
        border-radius: 4px;
        font-size: 10.5px;
        font-weight: 600;
    }}

    .section-title {{
        font-size: 13px;
        font-weight: 700;
        color: #1e293b;
        margin-bottom: 6px;
        display: flex;
        align-items: center;
        gap: 6px;
        text-transform: uppercase;
        letter-spacing: 0.6px;
    }}
    .section-title .dot {{
        width: 6px;
        height: 6px;
        background: #4f46e5;
        border-radius: 2px;
    }}

    .card {{
        background: #ffffff;
        border: 1px solid #e2e8f0;
        border-radius: 7px;
        padding: 9px 13px;
        margin-bottom: 9px;
    }}
    .statement-text {{
        font-size: 13.5px;
        color: #334155;
        line-height: 1.6;
        margin-bottom: 8px;
        white-space: pre-line;
    }}

    .examples-grid {{
        display: grid;
        grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
        gap: 8px;
        margin-bottom: 8px;
    }}
    .example-card {{
        background: #f8fafc;
        border: 1px solid #e2e8f0;
        border-radius: 6px;
        padding: 7px 10px;
    }}
    .example-title {{
        font-size: 11px;
        font-weight: 700;
        color: #475569;
        margin-bottom: 4px;
        text-transform: uppercase;
    }}
    .example-grid {{
        display: flex;
        flex-direction: column;
        gap: 4px;
    }}
    .io-box {{
        display: flex;
        flex-direction: column;
        gap: 2px;
    }}
    .io-label {{
        font-size: 9.5px;
        font-weight: 700;
        color: #64748b;
        text-transform: uppercase;
    }}
    .io-box code {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 12px;
        background: #ffffff;
        border: 1px solid #e2e8f0;
        padding: 2.5px 6px;
        border-radius: 4px;
        color: #0f172a;
        word-break: break-all;
        white-space: pre-wrap;
    }}
    .ex-explanation {{
        font-size: 12px;
        color: #64748b;
        margin-top: 4px;
        padding-top: 3px;
        border-top: 1px dashed #e2e8f0;
        line-height: 1.5;
    }}

    .constraints-card {{
        background: #fefce8;
        border: 1px solid #fef08a;
        border-radius: 6px;
        padding: 6px 10px;
        margin-top: 6px;
    }}
    .card-subtitle {{
        font-size: 11px;
        font-weight: 700;
        color: #854d0e;
        margin-bottom: 3px;
        text-transform: uppercase;
    }}
    .constraints-list {{
        list-style: none;
        display: flex;
        flex-wrap: wrap;
        gap: 8px;
    }}
    .constraints-list li code {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 12px;
        color: #713f12;
        background: #ffffff;
        padding: 2px 6px;
        border-radius: 4px;
        border: 1px solid #fde047;
    }}

    .differs-card {{
        background: #fff7ed;
        border: 1px solid #fed7aa;
        border-radius: 6px;
        padding: 7px 11px;
        margin-bottom: 9px;
    }}
    .differs-title {{
        font-size: 11.5px;
        font-weight: 700;
        color: #c2410c;
        margin-bottom: 3px;
        text-transform: uppercase;
    }}
    .differs-content {{
        font-size: 12.5px;
        color: #9a3412;
        line-height: 1.55;
        white-space: pre-line;
    }}

    .approach-header {{
        display: flex;
        align-items: center;
        justify-content: space-between;
        margin-bottom: 4px;
    }}
    .approach-title {{
        font-weight: 700;
        color: #4338ca;
        font-size: 13.5px;
    }}
    .intuition-box {{
        background: #eff6ff;
        border-left: 3px solid #3b82f6;
        padding: 7px 11px;
        border-radius: 0 5px 5px 0;
        color: #1e40af;
        font-size: 13px;
        line-height: 1.55;
        margin-bottom: 7px;
    }}
    .steps-container {{
        display: flex;
        flex-direction: column;
        gap: 4px;
        margin-bottom: 6px;
    }}
    .step-item {{
        display: flex;
        align-items: flex-start;
        gap: 6px;
    }}
    .step-badge {{
        background: #4f46e5;
        color: #ffffff;
        font-size: 10.5px;
        font-weight: 700;
        padding: 1.5px 6px;
        border-radius: 3px;
        white-space: nowrap;
        margin-top: 1px;
    }}
    .step-desc {{
        font-size: 12.5px;
        color: #334155;
        line-height: 1.5;
    }}

    /* Code Window */
    .code-window {{
        background: #0d1117;
        border: 1px solid #30363d;
        border-radius: 7px;
        overflow: hidden;
        margin-bottom: 9px;
        page-break-inside: auto;
        break-inside: auto;
    }}
    .code-topbar {{
        background: #161b22;
        padding: 6px 11px;
        display: flex;
        align-items: center;
        justify-content: space-between;
        border-bottom: 1px solid #30363d;
    }}
    .mac-dots {{ display: flex; gap: 5px; }}
    .dot-ctrl {{ width: 8px; height: 8px; border-radius: 50%; }}
    .dot-red {{ background: #ff5f56; }}
    .dot-yellow {{ background: #ffbd2e; }}
    .dot-green {{ background: #27c93f; }}
    .code-filename {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 11px;
        font-weight: 600;
        color: #c9d1d9;
    }}
    .lang-badge {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 10px;
        font-weight: 700;
        color: #58a6ff;
        background: rgba(56, 139, 253, 0.15);
        padding: 2px 6px;
        border-radius: 4px;
    }}
    .highlight {{
        padding: 8px 12px;
        overflow-x: auto;
        font-family: 'JetBrains Mono', monospace;
        font-size: 12.5px;
        line-height: 1.55;
    }}
    .highlight pre {{ margin: 0; }}
    .highlight .linenos {{
        color: #6e7681;
        padding-right: 8px;
        user-select: none;
        border-right: 1px solid #30363d;
        font-size: 11.5px;
    }}
    .highlight .code {{ padding-left: 8px; }}

    /* Complexity Matrix */
    .complexity-matrix {{
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 8px;
        margin-bottom: 8px;
        break-inside: avoid;
        page-break-inside: avoid;
    }}
    .complexity-card {{
        border-radius: 6px;
        padding: 7px 11px;
        border: 1px solid #e2e8f0;
        background: #ffffff;
    }}
    .tc-card {{ border-top: 3px solid #3b82f6; }}
    .sc-card {{ border-top: 3px solid #10b981; }}
    .comp-header {{
        display: flex;
        align-items: center;
        justify-content: space-between;
        margin-bottom: 3px;
    }}
    .comp-title {{
        font-size: 11px;
        font-weight: 700;
        color: #64748b;
        text-transform: uppercase;
    }}
    .comp-badge {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 12.5px;
        font-weight: 800;
        padding: 2px 6px;
        border-radius: 4px;
    }}
    .tc-badge {{ background: #eff6ff; color: #1d4ed8; border: 1px solid #bfdbfe; }}
    .sc-badge {{ background: #ecfdf5; color: #047857; border: 1px solid #a7f3d0; }}
    .comp-bullets {{
        list-style: none;
        font-size: 12px;
        color: #334155;
        line-height: 1.45;
    }}
    .comp-bullets li {{ margin-top: 2px; }}

    .insights-card {{
        background: #faf5ff;
        border: 1px solid #e9d5ff;
        border-radius: 6px;
        padding: 7px 11px;
        margin-bottom: 7px;
        break-inside: avoid;
        page-break-inside: avoid;
    }}
    .insights-title {{
        font-size: 11.5px;
        font-weight: 700;
        color: #7e22ce;
        text-transform: uppercase;
        margin-bottom: 4px;
        display: flex;
        align-items: center;
        gap: 5px;
    }}
    .insight-row {{
        display: flex;
        align-items: flex-start;
        gap: 5px;
        margin-bottom: 3px;
    }}
    .insight-bullet {{ color: #a855f7; font-size: 11px; margin-top: 1px; }}
    .insight-text {{ font-size: 12px; color: #4c1d95; line-height: 1.45; }}

    {pygments_css}
</style>
</head>
<body>
''')

    # 1. COVER PAGE
    html_parts.append(f'''
    <div class="cover-page">
        <div class="cover-top">
            <span>⚡ THE ULTIMATE TECHNICAL INTERVIEW HANDBOOK</span>
        </div>
        <div class="cover-center">
            <div class="cover-badge">{html.escape(brand_title)} &bull; COMPLETE EDITION</div>
            <h1 class="cover-title">{html.escape(book_title)}</h1>
            <p class="cover-subtitle">{html.escape(book_subtitle)}</p>
            <div class="cover-stats-grid">
                <div class="cover-stat-box">
                    <div class="cover-stat-num">{len(book_data)}</div>
                    <div class="cover-stat-label">Core Modules</div>
                </div>
                <div class="cover-stat-box">
                    <div class="cover-stat-num">{total_problems}</div>
                    <div class="cover-stat-label">C++ Solutions</div>
                </div>
                <div class="cover-stat-box">
                    <div class="cover-stat-num">C++20</div>
                    <div class="cover-stat-label">Optimal & In-Place</div>
                </div>
            </div>
        </div>
        <div class="cover-footer">
            <div>Balaji &bull; Codebase Edition</div>
            <div>Interactive PDF &bull; Clickable Navigation</div>
        </div>
    </div>
    ''')

    # 2. TABLE OF CONTENTS (INTERACTIVE MENU)
    html_parts.append('''
    <div class="page-break" id="table-of-contents">
        <div class="toc-container">
            <div class="toc-header">
                <div>
                    <h1 class="toc-title">Table of Contents</h1>
                    <div class="toc-subtitle">Interactive Menu &bull; Click any problem to jump directly to its solution</div>
                </div>
                <div class="cover-badge" style="margin-bottom: 0;">'''+f"{total_problems} Problems"+'''</div>
            </div>
    ''')

    for chap in book_data:
        html_parts.append(f'''
        <div class="toc-chapter-card">
            <div class="toc-chapter-title">
                <a href="#chap-{chap['slug']}" style="text-decoration: none; color: inherit;">📁 {html.escape(chap["title"])}</a>
                <span style="font-size: 10px; color: #64748b;">{len(chap["problems"])} Questions</span>
            </div>
            <ul class="toc-prob-list">
        ''')
        for p in chap["problems"]:
            diff_dot = "dot-easy" if "easy" in p.get("difficulty", "").lower() else ("dot-medium" if "medium" in p.get("difficulty", "").lower() else "dot-hard")
            p_num = p.get("problem_num", "•")
            p_title = p.get("problem_name", "Problem")
            html_parts.append(f'''
                <li class="toc-item">
                    <a href="#{p['anchor_id']}">
                        <span class="toc-diff-dot {diff_dot}"></span>
                        <span class="toc-prob-num">#{p_num}</span>
                        <span class="toc-prob-name">{html.escape(p_title)}</span>
                    </a>
                </li>
            ''')
        html_parts.append('''
            </ul>
        </div>
        ''')

    html_parts.append('''
        </div>
    </div>
    ''')

    # 3. PROBLEMS RENDER LOOP
    for chap_idx, chap in enumerate(book_data, 1):
        # Chapter Splash Page
        html_parts.append(f'''
        <div class="page-break chapter-splash-page" id="chap-{chap['slug']}">
            <div class="chap-splash-top">
                <span>⚡ {html.escape(brand_title)} &bull; MODULE {chap_idx:02d}</span>
                <a href="#table-of-contents" class="toc-jump-link">📖 Table of Contents</a>
            </div>
            <div class="chap-splash-hero">
                <div class="chap-badge">CHAPTER {chap_idx:02d}</div>
                <h1 class="chap-title">📁 {html.escape(chap['title'])}</h1>
                <p class="chap-subtitle">Curated collection of {len(chap['problems'])} interview questions with full algorithmic intuition, C++20 implementations, and time/space complexity proofs.</p>
                <div class="chap-stats-grid">
                    <div class="chap-stat-box">
                        <div class="chap-stat-num">{len(chap['problems'])}</div>
                        <div class="chap-stat-lbl">Questions</div>
                    </div>
                    <div class="chap-stat-box">
                        <div class="chap-stat-num">100%</div>
                        <div class="chap-stat-lbl">Verified Solutions</div>
                    </div>
                    <div class="chap-stat-box">
                        <div class="chap-stat-num">C++20</div>
                        <div class="chap-stat-lbl">Optimal & In-Place</div>
                    </div>
                </div>
            </div>
            <div class="chap-splash-footer">
                <div style="font-family: monospace; font-size: 8px; color: #475569;">CHAPTER_START::{chap_idx:02d}::{html.escape(chap['title'])}</div>
                <div>{html.escape(brand_title)} &bull; Chapter {chap_idx:02d}</div>
            </div>
        </div>
        ''')

        for p in chap["problems"]:
            # Syntax highlight
            code_text = p.get("code", "")
            highlighted_code = highlight(code_text, CppLexer(), formatter)

            diff = p.get("difficulty", "Medium").strip()
            diff_class = "badge-easy" if "easy" in diff.lower() else ("badge-medium" if "medium" in diff.lower() else "badge-hard")
            topics_html = "".join([f'<span class="topic-tag">{html.escape(t)}</span>' for t in p.get("topics", [])])

            links_html = ""
            for l in p.get("links", []):
                label = html.escape(l["label"])
                url = html.escape(l["url"])
                icon = "⚡" if "leetcode" in label.lower() else ("🌿" if "gfg" in label.lower() else "🔗")
                links_html += f'<a href="{url}" class="link-btn" target="_blank">{icon} {label}</a>'

            examples_html = ""
            for ex in p.get("examples", []):
                title = html.escape(ex.get("title", "Example"))
                inp = format_inline_markdown(ex.get("input", ""))
                out = format_inline_markdown(ex.get("output", ""))
                exp = format_inline_markdown(ex.get("explanation", ""))
                exp_row = f'<div class="ex-explanation"><strong>Explanation:</strong> {exp}</div>' if exp else ""
                examples_html += f'''
                <div class="example-card">
                    <div class="example-title">{title}</div>
                    <div class="example-grid">
                        <div class="io-box"><span class="io-label">Input</span><code>{inp}</code></div>
                        <div class="io-box"><span class="io-label">Output</span><code>{out}</code></div>
                    </div>
                    {exp_row}
                </div>
                '''

            constraints_html = ""
            if p.get("constraints"):
                c_items = "".join([f'<li><code>{format_inline_markdown(c)}</code></li>' for c in p["constraints"]])
                constraints_html = f'''
                <div class="constraints-card">
                    <div class="card-subtitle">Constraints</div>
                    <ul class="constraints-list">{c_items}</ul>
                </div>
                '''

            differs_html = ""
            if p.get("differs_from"):
                differs_html = f'''
                <div class="differs-card">
                    <div class="differs-title">🔄 How This Differs From Previously Solved Problems</div>
                    <div class="differs-content">{format_inline_markdown(p["differs_from"])}</div>
                </div>
                '''

            steps_html = ""
            for s in p.get("algorithm_steps", []):
                lbl = html.escape(s.get("label", ""))
                desc = format_inline_markdown(s.get("desc", ""))
                steps_html += f'''
                <div class="step-item">
                    <div class="step-badge">{lbl if lbl else "•"}</div>
                    <div class="step-desc">{desc}</div>
                </div>
                '''

            tc_details = "".join([f'<li>{format_inline_markdown(d)}</li>' for d in p.get("time_complexity_details", [])])
            sc_details = "".join([f'<li>{format_inline_markdown(d)}</li>' for d in p.get("space_complexity_details", [])])

            insights_html = ""
            for ki in p.get("key_insights", []):
                insights_html += f'<div class="insight-row"><span class="insight-bullet">✦</span><div class="insight-text">{format_inline_markdown(ki)}</div></div>'

            num_str = p.get('problem_num', '00')

            # Render Problem (Starts on clean new page with anchor ID)
            html_parts.append(f'''
            <div class="page-break" id="{p['anchor_id']}">
                <!-- Running Header with clickable Menu jump -->
                <div class="running-header">
                    <div class="brand">
                        <span>⚡ {html.escape(brand_title)}</span>
                        <span class="badge-track">{html.escape(p["topic_title"].upper())}</span>
                    </div>
                    <div style="display: flex; align-items: center; gap: 8px;">
                        <span style="font-size: 7.5px; color: #94a3b8; font-family: monospace;">PROBLEM_START::{num_str}::{html.escape(p.get("problem_name", "Problem"))}</span>
                        <a href="#table-of-contents" class="toc-jump-link">📖 Table of Contents</a>
                    </div>
                </div>

                <!-- Problem Header -->
                <div class="problem-header">
                    <div class="title-row">
                        <span class="prob-num-pill">#{num_str}</span>
                        <h2 class="prob-title">{html.escape(p.get("problem_name", "DSA Problem"))}</h2>
                    </div>
                    <div class="meta-bar">
                        <div class="meta-left">
                            <span class="badge-diff {diff_class}">{html.escape(diff)}</span>
                            {topics_html}
                        </div>
                        <div class="meta-links">{links_html}</div>
                    </div>
                </div>

                <!-- Statement & Examples -->
                <div class="section-title"><div class="dot"></div> Problem Statement</div>
                <div class="card">
                    <div class="statement-text">{format_inline_markdown(p.get("statement", ""))}</div>
                    <div class="examples-grid">{examples_html}</div>
                    {constraints_html}
                </div>

                {differs_html}

                <!-- Strategy & Intuition -->
                <div class="section-title"><div class="dot"></div> Strategy & Intuition</div>
                <div class="card">
                    <div class="approach-header">
                        <div class="approach-title">{html.escape(p.get("approach_title", "Optimal Strategy"))}</div>
                    </div>
                    {f'<div class="intuition-box"><strong>Core Intuition:</strong> {format_inline_markdown(p["intuition"])}</div>' if p.get("intuition") else ""}
                    <div class="steps-container">{steps_html}</div>
                </div>

                <div class="running-footer">
                    <div>{html.escape(brand_title)} &bull; {html.escape(p["topic_title"])}</div>
                    <div>Problem #{num_str}</div>
                </div>
            </div>

            <!-- Page 2 for this Problem: Code & Complexity -->
            <div class="page-break">
                <div class="running-header">
                    <div class="brand">
                        <span>⚡ {html.escape(brand_title)}</span>
                        <span class="badge-track">{html.escape(p["topic_title"].upper())} &bull; #{num_str}</span>
                    </div>
                    <div>
                        <a href="#table-of-contents" class="toc-jump-link">📖 Table of Contents</a>
                    </div>
                </div>

                <!-- Code Section -->
                <div class="section-title"><div class="dot"></div> C++ Implementation (Optimal)</div>
                <div class="code-window">
                    <div class="code-topbar">
                        <div class="mac-dots">
                            <div class="dot-ctrl dot-red"></div>
                            <div class="dot-ctrl dot-yellow"></div>
                            <div class="dot-ctrl dot-green"></div>
                        </div>
                        <div class="code-filename">Solution.cpp &bull; {html.escape(p.get("approach_title", "Optimal Solution")[:40])}</div>
                        <div class="lang-badge">C++20 / STL</div>
                    </div>
                    {highlighted_code}
                </div>

                <!-- Complexity Matrix -->
                <div class="section-title"><div class="dot"></div> Complexity Analysis</div>
                <div class="complexity-matrix">
                    <div class="complexity-card tc-card">
                        <div class="comp-header">
                            <span class="comp-title">Time Complexity</span>
                            <span class="comp-badge tc-badge">{html.escape(p.get("time_complexity", "O(N)"))}</span>
                        </div>
                        <ul class="comp-bullets">{tc_details}</ul>
                    </div>
                    <div class="complexity-card sc-card">
                        <div class="comp-header">
                            <span class="comp-title">Space Complexity</span>
                            <span class="comp-badge sc-badge">{html.escape(p.get("space_complexity", "O(1)"))}</span>
                        </div>
                        <ul class="comp-bullets">{sc_details}</ul>
                    </div>
                </div>

                <!-- Key Insights -->
                <div class="section-title"><div class="dot"></div> Key Insights & Edge Cases</div>
                <div class="insights-card">
                    <div class="insights-title">💡 Important Interview Takeaways</div>
                    {insights_html}
                </div>

                <div class="running-footer">
                    <div>{html.escape(brand_title)} &bull; Handcrafted Notes</div>
                    <div>Problem #{num_str} &bull; Solution</div>
                </div>
            </div>
            ''')

    html_parts.append('''
</body>
</html>
''')

    full_html = "\n".join(html_parts)
    html_path = os.path.join(os.path.dirname(__file__), "temp_book_render.html")
    with open(html_path, "w", encoding="utf-8") as f:
        f.write(full_html)

    print(f"\nRendering Master Book HTML -> PDF via Chrome Headless...")
    chrome_exe = r"C:\Program Files\Google\Chrome\Application\chrome.exe"
    if not os.path.exists(chrome_exe):
        chrome_exe = r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe"

    cmd = [
        chrome_exe,
        "--headless=new",
        "--disable-gpu",
        "--no-pdf-header-footer",
        "--run-all-compositor-stages-before-draw",
        f"--print-to-pdf={output_pdf}",
        html_path
    ]

    try:
        proc = subprocess.run(cmd, capture_output=True, text=True)
        if not os.path.exists(output_pdf):
            print(f"ERROR: Failed to render book. Stderr: {proc.stderr}")
            return False
        print(f"Generated raw PDF at: {output_pdf} ({os.path.getsize(output_pdf)} bytes)")
    finally:
        if os.path.exists(html_path):
            os.remove(html_path)

    # 4. Inject PDF Bookmarks (Native PDF Reader Outline) using PyMuPDF
    print("Injecting native PDF Sidebar Bookmarks (Outline tree)...")
    try:
        doc = pymupdf.open(output_pdf)
        toc = [
            [1, "Cover Page", 1],
            [1, "Table of Contents", 2]
        ]

        cur_chap_title = ""
        seen_chaps = set()
        seen_probs = set()

        for pno in range(len(doc)):
            txt = doc[pno].get_text()
            lines = [l.strip().encode('ascii', 'ignore').decode() for l in txt.splitlines() if l.strip()]

            for line in lines:
                if "CHAPTER_START::" in line:
                    m = re.search(r"CHAPTER_START::(\d+)::(.+)", line)
                    if m:
                        c_idx, c_title = m.group(1), m.group(2).strip()
                        if c_title not in seen_chaps:
                            seen_chaps.add(c_title)
                            cur_chap_title = c_title
                            toc.append([1, f"📁 {c_idx}. {c_title}", pno + 1])
                    break

                if "PROBLEM_START::" in line:
                    m = re.search(r"PROBLEM_START::([0-9•]+)::(.+)", line)
                    if m:
                        p_num, p_title = m.group(1), m.group(2).strip()
                        key = f"{cur_chap_title}-{p_num}-{p_title}"
                        if key not in seen_probs:
                            seen_probs.add(key)
                            toc.append([2, f"#{p_num} {p_title[:45]}", pno + 1])
                    break

        doc.set_toc(toc)
        temp_toc_pdf = output_pdf + ".tmp.pdf"
        doc.save(temp_toc_pdf)
        doc.close()
        os.replace(temp_toc_pdf, output_pdf)
        print(f"SUCCESS! Master Book with full interactive Menu & Outline is ready at:\n{output_pdf}")
    except Exception as e:
        print(f"Warning during TOC injection: {e}")

    return True

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description="Compile DSA Directory into an Interactive Master Book")
    parser.add_argument("folder", nargs="?", default=None, help="Target folder (e.g. '2. dynamic programming')")
    parser.add_argument("--dir", "-d", default=None, help="Base directory containing topic subfolders")
    parser.add_argument("--out", "-o", default=None, help="Output PDF file path")
    parser.add_argument("--title", "-t", default=None, help="Custom Book Title")
    parser.add_argument("--subtitle", "-s", default=None, help="Custom Book Subtitle")
    parser.add_argument("--topics", nargs="*", default=None, help="Filter specific subtopics")

    args = parser.parse_args()

    # Determine base directory
    target_dir = args.dir or args.folder or r"6. Love babbar sheet"
    build_book(
        base_dir=target_dir,
        output_pdf=args.out,
        filter_topics=args.topics,
        book_title=args.title,
        book_subtitle=args.subtitle
    )
