/*
GeeksforGeeks: Minimum Deletions
Difficulty: Medium

Problem:
Given a string s, write a program to delete the minimum number of characters from the string 
so that the resultant string is a palindrome, while maintaining the order of characters.

Examples:
Input: s = "aebcbda"
Output: 2
Explanation: Remove characters 'e' and 'd' to get "abcba" or "abdba".

Input: s = "geeksforgeeks"
Output: 8
Explanation: The longest palindromic subsequence is "eefee" (length 5). 
             The minimum deletions are: 13 (length of s) - 5 = 8.

Constraints:
1 <= s.size() <= 10^3

DP State Design:
- This problem is solved by finding the Longest Palindromic Subsequence (LPS) of s.
- Let i be the start index, and j be the end index in s.
- solve(i, j) determines the length of the LPS in s[i...j].
- Minimum deletions required = s.size() - LPS(s).

Time Complexity: O(N^2) where N is the length of string s.
Space Complexity: O(N^2) for top-down/tabulation, optimized to O(N) space.

GFG Link: https://www.geeksforgeeks.org/problems/minimum-deletions1648/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 1. Recursive Approach (Exponential Time)
// TC: O(2^N) in worst case, SC: O(N) recursion stack space
class DeletionsRecursive {
private:
    int solve(int i, int j, string &s) {
        // Base Case 1: Start index exceeds end index
        if (i > j) {
            return 0;
        }
        // Base Case 2: Only one character (always a palindrome of length 1)
        if (i == j) {
            return 1;
        }
        
        // Choice 1: Characters match at both ends
        if (s[i] == s[j]) {
            return 2 + solve(i + 1, j - 1, s);
        }
        
        // Choice 2: Characters do not match, try excluding one at a time
        return max(solve(i + 1, j, s), solve(i, j - 1, s));
    }
public:
    int minDeletions(string s) {
        int n = s.size();
        int lps_len = solve(0, n - 1, s);
        return n - lps_len;
    }
};

// 2. Memoization (Top-Down DP)
// TC: O(N^2), SC: O(N^2) dp state table + O(N) recursion stack space
class DeletionsMemoization {
private:
    int solve(int i, int j, string &s, vector<vector<int>> &dp) {
        // Base Case 1
        if (i > j) {
            return 0;
        }
        // Base Case 2
        if (i == j) {
            return 1;
        }
        
        // Return cached result
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        
        // Choice 1
        if (s[i] == s[j]) {
            return dp[i][j] = 2 + solve(i + 1, j - 1, s, dp);
        }
        
        // Choice 2
        return dp[i][j] = max(solve(i + 1, j, s, dp), solve(i, j - 1, s, dp));
    }
public:
    int minDeletions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        int lps_len = solve(0, n - 1, s, dp);
        return n - lps_len;
    }
};

// 3. Tabulation (Bottom-Up DP)
// TC: O(N^2), SC: O(N^2) dp table
// Let's learn Tabulation step-by-step! 
// Remember the 3 Golden Steps to convert any recursive DP into Tabulation:
// Step 1: Create the DP Table/Array.
// Step 2: Analyze & Initialize the Base Cases.
// Step 3: Run the loops (bottom-up) and write down the state transition.
class DeletionsTabulation {
public:
    int minDeletions(string s) {
        int n = s.size();
        
        /* 
         * Step 1: Create the DP Table.
         * dp[i][j] will store: "What is the length of the Longest Palindromic Subsequence (LPS) in s[i...j]?"
         * Size is n x n because both i and j range from 0 to n-1.
         * Initialize all cells as 0.
         */
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        /* 
         * Step 2: Analyze & Initialize the Base Cases.
         * 
         * Base Case 1: i > j (empty string range)
         * dp[i][j] = 0. This is already initialized to 0 by default!
         * 
         * Base Case 2: i == j (single character range)
         * Every single character is a palindrome of length 1.
         * So dp[i][i] = 1 for all indices i.
         */
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        /* 
         * Step 3: Run the loops bottom-up.
         * In recursion, we started from i=0, j=n-1 and solved smaller ranges like (i+1, j-1) or (i+1, j).
         * This means dp[i][j] depends on values in the next row (i+1) and previous column (j-1).
         * To ensure dependent values are computed first:
         * - i must iterate backwards from n-1 down to 0.
         * - j must iterate forwards from i+1 up to n-1.
         * 
         * State Transitions:
         * - Match Condition: If s[i] == s[j]:
         *   The characters at both ends match, so we add 2 to the LPS length of the inner substring:
         *   dp[i][j] = 2 + dp[i + 1][j - 1].
         * 
         * - Mismatch Condition:
         *   We try two choices (excluding s[i] or excluding s[j]) and take the maximum:
         *   dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]).
         */
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        
        // Length of Longest Palindromic Subsequence of the entire string s[0...n-1]
        int lps_len = dp[0][n - 1];
        
        // Minimum deletions required is total length minus the length of the LPS
        return n - lps_len;
    }
};

// 4. Space Optimized (Bottom-Up DP with O(N) space)
// TC: O(N^2), SC: O(N) space optimization
class Solution {
public:
    int minDeletions(string s) {
        int n = s.size();
        if (n == 0) return 0;
        
        // Space Optimization: dp[i][j] depends on row i+1 and row i.
        // We only need two rows of size n: 
        // nextRow representing dp[i+1] and currRow representing dp[i].
        vector<int> nextRow(n, 0);
        
        for (int i = n - 1; i >= 0; i--) {
            vector<int> currRow(n, 0);
            currRow[i] = 1; // base case for i == j (single character)
            
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    currRow[j] = 2 + nextRow[j - 1];
                }
                else {
                    currRow[j] = max(nextRow[j], currRow[j - 1]);
                }
            }
            nextRow = currRow;
        }
        
        int lps_len = nextRow[n - 1];
        return n - lps_len;
    }
};

/*
Dry Run — Example:
s = "aebcbda"
n = 7

Outer loop i goes from 6 down to 0:
- i = 6 (s[6] = 'a'):
  currRow[6] = 1.
  nextRow = [0, 0, 0, 0, 0, 0, 1]

- i = 5 (s[5] = 'd'):
  currRow[5] = 1.
  j = 6: s[5] != s[6] -> currRow[6] = max(nextRow[6], currRow[5]) = max(1, 1) = 1.
  nextRow = [0, 0, 0, 0, 0, 1, 1]

...

- i = 0 (s[0] = 'a'):
  currRow[0] = 1.
  j = 6: s[0] == s[6] ('a' == 'a') -> currRow[6] = 2 + nextRow[5] = 2 + 3 = 5. (Inner LPS length of "ebcbd" is 3, plus 2 = 5)

Returns lps_len = nextRow[6] = 5.
Minimum deletions = 7 - 5 = 2.
Output: 2
*/
