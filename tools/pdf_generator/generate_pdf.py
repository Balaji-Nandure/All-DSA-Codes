import os
import sys
import subprocess
import html
import re
from pygments import highlight
from pygments.lexers import CppLexer
from pygments.formatters import HtmlFormatter
from dsa_parser import parse_cpp_file

def format_inline_markdown(text):
    if not text:
        return ""
    t = html.escape(text)
    t = re.sub(r'\$([^\$]+)\$', r'<code class="inline-code">\1</code>', t)
    t = re.sub(r'`([^`]+)`', r'<code class="inline-code">\1</code>', t)
    return t

def generate_html(data):
    # Syntax highlight code
    code_text = data.get("code", "")
    formatter = HtmlFormatter(style="one-dark", linenos=True, cssclass="highlight")
    highlighted_code = highlight(code_text, CppLexer(), formatter)
    pygments_css = formatter.get_style_defs(".highlight")

    # Difficulty badge color
    diff = data.get("difficulty", "Medium").strip()
    diff_lower = diff.lower()
    if "easy" in diff_lower or "basic" in diff_lower:
        diff_class = "badge-easy"
    elif "medium" in diff_lower:
        diff_class = "badge-medium"
    else:
        diff_class = "badge-hard"

    # Topics tags
    topics_html = "".join([f'<span class="topic-tag">{html.escape(t)}</span>' for t in data.get("topics", [])])

    # Links
    links_html = ""
    for l in data.get("links", []):
        label = html.escape(l["label"])
        url = html.escape(l["url"])
        icon = "🔗"
        if "leetcode" in label.lower() or "leetcode" in url.lower():
            icon = "⚡"
        elif "gfg" in label.lower() or "geeksforgeeks" in url.lower():
            icon = "🌿"
        links_html += f'<a href="{url}" class="link-btn" target="_blank">{icon} {label}</a>'

    # Examples HTML
    examples_html = ""
    for ex in data.get("examples", []):
        title = html.escape(ex.get("title", "Example"))
        inp = format_inline_markdown(ex.get("input", ""))
        out = format_inline_markdown(ex.get("output", ""))
        exp = format_inline_markdown(ex.get("explanation", ""))
        exp_row = f'<div class="ex-explanation"><strong>Explanation:</strong> {exp}</div>' if exp else ""
        examples_html += f'''
        <div class="example-card">
            <div class="example-title">{title}</div>
            <div class="example-grid">
                <div class="io-box">
                    <span class="io-label">Input</span>
                    <code>{inp}</code>
                </div>
                <div class="io-box">
                    <span class="io-label">Output</span>
                    <code>{out}</code>
                </div>
            </div>
            {exp_row}
        </div>
        '''

    # Constraints HTML
    constraints_html = ""
    if data.get("constraints"):
        items = "".join([f'<li><code>{format_inline_markdown(c)}</code></li>' for c in data["constraints"]])
        constraints_html = f'''
        <div class="constraints-card">
            <div class="card-subtitle">Constraints</div>
            <ul class="constraints-list">{items}</ul>
        </div>
        '''

    # Difference section (if present)
    differs_html = ""
    if data.get("differs_from"):
        differs_html = f'''
        <div class="differs-card">
            <div class="differs-title">🔄 How This Problem Differs From Previously Solved Problems</div>
            <div class="differs-content">{format_inline_markdown(data["differs_from"])}</div>
        </div>
        '''

    # Algorithm steps HTML
    steps_html = ""
    for s in data.get("algorithm_steps", []):
        lbl = html.escape(s.get("label", ""))
        desc = format_inline_markdown(s.get("desc", ""))
        steps_html += f'''
        <div class="step-item">
            <div class="step-badge">{lbl if lbl else "•"}</div>
            <div class="step-desc">{desc}</div>
        </div>
        '''

    # Alternative approaches
    alts_html = ""
    if data.get("alternatives"):
        alt_items = "".join([f'<li>{format_inline_markdown(a)}</li>' for a in data["alternatives"]])
        alts_html = f'''
        <div class="alternatives-box">
            <div class="card-subtitle-alt">Alternative Approaches</div>
            <ul class="alt-list">{alt_items}</ul>
        </div>
        '''

    # Visual Two Pointers Diagram (Only for Reverse an Array)
    diagram_html = ""
    if "reverse" in data.get("problem_name", "").lower() and "array" in data.get("problem_name", "").lower():
        diagram_html = """
        <div class="diagram-container">
            <div class="diagram-title"><span>Visual Trace:</span> Two Pointers In-Place Swapping</div>
            <div class="diagram-steps">
                <div class="diagram-step">
                    <div class="step-header">Initial: <code>left=0, right=4</code></div>
                    <div class="array-visual">
                        <div class="cell active-left"><span class="cell-val">h</span><span class="ptr-tag ptr-left">L (0)</span></div>
                        <div class="cell"><span class="cell-val">e</span></div>
                        <div class="cell"><span class="cell-val">l</span></div>
                        <div class="cell"><span class="cell-val">l</span></div>
                        <div class="cell active-right"><span class="cell-val">o</span><span class="ptr-tag ptr-right">R (4)</span></div>
                    </div>
                    <div class="action-caption">Swap <code>arr[0], arr[4]</code> &rarr; <code>L++, R--</code></div>
                </div>
                <div class="diagram-step">
                    <div class="step-header">Step 1: <code>left=1, right=3</code></div>
                    <div class="array-visual">
                        <div class="cell swapped"><span class="cell-val">o</span></div>
                        <div class="cell active-left"><span class="cell-val">e</span><span class="ptr-tag ptr-left">L (1)</span></div>
                        <div class="cell"><span class="cell-val">l</span></div>
                        <div class="cell active-right"><span class="cell-val">l</span><span class="ptr-tag ptr-right">R (3)</span></div>
                        <div class="cell swapped"><span class="cell-val">h</span></div>
                    </div>
                    <div class="action-caption">Swap <code>arr[1], arr[3]</code> &rarr; <code>L++, R--</code></div>
                </div>
                <div class="diagram-step">
                    <div class="step-header">Stop: <code>left=2 & right=2</code></div>
                    <div class="array-visual">
                        <div class="cell swapped"><span class="cell-val">o</span></div>
                        <div class="cell swapped"><span class="cell-val">l</span></div>
                        <div class="cell active-meet"><span class="cell-val">l</span><span class="ptr-tag ptr-meet">L == R</span></div>
                        <div class="cell swapped"><span class="cell-val">e</span></div>
                        <div class="cell swapped"><span class="cell-val">h</span></div>
                    </div>
                    <div class="action-caption checkmark">&#10004; In-Place Reversed (O(1) Space)</div>
                </div>
            </div>
        </div>
        """

    # Complexity details
    tc_details = "".join([f'<li>{format_inline_markdown(d)}</li>' for d in data.get("time_complexity_details", [])])
    sc_details = "".join([f'<li>{format_inline_markdown(d)}</li>' for d in data.get("space_complexity_details", [])])

    # Key insights
    insights_html = ""
    for ki in data.get("key_insights", []):
        insights_html += f'<div class="insight-row"><span class="insight-bullet">✦</span><div class="insight-text">{format_inline_markdown(ki)}</div></div>'

    num_display = f"#{data.get('problem_num', '01')}" if data.get('problem_num') else "DSA"
    topic_display = data.get("topics", ["DSA"])[0].upper() if data.get("topics") else "DSA"

    html_content = f'''<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>{html.escape(data.get("problem_name", "DSA Solution"))}</title>
<style>
    @import url('https://fonts.googleapis.com/css2?family=Plus+Jakarta+Sans:wght@400;500;600;700;800&family=JetBrains+Mono:wght@400;500;600;700&display=swap');

    @page {{
        size: A4 portrait;
        margin: 8mm 11mm 8mm 11mm;
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
        font-size: 11.5px;
        line-height: 1.45;
        -webkit-print-color-adjust: exact;
        print-color-adjust: exact;
    }}

    .inline-code {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 10.5px;
        background: #f1f5f9;
        color: #0f172a;
        padding: 1px 4px;
        border-radius: 3px;
        border: 1px solid #e2e8f0;
    }}

    .page {{
        page-break-after: always;
        break-after: page;
        display: flex;
        flex-direction: column;
        justify-content: space-between;
        box-sizing: border-box;
    }}

    .page-last {{
        page-break-after: avoid;
        break-after: avoid;
    }}

    /* Running Header */
    .running-header {{
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-bottom: 5px;
        border-bottom: 1.5px solid #e2e8f0;
        margin-bottom: 8px;
        font-size: 9.5px;
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
        padding: 1.5px 6px;
        border-radius: 4px;
        font-size: 9px;
    }}

    /* Problem Header */
    .problem-header {{
        background: linear-gradient(135deg, #f8fafc 0%, #f1f5f9 100%);
        border: 1px solid #e2e8f0;
        border-radius: 9px;
        padding: 10px 14px;
        margin-bottom: 8px;
    }}
    .title-row {{
        display: flex;
        align-items: center;
        gap: 10px;
        margin-bottom: 6px;
    }}
    .prob-num-pill {{
        background: linear-gradient(135deg, #4f46e5, #3b82f6);
        color: #ffffff;
        font-weight: 800;
        font-size: 11px;
        padding: 2.5px 8px;
        border-radius: 5px;
        letter-spacing: 0.5px;
    }}
    .prob-title {{
        font-size: 16.5px;
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
        gap: 6px;
    }}
    .badge-diff {{
        display: inline-flex;
        align-items: center;
        gap: 4px;
        padding: 2px 7px;
        border-radius: 14px;
        font-size: 10px;
        font-weight: 700;
    }}
    .badge-diff::before {{
        content: "";
        width: 5px;
        height: 5px;
        border-radius: 50%;
    }}
    .badge-easy {{
        background: #ecfdf5;
        color: #047857;
        border: 1px solid #a7f3d0;
    }}
    .badge-easy::before {{ background: #10b981; }}
    .badge-medium {{
        background: #fffbeb;
        color: #b45309;
        border: 1px solid #fde68a;
    }}
    .badge-medium::before {{ background: #f59e0b; }}
    .badge-hard {{
        background: #fef2f2;
        color: #b91c1c;
        border: 1px solid #fecaca;
    }}
    .badge-hard::before {{ background: #ef4444; }}

    .topic-tag {{
        background: #ffffff;
        border: 1px solid #cbd5e1;
        color: #334155;
        padding: 1.5px 6px;
        border-radius: 4px;
        font-size: 10px;
        font-weight: 600;
    }}
    .meta-links {{
        display: flex;
        gap: 5px;
    }}
    .link-btn {{
        display: inline-flex;
        align-items: center;
        gap: 4px;
        background: #ffffff;
        border: 1px solid #cbd5e1;
        color: #0f172a;
        text-decoration: none;
        padding: 2px 7px;
        border-radius: 5px;
        font-size: 10px;
        font-weight: 600;
    }}

    /* Section Styling */
    .section-title {{
        font-size: 11.5px;
        font-weight: 700;
        color: #1e293b;
        margin-bottom: 5px;
        display: flex;
        align-items: center;
        gap: 5px;
        text-transform: uppercase;
        letter-spacing: 0.5px;
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
        border-radius: 8px;
        padding: 8px 12px;
        margin-bottom: 8px;
    }}

    .statement-text {{
        font-size: 11.5px;
        color: #334155;
        line-height: 1.5;
        margin-bottom: 8px;
        white-space: pre-line;
    }}

    /* Examples */
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
        padding: 7px 9px;
    }}
    .example-title {{
        font-size: 10px;
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
        gap: 1px;
    }}
    .io-label {{
        font-size: 8.5px;
        font-weight: 700;
        color: #64748b;
        text-transform: uppercase;
    }}
    .io-box code {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 10px;
        background: #ffffff;
        border: 1px solid #e2e8f0;
        padding: 2px 4px;
        border-radius: 3px;
        color: #0f172a;
        word-break: break-all;
        white-space: pre-wrap;
    }}
    .ex-explanation {{
        font-size: 9.5px;
        color: #64748b;
        margin-top: 4px;
        padding-top: 3px;
        border-top: 1px dashed #e2e8f0;
    }}

    /* Constraints */
    .constraints-card {{
        background: #fefce8;
        border: 1px solid #fef08a;
        border-radius: 6px;
        padding: 5px 10px;
    }}
    .card-subtitle {{
        font-size: 9.5px;
        font-weight: 700;
        color: #854d0e;
        margin-bottom: 3px;
        text-transform: uppercase;
        letter-spacing: 0.4px;
    }}
    .constraints-list {{
        list-style: none;
        display: flex;
        flex-wrap: wrap;
        gap: 8px;
    }}
    .constraints-list li code {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 10px;
        color: #713f12;
        background: #ffffff;
        padding: 1.5px 5px;
        border-radius: 3px;
        border: 1px solid #fde047;
    }}

    /* Differs Card */
    .differs-card {{
        background: #fff7ed;
        border: 1px solid #fed7aa;
        border-radius: 6px;
        padding: 6px 10px;
        margin-bottom: 8px;
    }}
    .differs-title {{
        font-size: 10px;
        font-weight: 700;
        color: #c2410c;
        margin-bottom: 3px;
        text-transform: uppercase;
        letter-spacing: 0.4px;
    }}
    .differs-content {{
        font-size: 10.5px;
        color: #9a3412;
        line-height: 1.4;
        white-space: pre-line;
    }}

    /* Intuition & Approach */
    .approach-header {{
        display: flex;
        align-items: center;
        justify-content: space-between;
        margin-bottom: 4px;
    }}
    .approach-title {{
        font-weight: 700;
        color: #4338ca;
        font-size: 12px;
    }}
    .intuition-box {{
        background: #eff6ff;
        border-left: 3px solid #3b82f6;
        padding: 6px 10px;
        border-radius: 0 5px 5px 0;
        color: #1e40af;
        font-size: 11px;
        line-height: 1.45;
        margin-bottom: 6px;
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
        font-size: 9px;
        font-weight: 700;
        padding: 1px 6px;
        border-radius: 3px;
        white-space: nowrap;
        margin-top: 1px;
    }}
    .step-desc {{
        font-size: 10.5px;
        color: #334155;
    }}

    /* Visual Trace Diagram */
    .diagram-container {{
        background: #0f172a;
        border-radius: 7px;
        padding: 8px 12px;
        margin-top: 6px;
        color: #f8fafc;
    }}
    .diagram-title {{
        font-size: 10px;
        font-weight: 700;
        color: #94a3b8;
        text-transform: uppercase;
        letter-spacing: 0.5px;
        margin-bottom: 6px;
    }}
    .diagram-title span {{
        color: #38bdf8;
    }}
    .diagram-steps {{
        display: grid;
        grid-template-columns: repeat(3, 1fr);
        gap: 8px;
    }}
    .diagram-step {{
        background: #1e293b;
        border: 1px solid #334155;
        border-radius: 5px;
        padding: 6px 8px;
        display: flex;
        flex-direction: column;
        justify-content: space-between;
    }}
    .step-header {{
        font-size: 9px;
        font-weight: 600;
        color: #cbd5e1;
        margin-bottom: 6px;
        font-family: 'JetBrains Mono', monospace;
    }}
    .array-visual {{
        display: flex;
        gap: 4px;
        justify-content: center;
        margin-bottom: 8px;
    }}
    .cell {{
        width: 24px;
        height: 25px;
        border: 1.5px solid #475569;
        border-radius: 4px;
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        background: #0f172a;
        position: relative;
    }}
    .cell-val {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 11px;
        font-weight: 700;
        color: #f8fafc;
    }}
    .active-left {{
        border-color: #38bdf8;
        background: rgba(56, 189, 248, 0.15);
    }}
    .active-right {{
        border-color: #ec4899;
        background: rgba(236, 72, 153, 0.15);
    }}
    .active-meet {{
        border-color: #34d399;
        background: rgba(52, 211, 153, 0.2);
    }}
    .swapped {{
        border-color: #22c55e;
    }}
    .ptr-tag {{
        position: absolute;
        bottom: -13px;
        font-size: 7px;
        font-weight: 700;
        padding: 0.5px 2px;
        border-radius: 2px;
        white-space: nowrap;
        font-family: 'JetBrains Mono', monospace;
    }}
    .ptr-left {{
        background: #38bdf8;
        color: #0f172a;
    }}
    .ptr-right {{
        background: #ec4899;
        color: #ffffff;
    }}
    .ptr-meet {{
        background: #34d399;
        color: #0f172a;
    }}
    .action-caption {{
        font-size: 8.5px;
        color: #94a3b8;
        margin-top: 10px;
        text-align: center;
        line-height: 1.2;
    }}
    .action-caption.checkmark {{
        color: #4ade80;
        font-weight: 600;
    }}

    .alternatives-box {{
        margin-top: 6px;
        padding-top: 5px;
        border-top: 1px solid #f1f5f9;
    }}
    .card-subtitle-alt {{
        font-size: 9.5px;
        font-weight: 700;
        color: #64748b;
        text-transform: uppercase;
        margin-bottom: 2px;
    }}
    .alt-list {{
        list-style: disc inside;
        font-size: 10.5px;
        color: #475569;
        line-height: 1.35;
    }}

    /* Code Container Styling */
    .code-window {{
        background: #0d1117;
        border: 1px solid #30363d;
        border-radius: 7px;
        overflow: hidden;
        margin-bottom: 6px;
    }}
    .code-topbar {{
        background: #161b22;
        padding: 4px 10px;
        display: flex;
        align-items: center;
        justify-content: space-between;
        border-bottom: 1px solid #30363d;
    }}
    .mac-dots {{
        display: flex;
        gap: 4px;
    }}
    .dot-ctrl {{
        width: 7px;
        height: 7px;
        border-radius: 50%;
    }}
    .dot-red {{ background: #ff5f56; }}
    .dot-yellow {{ background: #ffbd2e; }}
    .dot-green {{ background: #27c93f; }}
    .code-filename {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 9px;
        font-weight: 600;
        color: #c9d1d9;
    }}
    .lang-badge {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 8.5px;
        font-weight: 700;
        color: #58a6ff;
        background: rgba(56, 139, 253, 0.15);
        padding: 1px 5px;
        border-radius: 3px;
    }}

    .highlight {{
        padding: 5px 8px;
        overflow-x: auto;
        font-family: 'JetBrains Mono', monospace;
        font-size: 8.4px;
        line-height: 1.25;
    }}
    .highlight pre {{
        margin: 0;
    }}
    .highlight .linenos {{
        color: #484f58;
        padding-right: 8px;
        user-select: none;
        border-right: 1px solid #21262d;
    }}
    .highlight .code {{
        padding-left: 8px;
    }}

    /* Complexity Matrix */
    .complexity-matrix {{
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 6px;
        margin-bottom: 5px;
    }}
    .complexity-card {{
        border-radius: 6px;
        padding: 5px 10px;
        border: 1px solid #e2e8f0;
        background: #ffffff;
    }}
    .tc-card {{
        border-top: 2.5px solid #3b82f6;
    }}
    .sc-card {{
        border-top: 2.5px solid #10b981;
    }}
    .comp-header {{
        display: flex;
        align-items: center;
        justify-content: space-between;
        margin-bottom: 2px;
    }}
    .comp-title {{
        font-size: 9px;
        font-weight: 700;
        color: #64748b;
        text-transform: uppercase;
        letter-spacing: 0.5px;
    }}
    .comp-badge {{
        font-family: 'JetBrains Mono', monospace;
        font-size: 11px;
        font-weight: 800;
        padding: 1px 5px;
        border-radius: 3px;
    }}
    .tc-badge {{
        background: #eff6ff;
        color: #1d4ed8;
        border: 1px solid #bfdbfe;
    }}
    .sc-badge {{
        background: #ecfdf5;
        color: #047857;
        border: 1px solid #a7f3d0;
    }}
    .comp-bullets {{
        list-style: none;
        font-size: 9.5px;
        color: #334155;
        line-height: 1.32;
    }}
    .comp-bullets li {{
        margin-top: 1px;
    }}

    /* Key Insights */
    .insights-card {{
        background: #faf5ff;
        border: 1px solid #e9d5ff;
        border-radius: 6px;
        padding: 5px 10px;
        margin-bottom: 5px;
    }}
    .insights-title {{
        font-size: 9.5px;
        font-weight: 700;
        color: #7e22ce;
        text-transform: uppercase;
        letter-spacing: 0.5px;
        margin-bottom: 3px;
        display: flex;
        align-items: center;
        gap: 4px;
    }}
    .insight-row {{
        display: flex;
        align-items: flex-start;
        gap: 5px;
        margin-bottom: 2px;
    }}
    .insight-bullet {{
        color: #a855f7;
        font-size: 9px;
        margin-top: 1px;
    }}
    .insight-text {{
        font-size: 9.5px;
        color: #4c1d95;
        line-height: 1.32;
    }}

    /* Footer */
    .running-footer {{
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding-top: 5px;
        border-top: 1.5px solid #e2e8f0;
        font-size: 9px;
        color: #94a3b8;
    }}
    .footer-left {{
        font-weight: 600;
    }}

    {pygments_css}
</style>
</head>
<body>

    <!-- ================= PAGE 1: Problem & Approach ================= -->
    <div class="page">
        <div>
            <!-- Running Header -->
            <div class="running-header">
                <div class="brand">
                    <span>⚡ LOVE BABBAR 450 DSA SHEET</span>
                    <span class="badge-track">TOPIC: {html.escape(topic_display)}</span>
                </div>
                <div>PROBLEM {html.escape(num_display)}</div>
            </div>

            <!-- Problem Header -->
            <div class="problem-header">
                <div class="title-row">
                    <span class="prob-num-pill">{html.escape(num_display)}</span>
                    <h1 class="prob-title">{html.escape(data.get("problem_name", "DSA Problem"))}</h1>
                </div>
                <div class="meta-bar">
                    <div class="meta-left">
                        <span class="badge-diff {diff_class}">{html.escape(diff)}</span>
                        {topics_html}
                    </div>
                    <div class="meta-links">
                        {links_html}
                    </div>
                </div>
            </div>

            <!-- Problem Statement -->
            <div class="section-title"><div class="dot"></div> Problem Statement</div>
            <div class="card">
                <div class="statement-text">
                    {format_inline_markdown(data.get("statement", ""))}
                </div>

                <!-- Examples -->
                <div class="examples-grid">
                    {examples_html}
                </div>

                <!-- Constraints -->
                {constraints_html}
            </div>

            <!-- Difference Section (if present) -->
            {differs_html}

            <!-- Algorithmic Strategy & Intuition -->
            <div class="section-title"><div class="dot"></div> Strategy & Intuition</div>
            <div class="card">
                <div class="approach-header">
                    <div class="approach-title">{html.escape(data.get("approach_title", "Optimal Strategy"))}</div>
                </div>
                
                {f'<div class="intuition-box"><strong>Core Intuition:</strong> {format_inline_markdown(data["intuition"])}</div>' if data.get("intuition") else ""}

                <div class="steps-container">
                    {steps_html}
                </div>

                {diagram_html}

                {alts_html}
            </div>
        </div>

        <div class="running-footer">
            <div class="footer-left">Love Babbar 450 DSA Cracker &bull; Handcrafted Notes</div>
            <div>Problem {html.escape(num_display)} &bull; Page 1</div>
        </div>
    </div>

    <!-- ================= PAGE 2: Code & Complexity ================= -->
    <div class="page page-last">
        <div>
            <!-- Running Header -->
            <div class="running-header">
                <div class="brand">
                    <span>⚡ LOVE BABBAR 450 DSA SHEET</span>
                    <span class="badge-track">TOPIC: {html.escape(topic_display)}</span>
                </div>
                <div>PROBLEM {html.escape(num_display)} &bull; SOLUTION & NOTES</div>
            </div>

            <!-- Code Implementation -->
            <div class="section-title"><div class="dot"></div> C++20 Implementation (Optimal)</div>
            <div class="code-window">
                <div class="code-topbar">
                    <div class="mac-dots">
                        <div class="dot-ctrl dot-red"></div>
                        <div class="dot-ctrl dot-yellow"></div>
                        <div class="dot-ctrl dot-green"></div>
                    </div>
                    <div class="code-filename">Solution.cpp &bull; {html.escape(data.get('approach_title', 'Optimal Solution')[:40])}</div>
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
                        <span class="comp-badge tc-badge">{html.escape(data.get("time_complexity", "O(N)"))}</span>
                    </div>
                    <ul class="comp-bullets">
                        {tc_details}
                    </ul>
                </div>
                <div class="complexity-card sc-card">
                    <div class="comp-header">
                        <span class="comp-title">Space Complexity</span>
                        <span class="comp-badge sc-badge">{html.escape(data.get("space_complexity", "O(1)"))}</span>
                    </div>
                    <ul class="comp-bullets">
                        {sc_details}
                    </ul>
                </div>
            </div>

            <!-- Key Insights & Gotchas -->
            <div class="section-title"><div class="dot"></div> Key Insights & Interview Edge Cases</div>
            <div class="insights-card">
                <div class="insights-title">💡 Important Interview Takeaways</div>
                {insights_html}
            </div>
        </div>

        <div class="running-footer">
            <div class="footer-left">Love Babbar 450 DSA Cracker &bull; Handcrafted Notes</div>
            <div>Problem {html.escape(num_display)} &bull; Page 2</div>
        </div>
    </div>

</body>
</html>
'''
    return html_content

def convert_to_pdf(input_cpp, output_pdf=None):
    input_cpp = os.path.abspath(input_cpp)
    if not output_pdf:
        output_pdf = os.path.splitext(input_cpp)[0] + ".pdf"
    output_pdf = os.path.abspath(output_pdf)

    data = parse_cpp_file(input_cpp)
    html_code = generate_html(data)
    
    html_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "temp_render.html"))
    with open(html_path, "w", encoding="utf-8") as f:
        f.write(html_code)

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
        if os.path.exists(output_pdf):
            print(f"SUCCESS: PDF generated at {output_pdf} ({os.path.getsize(output_pdf)} bytes)")
        else:
            print(f"ERROR: Failed to generate PDF. Stderr: {proc.stderr}")
            return False
    finally:
        if os.path.exists(html_path):
            os.remove(html_path)

    # Render PNG previews only if explicitly requested with --preview
    if "--preview" in sys.argv:
        try:
            import pymupdf
            doc = pymupdf.open(output_pdf)
            preview_dir = os.path.join(os.path.dirname(__file__), "preview")
            os.makedirs(preview_dir, exist_ok=True)
            for f in os.listdir(preview_dir):
                if f.endswith(".png"):
                    os.remove(os.path.join(preview_dir, f))
            print(f"Generating page previews ({len(doc)} pages)...")
            for idx, page in enumerate(doc):
                pix = page.get_pixmap(dpi=150)
                img_path = os.path.join(preview_dir, f"page_{idx + 1}.png")
                pix.save(img_path)
                print(f"Saved: {img_path}")
        except Exception as e:
            print(f"Preview error: {e}")

    return True

if __name__ == "__main__":
    target_cpp = sys.argv[1] if len(sys.argv) > 1 else r"c:\Users\balaj\Desktop\Barana\All-DSA-Codes\6. Love babbar sheet\1. Arrays\1. Reverse an Array.cpp"
    convert_to_pdf(target_cpp)
