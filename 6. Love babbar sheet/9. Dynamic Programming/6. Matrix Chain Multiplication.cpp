#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/**
 * Problem: Matrix Chain Multiplication (MCM)
 * 
 * Given an array p[] of integers such that matrix A_i has dimension p[i-1] x p[i]
 * for 1 <= i <= N - 1. Find the minimum number of scalar multiplications needed 
 * to compute the product A_1 * A_2 * ... * A_{N-1}.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In 0-1 Knapsack or Coin Change, state was 1D or prefix-based (dp[i]).
 * - MCM is the foundational archetype of INTERVAL DP: subproblems are defined over 
 *   arbitrary contiguous subarrays [i ... j].
 * - The cost depends on WHERE the outermost split (parenthesization cut) is placed.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Interval Dynamic Programming:
 *   Let dp[i][j] be the minimum scalar operations needed to compute (A_i * A_{i+1} * ... * A_j).
 *   
 *   Base Case:
 *     dp[i][i] = 0 (a single matrix requires 0 multiplications).
 *   
 *   Recurrence Relation:
 *     To compute product from i to j, we must make a final multiplication between 
 *     the left block (A_i ... A_k) and the right block (A_{k+1} ... A_j) for some split k in [i, j-1]:
 *     
 *     dp[i][j] = min_{i <= k < j} { dp[i][k] + dp[k+1][j] + (p[i-1] * p[k] * p[j]) }
 *   
 *   Order of Computation:
 *     We MUST compute smaller chain lengths L (from 2 up to N-1) before longer lengths,
 *     because dp[i][j] relies on subchains of length k - i + 1 < j - i + 1.
 */

class Solution {
public:
    int matrixMultiplication(int N, int arr[]) {
        // dp[i][j] stores min multiplications for chain A_i ... A_j (1-indexed)
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // L is chain length (from 2 to N - 1)
        for (int L = 2; L < N; L++) {
            for (int i = 1; i < N - L + 1; i++) {
                int j = i + L - 1;
                dp[i][j] = INT_MAX;

                // Try all possible split points k between i and j - 1
                for (int k = i; k < j; k++) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Cost = cost(left_chain) + cost(right_chain) + cost(combining_two_resultant_matrices)
                    int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }

        // Entire chain spans from matrix 1 to matrix N - 1
        return dp[1][N - 1];
    }
};

int main() {
    Solution sol;
    int arr1[] = {10, 20, 30, 40, 30};
    int n1 = sizeof(arr1) / sizeof(arr1[0]); // 4 matrices: 10x20, 20x30, 30x40, 40x30
    cout << "Min Multiplications 1: " << sol.matrixMultiplication(n1, arr1) << "\n";
    // Optimal parenthesization: ((A1 * A2) * A3) * A4 -> 30,000

    int arr2[] = {10, 20, 30};
    int n2 = sizeof(arr2) / sizeof(arr2[0]); // 2 matrices: 10x20, 20x30
    cout << "Min Multiplications 2: " << sol.matrixMultiplication(n2, arr2) << "\n";
    // Cost = 10 * 20 * 30 = 6000

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^3). Three nested loops: chain length L, start index i, and partition point k.
 * - Space Complexity: O(N^2) to maintain the 2D DP memoization table.
 */
