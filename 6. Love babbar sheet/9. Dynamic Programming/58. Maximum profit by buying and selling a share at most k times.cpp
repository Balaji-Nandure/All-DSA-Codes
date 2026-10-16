#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Maximum profit by buying and selling a share at most k times
 * 
 * Given an integer K and an array of daily stock prices A[] of size N.
 * Find the maximum profit that can be made by buying and selling the share 
 * at most K times. You cannot hold more than one share at a time.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "48. Max profit with at most 2 transactions", K was hardcoded to 2 (4 state variables).
 * - Here, K is an arbitrary parameter.
 * - Naive DP takes O(K * N^2). By maintaining a running maximum difference 
 *   (max_diff = max(max_diff, dp[t-1][d] - price[d])), complexity drops to O(K * N).
 * - Alternatively, extending the State Machine to K levels achieves O(K * N) time and O(K) space!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - State Machine Dynamic Programming in O(K * N) Time and O(K) Space:
 *   Maintain two arrays of size K + 1:
 *   - `buy[t]`: Maximum capital balance after completing the t-th BUY.
 *   - `sell[t]`: Maximum capital balance after completing the t-th SELL.
 *   
 *   Base Case:
 *     buy[t] = -infinity for all 1 <= t <= K.
 *     sell[t] = 0 for all 0 <= t <= K.
 *   
 *   Transitions for each day's price p:
 *     For transaction level t from 1 to K:
 *       buy[t]  = max(buy[t],  sell[t - 1] - p)   // Buy share using proceeds from previous sell
 *       sell[t] = max(sell[t], buy[t] + p)       // Sell share to realize profit
 *   
 *   Infinite Transaction Shortcut:
 *     If K >= N / 2, we can capture every single upward price movement:
 *     sum_{i=1}^{N-1} max(0, A[i] - A[i - 1]) in O(N) time!
 */

class Solution {
public:
    int maxProfit(int K, int N, int A[]) {
        if (N <= 1 || K == 0) return 0;

        // Shortcut when K >= N / 2: effectively unlimited transactions
        if (K >= N / 2) {
            int profit = 0;
            for (int i = 1; i < N; i++) {
                if (A[i] > A[i - 1]) {
                    profit += A[i] - A[i - 1];
                }
            }
            return profit;
        }

        // State Machine DP arrays of size K + 1
        vector<int> buy(K + 1, INT_MIN);
        vector<int> sell(K + 1, 0);

        for (int i = 0; i < N; i++) {
            int p = A[i];
            for (int t = 1; t <= K; t++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Buy t builds upon proceeds from sell (t - 1)
                buy[t]  = max(buy[t],  sell[t - 1] - p);

                // Sell t realizes profit from buy t
                sell[t] = max(sell[t], buy[t] + p);
            }
        }

        return sell[K];
    }
};

int main() {
    Solution sol;
    int K1 = 2, N1 = 6;
    int A1[] = {10, 22, 5, 75, 65, 80};
    cout << "Max Profit (K=2): " << sol.maxProfit(K1, N1, A1) << "\n";
    // Buy at 10, sell at 22 (profit 12) + buy at 5, sell at 80 (profit 75) = 87. Expected: 87.

    int K2 = 1, N2 = 5;
    int A2[] = {100, 90, 80, 50, 25};
    cout << "Max Profit (K=1, decreasing): " << sol.maxProfit(K2, N2, A2) << "\n";
    // Decreasing prices: profit 0. Expected: 0.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(K * N). Outer loop runs N times, inner loop runs K times.
 * - Space Complexity: O(K) auxiliary space for buy and sell vectors.
 */
