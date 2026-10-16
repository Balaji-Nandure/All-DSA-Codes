#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest Repeated Subsequence (LRS)
 * 
 * Given a string str, find the length of the longest repeating subsequence such that 
 * the two subsequences do not use the same character at the same original index.
 * That is, the i-th character in the two subsequences cannot come from the same index in str.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "14. Longest Common Subsequence", we compared two different strings s1 and s2.
 * - Here, we compare the string WITH ITSELF (s1 = str, s2 = str).
 * - The critical difference is the index inequality condition: i != j!
 * - A character cannot be paired with itself; it must be matched with another identical 
 *   character at a different index in the string.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Modified LCS on Self with Index Constraint:
 *   Let dp[i][j] be the length of the longest repeated subsequence between str[0...i-1] and str[0...j-1].
 *   
 *   Transitions for 1 <= i, j <= n:
 *     If str[i-1] == str[j-1] AND i != j:
 *       dp[i][j] = 1 + dp[i-1][j-1]
 *     Else:
 *       dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *   
 *   Why this exact condition (i != j)?
 *     Without i != j, comparing a string with itself would trivially yield the entire string (LCS = N).
 *     Enforcing i != j forbids matching a character at position k with itself at position k, 
 *     forcing the match to be between TWO DISTINCT instances of the character in str.
 */

class Solution {
public:
    int LongestRepeatingSubsequence(string str) {
        int n = str.length();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Characters must match AND their original string indices must be distinct (i != j)
                if (str[i - 1] == str[j - 1] && i != j) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[n][n];
    }
};

int main() {
    Solution sol;
    string s1 = "axxzxy";
    cout << "LRS Length 1: " << sol.LongestRepeatingSubsequence(s1) << "\n";
    // Repeating subsequence: "xx" (length 2)

    string s2 = "aabebcdd";
    cout << "LRS Length 2: " << sol.LongestRepeatingSubsequence(s2) << "\n";
    // Repeating subsequence: "abd" (length 3)

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2) where N is the length of the string.
 * - Space Complexity: O(N^2) for the 2D DP table (can be optimized to O(N) using two rows).
 */
