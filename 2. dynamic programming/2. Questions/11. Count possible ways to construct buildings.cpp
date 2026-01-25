#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem Statement:
Given n sections along a road, each section has 2 plots (one on each side).
Count the total number of ways to construct buildings such that no two adjacent
plots on the same side both have buildings. Return total ways for both sides.

Approach:
Let f(n) be ways for one side with n plots and no adjacent buildings.
Recurrence: f(n) = f(n-1) + f(n-2), with f(0)=1, f(1)=2.
Answer = f(n) * f(n) (independent sides).
*/

// 1. Recursive
class BuildingsRecursive {
public:
    // TC: O(2^n), SC: O(n)
    int f(int n) {
        if (n == 0) return 1;
        if (n == 1) return 2;
        return f(n - 1) + f(n - 2);
    }
    int countWays(int n) {
        int oneSide = f(n);
        return oneSide * oneSide;
    }
};

// 2. Memoization
class BuildingsMemoization {
public:
    // TC: O(n), SC: O(n)
    int f(int n, vector<int>& dp) {
        if (n == 0) return 1;
        if (n == 1) return 2;
        if (dp[n] != -1) return dp[n];
        return dp[n] = f(n - 1, dp) + f(n - 2, dp);
    }
    int countWays(int n) {
        vector<int> dp(n + 1, -1);
        int oneSide = f(n, dp);
        return oneSide * oneSide;
    }
};

// 3. Tabulation
class BuildingsTabulation {
public:
    // TC: O(n), SC: O(n)
    int countWays(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        if (n >= 1) dp[1] = 2;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n] * dp[n];
    }
};

// 4. Space Optimized
class BuildingsSpaceOptimized {
public:
    // TC: O(n), SC: O(1)
    int countWays(int n) {
        if (n == 0) return 1;
        int prev2 = 1; // f(0)
        int prev1 = 2; // f(1)
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        int oneSide = (n == 1) ? 2 : prev1;
        return oneSide * oneSide;
    }
};

// 5. Solution
class Solution {
public:
    // TC: O(n), SC: O(1)
    int countWays(int n) {
        if (n == 0) return 1;
        int prev2 = 1;
        int prev1 = 2;
        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        int oneSide = (n == 1) ? 2 : prev1;
        return oneSide * oneSide;
    }
};