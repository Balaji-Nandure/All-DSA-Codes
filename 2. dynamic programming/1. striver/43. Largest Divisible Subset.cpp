#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Largest Divisible Subset
LeetCode 368: https://leetcode.com/problems/largest-divisible-subset/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/largest-divisible-subset/1

Given a set of distinct positive integers nums, return the largest subset answer such that
every pair (answer[i], answer[j]) of elements in this subset satisfies:
- answer[i] % answer[j] == 0, or
- answer[j] % answer[i] == 0

If there are multiple solutions, return any of them.

Constraints:
- 1 <= nums.length <= 1000
- 1 <= nums[i] <= 2 * 10^9
- All integers in nums are unique

Example:
nums = [1,2,3]
Largest Divisible Subset: [1,2] or [1,3]
Answer = [1,2]

Key Insight:
- Sort the array first (ascending order)
- After sorting, if nums[i] % nums[j] == 0 for j < i, then all elements in the subset ending at j
  can be extended by nums[i]
- This is similar to LIS, but with divisibility condition instead of increasing condition

DP State: dp[i] = length of largest divisible subset ending at index i
parent[i] = index of previous element in the subset (for backtracking)

Recurrence:
- dp[i] = 1 + max(dp[j]) for all j < i where nums[i] % nums[j] == 0
- parent[i] = j (the index j that gives maximum dp[j])
- If no such j exists, dp[i] = 1 and parent[i] = -1

Base Cases:
- dp[0] = 1 (single element is always a subset of length 1)
- parent[0] = -1 (no previous element)

Time Complexity: O(n^2) where n is the number of elements
Space Complexity: O(n) for dp and parent arrays

Note: We need to sort the array first to ensure that if nums[i] % nums[j] == 0, then
nums[j] <= nums[i] (since we sorted in ascending order).
*/

// in this case you cannot apply memoisaion in better way.
// its better to for this approach use this method i.e tabulation

// 3. Tabulation (Bottom-up DP) - Returns the actual subset instead of length
class LargestDivisibleSubsetTabulationLength {
public:
    // TC: O(n^2), SC: O(n) for dp array
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        
        sort(nums.begin(), nums.end());
        vector<int> dp(n, 1), parent(n, -1);
        int maxi = 1, lastIdx = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
            if (dp[i] > maxi) {
                maxi = dp[i];
                lastIdx = i;
            }
        }
        
        // Recover the subset
        vector<int> subset;
        int idx = lastIdx;
        while (idx != -1) {
            subset.push_back(nums[idx]);
            idx = parent[idx];
        }
        reverse(subset.begin(), subset.end());
        return subset;
    }
};
    