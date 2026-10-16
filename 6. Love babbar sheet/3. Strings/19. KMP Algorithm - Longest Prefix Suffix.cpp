// Problem: KMP Algorithm (Longest Prefix Suffix - LPS Array & Full Pattern Matching)
// Link (GFG): https://www.geeksforgeeks.org/problems/longest-prefix-suffix2527/1
// Article: https://www.geeksforgeeks.org/dsa/longest-prefix-also-suffix/
// Difficulty: Hard
// Topic: String, Knuth-Morris-Pratt (KMP), LPS Table, Deterministic Linear Search

/*
Problem Statement:
Part 1 (GFG Problem):
Given a string `s`, find the length of the longest proper prefix which is also 
a proper suffix. (A proper prefix/suffix cannot be the entire string itself).

Part 2 (Comprehensive KMP Application):
Using the precomputed LPS table, implement the Knuth-Morris-Pratt (KMP) algorithm 
to find all occurrences of pattern `pat` in text `txt` in guaranteed linear O(N + M) time 
without ever backtracking the text pointer.

Example 1:
Input: s = "abab"
Output: 2
Explanation: "ab" is the longest proper prefix that is also a proper suffix.

Example 2:
Input: s = "aaaa"
Output: 3
Explanation: "aaa" is the longest proper prefix and suffix.

Example 3:
Input: s = "abcab"
Output: 2 ("ab")

Constraints:
- 1 <= s.length() <= 10^5
- s consists of lowercase English alphabets.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Naive Pattern Matching:
//   * A mismatch at pattern position `j` causes the text pointer to backtrack `i = i - j + 1`, 
//     resulting in catastrophic O(N * M) performance on repetitive texts like "AAAAAAAB".
// - In Rabin-Karp (Problem 18):
//   * Uses hashing to achieve O(N + M) average time, but worst case is still O(N * M) 
//     if hash collisions occur frequently.
// - In KMP (Knuth-Morris-Pratt):
//   * GUARANTEED deterministic O(N + M) worst-case time!
//   * The text pointer `i` NEVER BACKTRACKS (moves strictly forward 0 to N-1).
//   * When a mismatch occurs at `pat[j]`, the LPS table tells us the exact longest prefix 
//     already matched that can serve as a prefix for the next attempt: `j = lps[j - 1]`.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// LPS Array Construction:
//   - Let `lps[i]` be the length of the longest proper prefix of `s[0..i]` that is also a suffix of `s[0..i]`.
//   - Pointer `len = 0`, index `i = 1`.
//   - Loop while `i < n`:
//       * If `s[i] == s[len]`: Match extended! `len++`, `lps[i] = len`, `i++`.
//       * If `s[i] != s[len]`:
//           - If `len != 0`: Fall back to previous longest matched prefix: `len = lps[len - 1]` 
//             (DO NOT increment `i`!).
//           - Else: No prefix matched, `lps[i] = 0`, `i++`.
//   - Output for GFG: `lps[n - 1]`.
//   - Time Complexity: O(N) to build LPS, O(M) for pattern match.
//   - Space Complexity: O(M) auxiliary space for LPS array.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Part 1: Construct LPS Array and Return Length of Longest Prefix Suffix
    // -------------------------------------------------------------------------
    vector<int> computeLPSArray(const string& s) {
        int n = s.length();
        vector<int> lps(n, 0);

        int len = 0; // Length of the previous longest prefix suffix
        int i = 1;

        while (i < n) {
            // Case 1: Match found, extend the prefix-suffix length
            if (s[i] == s[len]) {
                len++;
                lps[i] = len;
                i++;
            } 
            // Case 2: Mismatch
            else {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Instead of resetting `len = 0`, we fall back to the sub-prefix: `len = lps[len - 1]`.
                // Crucially, `i` is NOT incremented, so the current character gets another chance to match!
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

    int lps(string s) {
        if (s.empty()) return 0;
        vector<int> lpsArr = computeLPSArray(s);
        return lpsArr[s.length() - 1];
    }

    // -------------------------------------------------------------------------
    // Part 2: Complete KMP Pattern Search using the computed LPS array
    // -------------------------------------------------------------------------
    vector<int> kmpSearch(const string& txt, const string& pat) {
        vector<int> occurrences;
        int n = txt.length();
        int m = pat.length();
        if (m == 0 || n < m) return occurrences;

        vector<int> lpsArr = computeLPSArray(pat);

        int i = 0; // Index for txt (NEVER backtracks!)
        int j = 0; // Index for pat

        while (i < n) {
            if (txt[i] == pat[j]) {
                i++;
                j++;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Full pattern matched: Record start index, and shift j to lps[j - 1] to find overlapping matches!
            if (j == m) {
                occurrences.push_back(i - j); // 0-based match index
                j = lpsArr[j - 1];
            } 
            // Mismatch after j matches
            else if (i < n && txt[i] != pat[j]) {
                if (j != 0) {
                    j = lpsArr[j - 1]; // Fallback in pattern without retreating i
                } else {
                    i++;
                }
            }
        }

        return occurrences;
    }
};

int main() {
    Solution sol;
    string s = "abab";
    cout << "Longest Prefix Suffix of \"" << s << "\": " << sol.lps(s) << "\n";

    string txt = "ABABDABACDABABCABAB";
    string pat = "ABABCABAB";
    vector<int> matches = sol.kmpSearch(txt, pat);
    cout << "KMP search for \"" << pat << "\" in \"" << txt << "\":\nFound at 0-based index: ";
    for (int idx : matches) cout << idx << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity:
  * LPS Construction: O(M) where M is length of pattern.
  * KMP Pattern Search: O(N) where N is length of text.
  * Total Time: O(N + M) guaranteed worst-case without backtracking.
- Space Complexity: O(M) auxiliary space for the LPS array.

Key Takeaways:
- KMP's mathematical beauty lies in never incrementing or retreating the text pointer `i`.
  All state transitions are handled purely within the pattern's LPS lookup.
*/
