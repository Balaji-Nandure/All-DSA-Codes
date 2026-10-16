#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Space Optimized Solution of LCS
 * 
 * Given two strings s1 and s2, compute the length of their Longest Common Subsequence
 * using strictly O(min(M, N)) auxiliary space.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "14. Longest Common Subsequence", we used an M x N 2D grid which consumes O(M * N) memory.
 * - When strings have length 10^5, an M x N grid requires 40 GB of RAM, causing Memory Limit Exceeded (MLE).
 * - Here, we observe that the recurrence only accesses the IMMEDIATELY PRECEDING ROW and current row.
 * - By maintaining only two rolling rows (or a single 1D array with a diagonal tracker), 
 *   we reduce memory to strictly O(min(M, N)) bytes (under 1 MB).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Parity / 1D Rolling State Optimization:
 *   1. Orientation:
 *      If s1.length() < s2.length(), swap s1 and s2 so that the inner loop operates on the shorter string.
 *      Now space is strictly bounded by O(min(M, N)).
 *   
 *   2. Method A: Two Rolling Rows (prev and curr):
 *      - curr[j] = 1 + prev[j - 1] (if match)
 *      - curr[j] = max(prev[j], curr[j - 1]) (if mismatch)
 *      - At the end of each row, prev = curr.
 *   
 *   3. Method B: Single 1D Array with `prev_diag`:
 *      - Maintain single vector<int> dp(N + 1, 0).
 *      - Before updating dp[j], save its current value (which represents dp[i-1][j] for current step,
 *        and will become dp[i-1][j-1] for the next step j+1).
 *      - dp[j] = 1 + prev_diag (if match), else max(dp[j], dp[j - 1]).
 */

class Solution {
public:
    // Single 1D Array Optimization in O(min(M, N)) Space
    int lcsSpaceOptimized(string s1, string s2) {
        // Ensure s2 is the shorter string to minimize memory
        if (s1.length() < s2.length()) {
            swap(s1, s2);
        }

        int m = s1.length();
        int n = s2.length();

        // 1D DP table of size min(m, n) + 1
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= m; i++) {
            int prev_diag = 0; // Represents dp[i-1][j-1]

            for (int j = 1; j <= n; j++) {
                int temp = dp[j]; // Store dp[i-1][j] before it gets overwritten

                if (s1[i - 1] == s2[j - 1]) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Character match: use cached diagonal value dp[i-1][j-1]
                    dp[j] = 1 + prev_diag;
                } else {
                    // *** CRUCIAL LINE: Character mismatch: max(up: dp[j], left: dp[j - 1]) ***
                    dp[j] = max(dp[j], dp[j - 1]);
                }

                prev_diag = temp; // Advance diagonal pointer for next column
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";

    cout << "LCS Length (Space Optimized): " << sol.lcsSpaceOptimized(s1, s2) << "\n";
    // Expected: 4 ("GTAB")

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(M * N) same as 2D LCS.
 * - Space Complexity: O(min(M, N)) strictly optimal single array storage.
 */
