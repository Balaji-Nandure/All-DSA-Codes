#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;

/*
Problem: Ways to Make Coin Change
LeetCode 518: https://leetcode.com/problems/coin-change-2/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/coin-change2448/1

You are given an integer array coins representing coins of different denominations and an integer amount.
Return the number of combinations that make up that amount. 
You may assume that you have infinite number of each kind of coin.

Constraints:
- Each coin can be used unlimited times (unbounded knapsack variant)
- Find the number of ways to make up the amount (order of coins doesn't matter!)

Example:
coins = [1, 2, 5], amount = 5
Ways:
- 5 = 5
- 5 = 2+2+1
- 5 = 2+1+1+1
- 5 = 1+1+1+1+1
- 5 = 1+1+1+2
Answer = 4

DP State: dp[indx][amount] = number of ways to make up amount using coins[indx..n-1]
Recurrence:
dp[indx][amount] = dp[indx+1][amount] + dp[indx][amount-coins[indx]] if amount >= coins[indx]
- Not pick (next coin): dp[indx+1][amount]
- Pick (take same coin again): dp[indx][amount-coins[indx]]

Base Cases:
- If amount==0: 1 way
- If indx == n: 0 (except for amount==0)

Time Complexity: O(n * amount)
Space Complexity: O(n * amount)
*/

//  0 Pick/not pick - Recursive
class Solution {
private:
    int solve(int indx, int amount, vector<int> &coins){
        if(indx == coins.size()) return amount == 0;

        int noPick = solve(indx + 1, amount, coins);
        int pick = 0;
        if(amount >= coins[indx]){
            pick = solve(indx, amount - coins[indx], coins);
        }

        return pick + noPick;
    }


public:
    int change(int amount, vector<int>& coins) {
        return solve(0, amount, coins);
    }
};

// 1. Recursive - try every coin for every amount
class WaysToMakeCoinChangeRecursive {
public:
    int solve(int amount, vector<int>& coins) {
        if (amount == 0) return 1;
        if (amount < 0) return 0;
        int res = 0;
        for (int coin : coins)
            if (amount >= coin)
                res += solve(amount - coin, coins);
        return res;
    }
    int change(vector<int>& coins, int amount) {
        return solve(amount, coins);
    }
};


// 2. Memoization (Top-down DP), pick/not pick
class Solution {
    private:
        int solve(int indx, int amount, vector<int> &coins, vector<vector<int>>&dp){
            if(indx == coins.size()) return amount == 0;
            if(dp[indx][amount] != -1) return dp[indx][amount];
    
            int noPick = solve(indx + 1, amount, coins, dp);
            int pick = 0;
            if(amount >= coins[indx]){
                pick = solve(indx, amount - coins[indx], coins, dp);
            }
    
            return dp[indx][amount] = pick + noPick;
        }
    
    public:
        int change(int amount, vector<int>& coins) {
            // dp[n][amount + 1];
            int n = coins.size();
            vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
            return solve(0, amount, coins, dp);
        }
    };

// 3. Tabulation (Bottom-up DP)
class WaysToMakeCoinChangeTabulation {
public:
    int change(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, 0)); // use 0 for init

        for(int i = 0; i < n; i++){
            for(int j = 0; j <= amount; j++){
                if(j == 0) 
                    dp[i][j] = 1;
                else if(i == 0) 
                    dp[i][j] = (j % coins[0] == 0 ? 1 : 0);
                else {
                    int notPick = dp[i - 1][j];
                    int pick = 0;
                    if(j >= coins[i]){
                        pick = dp[i][j - coins[i]];
                    }
                    dp[i][j] = pick + notPick;
                }
            }
        }

        return dp[n - 1][amount];
    }
};

// 4. Space Optimized (1D DP)
// 4. Space Optimized (1D DP)
class WaysToMakeCoinChangeSpaceOptimized {
public:
    int change(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < n; ++i) {
            // For each coin, we process j from coins[i] to amount
            for (int j = coins[i]; j <= amount; ++j) {
                dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount];
    }
};