// Problem: Find the Longest Common Subsequence (LCS) Between Two Strings
// Link (GFG): https://www.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/1
// Article: https://www.geeksforgeeks.org/dsa/longest-common-subsequence-dp-4/
// Difficulty: Medium / Hard
// Topic: String, Dynamic Programming, Subsequence

/*
Problem Statement:
Given two strings s1 and s2, return the length of their longest common subsequence (LCS).
A subsequence of a string is a new string generated from the original string with some 
characters (can be none) deleted without changing the relative order of the remaining characters.
If there is no common subsequence, return 0.

Example 1:
Input: s1 = "ABCDGH", s2 = "AEDFHR"
Output: 3
Explanation: The longest common subsequence is "ADH" of length 3.

Example 2:
Input: s1 = "ABC", s2 = "AC"
Output: 2
Explanation: The longest common subsequence is "AC" of length 2.

Example 3:
Input: s1 = "XYZ", s2 = "ABC"
Output: 0

Constraints:
- 1 <= s1.length(), s2.length() <= 1000
- Strings consist of uppercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 9 (Longest Repeating Subsequence):
//   * We found LCS of a string with ITSELF while prohibiting identical indices (`i != j`).
// - In Problem 14 (Edit Distance):
//   * Non-matches incurred a penalty cost for deletion/insertion/replacement.
// - In Problem 31 (Standard LCS):
//   * This is the fundamental DP cornerstone: We find the maximal shared sequence between 
//     TWO DIFFERENT strings with zero edit cost penalties, branching on character equivalence.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Plain Recursion
//   - Branch on `s1[i] == s2[j]` or explore both branches.
//   - Complexity: O(2^(N+M)) exponential. TLE for N, M = 1000.
//
// Approach 2: 2D Dynamic Programming with 1D Space Optimization (Optimal & Chosen)
//   - Let `dp[i][j]` be the length of LCS of prefixes `s1[0..i-1]` and `s2[0..j-1]`.
//   - Recurrence:
//       * If `s1[i - 1] == s2[j - 1]`:
//           `dp[i][j] = 1 + dp[i - 1][j - 1]`
//       * Else:
//           `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`
//   - Since `dp[i][j]` only depends on row `i - 1` and row `i`, we can optimize 
//     space from O(N * M) to O(M) using two rolling vectors `prev` and `curr`!
//   - Complexity: O(N * M) time, O(M) auxiliary space.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Optimal Space O(M) LCS length computation
    int lcs(string s1, string s2) {
        int n = s1.length();
        int m = s2.length();

        // prev represents dp[i-1], curr represents dp[i]
        vector<int> prev(m + 1, 0);
        vector<int> curr(m + 1, 0);

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // If characters match, extend common subsequence from diagonal previous state dp[i-1][j-1].
                // Otherwise, take the maximum achieved by excluding either s1[i-1] or s2[j-1].
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }

        return prev[m];
    }

    // Reconstruct the actual LCS string (for full interview answers)
    string printLCS(const string& s1, const string& s2) {
        int n = s1.length();
        int m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Backtrack through DP table to retrieve characters
        string result = "";
        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                result += s1[i - 1];
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution sol;
    string s1 = "ABCDGH";
    string s2 = "AEDFHR";

    cout << "Length of LCS (\"" << s1 << "\", \"" << s2 << "\"): " 
         << sol.lcs(s1, s2) << "\n";
    cout << "Actual LCS string: \"" << sol.printLCS(s1, s2) << "\"\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * M) where N = s1.length(), M = s2.length().
- Space Complexity: O(M) auxiliary space for the rolling vector approach (or O(N * M) if reconstructing string).

Key Takeaways:
- LCS is the foundation for diff tools, version control merges, and bioinformatics sequence alignments.
*/
