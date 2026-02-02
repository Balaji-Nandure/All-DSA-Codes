/*
Problem:
2218. Maximum Value of K Coins From Piles

Approach:
Recursion + Memoization

State:
solve(i, k) = maximum value from piles[i..] using k coins

Transition:
Try taking x coins from pile i (x = 0 to min(pile[i].size(), k))
Add prefix sum of x coins + solve(i+1, k-x)

LeetCode:
https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/

Time Complexity:
O(n * k * avg_pile_size)

Space Complexity:
O(n * k)
*/
#include <bits/stdc++.h>
using namespace std;

int solve(int i,
          int k,
          vector<vector<int>>& piles,
          vector<vector<int>>& dp) {

    // Base cases
    if (i == piles.size() || k == 0)
        return 0;

    if (dp[i][k] != -1)
        return dp[i][k];

    int ans = solve(i + 1, k, piles, dp);  // take 0 coins

    int currSum = 0;
    int limit = min((int)piles[i].size(), k);

    for (int x = 1; x <= limit; x++) {
        currSum += piles[i][x - 1];   // prefix sum
        ans = max(ans, currSum + solve(i + 1, k - x, piles, dp));
    }

    return dp[i][k] = ans;
}

int maxValueOfCoins(vector<vector<int>>& piles, int k) {

    int n = piles.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));

    return solve(0, k, piles, dp);
}