import os
import re
import html

def clean_comment_text(raw_text):
    """
    Strips comment markers (/*, /**, */, //, and leading * on lines)
    while preserving indentation and content structure.
    """
    lines = raw_text.splitlines()
    cleaned_lines = []
    for line in lines:
        l = line.strip()
        # Remove comment openers and closers
        if l.startswith("/**") or l.startswith("/*"):
            line = re.sub(r"^\s*/\*+\s*", "", line)
        if l.endswith("*/"):
            line = re.sub(r"\s*\*+/\s*$", "", line)
        # Remove leading * or //
        line = re.sub(r"^\s*(?:\*|//)\s?", "", line)
        cleaned_lines.append(line)
    return "\n".join(cleaned_lines)

def parse_cpp_file(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        text = f.read()

    # Determine topic / category from folder if available
    folder_name = os.path.basename(os.path.dirname(file_path))
    topic_from_folder = re.sub(r"^\d+\.\s*", "", folder_name).strip()

    data = {
        "problem_name": "",
        "problem_num": "",
        "difficulty": "Medium",
        "topics": [topic_from_folder] if topic_from_folder else [],
        "links": [],
        "statement": "",
        "examples": [],
        "constraints": [],
        "differs_from": "",
        "approach_title": "",
        "intuition": "",
        "algorithm_steps": [],
        "alternatives": [],
        "code": "",
        "time_complexity": "O(N)",
        "time_complexity_details": [],
        "space_complexity": "O(1)",
        "space_complexity_details": [],
        "key_insights": []
    }

    base_name = os.path.basename(file_path)
    num_match = re.match(r"^(\d+)\.\s*(.+)\.cpp$", base_name)
    if num_match:
        data["problem_num"] = num_match.group(1).zfill(2)
        data["problem_name"] = num_match.group(2).strip()

    # Find where the actual executable code begins:
    # Code usually starts at #include, using namespace, class, struct, template, or function definition
    code_match = re.search(r"(?:^|\n)\s*(?:#include|using\s+namespace|class\s+\w+|struct\s+\w+|template\s*<|(?:void|int|bool|double|long|auto|Node\s*\*|TreeNode\s*\*|vector\s*<[\w\s,:]+>)\s+\w+\s*\([^)]*\)\s*\{)", text)
    if code_match:
        header_comments_raw = text[:code_match.start()]
        remaining_code = text[code_match.start():].strip()
    else:
        # Fallback to checking /* ... */ block
        prob_comment_m = re.search(r"/\*+[\s\S]*?(?:Problem|Problem Statement|Problem Name)[\s\S]*?\*+/", text, re.IGNORECASE)
        if prob_comment_m:
            header_comments_raw = prob_comment_m.group(0)
            remaining_code = text[prob_comment_m.end():].strip()
        elif "/*" in text and "*/" in text:
            last_comment_end = text.rfind("*/") + 2
            header_comments_raw = text[:last_comment_end]
            remaining_code = text[last_comment_end:].strip()
        else:
            header_comments_raw = ""
            remaining_code = text.strip()

    if not remaining_code and text.strip():
        remaining_code = text.strip()

    # Find comment blocks inside remaining_code to isolate trailing complexity analysis
    comment_blocks = list(re.finditer(r"/\*+[\s\S]*?\*+/", remaining_code))
    trailing_comments_raw = ""
    if comment_blocks:
        last_cb = comment_blocks[-1]
        cb_text_lower = last_cb.group(0).lower()
        after_last_cb = remaining_code[last_cb.end():].strip()
        # Only isolate as trailing complexity if it is truly at the end of the code
        if len(after_last_cb) < 150 and any(kw in cb_text_lower for kw in ["complexity", "takeaways", "insights", "time complexity"]):
            data["code"] = remaining_code[:last_cb.start()].strip()
            trailing_comments_raw = last_cb.group(0)
        else:
            data["code"] = remaining_code.strip()
    else:
        data["code"] = remaining_code.strip()

    # Clean the header comments
    header_clean = clean_comment_text(header_comments_raw)

    # 1. Metadata extraction
    for line in header_clean.splitlines():
        l_strip = line.strip()
        # Problem Name
        m_prob = re.match(r"^(?:Problem|Problem Name)\s*:\s*(.+)$", l_strip, re.IGNORECASE)
        if m_prob:
            val = m_prob.group(1).strip()
            if not data["problem_name"] or len(val) >= len(data["problem_name"]):
                data["problem_name"] = val

        # Difficulty
        m_diff = re.match(r"^Difficulty\s*:\s*(.+)$", l_strip, re.IGNORECASE)
        if m_diff:
            data["difficulty"] = m_diff.group(1).strip()

        # Category / Topic
        m_cat = re.match(r"^(?:Category|Topic)\s*:\s*(.+)$", l_strip, re.IGNORECASE)
        if m_cat:
            cat_list = [c.strip() for c in m_cat.group(1).split(",") if c.strip()]
            for c in cat_list:
                if c not in data["topics"]:
                    data["topics"].append(c)

        # Links & Platform
        if "http://" in l_strip or "https://" in l_strip:
            url_m = re.search(r"https?://[^\s)]+", l_strip)
            if url_m:
                url = url_m.group(0)
                label = l_strip[:url_m.start()].strip().rstrip(":").rstrip("-").strip()
                label = re.sub(r"^(?:Link|Article|Platform)\s*\(?", "", label, flags=re.IGNORECASE).rstrip(")")
                if not label:
                    label = "Problem Link"
                data["links"].append({"label": label.strip(), "url": url})
        elif l_strip.lower().startswith("platform:"):
            plat = l_strip.split(":", 1)[1].strip()
            if plat and not any(l["label"] == plat for l in data["links"]):
                data["links"].append({"label": plat, "url": "#"})

    # 2. Problem Statement extraction
    ps_match = re.search(r"(?:Problem Statement|Description)\s*:\s*(.*?)(?=(?:Example\s*\d+|Examples\s*:|Constraints\s*:|Expected Complexities\s*:|HOW THIS PROBLEM DIFFERS|APPROACH|\Z))", header_clean, re.DOTALL | re.IGNORECASE)
    if ps_match:
        data["statement"] = ps_match.group(1).strip()
    else:
        lines_list = [l for l in header_clean.splitlines() if l.strip()]
        if lines_list:
            data["statement"] = "\n".join(lines_list[:6])

    # 3. Examples extraction
    ex_section = re.search(r"(?:Examples\s*:|Example\s*1\s*:)(.*?)(?=(?:Constraints\s*:|Expected Complexities\s*:|HOW THIS PROBLEM DIFFERS|APPROACH|\Z))", header_clean, re.DOTALL | re.IGNORECASE)
    if ex_section:
        ex_content = ex_section.group(0)
        chunks = re.split(r"(?:^|\n)\s*(Example\s*\d+[^:\n]*:)", ex_content, flags=re.IGNORECASE)
        if len(chunks) > 1:
            for k in range(1, len(chunks), 2):
                title = chunks[k].strip().rstrip(":")
                body = chunks[k+1] if k+1 < len(chunks) else ""
                inp_m = re.search(r"Input\s*:\s*(.*?)(?=Output\s*:|\Z)", body, re.DOTALL | re.IGNORECASE)
                out_m = re.search(r"Output\s*:\s*(.*?)(?=Explanation\s*:|\Z)", body, re.DOTALL | re.IGNORECASE)
                exp_m = re.search(r"Explanation\s*:\s*(.*)", body, re.DOTALL | re.IGNORECASE)
                data["examples"].append({
                    "title": title,
                    "input": inp_m.group(1).strip() if inp_m else "",
                    "output": out_m.group(1).strip() if out_m else "",
                    "explanation": exp_m.group(1).strip() if exp_m else ""
                })
        else:
            io_pairs = re.findall(r"Input\s*:\s*(.*?)\n\s*Output\s*:\s*(.*?)(?=\n\s*(?:Explanation|Input|\Z))", ex_content, re.DOTALL | re.IGNORECASE)
            for idx, (inp, out) in enumerate(io_pairs):
                data["examples"].append({
                    "title": f"Example {idx + 1}",
                    "input": inp.strip(),
                    "output": out.strip(),
                    "explanation": ""
                })

    # 4. Constraints extraction
    c_m = re.search(r"Constraints\s*:\s*(.*?)(?=(?:Expected Complexities\s*:|HOW THIS PROBLEM DIFFERS|APPROACH|\Z))", header_clean, re.DOTALL | re.IGNORECASE)
    if c_m:
        c_lines = c_m.group(1).strip().splitlines()
        for cl in c_lines:
            cl_clean = cl.strip().lstrip("-").lstrip("*").strip()
            if cl_clean and not cl_clean.startswith("="):
                data["constraints"].append(cl_clean)

    # 5. Difference section
    diff_m = re.search(r"(?:HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS|HOW THIS PROBLEM DIFFERS)\s*:\s*(.*?)(?=(?:APPROACH & WHY|APPROACH|\Z))", header_clean, re.DOTALL | re.IGNORECASE)
    if diff_m:
        diff_lines = [l.strip() for l in diff_m.group(1).splitlines() if l.strip() and not l.strip().startswith("-") and not l.strip().startswith("=")]
        data["differs_from"] = "\n".join(diff_lines[:6])

    # 6. Approach / Intuition / Steps
    app_m = re.search(r"(?:APPROACH & WHY THIS APPROACH ONLY|APPROACH|INTUITION & STRATEGY)\s*(?:\([^)]*\))?\s*:\s*(.*)", header_clean, re.DOTALL | re.IGNORECASE)
    if app_m:
        app_text = app_m.group(1).strip()
        lines = [l for l in app_text.splitlines() if l.strip() and not l.strip().startswith("=")]
        
        if lines:
            data["approach_title"] = lines[0].strip().lstrip("-").lstrip("*").strip()

        # Intuition
        int_m = re.search(r"(?:Core Intuition|Intuition|Intuition & Strategy)\s*:\s*(.*?)(?=(?:\d+\.\s*Algorithm Steps|Algorithm Steps|Step 1|\d+\.\s*Alternative Approaches|Method 1|Method 2|\Z))", app_text, re.DOTALL | re.IGNORECASE)
        if int_m:
            data["intuition"] = int_m.group(1).strip()
        else:
            data["intuition"] = "\n".join(lines[1:4]) if len(lines) > 1 else (lines[0] if lines else "")

        # Algorithm Steps / Methods
        steps_found = re.findall(r"(?:^|\n)\s*(?:[-*]\s*)?(Step\s*\d+:|Method\s*\d+:|\d+\.)\s*(.*?)(?=(?:\n\s*(?:[-*]\s*)?(?:Step\s*\d+:|Method\s*\d+:|\d+\.)|\n\s*Alternative Approaches|\Z))", app_text, re.DOTALL | re.IGNORECASE)
        for s_lbl, s_desc in steps_found:
            s_desc_clean = " ".join([l.strip().lstrip("-").lstrip("*").strip() for l in s_desc.splitlines() if l.strip()])
            data["algorithm_steps"].append({
                "label": s_lbl.strip().rstrip(":"),
                "desc": s_desc_clean[:240]
            })

    # 7. Complexity Extraction (from header or trailing comments)
    combined_comp_text = trailing_comments_raw if trailing_comments_raw else header_comments_raw
    combined_comp_clean = clean_comment_text(combined_comp_text)

    # Time Complexity
    tc_m = re.search(r"(?:Time Complexity|Expected Time Complexity)\s*:\s*([^\n]+)(.*?)(?=(?:Space Complexity|Auxiliary Space|KEY TAKEAWAYS|Key Insights|\Z))", combined_comp_clean, re.DOTALL | re.IGNORECASE)
    if tc_m:
        raw_tc = tc_m.group(1).strip().rstrip(".")
        tc_body = tc_m.group(2).strip()
        
        # Check if there is an O(...) inside raw_tc or tc_body
        badge_m = re.search(r"O\([^)]+\)", raw_tc)
        if not badge_m and tc_body:
            badge_m = re.search(r"O\([^)]+\)", tc_body)
        
        if badge_m:
            data["time_complexity"] = badge_m.group(0)
            details = [l.strip().lstrip("-").lstrip("*").strip() for l in (raw_tc + "\n" + tc_body).splitlines() if l.strip().lstrip("-").lstrip("*").strip() and not l.strip().startswith("=")]
            data["time_complexity_details"] = details[:3]
        else:
            data["time_complexity"] = raw_tc[:20]
            data["time_complexity_details"] = [l.strip().lstrip("-").lstrip("*").strip() for l in tc_body.splitlines() if l.strip().lstrip("-").lstrip("*").strip()]

    # Space Complexity
    sc_m = re.search(r"(?:Space Complexity|Auxiliary Space)\s*:\s*([^\n]+)(.*?)(?=(?:KEY TAKEAWAYS|Key Insights|\Z))", combined_comp_clean, re.DOTALL | re.IGNORECASE)
    if sc_m:
        raw_sc = sc_m.group(1).strip().rstrip(".")
        sc_body = sc_m.group(2).strip()
        badge_m = re.search(r"O\([^)]+\)", raw_sc)
        if not badge_m and sc_body:
            badge_m = re.search(r"O\([^)]+\)", sc_body)
        if badge_m:
            data["space_complexity"] = badge_m.group(0)
            details = [l.strip().lstrip("-").lstrip("*").strip() for l in (raw_sc + "\n" + sc_body).splitlines() if l.strip().lstrip("-").lstrip("*").strip() and not l.strip().startswith("=")]
            data["space_complexity_details"] = details[:3]
        else:
            data["space_complexity"] = raw_sc[:20]
            data["space_complexity_details"] = [l.strip().lstrip("-").lstrip("*").strip() for l in sc_body.splitlines() if l.strip().lstrip("-").lstrip("*").strip()]

    # Key Insights / Key Takeaways
    ki_m = re.search(r"(?:KEY TAKEAWAYS|Key Insights|Takeaways)\s*:\s*(.*)", combined_comp_clean, re.DOTALL | re.IGNORECASE)
    if ki_m:
        ki_lines = [l.strip() for l in ki_m.group(1).splitlines() if l.strip() and not l.strip().startswith("=")]
        for kl in ki_lines:
            kl_clean = re.sub(r"^\d+\.\s*", "", kl).lstrip("-").lstrip("*").strip()
            if kl_clean:
                data["key_insights"].append(kl_clean)

    # Defaults if missing
    if not data["time_complexity_details"]:
        data["time_complexity_details"] = ["Optimal time complexity for this problem."]
    if not data["space_complexity_details"]:
        data["space_complexity_details"] = ["Optimal auxiliary space complexity."]
    if not data["key_insights"]:
        data["key_insights"] = [
            f"Optimized C++ implementation for {data['problem_name']}.",
            "Handles all boundary constraints and corner test cases without excess memory."
        ]

    return data

if __name__ == "__main__":
    import sys
    test_files = [
        r"6. Love babbar sheet\1. Arrays\1. Reverse an Array.cpp",
        r"6. Love babbar sheet\7. Greedy\5. Fractional Knapsack Problem.cpp",
        r"6. Love babbar sheet\6. Bit Manipulation\9. Calculate square of a number without using star slash and pow.cpp",
        r"00. gfg practice\7. stack\3. Medium\15. Max People Visible in a Line.cpp"
    ]
    for tf in test_files:
        if os.path.exists(tf):
            res = parse_cpp_file(tf)
            print(f"=== {os.path.basename(tf)} ===")
            print(f"  Title: {res['problem_num']}. {res['problem_name']} [{res['difficulty']}]")
            print(f"  Topics: {res['topics']}")
            print(f"  Statement: {len(res['statement'])} chars | Examples: {len(res['examples'])} | Constraints: {len(res['constraints'])}")
            print(f"  Differs: {bool(res['differs_from'])} | Approach: {res['approach_title'][:40]}")
            print(f"  Code: {len(res['code'])} chars")
            print(f"  TC: {res['time_complexity']} | SC: {res['space_complexity']}")
            print(f"  Insights: {len(res['key_insights'])}\n")
