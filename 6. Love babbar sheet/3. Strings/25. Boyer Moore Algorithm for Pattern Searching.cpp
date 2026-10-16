// Problem: Boyer Moore Algorithm for Pattern Searching (Bad Character Heuristic)
// Link (GFG): https://www.geeksforgeeks.org/problems/pattern-searching5231/1
// Article: https://www.geeksforgeeks.org/dsa/boyer-moore-algorithm-for-pattern-searching/
// Difficulty: Hard
// Topic: String, Pattern Searching, Boyer-Moore, Sub-linear Best Case

/*
Problem Statement:
Given a text string `txt` and a pattern string `pat`, find all starting positions 
where `pat` occurs in `txt` using the Boyer-Moore Algorithm (specifically the Bad Character Heuristic).

Unlike Naive and KMP which match from left-to-right, Boyer-Moore matches characters 
from RIGHT TO LEFT within the candidate window, allowing large multi-character shifts 
when a mismatch is encountered!

Example 1:
Input: txt = "ABAAABCD", pat = "ABC"
Output: [4] (0-based: index 4)

Example 2:
Input: txt = "THIS IS A TEST TEXT", pat = "TEST"
Output: [10]

Constraints:
- 1 <= pat.length() <= txt.length() <= 10^5
- Strings consist of standard ASCII characters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In KMP (Problem 19):
//   * Characters are matched from LEFT TO RIGHT (`j = 0` to `m - 1`).
//   * Shifts are governed by the Longest Prefix Suffix (LPS) table.
// - In Boyer-Moore:
//   * Characters are matched from RIGHT TO LEFT (`j = m - 1` down to 0).
//   * When a mismatch occurs on character `c` in text:
//     If `c` does not appear anywhere in `pat`, the ENTIRE pattern can be shifted 
//     past `c` in a single jump of length M!
//   * This enables SUB-LINEAR average-case performance: O(N / M)!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Bad Character Heuristic Table:
//   - Array `badChar[256]` initialized to -1.
//   - Record the RIGHTMOST occurrence of each character in pattern:
//       `badChar[(unsigned char)pat[i]] = i;`
//   - Search Loop:
//       - Maintain window shift `s = 0`.
//       - While `s <= n - m`:
//           - Scan backwards `j = m - 1` down to 0.
//           - If all characters match (`j < 0`):
//               * Record occurrence `s`.
//               * Shift pattern forward to align with next potential match:
//                 `s += (s + m < n) ? m - badChar[txt[s + m]] : 1`.
//           - If a mismatch occurs at index `j` with text character `txt[s + j]`:
//               * Shift amount = `max(1, j - badChar[txt[s + j]])`.
//               * Advance `s += shift`.
//   - Complexity: Best/Average O(N / M), Worst case O(N * M), Space O(256) = O(1).

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Preprocesses the pattern to calculate the bad character array
    void badCharHeuristic(const string& pat, int m, vector<int>& badChar) {
        fill(badChar.begin(), badChar.end(), -1);

        // Record rightmost index of every character in pat
        for (int i = 0; i < m; ++i) {
            badChar[(unsigned char)pat[i]] = i;
        }
    }

public:
    vector<int> search(string pat, string txt) {
        vector<int> occurrences;
        int m = pat.length();
        int n = txt.length();

        if (m == 0 || n < m) return occurrences;

        // 256 entries for all ASCII characters
        vector<int> badChar(256, -1);
        badCharHeuristic(pat, m, badChar);

        int s = 0; // Shift of pattern relative to text

        while (s <= (n - m)) {
            int j = m - 1;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Match backwards from the right end of the pattern towards the left
            while (j >= 0 && pat[j] == txt[s + j]) {
                j--;
            }

            // If pattern was fully matched (j < 0)
            if (j < 0) {
                occurrences.push_back(s);

                // Shift pattern so that the next character in text aligns with its last occurrence in pat
                s += (s + m < n) ? m - badChar[(unsigned char)txt[s + m]] : 1;
            } 
            else {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Bad Character Rule: Align mismatched text character txt[s + j] with its rightmost
                // appearance in the pattern. Using max(1, ...) ensures the pattern always shifts forward.
                s += max(1, j - badChar[(unsigned char)txt[s + j]]);
            }
        }

        return occurrences;
    }
};

int main() {
    Solution sol;
    string txt = "ABAAABCD";
    string pat = "ABC";

    vector<int> matches = sol.search(pat, txt);
    cout << "Occurrences of \"" << pat << "\" in \"" << txt << "\":\n";
    for (int idx : matches) cout << idx << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity:
  * Best Case: O(N / M). When all text characters are bad characters, each jump shifts by M.
  * Average Case: O(N) linear time on natural language texts.
  * Worst Case: O(N * M) (e.g., txt = "AAAAAAA", pat = "BAAA").
- Space Complexity: O(256) = O(1) auxiliary space for the bad character table.

Key Takeaways:
- Right-to-left matching provides maximum skip potential when an alien character is found.
- Industry-standard pattern matcher in text editors (GNU grep, Vim).
*/
