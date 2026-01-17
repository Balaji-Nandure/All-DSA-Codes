#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Coin Change
LeetCode 322: https://leetcode.com/problems/coin-change/
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/minimum-number-of-coins/0

You are given an integer array coins representing coins of different denominations 
and an integer amount representing a total amount of money. Return the fewest number 
of coins that you need to make up that amount. If that amount of money cannot be made 
up by any combination of the coins, return -1.

Constraints:
- Each coin can be used unlimited times (unbounded knapsack variant)
- Find minimum number of coins needed
- Return -1 if impossible

Example:
coins = [1, 2, 5], amount = 11
Minimum coins: 5 + 5 + 1 = 3 coins
Answer = 3

DP State: dp[amount] = minimum number of coins needed to make amount
Recurrence:
dp[amount] = min(dp[amount], 1 + dp[amount - coin]) for each coin
- Try each coin: if amount >= coin, use 1 coin and solve for (amount - coin)

Base Cases:
- dp[0] = 0 (0 coins needed to make amount 0)
- dp[amount] = INF initially (impossible until proven otherwise)

Time Complexity: O(n * amount) where n is number of coin types
Space Complexity: O(amount) for DP array
*/

//  0 Pick not pick
class CoinChangeRecursivePickNotPick {
public:
int solve(int indx, int amount, vector<int>& coins) {
    // Base cases
    if (amount == 0) return 0;
    if (indx >= coins.size()) return INF;
    
    int pick = INF;
    if (amount >= coins[indx])
        pick = 1 + solve(indx, amount - coins[indx], coins);
    // Not pick: move to next coin type
    int notPick = solve(indx + 1, amount, coins);
    return min(pick, notPick);
}
int coinChange(vector<int>& coins, int amount) {
    int res = solve(0, amount, coins);
    return (res == INF) ? -1 : res;
}   
};

// 1. Recursive approach (take/not take method)
class CoinChangeRecursive {
public:
    int solve(int amount, vector<int>& coins) {
        if (amount == 0) return 0;
        if (amount < 0) return INF;
        int res = INF;
        for (int coin : coins)
            res = min(res, 1 + solve(amount - coin, coins));
        return res;
    }
    int coinChange(vector<int>& coins, int amount) {
        int ans = solve(amount, coins);
        return (ans == INF) ? -1 : ans;
    }
};


// 2. Memoization (Top-down DP)
class CoinChangeMemoizationPickNotPick {
public:
    int solve(int indx, int amount, vector<int>& coins, vector<vector<int>>& dp) {
        // Base cases
        if (amount == 0) return 0;
        if (indx >= coins.size()) return INF;
        if (dp[indx][amount] != -1) return dp[indx][amount];

        int pick = INF;
        if (amount >= coins[indx])
            pick = 1 + solve(indx, amount - coins[indx], coins, dp);
        // Not pick: move to next coin type
        int notPick = solve(indx + 1, amount, coins, dp);

        return dp[indx][amount] = min(pick, notPick);
    }
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        int res = solve(0, amount, coins, dp);
        return (res == INF) ? -1 : res;
    }
};

// 3. Tabulation (Bottom-up DP)
class CoinChangeTabulation {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, INF);
        dp[0] = 0;
        for (int coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                int notTake = dp[i];
                int take = INF;
                if (i - coin >= 0)
                    take = 1 + dp[i - coin];
                dp[i] = min(notTake, take);
            }
        }
        return (dp[amount] == INF) ? -1 : dp[amount];
    }
};