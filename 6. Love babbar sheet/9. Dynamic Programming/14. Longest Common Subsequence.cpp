#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest Common Subsequence (LCS)
 * 
 * Given two strings text1 and text2, return the length of their Longest Common Subsequence.
 * A subsequence is derived by deleting zero or more characters from a string 
 * without altering the relative order of the remaining characters.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "Edit Distance" where mismatches allowed Replace (diagonal) and Insert/Delete,
 *   here matching characters provide +1 diagonally, while mismatches force a choice 
 *   between dropping from text1 (dp[i-1][j]) or dropping from text2 (dp[i][j-1]).
 * - Subsequences do NOT need to be contiguous (unlike Substring).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 2D Dynamic Programming (with Subsequence Reconstruction):
 *   Let dp[i][j] be the length of LCS between text1[0 ... i-1] and text2[0 ... j-1].
 *   
 *   Base Case:
 *     dp[i][0] = 0 and dp[0][j] = 0 (LCS with an empty string is always 0).
 *   
 *   Transitions for 1 <= i <= m and 1 <= j <= n:
 *     If text1[i-1] == text2[j-1]:
 *       dp[i][j] = 1 + dp[i-1][j-1]
 *     Else:
 *       dp[i][j] = max(dp[i-1][j], dp[i][j-1])
 *   
 *   Backtracking the LCS string:
 *     Starting from dp[m][n], follow the decisions back to (0, 0) to reconstruct 
 *     the actual common subsequence string.
 */

class Solution {
public:
    int lcs(int x, int y, string s1, string s2) {
        vector<vector<int>> dp(x + 1, vector<int>(y + 1, 0));

        for (int i = 1; i <= x; i++) {
            for (int j = 1; j <= y; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Character match: Extend LCS length from diagonal subproblem
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    // *** CRUCIAL LINE: Character mismatch: Take best of dropping char from s1 or s2 ***
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[x][y];
    }

    // Helper to reconstruct and print the actual LCS string
    string getLCSString(string s1, string s2) {
        int x = s1.length();
        int y = s2.length();
        vector<vector<int>> dp(x + 1, vector<int>(y + 1, 0));

        for (int i = 1; i <= x; i++) {
            for (int j = 1; j <= y; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        string lcs_str = "";
        int i = x, j = y;
        while (i > 0 && j > 0) {
            if (s1[i - 1] == s2[j - 1]) {
                lcs_str.push_back(s1[i - 1]);
                i--;
                j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        reverse(lcs_str.begin(), lcs_str.end());
        return lcs_str;
    }
};

int main() {
    Solution sol;
    string s1 = "ABCDGH", s2 = "AEDFHR";
    cout << "LCS Length: " << sol.lcs(s1.length(), s2.length(), s1, s2) << "\n"; // Expected: 3 ("ADH")
    cout << "LCS String: " << sol.getLCSString(s1, s2) << "\n";

    string s3 = "ABC", s4 = "AC";
    cout << "LCS Length: " << sol.lcs(s3.length(), s4.length(), s3, s4) << "\n"; // Expected: 2 ("AC")

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(M * N) to populate the M x N grid.
 * - Space Complexity: O(M * N) for the full 2D table (can be optimized to O(min(M, N)) as in problem 17).
 */
