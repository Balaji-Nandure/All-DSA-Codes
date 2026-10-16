#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Optimal Strategy for a Game (Coin Game Minimax)
 * 
 * Given an array of N coins of positive values arranged in a line.
 * In each turn, a player can pick either the FIRST coin or the LAST coin from the remaining row.
 * Player 1 moves first. Assuming both players play optimally, find the maximum possible 
 * amount of money Player 1 is guaranteed to win.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike "46. Coin game winner" which evaluated a single coin pile with fixed pick sizes {1, X, Y},
 *   here each coin has a distinct value, and picks must come from the OUTER BOUNDARIES [i, j].
 * - This is an Interval Minimax DP problem: Player 1 maximizes while anticipating that the 
 *   opponent will minimize Player 1's future gains.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Interval Minimax Dynamic Programming:
 *   Let dp[i][j] be the maximum money Player 1 can win from the coin interval arr[i ... j].
 *   
 *   Player 1 has two possible moves:
 *   
 *   Option 1: Pick the front coin arr[i]:
 *     The opponent now faces interval [i + 1 ... j].
 *     The opponent will play optimally to minimize Player 1's subsequent return:
 *     - If opponent picks front arr[i + 1], Player 1 gets dp[i + 2][j].
 *     - If opponent picks back arr[j], Player 1 gets dp[i + 1][j - 1].
 *     Guaranteed value from Option 1:
 *       arr[i] + min(dp[i + 2][j], dp[i + 1][j - 1])
 *   
 *   Option 2: Pick the back coin arr[j]:
 *     The opponent now faces interval [i ... j - 1].
 *     - If opponent picks front arr[i], Player 1 gets dp[i + 1][j - 1].
 *     - If opponent picks back arr[j - 1], Player 1 gets dp[i][j - 2].
 *     Guaranteed value from Option 2:
 *       arr[j] + min(dp[i + 1][j - 1], dp[i][j - 2])
 *   
 *   Recurrence:
 *     dp[i][j] = max(Option 1, Option 2)
 *   
 *   Base Cases:
 *     dp[i][i]     = arr[i]
 *     dp[i][i + 1] = max(arr[i], arr[i + 1])
 */

class Solution {
public:
    long long maximumAmount(int n, int arr[]) {
        vector<vector<long long>> dp(n, vector<long long>(n, 0));

        // Subarray lengths from 1 to n
        for (int L = 1; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;

                if (L == 1) {
                    dp[i][j] = arr[i];
                } else if (L == 2) {
                    dp[i][j] = max(arr[i], arr[j]);
                } else {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // If we pick arr[i], opponent leaves us min(dp[i+2][j], dp[i+1][j-1])
                    long long pick_front = arr[i] + min(dp[i + 2][j], dp[i + 1][j - 1]);

                    // If we pick arr[j], opponent leaves us min(dp[i+1][j-1], dp[i][j-2])
                    long long pick_back  = arr[j] + min(dp[i + 1][j - 1], dp[i][j - 2]);

                    // We maximize our return over both options
                    dp[i][j] = max(pick_front, pick_back);
                }
            }
        }

        return dp[0][n - 1];
    }
};

int main() {
    Solution sol;
    int arr1[] = {5, 3, 7, 10};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    cout << "Max Guaranteed Amount 1: " << sol.maximumAmount(n1, arr1) << "\n";
    // P1 picks 10 -> leaves {5, 3, 7}. P2 picks 7 -> leaves {5, 3}. P1 picks 5. Total = 10 + 5 = 15. Expected: 15.

    int arr2[] = {8, 15, 3, 7};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    cout << "Max Guaranteed Amount 2: " << sol.maximumAmount(n2, arr2) << "\n";
    // Expected: 22 (P1 picks 7 -> P2 picks 8 -> P1 picks 15 = 22).

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^2) filling an upper-triangular N x N matrix with O(1) transitions.
 * - Space Complexity: O(N^2) for the 2D DP matrix.
 */
