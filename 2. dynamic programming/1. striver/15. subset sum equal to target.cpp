#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Subset Sum Equal to Target
LeetCode: Partition Equal Subset Sum (416), Target Sum (494)
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1

Given an array of integers and a target sum, determine if there exists a subset 
of the array that sums to exactly the target.

Constraints:
- Each element can be used at most once
- We can either pick an element or skip it
- Return true if subset exists, false otherwise

Example:
arr = [1, 2, 3, 4], target = 7
Subset: [3, 4] -> Sum = 7
Answer = true

DP State: dp[i][target] = can we achieve target sum using elements from index 0 to i
Recurrence:
dp[i][target] = dp[i-1][target] OR dp[i-1][target - arr[i]]
- dp[i-1][target]: not pick arr[i]
- dp[i-1][target - arr[i]]: pick arr[i] (if target >= arr[i])

Base Cases:
- dp[i][0] = true (empty subset always sums to 0)
- dp[0][arr[0]] = true (if first element equals target and arr[0] <= target)

Time Complexity: O(n * target)
Space Complexity: O(n * target) for memoization/tabulation, O(target) for space optimization
*/

// 1. Recursive approach (take/not take method)
class SubsetSumRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    bool solve(int idx, vector<int> &arr, int sum) {
        // Base case: target achieved
        if (sum == 0) return true;
        // Base case: no more elements or sum becomes negative
        if (idx < 0 || sum < 0) return false;
        
        // Two choices: pick or not pick
        bool pick = false;
        if (sum >= arr[idx]) {
            pick = solve(idx - 1, arr, sum - arr[idx]); // Pick current element
        }
        bool notPick = solve(idx - 1, arr, sum); // Not pick current element
        
        return pick || notPick;
    }
    
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
        return solve(n - 1, arr, sum);
    }
};

// 2. Memoization approach (Top-down DP)
class SubsetSumMemoization {
public:
    // TC: O(n * target), SC: O(n * target) for dp array + O(n) recursion stack
    bool solve(int idx, int target, vector<int> &arr, vector<vector<int>> &dp) {
        // Base case: target achieved (empty subset sum)
        if (target == 0) return true;
        // Base case: no more elements or invalid target
        if (idx < 0 || target < 0) return false;
        
        // Return cached result (1: true, 0: false, -1: not computed)
        if (dp[idx][target] != -1) return dp[idx][target];
        
        // Try including the current element arr[idx], if possible
        bool pick = false;
        if (target >= arr[idx]) {
            pick = solve(idx - 1, target - arr[idx], arr, dp);
        }
        
        // Try excluding the current element
        bool notPick = solve(idx - 1, target, arr, dp);
        
        // Save and return if either pick or notPick is true
        return dp[idx][target] = (pick || notPick);
    }
    
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
        // dp[i][t] = -1 means not calculated, 1:true, 0:false
        vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
        return solve(n - 1, sum, arr, dp);
    }
};

bool isSubsetSum(vector<int>& arr, int target) {
    int n = arr.size();
    vector<vector<bool>> dp(n, vector<bool>(target + 1, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= target; j++) {
            if (j == 0) {
                dp[i][j] = true;
            } 
            else if (i == 0) {
                dp[i][j] = (arr[0] == j);
            } 
            else {
                bool notTake = dp[i - 1][j];
                bool take = false;
                if (arr[i] <= j) {
                    take = dp[i - 1][j - arr[i]];
                }
                dp[i][j] = take || notTake;
            }
        }
    }

    return dp[n - 1][target];
}

// 4. Space Optimization (Only Previous Row)
bool isSubsetSum(vector<int>& arr, int target) {
    int n = arr.size();
    vector<bool> prev(target + 1, false);

    prev[0] = true; // Base case: sum 0 is always possible
    if(arr[0] <= target) prev[arr[0]] = true;

    for (int i = 1; i < n; i++) {
        vector<bool> curr(target + 1, false);
        curr[0] = true; 
        for (int j = 1; j <= target; j++) {
            bool notTake = prev[j];
            bool take = false;
            if (arr[i] <= j) take = prev[j - arr[i]];
            
            curr[j] = take || notTake;
        }
        prev = curr;
    }
    return prev[target];
}