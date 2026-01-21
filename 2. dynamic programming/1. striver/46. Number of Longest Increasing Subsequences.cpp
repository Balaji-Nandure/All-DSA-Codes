#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Number of Longest Increasing Subsequence
LeetCode 673: https://leetcode.com/problems/number-of-longest-increasing-subsequence/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/number-of-longest-increasing-subsequence/1

Given an integer array nums, return the number of longest increasing subsequences.

Notice that the sequence has to be strictly increasing.

Constraints:
- 1 <= nums.length <= 2000
- -10^6 <= nums[i] <= 10^6

Example:
nums = [1,3,5,4,7]
Longest Increasing Subsequence: [1,3,5,7] or [1,3,4,7]
Length = 4, Count = 2

Key Insight:
- We need to track both the length and count of LIS ending at each index
- For each index i:
  - dp[i] = length of longest increasing subsequence ending at index i
  - count[i] = number of LIS of length dp[i] ending at index i
- When extending from j to i:
  - If dp[j] + 1 > dp[i]: update dp[i] and reset count[i] = count[j]
  - If dp[j] + 1 == dp[i]: add count[j] to count[i]

DP State:
- dp[i] = length of longest increasing subsequence ending at index i
- count[i] = number of LIS of length dp[i] ending at index i

Recurrence:
- For each j < i where nums[j] < nums[i]:
  - If dp[j] + 1 > dp[i]:
    - dp[i] = dp[j] + 1
    - count[i] = count[j]
  - Else if dp[j] + 1 == dp[i]:
    - count[i] += count[j]

Base Cases:
- dp[i] = 1 for all i (each element is a subsequence of length 1)
- count[i] = 1 for all i (each element forms 1 subsequence of length 1)

Time Complexity: O(n^2) where n is the array size
Space Complexity: O(n) for dp and count arrays
*/

// 4. Space Optimization (Same as tabulation, already O(n) space)
// Note: The tabulation approach already uses O(n) space, which is optimal.
class Solution {
public:
    // TC: O(n^2), SC: O(n) for dp and count arrays
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> dp(n, 1);
        vector<int> count(n, 1);
        
        int maxLen = 1;
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    if (dp[j] + 1 > dp[i]) {
                        // Found longer subsequence, reset count
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    } else if (dp[j] + 1 == dp[i]) {
                        // Same length, add to count
                        count[i] += count[j];
                    }
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        
        // Sum counts for all subsequences of maximum length
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] == maxLen) {
                result += count[i];
            }
        }
        
        return result;
    }
};
