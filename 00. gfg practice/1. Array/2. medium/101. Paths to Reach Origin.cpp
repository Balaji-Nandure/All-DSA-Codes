/*
Problem: Paths to Reach Origin

GFG:
https://www.geeksforgeeks.org/problems/paths-to-reach-origin3850/1

LeetCode Similar:
https://leetcode.com/problems/unique-paths/

Example:
Input:
x = 3, y = 2

Possible moves:
Only LEFT or DOWN

From (3,2) to (0,0)

Total paths = 10

---------------------------------------------------

Intuition / Approach:

At every point (i,j),
we have only 2 choices:

1. Move LEFT  -> (i-1, j)
2. Move DOWN  -> (i, j-1)

So,

ways(i,j) =
ways(i-1,j) + ways(i,j-1)

Base Case:
If we are on first row or first column,
there is only ONE possible path.

This is a classic GRID DP problem.

Pattern:
Grid DP / Unique Paths

---------------------------------------------------

Why DP Works?

Many states repeat again and again.

Example:
ways(3,3) needs ways(2,3)
ways(4,3) also needs ways(2,3)

So memoization/tabulation avoids recomputation.

---------------------------------------------------

Time Complexity: O(x * y)

Space Complexity: O(x * y)

---------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class RecursionSolution {
public:

    static const int MOD = 1e9 + 7;

    // TC: Exponential
    // SC: O(x+y)

    int solve(int x, int y) {

        // Reached origin
        if(x == 0 || y == 0)
            return 1;

        long long left = solve(x - 1, y);

        long long down = solve(x, y - 1);

        return (left + down) % MOD;
    }
};

class MemoizationSolution {
public:

    static const int MOD = 1e9 + 7;

    // TC: O(x*y)
    // SC: O(x*y) + recursion stack

    int solve(int x, int y, vector<vector<int>>& dp) {

        // Base case
        if(x == 0 || y == 0)
            return 1;

        // Already computed
        if(dp[x][y] != -1)
            return dp[x][y];

        long long left = solve(x - 1, y, dp);

        long long down = solve(x, y - 1, dp);

        return dp[x][y] = (left + down) % MOD;
    }

    int ways(int x, int y) {

        vector<vector<int>> dp(x + 1,
                               vector<int>(y + 1, -1));

        return solve(x, y, dp);
    }
};

class TabulationSolution {
public:

    static const int MOD = 1e9 + 7;

    // TC: O(x*y)
    // SC: O(x*y)

    int ways(int x, int y) {

        vector<vector<int>> dp(x + 1,
                               vector<int>(y + 1, 0));

        // First row = 1
        for(int j = 0; j <= y; j++) {
            dp[0][j] = 1;
        }

        // First column = 1
        for(int i = 0; i <= x; i++) {
            dp[i][0] = 1;
        }

        // Fill remaining cells
        for(int i = 1; i <= x; i++) {

            for(int j = 1; j <= y; j++) {

                dp[i][j] =
                (dp[i-1][j] + dp[i][j-1]) % MOD;
            }
        }

        return dp[x][y];
    }
};

class SpaceOptimizationSolution {
public:

    static const int MOD = 1e9 + 7;

    // TC: O(x*y)
    // SC: O(y)

    int ways(int x, int y) {

        vector<int> prev(y + 1, 1);

        for(int i = 1; i <= x; i++) {

            vector<int> curr(y + 1, 1);

            for(int j = 1; j <= y; j++) {

                curr[j] =
                (prev[j] + curr[j-1]) % MOD;
            }

            prev = curr;
        }

        return prev[y];
    }
};

/*
Online Judge Solution
Using Best Optimized Approach
*/

class Solution {
public:
    static const int MOD = 1e9 + 7;

    int ways(int x, int y) {
        vector<int> dp(y + 1, 1);         // dp[j] = ways for current i, column j
        for (int i = 1; i <= x; ++i) {
            for (int j = 1; j <= y; ++j) {
                dp[j] = (dp[j] + dp[j - 1]) % MOD;
            }
        }
        return dp[y];
    }
};

/*
Dry Run:

x = 2
y = 2

Initial:
1 1 1

After row 1:
1 2 3

After row 2:
1 3 6

Answer = 6

---------------------------------------------------

Common Mistakes:
1. Forgetting modulo
2. Wrong base case
3. Using x*y instead of (x+1)*(y+1)
4. Confusing moves direction

---------------------------------------------------

Reusable Pattern:

Whenever:
- Grid
- 2 directions
- Count paths

Think:
dp[i][j] =
dp[from top] + dp[from left]

---------------------------------------------------
*/


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    GRID + COUNT PATHS

Think immediately:
    DP[i][j] = DP[i-1][j] + DP[i][j-1]

-----------------------------------------------------

KEY OBSERVATIONS:

1. Only 2 directions allowed: LEFT and DOWN
2. Base case: first row/first column = 1 path
3. Standard unique paths problem

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting modulo operation
2. Wrong base case initialization
3. Using x*y instead of (x+1)*(y+1) for DP size
4. Confusing move directions

-----------------------------------------------------

SIMILAR PROBLEMS

- Unique Paths
- Unique Paths II
- Grid Travel Problems
- Combinatorial Path Counting

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Grid
- 2 directions
- Count paths

Think:
dp[i][j] = dp[from top] + dp[from left]

-----------------------------------------------------
*/
