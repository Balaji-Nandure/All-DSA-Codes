/*
    LeetCode 790. Domino and Tromino Tiling
    
    Problem: You have two types of tiles: a 2x1 domino shape and a tromino shape (L-shaped).
    You may rotate these shapes. Given an integer n, return the number of ways to tile 
    a 2 x n board. The answer should be returned modulo 10^9 + 7.
    
    Domino: XX    or    X
                        X
    
    Tromino: XX   or   XX   or   X    or    X
             X          X        XX         XX
    
    Example 1:
    Input: n = 3
    Output: 5
    Explanation: The five different ways are:
    1. XXX (3 vertical dominoes)
    2. Three horizontal dominoes
    3-5. Various combinations with trominos
    
    Example 2:
    Input: n = 1
    Output: 1
*/


#include <vector>
using namespace std;

class Solution {
public:
    int numTilings(int n) {
        const int MOD = 1e9 + 7;

        if (n == 1) return 1;
        if (n == 2) return 2;
        if (n == 3) return 5;
        
        vector<long long> dp(n + 1);
        
        // Base cases
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;
        
        // Apply the formula: dp[n] = 2 * dp[n-1] + dp[n-3]
        for (int i = 4; i <= n; i++) {
            dp[i] = (2 * dp[i-1] % MOD + dp[i-3]) % MOD;
        }
        
        return dp[n];
    }
};

/*
    Time Complexity: O(n)
    Space Complexity: O(n)
    
    Approach:
    - Use the recurrence formula: dp[n] = 2 * dp[n-1] + dp[n-3]
    - This formula captures all possible ways to tile a 2 x n board
    - Base cases: dp[1] = 1, dp[2] = 2, dp[3] = 5
    
    The formula works because:
    - 2 * dp[n-1]: represents adding tiles to the previous state in two ways
    - dp[n-3]: accounts for the tromino patterns that span 3 columns
    
    This is a simplified approach compared to tracking partial states explicitly.
*/



















