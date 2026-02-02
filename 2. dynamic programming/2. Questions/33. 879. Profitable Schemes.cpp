/*
Problem:
879. Profitable Schemes

Approach:
0/1 Knapsack (Tabulation)

State:
dp[people][profit]
= number of schemes using exactly `people` members
  and achieving profit >= profit (capped)

Transition:
For each crime i:
  dp[p][newProfit] += dp[p - group[i]][oldProfit]

Profit is capped at minProfit.

LeetCode:
https://leetcode.com/problems/profitable-schemes/

Time Complexity:
O(m * n * minProfit)

Space Complexity:
O(n * minProfit)
*/

const int MOD = 1000000007;

int solve(int i, int people, int profit, 
          vector<int>& group, vector<int>& gain, int minProfit,
          vector<vector<vector<int>>>& dp) {
    
    // Base case: processed all crimes
    if (i == group.size()) {
        // If we achieved at least minProfit, this is a valid scheme
        return profit >= minProfit ? 1 : 0;
    }
    
    // Check memoized result
    if (dp[i][people][profit] != -1) {
        return dp[i][people][profit];
    }
    
    int ans = 0;
    
    // Option 1: Don't take this crime
    ans = solve(i + 1, people, profit, group, gain, minProfit, dp);
    
    // Option 2: Take this crime (if we have enough people)
    if (people >= group[i]) {
        int newProfit = min(minProfit, profit + gain[i]);  // Cap profit at minProfit
        ans = (ans + solve(i + 1, people - group[i], newProfit, group, gain, minProfit, dp)) % MOD;
    }
    
    return dp[i][people][profit] = ans;
}

int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
    int m = group.size();
    // dp[i][people][profit] = number of schemes from crime i onwards
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n + 1, vector<int>(minProfit + 1, -1)));
    
    return solve(0, n, 0, group, profit, minProfit, dp);
}
