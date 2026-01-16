#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Partition Equal Subset Sum
LeetCode 416: https://leetcode.com/problems/partition-equal-subset-sum/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/subset-sum-problem2014/1

Given a non-empty array containing only positive integers, find if the array 
can be partitioned into two subsets such that the sum of elements in both 
subsets is equal.

Key Insight:
- If we can partition into two equal subsets, each subset must sum to total_sum/2
- If total_sum is odd, it's impossible to partition equally
- This reduces to: check if there exists a subset that sums to total_sum/2

Example:
nums = [1, 5, 11, 5]
Total sum = 22, target = 11
Subset: [1, 5, 5] -> Sum = 11
Answer = true

DP State: dp[i][target] = can we achieve target sum using elements from index 0 to i
Recurrence:
dp[i][target] = dp[i-1][target] OR dp[i-1][target - nums[i]]
- dp[i-1][target]: not pick nums[i]
- dp[i-1][target - nums[i]]: pick nums[i] (if target >= nums[i])

Base Cases:
- dp[i][0] = true (empty subset always sums to 0)
- dp[0][nums[0]] = true (if first element equals target and nums[0] <= target)

Time Complexity: O(n * target) where target = sum/2
Space Complexity: O(n * target) for memoization/tabulation, O(target) for space optimization
*/

// 1. Recursive approach (take/not take method)
class PartitionEqualSubsetSumRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    bool solve(int idx, vector<int> &nums, int sum) {
        // Base case: target achieved
        if (sum == 0) return true;
        // Base case: no more elements or sum becomes negative
        if (idx < 0 || sum < 0) return false;
        
        // Two choices: pick or not pick
        bool pick = false;
        if (sum >= nums[idx]) {
            pick = solve(idx - 1, nums, sum - nums[idx]); // Pick current element
        }
        bool notPick = solve(idx - 1, nums, sum); // Not pick current element
        
        return pick || notPick;
    }
    
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // If sum is odd, cannot partition equally
        if (totalSum % 2 != 0) return false;
        
        int target = totalSum / 2;
        return solve(n - 1, nums, target);
    }
};

// 1.0. Recursive approach using for loop method
class PartitionEqualSubsetSumRecursiveForLoop {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    bool solve(int idx, vector<int>& nums, int sum) {
        // Base case: target achieved
        if (sum == 0) return true;
        // Base case: invalid state
        if (sum < 0 || idx < 0) return false;
        
        // Try picking any element from idx down to 0
        for (int i = idx; i >= 0; i--) {
            if (sum >= nums[i]) {
                if (solve(i - 1, nums, sum - nums[i])) {
                    return true; // Found valid subset
                }
            }
        }
        return false; // No valid subset found
    }
    
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // If sum is odd, cannot partition equally
        if (totalSum % 2 != 0) return false;
        
        int target = totalSum / 2;
        return solve(n - 1, nums, target);
    }
};

// 2. Memoization approach (Top-down DP)
class PartitionEqualSubsetSumMemoization {
public:
    // TC: O(n * target), SC: O(n * target) for dp array + O(n) recursion stack
    bool solve(int idx, int target, vector<int> &nums, vector<vector<int>> &dp) {
        // Base case: target achieved (empty subset sum)
        if (target == 0) return true;
        // Base case: no more elements or invalid target
        if (idx < 0 || target < 0) return false;
        
        // Return cached result (1: true, 0: false, -1: not computed)
        if (dp[idx][target] != -1) return dp[idx][target];
        
        // Try including the current element nums[idx], if possible
        bool pick = false;
        if (target >= nums[idx]) {
            pick = solve(idx - 1, target - nums[idx], nums, dp);
        }
        
        // Try excluding the current element
        bool notPick = solve(idx - 1, target, nums, dp);
        
        // Save and return if either pick or notPick is true
        return dp[idx][target] = (pick || notPick);
    }
    
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // If sum is odd, cannot partition equally
        if (totalSum % 2 != 0) return false;
        
        int target = totalSum / 2;
        // dp[i][t] = -1 means not calculated, 1:true, 0:false
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        return solve(n - 1, target, nums, dp);
    }
};

// 3. Tabulation approach (Bottom-up DP)
class PartitionEqualSubsetSumTabulation {
public:
    // TC: O(n * target), SC: O(n * target) for dp array
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // If sum is odd, cannot partition equally
        if (totalSum % 2 != 0) return false;
        
        int target = totalSum / 2;
        // dp[i][t]: can we get sum t using first (i+1) items?
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
        
        // Base Case: sum 0 can be made with empty subset
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        
        // Base Case: using only nums[0]
        if (nums[0] <= target) {
            dp[0][nums[0]] = true;
        }
        
        // Build table
        for (int i = 1; i < n; i++) {
            for (int t = 1; t <= target; t++) {
                // Include nums[i] if t >= nums[i]
                bool pick = false;
                if (t >= nums[i]) {
                    pick = dp[i-1][t - nums[i]];
                }
                // Exclude nums[i]
                bool notPick = dp[i-1][t];
                
                dp[i][t] = pick || notPick;
            }
        }
        
        return dp[n-1][target];
    }
};