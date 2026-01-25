#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem Statement:
You are given an array jumps[] of size n, where jumps[i] is the maximum jump length
from step i. You start at step 0 and want to reach step n (just beyond last index).
Return the minimum number of moves to reach step n, or -1 if impossible.

Approach:
Let dp[i] be the minimum moves needed to reach step n from step i.
Transition:
dp[i] = 1 + min(dp[i + j]) for j in [1, jumps[i]] and i + j <= n
Base:
dp[n] = 0
Answer:
dp[0] if reachable else -1
*/

// 1. Recursive
class MinMovesRecursive {
public:
    // TC: O(k^n), SC: O(n)
    int solve(int i, const vector<int>& jumps, int n) {
        if (i == n) return 0;
        if (i > n || jumps[i] == 0) return INF;
        int best = INF;
        for (int j = 1; j <= jumps[i] && i + j <= n; j++) {
            int next = solve(i + j, jumps, n);
            if (next != INF) best = min(best, 1 + next);
        }
        return best;
    }
    int minMoves(vector<int>& jumps) {
        int n = (int)jumps.size();
        int ans = solve(0, jumps, n);
        return ans == INF ? -1 : ans;
    }
};

// 2. Memoization
class MinMovesMemoization {
public:
    // TC: O(n * k), SC: O(n)
    int solve(int i, const vector<int>& jumps, int n, vector<int>& dp) {
        if (i == n) return 0;
        if (i > n || jumps[i] == 0) return INF;
        if (dp[i] != -1) return dp[i];
        int best = INF;
        for (int j = 1; j <= jumps[i] && i + j <= n; j++) {
            int next = solve(i + j, jumps, n, dp);
            if (next != INF) best = min(best, 1 + next);
        }
        return dp[i] = best;
    }
    int minMoves(vector<int>& jumps) {
        int n = (int)jumps.size();
        vector<int> dp(n + 1, -1);
        int ans = solve(0, jumps, n, dp);
        return ans == INF ? -1 : ans;
    }
};

// 3. Tabulation
class MinMovesTabulation {
public:
    // TC: O(n * k), SC: O(n)
    int minMoves(vector<int>& jumps) {
        int n = (int)jumps.size();
        vector<int> dp(n + 1, INF);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            int best = INF;
            for (int j = 1; j <= jumps[i] && i + j <= n; j++) {
                best = min(best, dp[i + j]);
            }
            if (best != INF) dp[i] = 1 + best;
        }
        return dp[0] == INF ? -1 : dp[0];
    }
};

// 4. Solution
class Solution {
public:
    // TC: O(n * k), SC: O(n)
    int minMoves(vector<int>& jumps) {
        int n = (int)jumps.size();
        vector<int> dp(n + 1, INF);
        dp[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            int best = INF;
            for (int j = 1; j <= jumps[i] && i + j <= n; j++) {
                best = min(best, dp[i + j]);
            }
            if (best != INF) dp[i] = 1 + best;
        }
        return dp[0] == INF ? -1 : dp[0];
    }
};
