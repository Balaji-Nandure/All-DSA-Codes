#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: House Robber 1
You are a professional robber planning to rob houses along a street. Each house has a 
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

// recursive approach
int houseRobber1(int idx, vector<int> &nums){
    if(idx < 0) return 0; // base case: no houses left
    if(idx == 0) return nums[0]; // only one house, must rob it
    
    // Two choices:
    // 1. Rob current house: nums[idx] + houseRobber1(idx-2) (skip previous)
    // 2. Skip current house: houseRobber1(idx-1) (can rob previous)
    int rob = nums[idx] + houseRobber1(idx - 2, nums);
    int notRob = houseRobber1(idx - 1, nums);
    
    return max(rob, notRob);
}

// memoization approach
int houseRobber1Memoization(int idx, vector<int> &nums, vector<int> &dp){
    if(idx < 0) return 0;
    if(idx == 0) return nums[0];
    if(dp[idx] != -1) return dp[idx];
    
    int rob = nums[idx] + houseRobber1Memoization(idx - 2, nums, dp);
    int notRob = houseRobber1Memoization(idx - 1, nums, dp);
    
    return dp[idx] = max(rob, notRob);
}

// tabulation approach
int houseRobber1Tabulation(int n, vector<int> &nums){
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]); // can rob either first or second house
    
    for(int i = 2; i < n; i++){
        int rob = nums[i] + dp[i - 2];
        int notRob = dp[i - 1];
        dp[i] = max(rob, notRob);
    }
    
    return dp[n - 1];
}

// space optimization approach
int houseRobber1SpaceOptimization(int n, vector<int> &nums){
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    
    int prev2 = nums[0]; // dp[0]
    int prev1 = max(nums[0], nums[1]); // dp[1]
    
    for(int i = 2; i < n; i++){
        int rob = nums[i] + prev2;
        int notRob = prev1;
        int curr = max(rob, notRob);
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

