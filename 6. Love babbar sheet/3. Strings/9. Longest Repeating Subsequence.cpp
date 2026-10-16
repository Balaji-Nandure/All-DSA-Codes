// Problem: Find Longest Repeating Subsequence in String
// Link (GFG): https://www.geeksforgeeks.org/problems/longest-repeating-subsequence2004/1
// Article: https://www.geeksforgeeks.org/dsa/longest-repeating-subsequence/
// Difficulty: Medium
// Topic: String, Dynamic Programming, LCS Variation

/*
Problem Statement:
Given a string str, find the length of the longest repeating subsequence such that 
the two subsequences don't have the same string character at the same index, 
i.e., any i-th character in the two subsequences shouldn't have the same index in the original string.

Example 1:
Input: str = "axxxy"
Output: 2
Explanation: The given array with indexes looks like:
a x x x y
0 1 2 3 4
The longest repeating subsequence is "xx", which appears twice at indices (1, 2) and (2, 3).
Notice that indices do not overlap: index 1 matches index 2, and index 2 matches index 3 (i != j).

Example 2:
Input: str = "aab"
Output: 1
Explanation: Subsequence "a" repeats at index 0 and 1.

Example 3:
Input: str = "AABEBCDD"
Output: 3
Explanation: The longest repeating subsequence is "ABD".

Constraints:
- 1 <= str.length() <= 1000
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In standard Longest Common Subsequence (LCS) between two different strings s1 and s2:
//   * Any matching characters `s1[i-1] == s2[j-1]` can be paired up because they belong to 
//     different strings.
// - In Longest Repeating Subsequence (LRS):
//   * We find the LCS of `str` WITH ITSELF (`str` vs `str`).
//   * BUT with one vital constraint: A character cannot be paired with ITSELF!
//   * That is, `str[i-1] == str[j-1]` is a valid match ONLY IF `i != j`!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Recursive Subsequence Generation
//   - Generate all subsequences and check for duplicates.
//   - Complexity: O(2^N) time. Intractable for N = 1000.
//
// Approach 2: Modified LCS Dynamic Programming (Optimal & Chosen)
//   - Let `dp[i][j]` be the length of the LRS in prefixes `str[0..i-1]` and `str[0..j-1]`.
//   - Recurrence:
//       * If `str[i - 1] == str[j - 1] && i != j`:
//           `dp[i][j] = 1 + dp[i - 1][j - 1]`
//       * Else:
//           `dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`
//   - Notice `dp[i][j]` only depends on previous row `dp[i-1]`.
//     Thus, we can optimize space to O(N) using two rows (rolling array).
//   - Complexity: O(N^2) time, O(N) auxiliary space.
//   - Why this approach: Exploits the exact structure of LCS with an index inequality guard.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int LongestRepeatingSubsequence(string str) {
        int n = str.length();

        // 1D Rolling array for space optimization: prev represents dp[i-1], curr represents dp[i]
        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // The single condition `i != j` is the ENTIRE difference between standard LCS and LRS!
                // It forbids a character at index i from pairing with itself, forcing it to find
                // another occurrence of the same character elsewhere in the string.
                if (str[i - 1] == str[j - 1] && i != j) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }

        return prev[n];
    }
};

int main() {
    Solution sol;
    string s1 = "axxxy";
    cout << "LRS of \"" << s1 << "\": " << sol.LongestRepeatingSubsequence(s1) << "\n";

    string s2 = "aab";
    cout << "LRS of \"" << s2 << "\": " << sol.LongestRepeatingSubsequence(s2) << "\n";

    string s3 = "AABEBCDD";
    cout << "LRS of \"" << s3 << "\": " << sol.LongestRepeatingSubsequence(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N^2), two nested loops of size N.
- Space Complexity: O(N) auxiliary space using two rolling rows of size N+1.

Key Takeaways:
- Longest Repeating Subsequence is an identical reduction to LCS(str, str) with the constraint `i != j`.
*/
