#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Count all subsequences having product less than K
 * 
 * Given an array of positive integers and a positive integer K,
 * count the number of non-empty subsequences having product strictly less than K.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - "Count subarrays having product less than K" is a CONTIGUOUS problem, solvable 
 *   via a sliding window (two pointers) in O(N) time.
 * - Here, we are counting SUBSEQUENCES (any subset of indices).
 * - Because elements do not need to be adjacent, this is a multiplicative 0-1 Knapsack problem!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Multiplicative Knapsack Dynamic Programming:
 *   Let dp[j] be the number of non-empty subsequences formed from elements processed so far 
 *   having product <= j.
 *   Target is all subsequences with product <= (K - 1).
 *   
 *   Recurrence for each element x in arr:
 *     Traverse budget j BACKWARD from (K - 1) down to 1:
 *     If j >= x:
 *       dp[j] = dp[j] + 1 + dp[j / x]
 *       - dp[j] is the count of existing subsequences (excluding x).
 *       - 1 represents the new single-element subsequence {x}.
 *       - dp[j / x] represents extending all existing subsequences whose product was <= j / x 
 *         by multiplying them by x (yielding a new product <= j).
 *   
 *   Why traverse backward?
 *     Traversing backward ensures that element x is included at most once per subsequence (0-1 property),
 *     preventing x from multiplying into a power of itself within the same transition.
 */

class Solution {
public:
    int countSubsequences(vector<int>& arr, int k) {
        if (k <= 1) return 0; // All elements are positive integers >= 1, so product >= 1

        int target = k - 1; // Strictly less than k means <= k - 1
        vector<int> dp(target + 1, 0);

        for (int x : arr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Backward traversal prevents using element x multiple times in the same subsequence
            for (int j = target; j >= 1; j--) {
                if (j >= x) {
                    // *** CRUCIAL LINE: 1 (for {x}) + dp[j/x] (extending previous valid subsets by x) ***
                    dp[j] += 1 + dp[j / x];
                }
            }
        }

        return dp[target];
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 2, 3, 4};
    int k1 = 10;
    cout << "Subsequences with product < 10: " << sol.countSubsequences(arr1, k1) << "\n";
    // Subsequences with product < 10:
    // Single: {1}, {2}, {3}, {4} (4)
    // Double: {1,2}, {1,3}, {1,4}, {2,3}, {2,4} (5)
    // Triple: {1,2,3}, {1,2,4} (2)
    // Total = 4 + 5 + 2 = 11

    vector<int> arr2 = {4, 8, 7, 2};
    int k2 = 50;
    cout << "Subsequences with product < 50: " << sol.countSubsequences(arr2, k2) << "\n";

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * K) where N is array length and K is the target threshold.
 * - Space Complexity: O(K) space using a single 1D rolling array.
 */
