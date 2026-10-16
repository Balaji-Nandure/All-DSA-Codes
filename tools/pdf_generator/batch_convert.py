import os
import sys
import glob
from generate_pdf import convert_to_pdf

def batch_convert_folder(folder_path):
    cpp_files = sorted(glob.glob(os.path.join(folder_path, "*.cpp")))
    print(f"Found {len(cpp_files)} C++ files in '{folder_path}'")
    success_count = 0
    for f in cpp_files:
        print(f"\n--- Processing: {os.path.basename(f)} ---")
        if convert_to_pdf(f):
            success_count += 1
    print(f"\nCompleted! Successfully converted {success_count}/{len(cpp_files)} files to PDF.")

if __name__ == "__main__":
    folder = sys.argv[1] if len(sys.argv) > 1 else r"c:\Users\balaj\Desktop\Barana\All-DSA-Codes\6. Love babbar sheet\1. Arrays"
    batch_convert_folder(folder)
