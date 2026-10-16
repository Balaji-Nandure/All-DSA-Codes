import os
import sys
import pymupdf
import re
from build_book import build_book

HANDBOOKS = [
    {
        "folder": "6. Love babbar sheet",
        "out": r"6. Love babbar sheet\Love_Babbar_450_DSA_Master_Book.pdf",
        "title": "Love Babbar 450 DSA Sheet Handbook",
        "subtitle": "Complete Solutions, Algorithmic Intuition, Step-by-Step Logic, and In-Depth Complexity Analysis",
        "brand": "LOVE BABBAR 450 DSA",
        "vol_title": "Volume 1: Love Babbar 450 DSA Sheet"
    },
    {
        "folder": "1. Recursion & backtracking",
        "out": r"1. Recursion & backtracking\Recursion_Backtracking_Handbook.pdf",
        "title": "Recursion & Backtracking Handbook",
        "subtitle": "Recursive Trees, State-Space Exploration, Subsets, Combinations, and Pruning Strategies",
        "brand": "RECURSION & BACKTRACKING",
        "vol_title": "Volume 2: Recursion & Backtracking"
    },
    {
        "folder": "2. dynamic programming",
        "out": r"2. dynamic programming\Dynamic_Programming_Handbook.pdf",
        "title": "Dynamic Programming Master Handbook",
        "subtitle": "Memoization, Tabulation, Space Optimization, MCM, DP on Trees, and Bitmask DP",
        "brand": "DYNAMIC PROGRAMMING",
        "vol_title": "Volume 3: Dynamic Programming"
    },
    {
        "folder": "3. Linked List",
        "out": r"3. Linked List\LinkedList_Handbook.pdf",
        "title": "Linked List Master Handbook",
        "subtitle": "Pointer Manipulation, Fast & Slow Pointers, Reversal, Cycle Detection, and In-Place Modifications",
        "brand": "LINKED LIST",
        "vol_title": "Volume 4: Linked List"
    },
    {
        "folder": "4. Tree",
        "out": r"4. Tree\Trees_Handbook.pdf",
        "title": "Trees & Binary Trees Handbook",
        "subtitle": "Traversals, Tree Construction, Views, Diameter, LCA, Path Sums, and Tree DP",
        "brand": "BINARY TREES",
        "vol_title": "Volume 5: Binary Trees"
    },
    {
        "folder": "5. Graph",
        "out": r"5. Graph\Graphs_Handbook.pdf",
        "title": "Graphs & Graph Algorithms Handbook",
        "subtitle": "BFS, DFS, Shortest Paths (Dijkstra/Floyd/Bellman), Topological Sort, DSU, and MST",
        "brand": "GRAPH ALGORITHMS",
        "vol_title": "Volume 6: Graph Algorithms"
    },
    {
        "folder": "0. GFG WEBSITE",
        "out": r"0. GFG WEBSITE\GFG_Website_Handbook.pdf",
        "title": "GeeksforGeeks Website Curated Handbook",
        "subtitle": "Selected Foundational Problems, Edge Cases, and Standard Interview Implementations",
        "brand": "GFG CURATED",
        "vol_title": "Volume 7: GFG Website Curated Problems"
    },
    {
        "folder": "00. gfg practice",
        "out": r"00. gfg practice\GFG_Practice_Master_Archive.pdf",
        "title": "GeeksforGeeks Practice Master Archive",
        "subtitle": "Extensive Problem Archive Across All Difficulty Levels: Basic, Easy, and Medium",
        "brand": "GFG PRACTICE ARCHIVE",
        "vol_title": "Volume 8: GFG Practice Archive"
    }
]

def build_all(skip_existing=True):
    print("=" * 60)
    print("DSA MASTER REPOSITORY BUILDER")
    print("=" * 60)

    # Step 1: Build each volume handbook
    for idx, cfg in enumerate(HANDBOOKS, 1):
        fld = cfg["folder"]
        out_pdf = cfg["out"]
        print(f"\n[{idx}/{len(HANDBOOKS)}] Processing '{fld}'...")

        if skip_existing and os.path.exists(out_pdf):
            sz = os.path.getsize(out_pdf) / (1024 * 1024)
            print(f"  -> Existing PDF found at '{out_pdf}' ({sz:.2f} MB). Skipping build.")
            continue

        success = build_book(
            base_dir=fld,
            output_pdf=out_pdf,
            book_title=cfg["title"],
            book_subtitle=cfg["subtitle"],
            brand_title=cfg["brand"]
        )
        if not success:
            print(f"  -> WARNING: Failed to build '{out_pdf}'")

    # Step 2: Merge all into one Master Encyclopedia PDF
    print("\n" + "=" * 60)
    print("MERGING ALL VOLUMES INTO MASTER ENCYCLOPEDIA")
    print("=" * 60)

    master_pdf = "DSA_Complete_Master_Encyclopedia.pdf"
    master_doc = pymupdf.open()
    master_toc = []
    current_page = 1

    for cfg in HANDBOOKS:
        out_pdf = cfg["out"]
        if not os.path.exists(out_pdf):
            print(f"Skipping missing volume: {out_pdf}")
            continue

        print(f"Merging '{cfg['vol_title']}' ({out_pdf})...")
        vol_doc = pymupdf.open(out_pdf)
        vol_page_count = len(vol_doc)

        # Add top-level volume entry in TOC
        master_toc.append([1, f"📚 {cfg['vol_title']}", current_page])

        # Get existing TOC of this volume and shift levels and page numbers
        vol_toc = vol_doc.get_toc()
        for item in vol_toc:
            lvl, title, pno = item[0], item[1], item[2]
            # Map Level 1 chapters in volume to Level 2 in master
            # Map Level 2 problems in volume to Level 3 in master
            new_lvl = lvl + 1
            new_pno = current_page + (pno - 1)
            # Skip duplicate cover/TOC entries inside volumes to keep sidebar sleek
            if title.lower() in ["cover page", "table of contents"] and lvl == 1:
                continue
            master_toc.append([new_lvl, title, new_pno])

        master_doc.insert_pdf(vol_doc)
        vol_doc.close()
        current_page += vol_page_count

    print(f"\nSetting Master TOC ({len(master_toc)} entries) across {len(master_doc)} total pages...")
    master_doc.set_toc(master_toc)
    master_doc.save(master_pdf)
    master_doc.close()

    total_mb = os.path.getsize(master_pdf) / (1024 * 1024)
    print(f"\n[SUCCESS] MASTER ENCYCLOPEDIA SUCCESSFULLY CREATED!")
    print(f"Output File: {os.path.abspath(master_pdf)}")
    print(f"Total Pages: {current_page - 1}")
    print(f"File Size: {total_mb:.2f} MB")
    print(f"Total Bookmarks in Outline: {len(master_toc)}")

    if "--keep-only-master" in sys.argv:
        print("\nCleaning up intermediate volume PDFs as requested...")
        for cfg in HANDBOOKS:
            out_pdf = cfg["out"]
            if os.path.exists(out_pdf):
                try:
                    os.remove(out_pdf)
                    print(f"  Deleted intermediate volume: {out_pdf}")
                except Exception as e:
                    print(f"  Could not delete {out_pdf}: {e}")

if __name__ == "__main__":
    skip = "--force" not in sys.argv
    build_all(skip_existing=skip)
