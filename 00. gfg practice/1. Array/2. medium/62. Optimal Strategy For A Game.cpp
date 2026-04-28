/*
PROBLEM: Optimal Strategy For A Game
------------------------------------------------
Given:
- arr[] of size n representing coin values
- Two players alternate turns, each can pick first or last coin
- Both players play optimally
- You go first

Return:
- Maximum amount of money you can win

Example:
arr[] = [5, 3, 7, 10] → Output: 15
Explanation: You pick 5, opponent picks 3 (or 10), you pick 10 → total = 15

arr[] = [8, 15, 3, 7] → Output: 22  
Explanation: You pick 7, opponent picks 8, you pick 15 → total = 22

Constraints:
2 ≤ n ≤ 10^3
1 ≤ arr[i] ≤ 10^6

------------------------------------------------
INTUITION / APPROACH:
------------------------------------------------
Pattern: Game Theory + Dynamic Programming

Key Insight:
- When it's your turn, you choose max(arr[i] + min(solve(i+2,j), solve(i+1,j-1)),
                              arr[j] + min(solve(i+1,j-1), solve(i,j-2)))
- Why min? Because opponent plays optimally and will leave you with minimum

DP State:
dp[i][j] = maximum value you can collect from subarray arr[i..j]
When you pick arr[i]: opponent will pick optimally from arr[i+1..j]
- If opponent picks arr[i+1], you get dp[i+2][j]
- If opponent picks arr[j], you get dp[i+1][j-1]
- Opponent leaves you with min(dp[i+2][j], dp[i+1][j-1])

Similarly for picking arr[j]:
- Opponent leaves you with min(dp[i+1][j-1], dp[i][j-2])

Transition:
dp[i][j] = max(arr[i] + min(dp[i+2][j], dp[i+1][j-1]),
                arr[j] + min(dp[i+1][j-1], dp[i][j-2]))

Base Cases:
dp[i][i] = arr[i] (single coin)
dp[i][i+1] = max(arr[i], arr[i+1]) (two coins)

------------------------------------------------
TIME COMPLEXITY:
O(n²) - fill DP table of size n×n

SPACE COMPLEXITY:
O(n²) for DP table
O(n) with space optimization

------------------------------------------------
GFG LINK:
https://www.geeksforgeeks.org/problems/optimal-strategy-for-a-game/1

Related:
- Game Theory problems
- DP on intervals/subarrays
- Predict the Winner (LeetCode)

------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ---------------- MEMOIZATION ----------------
    // TC: O(n²)  SC: O(n²) + recursion stack
    int solveMemo(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
        
        // Base cases
        if(i > j) return 0;
        if(i == j) return arr[i];
        if(j == i + 1) return max(arr[i], arr[j]);
        
        if(dp[i][j] != -1) return dp[i][j];
        
        // If I pick arr[i], opponent will play optimally
        int pick_i = arr[i] + min(
            solveMemo(i + 2, j, arr, dp),    // opponent picks arr[i+1]
            solveMemo(i + 1, j - 1, arr, dp) // opponent picks arr[j]
        );
        
        // If I pick arr[j], opponent will play optimally  
        int pick_j = arr[j] + min(
            solveMemo(i + 1, j - 1, arr, dp), // opponent picks arr[i]
            solveMemo(i, j - 2, arr, dp)      // opponent picks arr[j-1]
        );
        
        return dp[i][j] = max(pick_i, pick_j);
    }


    // ---------------- TABULATION ----------------
    // TC: O(n²)  SC: O(n²)
    int solveTab(vector<int>& arr) {
        
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Base case: single coin
        for(int i = 0; i < n; i++) {
            dp[i][i] = arr[i];
        }
        
        // Base case: two coins
        for(int i = 0; i < n - 1; i++) {
            dp[i][i + 1] = max(arr[i], arr[i + 1]);
        }
        
        // Fill DP table for subarrays of length >= 3
        for(int length = 3; length <= n; length++) {
            for(int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                
                // If I pick arr[i]
                int pick_i = arr[i] + min(dp[i + 2][j], dp[i + 1][j - 1]);
                
                // If I pick arr[j]
                int pick_j = arr[j] + min(dp[i + 1][j - 1], dp[i][j - 2]);
                
                dp[i][j] = max(pick_i, pick_j);
            }
        }
        
        return dp[0][n - 1];
    }


    // ---------------- SPACE OPTIMIZED ----------------
    // TC: O(n²)  SC: O(n)
    int solveSpace(vector<int>& arr) {
        
        int n = arr.size();
        vector<int> dp(n);
        
        // dp[i] will store result for subarray starting at i
        for(int i = 0; i < n; i++) {
            dp[i] = arr[i];
        }
        
        // Iterate for different subarray lengths
        for(int length = 2; length <= n; length++) {
            for(int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                
                if(length == 2) {
                    dp[i] = max(arr[i], arr[j]);
                } else {
                    // Need previous values, so store them first
                    int a = (i + 2 <= j) ? dp[i + 2] : 0;
                    int b = dp[i + 1];
                    int c = (i <= j - 2) ? dp[i] : 0;
                    
                    int pick_i = arr[i] + min(a, b);
                    int pick_j = arr[j] + min(b, c);
                    
                    dp[i] = max(pick_i, pick_j);
                }
            }
        }
        
        return dp[0];
    }


    // ---------------- MAIN FUNCTION ----------------
    int maximumAmount(vector<int>& arr) {
        
        int n = arr.size();
        
        // Edge case: empty array
        if(n == 0) return 0;
        
        // --------- CHOOSE ONE ---------
        
        // 1) Memoization
        // vector<vector<int>> dp(n, vector<int>(n, -1));
        // return solveMemo(0, n - 1, arr, dp);
        
        // 2) Tabulation (Recommended)
        return solveTab(arr);
        
        // 3) Space Optimized
        // return solveSpace(arr);
    }
};

/*
ALGORITHM SUMMARY:
--------------------------------
1. dp[i][j] = max value you can collect from arr[i..j]
2. If you pick arr[i]: opponent leaves min(dp[i+2][j], dp[i+1][j-1])
3. If you pick arr[j]: opponent leaves min(dp[i+1][j-1], dp[i][j-2])
4. dp[i][j] = max(arr[i] + min(...), arr[j] + min(...))
5. Answer: dp[0][n-1]

Key Insights:
- Both players play optimally → opponent minimizes your gain
- Game theory: think one step ahead (consider opponent's response)
- DP on intervals: smaller subarrays help solve larger ones
- Why min? Opponent will choose move that gives you minimum

Interview Tips:
- Explain why opponent's optimal play leads to min()
- Show the recursion tree for small examples
- Mention this is a classic game theory DP problem
- Compare with simpler "pick from ends" problems

Game Theory Intuition:
- You maximize your gain assuming opponent minimizes it
- This is a zero-sum game with perfect information
- Each player has complete knowledge of the game state

------------------------------------------------
TEST CASES:
--------------------------------
1. arr = [5,3,7,10] → 15 (pick 5, then 10)
2. arr = [8,15,3,7] → 22 (pick 7, then 15)
3. arr = [20,30,2,2,2,10] → 42
4. arr = [5,5,5,5,5] → 15 (you get 3 out of 5 coins)
5. arr = [100,1,1,100] → 101 (pick 100, opponent picks 1, you pick 100)
6. arr = [1,2,3,4,5,6] → 12
7. arr = [6,5,4,3,2,1] → 12
8. arr = [8,15,3,7,10,5] → 27

Edge Cases:
- n=2: max of two coins
- All coins same: you get ceil(n/2) coins
- Increasing/Decreasing sequence
- Large values

------------------------------------------------
*/
