#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest Increasing Subsequence (LIS)
 * 
 * Given an integer array nums, return the length of the longest strictly increasing subsequence.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Unlike LCS which compared two strings, LIS operates on a SINGLE array.
 * - The constraint is order-preserving monotonicity: nums[i_1] < nums[i_2] < ... < nums[i_k].
 * - Standard DP takes O(N^2), but Patience Sorting + Binary Search achieves optimal O(N log N).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Approach 1: Classic DP in O(N^2) Time:
 *   Let dp[i] be the length of the LIS ending at index i.
 *   dp[i] = 1 + max_{0 <= j < i, nums[j] < nums[i]} dp[j].
 *   Result = max(dp[i]).
 * 
 * - Approach 2: Patience Sorting with Binary Search in O(N log N) Time:
 *   Maintain a vector `tails` where `tails[k]` stores the SMALLEST ending element of all 
 *   increasing subsequences of length (k + 1) seen so far.
 *   
 *   Invariant:
 *     The `tails` vector is always strictly SORTED in ascending order.
 *   
 *   For each element x in nums:
 *     Use binary search (`lower_bound`) to find the first element in `tails` >= x:
 *     - If no such element exists (x is greater than all tails):
 *       x extends the longest subsequence found so far -> tails.push_back(x).
 *     - If an element >= x is found at index idx:
 *       Update `tails[idx] = x`.
 *       (Replacing a larger tail with x maintains the same subsequence length but lowers 
 *        the threshold for future elements to extend this subsequence!).
 *   
 *   The length of `tails` at the end is strictly the length of the LIS!
 */

class Solution {
public:
    // Optimal O(N log N) Patience Sorting + Binary Search
    int longestSubsequence(int n, vector<int>& a) {
        if (n == 0) return 0;

        vector<int> tails;

        for (int x : a) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Find the position of the first element >= x via binary search in O(log N)
            auto it = lower_bound(tails.begin(), tails.end(), x);

            if (it == tails.end()) {
                // x is strictly greater than all current subsequence tails: extends length
                tails.push_back(x);
            } else {
                // *** CRUCIAL LINE: Greedily minimize tail value to make future extensions easier ***
                *it = x;
            }
        }

        return tails.size();
    }

    // Classic O(N^2) DP
    int longestSubsequenceDP(int n, vector<int>& a) {
        vector<int> dp(n, 1);
        int max_lis = 1;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (a[j] < a[i]) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
            max_lis = max(max_lis, dp[i]);
        }

        return max_lis;
    }
};

int main() {
    Solution sol;
    vector<int> a1 = {10, 9, 2, 5, 3, 7, 101, 18};
    int n1 = a1.size();
    cout << "LIS Length 1 (O(N log N)): " << sol.longestSubsequence(n1, a1) << "\n";   // Expected: 4 ([2, 3, 7, 101] or [2, 5, 7, 101])
    cout << "LIS Length 1 (O(N^2)):     " << sol.longestSubsequenceDP(n1, a1) << "\n"; // Expected: 4

    vector<int> a2 = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    int n2 = a2.size();
    cout << "LIS Length 2 (O(N log N)): " << sol.longestSubsequence(n2, a2) << "\n";   // Expected: 6

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Optimal Method: Time Complexity O(N log N) using binary search (lower_bound) across N elements.
 * - Space Complexity: O(N) auxiliary space to store the `tails` array.
 */
