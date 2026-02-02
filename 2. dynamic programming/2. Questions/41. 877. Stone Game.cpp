/*
Problem: LeetCode 877 - Stone Game

Alice and Bob play a game with piles of stones. There are an even number of piles arranged in a row, 
and each pile has a positive integer number of stones piles[i].

The objective of the game is to end with the most stones. The total number of stones across all the piles is odd, 
so there are no ties.

Alice and Bob take turns, with Alice starting first. Each turn, a player takes the entire pile of stones either 
from the beginning or from the end of the row. This continues until there are no more piles left, at which point 
the person with the most stones wins.

Assuming Alice and Bob play optimally, return true if Alice wins the game, or false if Bob wins.

Example 1:
Input: piles = [5,3,4,5]
Output: true
Explanation: 
Alice starts first, and can only take the first 5 or the last 5.
Say she takes the first 5, so that the row becomes [3, 4, 5].
If Bob takes 3, then the row becomes [4, 5], and Alice takes 5 to win with 10 points to 8.
If Bob takes the last 5, then the row becomes [3, 4], and Alice takes 4 to win with 9 points to 8.
Thus, Alice always wins.

Example 2:
Input: piles = [3,7,2,3]
Output: true

Approach 1: Mathematical Observation (Optimal)
Key Insight:
- There are an even number of piles
- Alice goes first
- Alice can always choose to take all even-indexed piles OR all odd-indexed piles
- Since the total is odd, one of these groups must have more stones than the other
- Alice can force this strategy, so she always wins!

This is a trick question - Alice always wins regardless of the input!

Approach 2: Minimax with Memoization (Game Theory Solution)
For learning purposes, we'll also implement the general game theory solution.

Key Insight:
- Both players play optimally
- We calculate the maximum score difference the current player can achieve
- dp[i][j] = maximum score difference (current player - opponent) for piles[i..j]

State:
dp[i][j] = maximum advantage current player can get from piles[i..j]

Transition:
At range [i, j], current player can take either piles[i] or piles[j]
- Take left: piles[i] - dp[i+1][j] (opponent plays optimally on remaining)
- Take right: piles[j] - dp[i][j-1] (opponent plays optimally on remaining)
Choose the maximum of these two options.

Base case:
If i == j, return piles[i] (only one pile left, take it)

LeetCode:
https://leetcode.com/problems/stone-game/

Time Complexity:
Approach 1: O(1)
Approach 2: O(n^2) where n is the number of piles

Space Complexity:
Approach 1: O(1)
Approach 2: O(n^2) for dp array
*/

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Mathematical Observation - Alice Always Wins!
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        // Alice always wins because:
        // 1. There are an even number of piles
        // 2. Alice goes first
        // 3. Alice can choose to take all even-indexed or all odd-indexed piles
        // 4. Since total is odd, one group has more stones
        // 5. Alice can force the winning strategy
        return true;
    }
};

// Time Complexity: O(1)
// Space Complexity: O(1)


/*
Approach 2: Minimax with Memoization (Top-Down DP)
This is the general game theory solution that works for any stone game variant.

Striver's DP Pattern:
1. Express everything in terms of (i, j) - the range of piles
2. Explore all possibilities - take left or take right
3. Take the maximum - maximize score difference
*/

class Solution2 {
public:
    int solve(int i, int j, vector<int>& piles, vector<vector<int>>& dp) {
        if (i > j) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        int takeLeft = piles[i] - solve(i + 1, j, piles, dp);
        int takeRight = piles[j] - solve(i, j - 1, piles, dp);
        return dp[i][j] = max(takeLeft, takeRight);
    }

    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        int ans = solve(0, n - 1, piles, dp);
        return ans > 0;
    }
};


class Solution3 {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        // dp[i][j] = in array i to j, the score diff of alice and bob.
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int takeLeft = piles[i] - dp[i + 1][j];
                int takeRight = piles[j] - dp[i][j - 1];
                dp[i][j] = max(takeLeft, takeRight);
            }
        }

        return dp[0][n - 1] > 0;

    }
}

// Time Complexity: O(n^2)
// Space Complexity: O(n^2)
