#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem Statement:
Given a string s containing digits, return the number of ways to decode it
where '1' -> 'A', '2' -> 'B', ..., '26' -> 'Z'. A '0' cannot be decoded alone.

Approach:
Let dp[i] be the number of ways to decode the suffix starting at index i.
At position i:
- If s[i] == '0' => dp[i] = 0
- Otherwise, dp[i] = dp[i+1] (take one digit)
- If s[i..i+1] forms a valid number 10..26, add dp[i+2]
Answer = dp[0]
*/

// 1. Recursive
class DecodeWaysRecursive {
public:
    // TC: O(2^n), SC: O(n)
    int solve(int i, const string& s) {
        if (i == (int)s.size()) return 1;
        if (s[i] == '0') return 0;

        int ways = solve(i + 1, s);
        if (i + 1 < (int)s.size()) {
            int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (val >= 10 && val <= 26) ways += solve(i + 2, s);
        }
        return ways;
    }
    int numDecodings(string s) {
        return solve(0, s);
    }
};

// 2. Memoization
class DecodeWaysMemoization {
public:
    // TC: O(n), SC: O(n)
    int solve(int i, const string& s, vector<int>& dp) {
        if (i == (int)s.size()) return 1;
        if (s[i] == '0') return 0;
        if (dp[i] != -1) return dp[i];

        int ways = solve(i + 1, s, dp);
        if (i + 1 < (int)s.size()) {
            int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
            if (val >= 10 && val <= 26) ways += solve(i + 2, s, dp);
        }
        return dp[i] = ways;
    }
    int numDecodings(string s) {
        vector<int> dp(s.size(), -1);
        return solve(0, s, dp);
    }
};

// 3. Tabulation
class DecodeWaysTabulation {
public:
    // TC: O(n), SC: O(n)
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n + 2, 0);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                dp[i] = 0;
                continue;
            }
            dp[i] = dp[i + 1];
            if (i + 1 < n) {
                int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
                if (val >= 10 && val <= 26) dp[i] += dp[i + 2];
            }
        }
        return dp[0];
    }
};

// 4. Space Optimized
class DecodeWaysSpaceOptimized {
public:
    // TC: O(n), SC: O(1)
    int numDecodings(string s) {
        int n = s.size();
        int next2 = 0; // dp[i+2]
        int next1 = 1; // dp[i+1] when i = n-1 -> dp[n] = 1

        for (int i = n - 1; i >= 0; i--) {
            int curr = 0;
            if (s[i] != '0') {
                curr = next1;
                if (i + 1 < n) {
                    int val = (s[i] - '0') * 10 + (s[i + 1] - '0');
                    if (val >= 10 && val <= 26) curr += next2;
                }
            }
            next2 = next1;
            next1 = curr;
        }
        return next1;
    }
};
