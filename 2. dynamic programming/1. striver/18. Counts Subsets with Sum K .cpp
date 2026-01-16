#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Count Subsets with Sum K
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/perfect-sum-problem5633/1
LeetCode: Target Sum (494) - similar concept

Given an array of integers and a target sum K, count the number of subsets 
that sum to exactly K.

Constraints:
- Each element can be used at most once
- We can either pick an element or skip it
- Return the count of subsets that sum to K

Example:
arr = [1, 2, 2, 3], K = 3
Subsets: [1, 2], [3], [1, 2] (duplicate)
Answer = 3

DP State: dp[i][target] = number of ways to achieve target sum using elements from index 0 to i
Recurrence:
dp[i][target] = dp[i-1][target] + dp[i-1][target - arr[i]]
- dp[i-1][target]: not pick arr[i] (count of ways without arr[i])
- dp[i-1][target - arr[i]]: pick arr[i] (count of ways with arr[i], if target >= arr[i])

Base Cases:
- dp[i][0] = 1 (one way: empty subset always sums to 0)
- dp[0][arr[0]] = 1 (if first element equals target and arr[0] <= target)
- Note: if arr[0] = 0, then dp[0][0] = 2 (pick or not pick both give sum 0)

Time Complexity: O(n * K)
Space Complexity: O(n * K) for memoization/tabulation, O(K) for space optimization
*/

// 1. Recursive approach (take/not take method)
class CountSubsetsRecursive {
public:
    // this base case is wrong because we are stopping early when sum = 0.
    // int solve(int idx, vector<int> &arr, int sum) {
    //     if (sum == 0) return 1;f
    //     if (idx >= arr.size() || sum < 0) return 0;
        
    //     int pick = 0;
    //     if (sum >= arr[idx]) {
    //         pick = solve(idx + 1, arr, sum - arr[idx]); // Pick current element
    //     }
    //     int notPick = solve(idx + 1, arr, sum); // Not pick current element
    //     return pick + notPick; // Total ways = ways with pick + ways without pick
    // }
    
    // int perfectSum(vector<int>& arr, int k) {
    //     int n = arr.size();
    //     return solve(0, arr, k);
    // }

    // dont stop only when sum = 0 stop when all the elements are checked.
    // because there coule be elements with value = 0. which will be taken in to account 
    // only when we wait till processing all the elements.
    int solve(int indx, vector<int> &arr, int sum){
        if(indx == arr.size()) return sum == 0;
        int pick = solve(indx + 1, arr, sum - arr[indx]);
        int notPick = solve(indx + 1, arr, sum);
        
        return pick + notPick;
    }
    int perfectSum(vector<int>& arr, int target) {
        // code here
        int n = arr.size();
        return solve(0, arr, target);
    }
};


// 2. Memoization approach (Top-down DP), consistent with pure recursion approach above
class CountSubsetsMemoization {
public:
    // TC: O(n*K), SC: O(n*K) for dp array + O(n) recursion stack
    int solve(int indx, int sum, vector<int> &arr, vector<vector<int>> &dp) {
        if (indx == arr.size()) return sum == 0;
        if (sum < 0) return 0; // Only prune invalid sums

        if (dp[indx][sum] != -1) return dp[indx][sum];

        int pick = solve(indx + 1, sum - arr[indx], arr, dp);
        int notPick = solve(indx + 1, sum, arr, dp);

        return dp[indx][sum] = (pick + notPick) % MOD;
    }
    int perfectSum(vector<int>& arr, int target) {
        int n = arr.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
        return solve(0, target, arr, dp);
    }
};


// 3. Tabulation approach (Bottom-up DP)
class CountSubsetsTabulation {
public:
    // TC: O(n * K), SC: O(n * K) for dp array
    int perfectSum(vector<int>& arr, int k) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, 0));

        // Handle base cases for the first element
        dp[0][0] = 1;
        if (arr[0] <= k) dp[0][arr[0]] += 1;

        // Build DP table
        for (int i = 1; i < n; i++) {
            // Iterate all possible target sums for current index
            for (int t = 0; t <= k; t++) {
                // Not pick current element
                dp[i][t] = dp[i-1][t];
                // Pick current element if possible
                if (t >= arr[i]) dp[i][t] += dp[i-1][t-arr[i]];
            }
        }

        return dp[n-1][k];
    }
};

// 4. Space Optimization (Only Previous Row)
class Solution {
public:
    int perfectSum(vector<int>& arr, int target) {
        // code here
        int n = arr.size();
        // vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        vector<int> prev(target + 1, 0);
        prev[0] = 1;
        if(arr[0] <= target) prev[arr[0]] += 1;
        
        for(int i = 1; i < n; i++){
            vector<int> curr(target + 1, 0);
            for(int t = 0; t <= target; t++){
                curr[t] = prev[t];
                if(t >= arr[i]) curr[t] += prev[t - arr[i]];
            }
            prev = curr;
        }
        
        return prev[target];
    }
};