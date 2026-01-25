#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem Statement:
Given an array nums, return the maximum sum of a subsequence such that
no two selected elements are adjacent.

Approach:
Let dp[i] be the maximum sum using elements up to index i.
Recurrence:
dp[i] = max(dp[i-1], nums[i] + (i>=2 ? dp[i-2] : 0))
Base: dp[0] = nums[0]
*/

// 1. Recursive
class MaxSumNonAdjacentRecursive {
public:
    // TC: O(2^n), SC: O(n)
    int solve(int i, const vector<int>& nums) {
        if (i < 0) return 0;
        if (i == 0) return nums[0];
        int pick = nums[i] + solve(i - 2, nums);
        int skip = solve(i - 1, nums);
        return max(pick, skip);
    }
    int maxSum(vector<int>& nums) {
        return solve((int)nums.size() - 1, nums);
    }
};

// 2. Memoization
class MaxSumNonAdjacentMemoization {
public:
    // TC: O(n), SC: O(n)
    int solve(int i, const vector<int>& nums, vector<int>& dp) {
        if (i < 0) return 0;
        if (i == 0) return nums[0];
        if (dp[i] != -1) return dp[i];
        int pick = nums[i] + solve(i - 2, nums, dp);
        int skip = solve(i - 1, nums, dp);
        return dp[i] = max(pick, skip);
    }
    int maxSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        return solve(n - 1, nums, dp);
    }
};

// 3. Tabulation
class MaxSumNonAdjacentTabulation {
public:
    // TC: O(n), SC: O(n)
    int maxSum(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i - 1], nums[i] + dp[i - 2]);
        }
        return dp[n - 1];
    }
};

// 4. Space Optimized
class MaxSumNonAdjacentSpaceOptimized {
public:
    // TC: O(n), SC: O(1)
    int maxSum(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        int prev2 = nums[0];
        int prev1 = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            int curr = max(prev1, nums[i] + prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};
