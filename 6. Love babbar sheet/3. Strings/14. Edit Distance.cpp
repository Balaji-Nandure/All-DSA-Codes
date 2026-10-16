// Problem: Edit Distance (Levenshtein Distance) [Very Imp]
// Link (GFG): https://www.geeksforgeeks.org/problems/edit-distance3702/1
// Article: https://www.geeksforgeeks.org/dsa/edit-distance-dp-5/
// Difficulty: Hard
// Topic: String, Dynamic Programming, Classical Levenshtein Metric

/*
Problem Statement:
Given two strings s and t. Find the minimum number of operations required to convert string s to string t.
The permitted operations are:
  1. Insert a character
  2. Remove / Delete a character
  3. Replace / Substitute a character

Example 1:
Input: s = "geek", t = "gesek"
Output: 1
Explanation: Insert 's' between the two 'e's in "geek" to make "gesek".

Example 2:
Input: s = "gfg", t = "gfg"
Output: 0
Explanation: Both strings are identical.

Example 3:
Input: s = "horse", t = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Constraints:
- 1 <= s.length(), t.length() <= 1000
- Strings consist of lowercase English alphabets.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Longest Common Subsequence (LCS, Problem 31):
//   * Only DELETIONS were modeled (matching characters were kept, non-matching were skipped).
// - In Edit Distance:
//   * THREE distinct edit operations are simultaneously possible:
//     1. INSERTION: matches `t[j-1]`, so we advance index in `t` while staying at current `s`.
//     2. DELETION: removes `s[i-1]`, so we advance index in `s` while staying at current `t`.
//     3. REPLACEMENT: transforms `s[i-1]` into `t[j-1]`, advancing BOTH indices simultaneously!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Dynamic Programming (Levenshtein Distance):
//   - Let `dp[i][j]` = min operations to convert prefix `s[0..i-1]` to prefix `t[0..j-1]`.
//   - Base Cases:
//       * `dp[i][0] = i`: Converting length `i` string to empty string requires `i` deletions.
//       * `dp[0][j] = j`: Converting empty string to length `j` string requires `j` insertions.
//   - Recurrence:
//       * If `s[i - 1] == t[j - 1]`:
//           `dp[i][j] = dp[i - 1][j - 1]` (no new operation needed!)
//       * If `s[i - 1] != t[j - 1]`:
//           `dp[i][j] = 1 + min({`
//               `dp[i][j - 1],`     // INSERT (cost of matching t[j-1])
//               `dp[i - 1][j],`     // DELETE (cost of removing s[i-1])
//               `dp[i - 1][j - 1]`  // REPLACE (cost of substituting s[i-1] with t[j-1])
//           `})`
//   - Space Optimization:
//       `dp[i][j]` only relies on the previous row (`i-1`) and current row (`i`).
//       We can optimize space from O(N * M) down to O(M) using two rolling vectors!
//   - Complexity: O(N * M) time, O(M) space.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int editDistance(string s, string t) {
        int n = s.length();
        int m = t.length();

        // prev represents dp[i-1], curr represents dp[i]
        vector<int> prev(m + 1, 0);
        vector<int> curr(m + 1, 0);

        // Base case: Converting empty s to prefix of t of length j takes j insertions
        for (int j = 0; j <= m; ++j) {
            prev[j] = j;
        }

        for (int i = 1; i <= n; ++i) {
            // Base case: Converting prefix of s of length i to empty t takes i deletions
            curr[0] = i;

            for (int j = 1; j <= m; ++j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // If characters match, no operation cost is incurred; copy diagonally.
                if (s[i - 1] == t[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // If characters mismatch, pick the minimum among:
                    // 1. curr[j - 1]     -> INSERTION
                    // 2. prev[j]         -> DELETION
                    // 3. prev[j - 1]     -> REPLACEMENT
                    curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
                }
            }

            prev = curr;
        }

        return prev[m];
    }
};

int main() {
    Solution sol;
    string s1 = "geek", t1 = "gesek";
    cout << "Edit Distance (\"" << s1 << "\", \"" << t1 << "\"): " 
         << sol.editDistance(s1, t1) << "\n";

    string s2 = "horse", t2 = "ros";
    cout << "Edit Distance (\"" << s2 << "\", \"" << t2 << "\"): " 
         << sol.editDistance(s2, t2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * M), nested iterations over string lengths N and M.
- Space Complexity: O(M) auxiliary space using 1D rolling array optimization.

Key Takeaways:
- Edit Distance forms the algorithmic core of spell checkers, DNA sequence alignment (Needleman-Wunsch),
  and Git diff engines.
*/
