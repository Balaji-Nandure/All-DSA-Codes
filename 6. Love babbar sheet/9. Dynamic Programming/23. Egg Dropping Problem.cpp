#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Egg Dropping Problem (Super Egg Drop)
 * 
 * Given N eggs and a building with K floors.
 * Determine the minimum number of egg drops required in the WORST CASE 
 * to find the critical threshold floor above which eggs break.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is a MINIMAX optimization problem: we minimize the maximum (worst-case) drops.
 * - Standard DP takes O(N * K^2), which TLEs for large K (e.g. K = 10,000).
 * - By mathematically INVERTING the question ("Given m moves and n eggs, what is the MAX floors 
 *   we can check?"), the complexity drops from quadratic to O(N * log K) / O(N * moves)!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1: Mathematical Inversion (Max Floors Checkable with m Moves):
 *   Let dp[e] be the maximum number of floors we can test using e eggs with the current move count m.
 *   
 *   If we drop an egg from floor X:
 *   - If it breaks: we have (e - 1) eggs and (m - 1) moves left to test floors BELOW -> dp[e - 1] floors.
 *   - If it survives: we have e eggs and (m - 1) moves left to test floors ABOVE -> dp[e] floors.
 *   - Together with the test floor itself:
 *     new_dp[e] = 1 + dp[e - 1] + dp[e]
 *   
 *   Algorithm:
 *     Initialize dp[e] = 0 for all e.
 *     Increment move count m = 1, 2, 3, ...
 *     Update dp[e] backward from N down to 1.
 *     As soon as dp[N] >= K, return m!
 *   
 *   Why this is brilliant:
 *     For N = 2 eggs and K = 100 floors, m is at most 14! The loop executes just 14 times!
 * 
 * - Method 2: Classic Minimax DP with Binary Search:
 *   dp[e][f] = 1 + min_{1 <= x <= f} max(dp[e - 1][x - 1], dp[e][f - x]).
 */

class Solution {
public:
    // Optimal Inversion DP: O(N * moves) time, O(N) space
    int eggDrop(int n, int k) {
        // dp[e] = max floors testable with e eggs and m moves
        vector<int> dp(n + 1, 0);

        int moves = 0;

        // Keep incrementing moves until the testable floors >= total building floors K
        while (dp[n] < k) {
            moves++;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Traverse backward: new_dp[e] = 1 + (floors below if broken) + (floors above if survived)
            for (int e = n; e >= 1; e--) {
                dp[e] = 1 + dp[e - 1] + dp[e];
            }
        }

        return moves;
    }

    // Classic Minimax DP (demonstrates O(N * K^2) derivation)
    int eggDropClassic(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        // Base cases: 1 floor -> 1 drop; 0 floors -> 0 drops
        for (int i = 1; i <= n; i++) {
            dp[i][1] = 1;
            dp[i][0] = 0;
        }

        // Base case: 1 egg -> must test floor by floor from 1 to j (j drops)
        for (int j = 1; j <= k; j++) {
            dp[1][j] = j;
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= k; j++) {
                dp[i][j] = INT_MAX;
                for (int x = 1; x <= j; x++) {
                    int worst_case = 1 + max(dp[i - 1][x - 1], dp[i][j - x]);
                    dp[i][j] = min(dp[i][j], worst_case);
                }
            }
        }

        return dp[n][k];
    }
};

int main() {
    Solution sol;
    int n1 = 2, k1 = 10;
    cout << "Min moves (n=2, k=10):  " << sol.eggDrop(n1, k1) << "\n"; // Expected: 4
    cout << "Classic (n=2, k=10):    " << sol.eggDropClassic(n1, k1) << "\n";

    int n2 = 1, k2 = 2;
    cout << "Min moves (n=1, k=2):   " << sol.eggDrop(n2, k2) << "\n"; // Expected: 2

    int n3 = 2, k3 = 100;
    cout << "Min moves (n=2, k=100): " << sol.eggDrop(n3, k3) << "\n"; // Expected: 14

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Optimal Inversion Method: Time Complexity O(N * moves) <= O(N * sqrt(K)). Space Complexity strictly O(N).
 * - Classic DP Method: Time Complexity O(N * K^2), Space Complexity O(N * K).
 */
