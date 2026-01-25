/*
Problem:
Given an array of coin denominations and an amount,
return the minimum number of coins needed to make that amount.
Return -1 if it is not possible.

Approach:
- At each step, try taking one coin and reduce amount.
- Take minimum over all choices.
- Use memoization to avoid recomputation.

Time Complexity: O(n * amount)
Space Complexity: O(amount) recursion + dp
*/

class Solution {
public:
    int solve(int amount, vector<int> &coins, vector<int> &dp) {
        // Base case: exact amount formed
        if (amount == 0)
            return 0;

        // Base case: invalid (over-used coins)
        if (amount < 0)
            return 1e9;   // large number representing impossible

        // Memoization check
        if (dp[amount] != -1)
            return dp[amount];

        int mini = 1e9;

        // Try every coin
        for (int coin : coins) {
            int res = solve(amount - coin, coins, dp);

            // If subproblem is solvable, update minimum
            if (res != 1e9)
                mini = min(mini, 1 + res);
        }

        return dp[amount] = mini;
    }

    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);

        int ans = solve(amount, coins, dp);

        // If still infinite, return -1
        return (ans >= 1e9) ? -1 : ans;
    }
};

/*
dp[x] = minimum number of coins required to make amount x

Transition:
dp[x] = min(dp[x], 1 + dp[x - coin])

Initialization:
dp[0] = 0      (0 coins to make amount 0)
All others = INF

Answer:
dp[amount]
*/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        const int INF = 1e9;

        // dp[i] = min coins needed to make amount i
        vector<int> dp(amount + 1, INF);

        // Base case
        dp[0] = 0;

        // Build answer bottom-up
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0 && dp[i - coin] != INF) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }

        return (dp[amount] == INF) ? -1 : dp[amount];
    }
};
