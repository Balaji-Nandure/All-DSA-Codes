#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Longest Increasing Subsequence (LIS)
LeetCode 300: https://leetcode.com/problems/longest-increasing-subsequence/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1

Given an integer array nums, return the length of the longest strictly increasing subsequence.

A subsequence is a sequence that can be derived from an array by deleting some or no elements
without changing the order of the remaining elements.

Constraints:
- 1 <= nums.length <= 2500
- -10^4 <= nums[i] <= 10^4

Example:
nums = [10,9,2,5,3,7,101,18]
LIS: [2,5,7,101] or [2,5,7,18]
Length = 4

DP State: dp[i] = length of longest increasing subsequence ending at index i

Recurrence:
- dp[i] = 1 + max(dp[j]) for all j < i where nums[j] < nums[i]
- If no such j exists, dp[i] = 1 (only the element itself)

Base Cases:
- dp[0] = 1 (single element is always a subsequence of length 1)

Time Complexity: O(n^2) for DP approach, O(n log n) for binary search approach
Space Complexity: O(n) for DP array

Alternative O(n log n) approach:
- Use binary search to maintain the smallest tail element of all increasing subsequences
- For each element, find the position where it can be placed using binary search
*/

// 1. Recursive approach (take/not take method)
class LISRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int idx, int prevIdx, vector<int>& nums) {
        // Base case: reached end of array
        if (idx == nums.size()) return 0;
        
        // Option 1: Don't take current element
        int notTake = solve(idx + 1, prevIdx, nums);
        
        // Option 2: Take current element (if it's greater than previous)
        int take = 0;
        if (prevIdx == -1 || nums[idx] > nums[prevIdx]) {
            take = 1 + solve(idx + 1, idx, nums);
        }
        
        return max(take, notTake);
    }
    
    int lengthOfLIS(vector<int>& nums) {
        return solve(0, -1, nums);
    }
};


// 2. Memoization (Top-down DP)
class LISMemoization {
public:
    // TC: O(n^2), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int idx, int prevIdx, vector<int>& nums, vector<vector<int>>& dp) {
        if (idx == nums.size()) return 0;
        // Use prevIdx+1 to handle -1 case (prevIdx = -1 maps to index 0)
        if (dp[idx][prevIdx + 1] != -1) return dp[idx][prevIdx + 1];
        
        int notTake = solve(idx + 1, prevIdx, nums, dp);
        
        int take = 0;
        if (prevIdx == -1 || nums[idx] > nums[prevIdx]) {
            take = 1 + solve(idx + 1, idx, nums, dp);
        }
        
        return dp[idx][prevIdx + 1] = max(take, notTake);
    }
    
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        // dp[i][j+1] where j can be -1 to n-1, so we need n+1 columns
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solve(0, -1, nums, dp);
    }
};


// 3. Tabulation (Bottom-up DP)
class LISTabulation {
public:
    // TC: O(n^2), SC: O(n) for dp array
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // dp[i] = length of LIS ending at index i
        vector<int> dp(n, 1);
        
        // For each element, check all previous elements
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // If nums[j] < nums[i], we can extend the LIS ending at j
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
        }
        
        // Return the maximum value in dp array
        return *max_element(dp.begin(), dp.end());
    }
};


// nums = [10, 9, 2, 5, 3, 7, 101, 18]
// nums[i]	tail update
// 10	[10]
// 9	[9]
// 2	[2]
// 5	[2, 5]
// 3	[2, 3]
// 7	[2, 3, 7]
// 101	[2, 3, 7, 101]
// 18	[2, 3, 7, 18]
// 4. Space Optimization (O(n log n) using Binary Search)


class Solution {
public:
    // TC: O(n log n), SC: O(n) for tail array
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        // tail[i] = smallest tail element of all increasing subsequences of length i+1
        vector<int> tail;
        tail.push_back(nums[0]);
        
        for (int i = 1; i < n; i++) {
            if (nums[i] > tail.back()) {
                // Extend the longest subsequence
                tail.push_back(nums[i]);
            } else {
                // Replace the first element >= nums[i] in tail
                // This maintains the smallest tail for each length
                auto it = lower_bound(tail.begin(), tail.end(), nums[i]);
                *it = nums[i];
            }
        }
        
        return tail.size();
    }
};
