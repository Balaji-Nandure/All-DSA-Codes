#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Count Partitions With Given Difference

You are given an array of n integers and an integer d. You have to count the number of ways to partition the array into two subsets such that the difference of subset sums == d.

Let S1 and S2 be the sums of the two subsets.
We need: S1 - S2 = d
But also: S1 + S2 = totalSum
=> 2*S1 = totalSum + d  => S1 = (totalSum + d)/2

So, reduce this to: Count number of subsets with sum == S1, where S1 = (totalSum + d)/2, and totalSum + d is even, S1 >= 0.

This is the classic subset sum count.

*/

// 1. Recursive approach for understanding (not recommended for large inputs)
class CountPartitionsRecursive {
public:
    int solve(int indx, vector<int>& arr, int sum) {
        if (indx == arr.size()) return sum == 0;
        int pick = 0, notPick = 0;
        if (sum >= arr[indx])
            pick = solve(indx + 1, arr, sum - arr[indx]);
        notPick = solve(indx + 1, arr, sum);
        return pick + notPick;
    }
    int countPartitions(int n, int d, vector<int>& arr) {
        int totalSum = accumulate(arr.begin(), arr.end(), 0LL);
        // Check if (totalSum + d) is possible to partition equally
        if (totalSum < d || (totalSum + d) % 2 != 0) return 0;
        int target = (totalSum + d) / 2;
        return solve(0, arr, target);
    }
};

// 2. Memoization (Top-down DP)
class CountPartitionsMemoization {
public:
    int solve(int i, int sum, vector<int>& arr, vector<vector<int>>& dp) {
        if (i == arr.size()) return sum == 0;
        if (dp[i][sum] != -1) return dp[i][sum];
        int pick = 0, notPick = 0;
        if (sum >= arr[i])
            pick = solve(i + 1, sum - arr[i], arr, dp);
        notPick = solve(i + 1, sum, arr, dp);
        return dp[i][sum] = (pick + notPick) % MOD;
    }
    int countPartitions(int n, int d, vector<int>& arr) {
        int totalSum = accumulate(arr.begin(), arr.end(), 0LL);
        if (totalSum < d || (totalSum + d) % 2 != 0) return 0;
        int target = (totalSum + d) / 2;
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
        return solve(0, target, arr, dp);
    }
};

// 3. Tabulation (Bottom-up DP)
class CountPartitionsTabulation {
public:
    int countPartitions(int n, int d, vector<int>& arr) {
        int totalSum = accumulate(arr.begin(), arr.end(), 0LL);
        if (totalSum < d || (totalSum + d) % 2 != 0) return 0;
        int target = (totalSum + d) / 2;
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int t = 0; t <= target; ++t) {
                // Not pick
                dp[i][t] = dp[i - 1][t];
                // Pick current number if possible
                if (t >= arr[i - 1])
                    dp[i][t] += dp[i - 1][t - arr[i - 1]];
            }
        }
        return dp[n][target];
    }
};

// 4. Space Optimized (O(target) DP)
class Solution {
public:
    int countPartitions(int n, int d, vector<int>& arr) {
        int totalSum = accumulate(arr.begin(), arr.end(), 0LL);
        if (totalSum < d || (totalSum + d) % 2 != 0) return 0;
        int target = (totalSum + d) / 2;
        vector<int> prev(target + 1, 0);
        prev[0] = 1;
        for (int i = 0; i < n; ++i) {
            vector<int> curr(target + 1, 0);
            for (int t = 0; t <= target; ++t) {
                // Not pick arr[i]
                curr[t] = prev[t];
                // Pick arr[i] if it can fit into target sum
                if (t >= arr[i])
                    curr[t] +=  prev[t - arr[i]];
            }
            prev = curr;
        }
        return prev[target];
    }
};