/*
PROBLEM: Dice Throw

Given:
- n dice
- each dice has faces from 1 to m

Find number of ways to get sum x.

-----------------------------------------------------

STATE:

dp[dice][target]

Meaning:
Number of ways to form:
    target
using:
    dice dice

-----------------------------------------------------

RECURRENCE:

Try every face:

ways += solve(
            dice - 1,
            target - face
        )

-----------------------------------------------------

BASE CASES:

1. dice == 0 && target == 0
        return 1

2. dice == 0 || target < 0
        return 0

-----------------------------------------------------
*/


/*
=====================================================
1. RECURSION
=====================================================

TC: Exponential
SC: O(n)

🔥 PURE RECURSION APPROACH
- Simple but very slow
- Exponential due to repeated states
- Good for understanding the problem

🧠 LOGIC:
1. Base case: If no dice left and target = 0, we found a valid way
2. Invalid case: If no dice left but target > 0, impossible
3. Recursive case: Try every face value (1 to m) and reduce problem

⚠️ PERFORMANCE ISSUE:
Same subproblems solved multiple times
Example: solve(6,2,8) called many times from different paths
*/

class RecursionSolution {
public:

    long long solve(int m, int n, int x) {
        
        // Perfect sum formed using exactly n dice
        if (n == 0 && x == 0) {
            return 1;
        }
        
        // Invalid state: No dice left but still need to reach target
        if (n == 0 || x < 0) {
            return 0;
        }
        
        long long ways = 0;
        
        // Try every possible face value (1 to m)
        for (int face = 1; face <= m; face++) {
            
            // Reduce problem: use one die, reduce target by face value
            ways += solve(
                m,           // same number of faces
                n - 1,        // one less die available
                x - face        // reduce target by current face value
            );
        }
        
        return ways;
    }

    long long noOfWays(int m, int n, int x) {
        return solve(m, n, x);
    }
};



/*
=====================================================
2. MEMOIZATION
=====================================================

TC: O(n * x * m)
SC: O(n * x) + recursion stack
*/

class MemoizationSolution {
public:

    long long solve(
        int m,
        int n,
        int x,
        vector<vector<long long>>& dp
    ) {
        
        // Perfect sum formed
        if (n == 0 && x == 0) {
            return 1;
        }
        
        // Invalid state
        if (n == 0 || x < 0) {
            return 0;
        }
        
        // Already computed
        if (dp[n][x] != -1) {
            return dp[n][x];
        }
        
        long long ways = 0;
        
        // Try every face
        for (int face = 1; face <= m; face++) {
            
            ways += solve(
                m,
                n - 1,
                x - face,
                dp
            );
        }
        
        return dp[n][x] = ways;
    }

    long long noOfWays(int m, int n, int x) {
        
        vector<vector<long long>> dp(
            n + 1,
            vector<long long>(x + 1, -1)
        );
        
        return solve(m, n, x, dp);
    }
};



/*
=====================================================
3. TABULATION
=====================================================

TC: O(n * x * m)
SC: O(n * x)
*/

class TabulationSolution {
public:

    long long noOfWays(int m, int n, int x) {
        
        vector<vector<long long>> dp(
            n + 1,
            vector<long long>(x + 1, 0)
        );
        
        // Base case
        dp[0][0] = 1;
        
        for (int dice = 1; dice <= n; dice++) {
            
            for (int target = 1; target <= x; target++) {
                
                long long ways = 0;
                
                // Try every face
                for (int face = 1; face <= m; face++) {
                    
                    if (target - face >= 0) {
                        
                        ways += dp[dice - 1][target - face];
                    }
                }
                
                dp[dice][target] = ways;
            }
        }
        
        return dp[n][x];
    }
};



/*
=====================================================
4. SPACE OPTIMIZATION
=====================================================

TC: O(n * x * m)
SC: O(x)
*/

class SpaceOptimizationSolution {
public:

    long long noOfWays(int m, int n, int x) {
        
        vector<long long> prev(x + 1, 0);
        
        // Base case
        prev[0] = 1;
        
        for (int dice = 1; dice <= n; dice++) {
            
            vector<long long> curr(x + 1, 0);
            
            for (int target = 1; target <= x; target++) {
                
                long long ways = 0;
                
                // Try every face
                for (int face = 1; face <= m; face++) {
                    
                    if (target - face >= 0) {
                        
                        ways += prev[target - face];
                    }
                }
                
                curr[target] = ways;
            }
            
            prev = curr;
        }
        
        return prev[x];
    }
};



/*
=====================================================
FINAL GFG CLASS
=====================================================

Return MOST OPTIMIZED solution.
*/

class Solution {
public:

    long long noOfWays(int m, int n, int x) {
        
        SpaceOptimizationSolution obj;
        
        return obj.noOfWays(m, n, x);
    }
};


/*
-----------------------------------------------------

🧠 STRIVER DP FLOW

Recursion
    ↓
Memoization
    ↓
Tabulation
    ↓
Space Optimization

-----------------------------------------------------

PATTERN:
Count Ways DP

-----------------------------------------------------
*/
