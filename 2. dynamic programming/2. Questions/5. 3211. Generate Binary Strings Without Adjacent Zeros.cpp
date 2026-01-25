#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: 3211. Generate Binary Strings Without Adjacent Zeros
LeetCode 3211: https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/

Given n, return all binary strings of length n with no two consecutive '0's.

DP State: dp[i][0] = strings ending with '0', dp[i][1] = strings ending with '1'
Recurrence: 
- dp[i][0] = dp[i-1][1]
- dp[i][1] = dp[i-1][0] + dp[i-1][1]
*/

// 1. Recursive
class GenerateBinaryStringsRecursive {
public:
    void generate(int idx, int n, string& s, vector<string>& res) {
        if (idx == n) {
            res.push_back(s);
            return;
        }
        s.push_back('1');
        generate(idx + 1, n, s, res);
        s.pop_back();
        if (idx == 0 || s.back() != '0') {
            s.push_back('0');
            generate(idx + 1, n, s, res);
            s.pop_back();
        }
    }
    vector<string> validStrings(int n) {
        vector<string> res;
        string s;
        generate(0, n, s, res);
        return res;
    }
};

// 2. Memoization (for counting)
class GenerateBinaryStringsMemoization {
public:
    int dfs(int len, int last, vector<vector<int>> &dp) {
        // No more characters to place
        if (len == 0) return 1;

        if (dp[len][last] != -1)
            return dp[len][last];

        int ways = 0;

        // Always can place '1'
        ways += dfs(len - 1, 1, dp);

        // Can place '0' only if last was '1'
        if (last == 1) {
            ways += dfs(len - 1, 0, dp);
        }

        return dp[len][last] = ways;
    }

    int countValidStrings(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));

        // First character can be '0' or '1'
        return dfs(n - 1, 0, dp) + dfs(n - 1, 1, dp);
    }
};
    

// 3. Tabulation
/*
dp[i][0] → number of valid strings of length i ending with '0'
dp[i][1] → number of valid strings of length i ending with '1'
*/

class GenerateBinaryStringsTabulation {
public:
    int countValidStrings(int n) {
        if (n == 0) return 1;
        if (n == 1) return 2;

        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        // Base case: length 1
        dp[1][0] = 1;   // "0"
        dp[1][1] = 1;   // "1"

        for (int i = 2; i <= n; i++) {
            dp[i][0] = dp[i - 1][1];                  // zero only after one
            dp[i][1] = dp[i - 1][0] + dp[i - 1][1];   // one after anything
        }

        return dp[n][0] + dp[n][1];
    }
};


// 4. Space Optimized
class GenerateBinaryStringsSpaceOptimized {
public:
    int countValidStrings(int n) {
        if (n == 0) return 1;
        if (n == 1) return 2;

        int prev0 = 1;  // strings ending with '0'
        int prev1 = 1;  // strings ending with '1'

        for (int i = 2; i <= n; i++) {
            int curr0 = prev1;
            int curr1 = prev0 + prev1;

            prev0 = curr0;
            prev1 = curr1;
        }

        return prev0 + prev1;
    }
};


// 5. Solution
class Solution {
public:
    void generate(int idx, int n, string& s, vector<string>& res) {
        if (idx == n) {
            res.push_back(s);
            return;
        }
        s.push_back('1');
        generate(idx + 1, n, s, res);
        s.pop_back();
        if (idx == 0 || s.back() != '0') {
            s.push_back('0');
            generate(idx + 1, n, s, res);
            s.pop_back();
        }
    }
    vector<string> validStrings(int n) {
        vector<string> res;
        string s;
        generate(0, n, s, res);
        return res;
    }
};
