// Problem: Subarray with 0 Sum
// Link (Article): https://www.geeksforgeeks.org/dsa/find-if-there-is-a-subarray-with-0-sum/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/subarray-with-0-sum-1587115621/1
// Difficulty: Medium / Easy
// Topic: Array, Hash Set, Prefix Sum

/*
Problem Statement:
Given an array of integers `arr[]`, determine whether there exists a non-empty subarray with a sum equal to 0.
Return `true` if such a subarray exists, otherwise return `false`.

Example 1:
Input: arr = [4, 2, -3, 1, 6]
Output: true
Explanation: Subarray [2, -3, 1] has a sum = 2 - 3 + 1 = 0.

Example 2:
Input: arr = [4, 2, 0, 1, 6]
Output: true
Explanation: Subarray [0] has a sum = 0.

Example 3:
Input: arr = [1, 2, -1]
Output: false
Explanation: No subarray sums to 0.

Constraints:
- 1 <= arr.size() <= 10^5
- -10^5 <= arr[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Kadane): We wanted the MAXIMUM contiguous sum (reset on negative).
// - In Problem 18 (Pair Sum): We looked for pairs x + y = target using a hash map.
// - In Problem 21 (0-Sum Subarray):
//   * A subarray sum between indices (i + 1) and j equals: `PrefixSum[j] - PrefixSum[i]`.
//   * For this difference to be 0, we must have `PrefixSum[j] == PrefixSum[i]`!
//   * Thus, finding a 0-sum subarray reduces to detecting a REPEATED PREFIX SUM!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force O(N^2)
//   - Check all pairs (i, j) and compute subarray sum: O(N^2). TLE for N = 10^5.
//
// Approach 2: Prefix Sum with Hash Set (OPTIMAL & CHOSEN)
//   - Maintain a running `prefixSum` and an `unordered_set<long long> seen`.
//   - For each element `x` in `arr`:
//     * `prefixSum += x`.
//     * If `prefixSum == 0`: A subarray starting from index 0 sums to 0!
//     * If `seen.count(prefixSum)`: We encountered this exact prefix sum previously at some index `i`.
//       The subarray between index `i + 1` and current index `j` has sum 0!
//     * Insert `prefixSum` into `seen`.
//   - Complexity: O(N) average time, O(N) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool subArrayExists(vector<int>& arr) {
        unordered_set<long long> seenPrefixSums;
        long long prefixSum = 0;

        for (int x : arr) {
            prefixSum += x;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 1. If prefixSum == 0: Subarray [0 ... current] has sum 0.
            // 2. If seenPrefixSums has prefixSum: Subarray (prevIndex ... current] has sum 0
            //    because: CurrentPrefixSum - PreviousPrefixSum = 0!
            if (prefixSum == 0 || seenPrefixSums.find(prefixSum) != seenPrefixSums.end()) {
                return true;
            }

            // Record this prefix sum in our hash set
            seenPrefixSums.insert(prefixSum);
        }

        return false;
    }
};

/*
Time Complexity: O(N)
- Exactly one linear scan through the array.
- Set lookups and insertions take O(1) average time.
- Overall Time Complexity: O(N).

Space Complexity: O(N) Auxiliary Space
- Unordered set stores at most N prefix sums.

Key Insights:
1. The Mathematical Invariant:
   - Sum of subarray [L ... R] = Prefix[R] - Prefix[L - 1].
   - If Prefix[R] - Prefix[L - 1] = 0  ==>  Prefix[R] = Prefix[L - 1].
   - Detecting duplicates in the prefix sum sequence is completely equivalent to finding a zero-sum range!
2. Extension to Target Sum K:
   - To find if a subarray with sum K exists: check if `seen.count(prefixSum - K)`.
*/
