/*
GeeksforGeeks: Interleaved Strings
Difficulty: Medium

Problem:
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
Interleaving requires maintaining the relative order of characters from s1 and s2.
Also, the length of s3 must be equal to s1.length() + s2.length().

Examples:
Input: s1 = "AAB", s2 = "AAC", s3 = "AAAABC"
Output: true
Explanation: The string "AAAABC" has all characters of the other two strings and in the same order.

Input: s1 = "AB", s2 = "C", s3 = "ACB"
Output: true
Explanation: s3 has all characters of s1 and s2 and retains order of characters of s1.

Input: s1 = "YX", s2 = "X", s3 = "XXY"
Output: false

Constraints:
1 <= s1.length, s2.length <= 300
1 <= s3.length <= 600

Core Idea:
Use a 2D dynamic programming table `dp` of size `(n + 1) * (m + 1)`:
- `dp[i][j]` will be true if `s3[0...i+j-1]` is a valid interleaving of `s1[0...i-1]` and `s2[0...j-1]`.
- Base Case:
  - `dp[0][0] = true` (empty strings can interleave to form an empty s3).
- DP Transition:
  - We can reach `dp[i][j]` from:
    1. `dp[i-1][j]` if the last character of `s1` (which is `s1[i-1]`) matches `s3[i+j-1]`.
    2. `dp[i][j-1]` if the last character of `s2` (which is `s2[j-1]`) matches `s3[i+j-1]`.

Approach:
1. If `s1.length() + s2.length() != s3.length()`, return `false`.
2. Initialize `dp[n+1][m+1]` with `false`.
3. Set `dp[0][0] = true`.
4. Fill the 2D DP table:
  - For `i` from 0 to `n`:
    - For `j` from 0 to `m`:
      - If `i > 0` and `s1[i-1] == s3[i+j-1]`, then `dp[i][j] = dp[i][j] || dp[i-1][j]`.
      - If `j > 0` and `s2[j-1] == s3[i+j-1]`, then `dp[i][j] = dp[i][j] || dp[i][j-1]`.
5. Return `dp[n][m]`.

Time Complexity: O(N * M) where N is length of s1 and M is length of s2.
Space Complexity: O(N * M) to store the DP table.

GFG Link: https://www.geeksforgeeks.org/problems/interleaved-strings/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. Recursive Approach (Exponential Time)
// TC: O(2^(N+M)) in worst case, SC: O(N+M) recursion stack space
class InterleaveRecursive {
private:
    bool solve(int i, int j, const string& s1, const string& s2, const string& s3) {
        // Base Case: if we have reached the end of both strings, match is successful
        if (i == s1.length() && j == s2.length()) {
            return true;
        }

        // Try to match current character of s3 with s1 (short-circuiting check)
        if (i < s1.length() && s1[i] == s3[i + j] ) {
            if(solve(i+1,j,s1,s2,s3)){
                return true;
            }
        }
        // Try to match current character of s3 with s2 (short-circuiting check)
        if (j < s2.length() && s2[j] == s3[i + j] ) {
            if(solve(i,j+1,s1 ,s2,s3)){
                return true;
            }
        }

        return false;
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) {
            return false;
        }
        return solve(0, 0, s1, s2, s3);
    }
};

// 2. Memoization (Top-Down DP)
// TC: O(N * M), SC: O(N * M) dp state table + O(N + M) recursion stack space
class InterleaveMemoization {
private:
    bool solve(int i, int j, const string& s1, const string& s2, const string& s3, vector<vector<int>>& dp) {
        // Base Case
        if (i == s1.length() && j == s2.length()) {
            return true;
        }
        
        // Return cached result
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // Try to match with s1
        if (i < s1.length() && s1[i] == s3[i + j]) {
            if (solve(i + 1, j, s1, s2, s3, dp)) {
                return dp[i][j] = true;
            }
        }
        // Try to match with s2
        if (j < s2.length() && s2[j] == s3[i + j]) {
            if (solve(i, j + 1, s1, s2, s3, dp)) {
                return dp[i][j] = true;
            }
        }

        return dp[i][j] = false;
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.length();
        int m = s2.length();
        
        if (n + m != s3.length()) {
            return false;
        }
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solve(0, 0, s1, s2, s3, dp);
    }
};

// 3. Tabulation (Bottom-Up DP)
// TC: O(N * M), SC: O(N * M) dp table
// Let's learn Tabulation step-by-step! 
// Remember the 3 Golden Steps to convert any recursive DP into Tabulation:
// Step 1: Create the DP Table/Array.
// Step 2: Analyze & Initialize the Base Case.
// Step 3: Run the loops (bottom-up) and write down the state transition.
class InterleaveTabulation {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.length();
        int m = s2.length();
        
        // Fast Check: If combined length doesn't match s3, it can't be interleaved!
        if (n + m != s3.length()) {
            return false;
        }
        
        /* 
         * Step 1: Create the DP Array.
         * dp[i][j] will store: "Can s3's prefix of length (i + j) be formed by 
         * interleaving s1's prefix of length i and s2's prefix of length j?"
         * Size is (n + 1) x (m + 1) because prefix lengths range from 0 to n and 0 to m.
         * Initialize all cells as false.
         */
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        
        /* 
         * Step 2: Initialize the Base Case.
         * dp[0][0] = true. Why? Because an empty s1 (length 0) and empty s2 (length 0) 
         * can form an empty s3 (length 0). It's a valid match!
         */
        dp[0][0] = true;
        
        /* 
         * Step 3: Write the loops & logic.
         * We iterate bottom-up from length i = 0 to n and j = 0 to m.
         * For each state dp[i][j], we have two choices to check:
         * 
         * Choice 1: Can we match the current character of s3 (at index i+j-1) 
         * using the last character of s1's prefix (which is s1[i-1])?
         * - Condition: We must have used at least 1 character of s1 (i > 0) AND s1[i-1] == s3[i+j-1].
         * - If yes, then the result for dp[i][j] depends on whether we could interleave 
         *   the remaining characters previously, which is dp[i-1][j].
         * 
         * Choice 2: Can we match the current character of s3 (at index i+j-1) 
         * using the last character of s2's prefix (which is s2[j-1])?
         * - Condition: We must have used at least 1 character of s2 (j > 0) AND s2[j-1] == s3[i+j-1].
         * - If yes, then the result for dp[i][j] depends on whether we could interleave 
         *   the remaining characters previously, which is dp[i][j-1].
         */
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                // If we are at (0,0), it's already set to true, so skip overriding it
                if (i == 0 && j == 0) continue;
                
                // Check Choice 1 (matching s1's character)
                if (i > 0 && s1[i - 1] == s3[i + j - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
                
                // Check Choice 2 (matching s2's character)
                if (j > 0 && s2[j - 1] == s3[i + j - 1]) {
                    dp[i][j] = dp[i][j] || dp[i][j - 1];
                }
            }
        }
        
        // Final Answer: Can s1 of length n and s2 of length m form s3 of length n+m?
        return dp[n][m];
    }
};

// 4. Space Optimized (Bottom-Up DP with O(M) space)
// TC: O(N * M), SC: O(M) space optimization
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.length();
        int m = s2.length();
        
        if (n + m != s3.length()) {
            return false;
        }
        
        vector<bool> prev(m + 1, false);
        prev[0] = true; // dp[0][0] = true
        
        // Base case for row 0: matching only s2 with s3 (since s1 prefix is empty)
        for (int j = 1; j <= m; j++) {
            prev[j] = prev[j - 1] && (s2[j - 1] == s3[j - 1]);
        }
        
        for (int i = 1; i <= n; i++) {
            vector<bool> curr(m + 1, false);
            // Base case for col 0: matching only s1 with s3 (since s2 prefix is empty)
            curr[0] = prev[0] && (s1[i - 1] == s3[i - 1]);
            
            for (int j = 1; j <= m; j++) {
                bool matchS1 = (s1[i - 1] == s3[i + j - 1]) && prev[j];
                bool matchS2 = (s2[j - 1] == s3[i + j - 1]) && curr[j - 1];
                curr[j] = matchS1 || matchS2;
            }
            prev = curr;
        }
        
        return prev[m];
    }
};

/*
Dry Run — Example:
s1 = "AB", s2 = "C", s3 = "ACB"
n = 2, m = 1, s3.length() = 3 (matches 2 + 1)

dp table size 3x2, initialized to false except dp[0][0] = true:
- i = 0, j = 0: dp[0][0] = true
- i = 0, j = 1: s2[0] ('C') == s3[0] ('A')? No -> dp[0][1] = false

- i = 1, j = 0: s1[0] ('A') == s3[0] ('A')? Yes -> dp[1][0] = dp[1][0] || dp[0][0] = true
- i = 1, j = 1: 
  - s1[0] ('A') == s3[1] ('C')? No
  - s2[0] ('C') == s3[1] ('C')? Yes -> dp[1][1] = dp[1][1] || dp[1][0] = true

- i = 2, j = 0: s1[1] ('B') == s3[1] ('C')? No -> dp[2][0] = false
- i = 2, j = 1:
  - s1[1] ('B') == s3[2] ('B')? Yes -> dp[2][1] = dp[2][1] || dp[1][1] = true
  - s2[0] ('C') == s3[2] ('B')? No

Returns dp[2][1] which is true.

Output: true
*/
