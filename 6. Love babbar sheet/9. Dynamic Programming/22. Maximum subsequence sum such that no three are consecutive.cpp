#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum subsequence sum such that no three are consecutive
 * 
 * Given an array of positive integers, find the maximum sum of a subsequence 
 * such that NO THREE elements in the chosen subsequence were consecutive in the original array.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "House Robber" / "Stickler Thief", no TWO adjacent elements could be selected:
 *     dp[i] = max(dp[i-1], dp[i-2] + arr[i]).
 * - Here, choosing TWO consecutive elements IS allowed (e.g. arr[i] and arr[i-1]),
 *   but choosing THREE consecutive elements (arr[i], arr[i-1], arr[i-2]) is forbidden.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Tri-Choice Dynamic Programming:
 *   For element at index i, there are 3 mutually exclusive cases:
 *   
 *   Case 1: arr[i] is EXCLUDED:
 *     The maximum sum is simply dp[i - 1].
 *   
 *   Case 2: arr[i] is INCLUDED, and arr[i - 1] is EXCLUDED:
 *     The maximum sum is dp[i - 2] + arr[i].
 *   
 *   Case 3: BOTH arr[i] and arr[i - 1] are INCLUDED:
 *     To satisfy the constraint (no 3 consecutive), arr[i - 2] MUST be EXCLUDED!
 *     The maximum sum is dp[i - 3] + arr[i - 1] + arr[i].
 *   
 *   Recurrence:
 *     dp[i] = max({
 *       dp[i - 1],                          // Exclude arr[i]
 *       dp[i - 2] + arr[i],                 // Include arr[i], exclude arr[i-1]
 *       dp[i - 3] + arr[i - 1] + arr[i]     // Include arr[i] and arr[i-1], exclude arr[i-2]
 *     })
 *   
 *   Base Cases (0-indexed):
 *     dp[0] = arr[0]
 *     dp[1] = arr[0] + arr[1]
 *     dp[2] = max({dp[1], arr[0] + arr[2], arr[1] + arr[2]})
 */

class Solution {
public:
    int maxSumWO3Consec(vector<int>& arr, int n) {
        if (n == 0) return 0;
        if (n == 1) return arr[0];
        if (n == 2) return arr[0] + arr[1];

        vector<int> dp(n, 0);

        // Base cases
        dp[0] = arr[0];
        dp[1] = arr[0] + arr[1];
        dp[2] = max({dp[1], arr[0] + arr[2], arr[1] + arr[2]});

        for (int i = 3; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Tri-case transition: Exclude arr[i], OR include only arr[i], OR include both arr[i] and arr[i-1]
            dp[i] = max({
                dp[i - 1],                          // Exclude arr[i]
                dp[i - 2] + arr[i],                 // Include arr[i], exclude arr[i-1]
                dp[i - 3] + arr[i - 1] + arr[i]     // Include both arr[i] & arr[i-1], force exclude arr[i-2]
            });
        }

        return dp[n - 1];
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {3000, 2000, 1000, 3, 10};
    int n1 = arr1.size();
    cout << "Max sum 1: " << sol.maxSumWO3Consec(arr1, n1) << "\n";
    // Can pick: 3000, 2000 (skip 1000), 3, 10 -> 3000 + 2000 + 3 + 10 = 5013.

    vector<int> arr2 = {100, 1000, 100, 1000, 1};
    int n2 = arr2.size();
    cout << "Max sum 2: " << sol.maxSumWO3Consec(arr2, n2) << "\n";
    // Pick 100, 1000, 1000 -> 2100.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear scan from 3 to N - 1.
 * - Space Complexity: O(N) auxiliary space (can be reduced to O(1) keeping last 3 values).
 */
