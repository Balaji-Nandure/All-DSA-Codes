
/*
Problem:
1140. Stone Game II

Description:
Alice and Bob continue their games with piles of stones. There are a number of piles arranged in a row, 
and each pile has a positive integer number of stones piles[i]. The objective of the game is to end with 
the most stones.

Alice and Bob take turns, with Alice starting first. Initially, M = 1.

On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M. 
Then, we set M = max(M, X).

The game continues until all the stones have been taken.

Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.

Example 1:
Input: piles = [2,7,9,4,4]
Output: 10
Explanation: If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. 
Alice can get 2 + 4 + 4 = 10 piles in total. If Alice takes two piles at the beginning, then Bob can take 
all three piles left. In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger.

Example 2:
Input: piles = [1,2,3,4,5,100]
Output: 104

Approach:
Minimax with Memoization (Top-Down DP)

Key Insight:
- Both players play optimally
- Alice wants to maximize her stones
- Bob wants to minimize Alice's stones (maximize his own)
- We need to think from the perspective of the current player

State:
dp[i][M] = maximum stones the current player can get from piles[i..n-1] with parameter M

Transition:
At position i with parameter M, the current player can take X piles where 1 <= X <= 2M
For each choice X:
- Current player gets: sum of piles[i..i+X-1]
- Opponent gets: dp[i+X][max(M, X)] stones from remaining piles
- Since total remaining stones = suffix_sum[i], current player gets:
  suffix_sum[i] - dp[i+X][max(M, X)]

We want to maximize this value over all valid X.

Base case:
If i >= n, return 0 (no more piles)
If i + 2*M >= n, take all remaining piles (suffix_sum[i])

LeetCode:
https://leetcode.com/problems/stone-game-ii/

Time Complexity:
O(n^3) where n is the number of piles (n states × n choices per state)

Space Complexity:
O(n^2) for dp array and recursion stack
*/

#include <bits/stdc++.h>
using namespace std;
class Solution {
private:
    // Recursive function to calculate maximum stones current player can get
    // i: current position in piles array
    // M: current M parameter (can take up to 2*M piles)
    // piles: array of stone piles
    // dp: memoization table
    int solve(int i, int M, vector<int>& piles, vector<vector<int>>& dp) {
        int n = piles.size();
        
        // Base case: no more piles left to take
        if (i >= n) {
            return 0;
        }
        
        // Check if we've already computed this state
        if (dp[i][M] != -1) {
            return dp[i][M];
        }
        
        // Track the maximum stones we can get from this state
        int max_stones = 0;
        
        // Track cumulative sum of piles we're taking in current move
        int current_sum = 0;
        
        // Try taking X piles where 1 <= X <= 2M
        // This represents all valid moves the current player can make
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {
            // Add the X-th pile to our current move's sum
            current_sum += piles[i + X - 1];
            
            // Recursively calculate what happens after this move
            // The opponent plays next from position i+X with updated M = max(M, X)
            // The opponent will try to maximize their stones, which minimizes ours
            int remaining = solve(i + X, max(M, X), piles, dp);
            
            // Total stones current player gets = stones from current move + stones from future moves
            // Note: 'remaining' represents the best the opponent can do from the remaining piles
            // Since we're using a minimax approach, we need to calculate total remaining stones
            // and subtract what opponent gets to find what we get in future turns
            int current_stones = current_sum + remaining;
            
            // Choose the move that maximizes our stones
            max_stones = max(max_stones, current_stones);
        }
        
        // Memoize and return the result
        return dp[i][M] = max_stones;
    }
    
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        
        // Initialize DP table with -1 (uncomputed state)
        // dp[i][M] = max stones current player can get from piles[i..n-1] with parameter M
        // M can range from 1 to n in worst case, so we use n+1 size for safety
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        
        // Start the game: Alice begins at position 0 with M = 1
        return solve(0, 1, piles, dp);
    }
};

// Time Complexity: O(n^3)
// Space Complexity: O(n^2)
