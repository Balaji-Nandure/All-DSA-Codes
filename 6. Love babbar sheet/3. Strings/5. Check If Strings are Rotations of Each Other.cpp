// Problem: Check If Strings are Rotations of Each Other
// Link (GFG): https://www.geeksforgeeks.org/problems/check-if-strings-are-rotations-of-each-other-or-not-1587115620/1
// Article: https://www.geeksforgeeks.org/dsa/a-program-to-check-if-strings-are-rotations-of-each-other/
// Difficulty: Basic / Easy
// Topic: String, Pattern Matching, KMP

/*
Problem Statement:
You are given two strings s1 and s2 of equal or unequal length.
Check if s2 is a rotation of s1.
A string s2 is said to be a rotation of s1 if it can be obtained by shifting 
characters of s1 cyclically.

Example 1:
Input: s1 = "geeksforgeeks", s2 = "forgeeksgeeks"
Output: true
Explanation: s1 is rotated cyclically by 5 characters to produce s2.

Example 2:
Input: s1 = "mightandmagic", s2 = "andmagicmigth"
Output: false
Explanation: "andmagicmigth" has 't' and 'h' swapped at the end, not a valid rotation.

Example 3:
Input: s1 = "abc", s2 = "abcd"
Output: false (lengths differ)

Constraints:
- 1 <= s1.length(), s2.length() <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 7 (Cyclically Rotate an Array by One):
//   * We actively generated the rotation by shifting elements or 3-step reversal.
// - In Strings Problem 5 (Check if Rotations):
//   * We do NOT need to generate all N possible rotations one by one (which would be O(N^2)).
//   * The elegant mathematical property:
//     If `s1 = X + Y`, then any rotation is `Y + X`.
//     Notice what happens when we concatenate `s1` with itself:
//     `s1 + s1 = (X + Y) + (X + Y) = X + (Y + X) + Y`.
//     The rotated string `Y + X` is GUARANTEED to appear as a contiguous substring 
//     inside `s1 + s1`!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Generate All N Rotations
//   - Rotate s1 one character at a time, compare with s2.
//   - Complexity: N rotations * O(N) string equality = O(N^2) time.
//   - Why Suboptimal: Far too slow for N = 10^5.
//
// Approach 2: Concatenation + Substring Search (Optimal & Chosen)
//   - Step 1: Check length guard: `if (s1.length() != s2.length()) return false;`
//   - Step 2: Form `string doubled = s1 + s1;`
//   - Step 3: Search if `s2` exists as a substring in `doubled`:
//     * In standard C++, `doubled.find(s2) != string::npos`.
//     * Using KMP (Knuth-Morris-Pratt), substring search runs in strict linear O(N) time!
//   - Complexity: O(N) time, O(N) space.
//   - Why this approach: Transforms cyclic rotational checking into a single linear pattern match.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    // Standard KMP LPS (Longest Proper Prefix which is also Suffix) builder
    vector<int> buildLPS(const string& pat) {
        int m = pat.length();
        vector<int> lps(m, 0);
        int len = 0;
        int i = 1;

        while (i < m) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
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

    // KMP Substring Search in O(text.length() + pat.length())
    bool kmpSearch(const string& text, const string& pat) {
        int n = text.length();
        int m = pat.length();
        if (m == 0) return true;
        if (n < m) return false;

        vector<int> lps = buildLPS(pat);
        int i = 0, j = 0;

        while (i < n) {
            if (text[i] == pat[j]) {
                i++;
                j++;
            }
            if (j == m) {
                return true; // Match found!
            } else if (i < n && text[i] != pat[j]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return false;
    }

public:
    bool areRotations(const string& s1, const string& s2) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Guard 1: Rotations MUST have identical lengths.
        if (s1.length() != s2.length()) {
            return false;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Guard 2: Any rotation of s1 is mathematically guaranteed to be a contiguous substring of (s1 + s1).
        string doubled = s1 + s1;

        // Perform linear KMP search (or doubled.find(s2) != string::npos)
        return kmpSearch(doubled, s2);
    }
};

int main() {
    Solution sol;
    string s1 = "geeksforgeeks";
    string s2 = "forgeeksgeeks";

    cout << "Are \"" << s1 << "\" and \"" << s2 << "\" rotations? " 
         << (sol.areRotations(s1, s2) ? "Yes" : "No") << "\n";

    string s3 = "mightandmagic";
    string s4 = "andmagicmigth";
    cout << "Are \"" << s3 << "\" and \"" << s4 << "\" rotations? " 
         << (sol.areRotations(s3, s4) ? "Yes" : "No") << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) where N = length of s1.
  * Concatenation: O(N).
  * KMP preprocessing (LPS table): O(N).
  * KMP pattern search over length 2N: O(2N) = O(N).
- Space Complexity: O(N) for `s1 + s1` and LPS table.

Key Takeaways:
- Concatenating a string with itself `(s + s)` is the canonical idiom for linearizing 
  circular/rotational string problems.
*/
