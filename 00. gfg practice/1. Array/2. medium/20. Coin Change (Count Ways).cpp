/*
Problem: Coin Change (Count Ways)

GFG: https://www.geeksforgeeks.org/coin-change-dp-7/

Description: Given an integer array coins[ ] representing different denominations of currency and an integer sum, find the number of ways you can make sum by using different combinations from coins[ ]. 
Note: Assume that you have an infinite supply of each type of coin. Therefore, you can use any coin as many times as you want.
Answers are guaranteed to fit into a 32-bit integer.

Examples:

Input: coins[] = [1, 2, 3], sum = 4
Output: 4
Explanation: Four Possible ways are: [1, 1, 1, 1], [1, 1, 2], [2, 2], [1, 3].
Input: coins[] = [2, 5, 3, 6], sum = 10
Output: 5
Explanation: Five Possible ways are: [2, 2, 2, 2, 2], [2, 2, 3, 3], [2, 2, 6], [2, 3, 5] and [5, 5].
Input: coins[] = [5, 10], sum = 3
Output: 0
Explanation: Since all coin denominations are greater than sum, no combination can make the target sum.

Constraints:
1 <= sum <= 103
1 <= coins[i] <= 104
1 <= coins.size() <= 103

Striver DP Intuition (Pick / Not Pick):

This is Unbounded Knapsack pattern.

At index i, we have two choices:
1. Pick coin[i]  → stay at same index (infinite supply)
2. Not Pick      → move to next index

Recurrence:
f(i, sum) = f(i, sum - coins[i]) + f(i+1, sum)

Base Cases:
If sum == 0 → return 1
If i == n → return 0

DP Tabulation:

dp[i][s] = number of ways using first i coins to make sum s

Transition:
dp[i][s] =
    dp[i][s - coin]   (pick)
  + dp[i-1][s]        (not pick)

Space Optimization → 1D DP

Pattern:
Unbounded Knapsack (Count Ways)

Time Complexity: O(n * sum)
Space Complexity: O(sum)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int count(vector<int>& coins, int sum) {
        int n = coins.size();

        // dp[s] = number of ways to make sum s
        vector<int> dp(sum + 1, 0);

        // Base case: 1 way to make sum 0
        dp[0] = 1;

        // For each coin
        for(int i = 0; i < n; i++) {
            // For each sum
            for(int s = coins[i]; s <= sum; s++) {
                dp[s] = dp[s] + dp[s - coins[i]];
            }
        }

        return dp[sum];
    }
};

/*
Final Summary (Interview Revision):

This is Unbounded Knapsack (Count Ways).

DP Meaning:
dp[s] = number of ways to make sum s

Transition:
dp[s] += dp[s - coin]

Base Case:
dp[0] = 1

IMPORTANT Loop Order:
for coin
    for sum
This gives COMBINATIONS.

If reversed:
for sum
    for coin
This gives PERMUTATIONS.

Memory Trick:
Coin outside → Combination
Sum outside → Permutation
*/
