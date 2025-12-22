#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
 * Problem: House Robber
 *
 * LeetCode 198: House Robber
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/stickler-theif/0
 *
 * You are a professional robber planning to rob houses along a street. Each house has a 
certain amount of money stashed, the only constraint stopping you from robbing each of 
them is that adjacent houses have security systems connected and it will automatically 
contact the police if two adjacent houses were broken into on the same night.

Given an array of integers representing the amount of money in each house, return the 
maximum amount of money you can rob tonight without alerting the police.

- We can either rob a house or skip it
- If we rob house i, we cannot rob house i-1
- If we skip house i, we can rob house i-1

Example:
nums = [2, 7, 9, 3, 1]
Rob: 2, 9, 1 -> Sum = 12
Or: 7, 3 -> Sum = 10
Maximum = 12
*/

// Recursive approach
int houseRobber1(int idx, vector<int> &nums){
    // Base case: no houses left
    if(idx < 0) return 0;
    // Base case: only one house, must rob it
    if(idx == 0) return nums[0];
    
    // Two choices:
    // 1. Rob current: nums[idx] + maxSum(idx-2) (skip previous)
    int rob = nums[idx] + houseRobber1(idx - 2, nums);
    // 2. Skip current: maxSum(idx-1) (can rob previous)
    int notRob = houseRobber1(idx - 1, nums);
    
    return max(rob, notRob);
}

// Memoization approach (Top-down DP)
int houseRobber1Memoization(int idx, vector<int> &nums, vector<int> &dp){
    // Base cases
    if(idx < 0) return 0;
    if(idx == 0) return nums[0];
    // Return cached result
    if(dp[idx] != -1) return dp[idx];
    
    // Compute and store result
    int rob = nums[idx] + houseRobber1Memoization(idx - 2, nums, dp);
    int notRob = houseRobber1Memoization(idx - 1, nums, dp);
    
    return dp[idx] = max(rob, notRob);
}

// Tabulation approach (Bottom-up DP)
int houseRobber1Tabulation(int n, vector<int> &nums){
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    
    vector<int> dp(n, 0);
    dp[0] = nums[0]; // Base case
    dp[1] = max(nums[0], nums[1]); // Can rob either first or second
    
    // Fill dp array
    for(int i = 2; i < n; i++){
        int rob = nums[i] + dp[i - 2]; // Rob current, skip previous
        int notRob = dp[i - 1]; // Skip current, can rob previous
        dp[i] = max(rob, notRob);
    }
    
    return dp[n - 1];
}

// Space optimization (only need last 2 values)
int houseRobber1SpaceOptimization(int n, vector<int> &nums){
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    
    int prev2 = nums[0]; // dp[0]
    int prev1 = max(nums[0], nums[1]); // dp[1]
    
    for(int i = 2; i < n; i++){
        int rob = nums[i] + prev2; // Rob current
        int notRob = prev1; // Skip current
        int curr = max(rob, notRob);
        // Update for next iteration
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}

signed main() {
    vector<int> nums = {2, 7, 9, 3, 1};
    int n = nums.size();
    
    int recursive = houseRobber1(n - 1, nums);
    
    vector<int> dp1(n, -1);
    int memoization = houseRobber1Memoization(n - 1, nums, dp1);
    
    int tabulation = houseRobber1Tabulation(n, nums);
    int spaceOptimization = houseRobber1SpaceOptimization(n, nums);
    
    cout << "Recursive: " << recursive << endl;
    cout << "Memoization: " << memoization << endl;
    cout << "Tabulation: " << tabulation << endl;
    cout << "Space Optimization: " << spaceOptimization << endl;
    
    return 0;
}

