/*
Problem: LeetCode 1406 - Stone Game III

Alice and Bob continue their games with piles of stones. There are several stones arranged in a row, 
and each stone has an associated value which is an integer given in the array stoneValue.

Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2, 
or 3 stones from the first remaining stones in the row.

The score of each player is the sum of the values of the stones taken. The score of each player is 0 initially.

The objective of the game is to end with the highest score, and the winner is the player with the highest score 
and there could be a tie. The game continues until all the stones have been taken.

Assume Alice and Bob play optimally.

Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they will end the game with the same score.

Example 1:
Input: stoneValue = [1,2,3,7]
Output: "Bob"
Explanation: Alice will always lose. Her best move will be to take three piles and the score become 6. 
Now the score of Bob is 7 and Bob wins.

Example 2:
Input: stoneValue = [1,2,3,-9]
Output: "Alice"
Explanation: Alice must choose all the three piles at the first move to win and leave Bob with negative score.
If Alice chooses one pile her score will be 1 and the next move Bob's score becomes 5. In the next move, 
Alice will take the pile with value = -9 and lose.
If Alice chooses two piles her score will be 3 and the next move Bob's score becomes 3. In the next move, 
Alice will take the pile with value = -9 and also lose.
Remember that both play optimally so here Alice will choose the scenario that makes her win.

Example 3:
Input: stoneValue = [1,2,3,6]
Output: "Tie"

Approach:
Minimax with Memoization (Top-Down DP)

Key Insight:
- Both players play optimally
- We need to calculate the maximum score difference the current player can achieve
- dp[i] = maximum score difference (current player - opponent) from position i onwards
- The current player wants to maximize their advantage over the opponent

State:
dp[i] = maximum score difference the current player can get from stoneValue[i..n-1]

Transition:
At position i, the current player can take 1, 2, or 3 stones
For each choice X (1, 2, or 3):
- Current player gets: sum of stoneValue[i..i+X-1]
- The score difference from remaining stones: -dp[i+X] (negative because opponent plays next)
- Total difference: sum(stoneValue[i..i+X-1]) - dp[i+X]

We want to maximize this value over all valid X.

Base case:
If i >= n, return 0 (no more stones)

LeetCode:
https://leetcode.com/problems/stone-game-iii/

Time Complexity:
O(n) where n is the number of stones (n states × 3 choices per state)

Space Complexity:
O(n) for dp array and recursion stack
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Recursive function to calculate maximum score difference current player can achieve
    // i: current position in stoneValue array
    // stoneValue: array of stone values
    // dp: memoization table
    int solve(int i, vector<int>& stoneValue, vector<int>& dp) {
        int n = stoneValue.size();
        
        // Base case: no more stones left to take
        if (i >= n) {
            return 0;
        }
        
        // Check if we've already computed this state
        if (dp[i] != INT_MIN) {
            return dp[i];
        }
        
        // Track the maximum score difference we can achieve from this state
        int max_diff = INT_MIN;
        
        // Track cumulative sum of stones we're taking in current move
        int current_sum = 0;
        
        // Try taking X stones where 1 <= X <= 3
        // This represents all valid moves the current player can make
        for (int X = 1; X <= 3 && i + X <= n; X++) {
            // Add the X-th stone to our current move's sum
            current_sum += stoneValue[i + X - 1];
            
            // Recursively calculate what happens after this move
            // The opponent plays next from position i+X
            // dp[i+X] represents the best score difference the opponent can achieve
            // Since it's the opponent's turn, we subtract it (they gain, we lose relatively)
            int future_diff = solve(i + X, stoneValue, dp);
            
            // Total score difference = stones we get now - opponent's advantage from remaining stones
            int current_diff = current_sum - future_diff;
            
            // Choose the move that maximizes our score difference
            max_diff = max(max_diff, current_diff);
        }
        
        // Memoize and return the result
        return dp[i] = max_diff;
    }
    
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // Initialize DP table with INT_MIN (uncomputed state)
        // dp[i] = max score difference current player can get from stoneValue[i..n-1]
        vector<int> dp(n, INT_MIN);
        
        // Start the game: Alice begins at position 0
        // The result is the score difference (Alice - Bob)
        int score_diff = solve(0, stoneValue, dp);
        
        // Determine the winner based on score difference
        if (score_diff > 0) {
            return "Alice";
        } else if (score_diff < 0) {
            return "Bob";
        } else {
            return "Tie";
        }
    }
};

// Time Complexity: O(n)
// Space Complexity: O(n)



/*
Bottom-Up DP Approach (Tabulation)

This approach is easier to understand than the recursive version.
We build the solution from the end of the array backwards to the beginning.

Key Insight:
- dp[i] = maximum score difference (current player - opponent) starting from position i
- At position i, the current player can take 1, 2, or 3 stones
- After taking X stones, the opponent plays optimally from position i+X
- The opponent's advantage becomes our disadvantage, so we subtract it

Building from the end:
- At the last position, we can only take remaining stones (no opponent moves after)
- Moving backwards, we know the optimal play for all future positions
- This makes it easier to understand than thinking recursively

Example walkthrough with [1,2,3,7]:
Position 3 (last): Take 7, opponent gets 0, diff = 7 - 0 = 7
Position 2: Take 3, opponent gets 7, diff = 3 - 7 = -4
            OR take 3+7=10, opponent gets 0, diff = 10 - 0 = 10 (better!)
Position 1: Try all options and pick best
Position 0: Try all options and pick best
*/

class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        
        // dp[i] = max score difference current player can achieve from position i onwards
        // Initialize with very negative value (worse than any possible game outcome)
        vector<int> dp(n + 3, INT_MIN);
        
        // Base case: beyond the array, no stones to take, difference is 0
        dp[n] = 0;
        dp[n + 1] = 0;
        dp[n + 2] = 0;
        
        // Build solution from right to left (from end of array to beginning)
        for (int i = n - 1; i >= 0; i--) {
            int current_sum = 0;
            
            // Try taking 1, 2, or 3 stones from position i
            for (int X = 1; X <= 3 && i + X <= n; X++) {
                // Add the value of the X-th stone we're taking
                current_sum += stoneValue[i + X - 1];
                
                // After we take X stones, opponent plays from position i+X
                // dp[i+X] = opponent's best score difference from that position
                // Our score difference = what we get now - opponent's advantage later
                int current_diff = current_sum - dp[i + X];
                
                // Keep the best option (maximum score difference)
                dp[i] = max(dp[i], current_diff);
            }
        }
        
        // dp[0] is Alice's score difference when starting from position 0
        // Positive means Alice wins, negative means Bob wins, zero means tie
        if (dp[0] > 0) {
            return "Alice";
        } else if (dp[0] < 0) {
            return "Bob";
        } else {
            return "Tie";
        }
    }
};

// Time Complexity: O(n) - single pass through array, constant work per position
// Space Complexity: O(n) - dp array