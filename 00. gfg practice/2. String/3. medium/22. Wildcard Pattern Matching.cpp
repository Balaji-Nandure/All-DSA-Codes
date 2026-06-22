/*
GeeksforGeeks: Wildcard Pattern Matching
Difficulty: Medium

Problem:
Given two strings pat and txt which may be of different sizes, return true if the wildcard pattern pat matches with txt, else return false.
The wildcard pattern pat can include the characters '?' and '*'.
- '?' matches any single character.
- '*' matches any sequence of characters (including the empty sequence).
Note: The matching must cover the entire txt.

Examples:
Input: txt = "abcde", pat = "a?c*"
Output: true
Explanation: '?' matches with 'b' and '*' matches with "de".

Input: txt = "baaabab", pat = "a*ab"
Output: false

Input: txt = "abc", pat = "*"
Output: true

Constraints:
1 <= txt.size(), pat.size() <= 100

DP State Design:
- i is current index in pat (from 0 to n)
- j is current index in txt (from 0 to m)
- solve(i, j) determines if pat[i...] matches txt[j...]

Time Complexity: O(N * M)
Space Complexity: O(N * M) for top-down/tabulation, optimized to O(M) space.

GFG Link: https://www.geeksforgeeks.org/problems/wildcard-pattern-matching/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 1. Recursive Approach (Exponential Time)
// TC: O(2^(N+M)) in worst case, SC: O(N+M) recursion stack space
class WildcardRecursive {
private:
    bool solve(int i, int j, const string& pat, const string& txt) {
        // Base Case 1: Both pattern and text are exhausted -> successful match
        if (i == pat.length() && j == txt.length()) {
            return true;
        }
        // Base Case 2: Pattern is exhausted, but text still has characters -> no match
        if (i == pat.length()) {
            return false;
        }
        // Base Case 3: Text is exhausted, but pattern has characters remaining
        if (j == txt.length()) {
            // Remaining pattern characters must all be '*' to match an empty text
            for (int k = i; k < pat.length(); k++) {
                if (pat[k] != '*') return false;
            }
            return true;
        }

        // Choice 1: Current characters match, or pattern has a '?'
        if (pat[i] == txt[j] || pat[i] == '?') {
            if (solve(i + 1, j + 1, pat, txt)) {
                return true;
            }
        }
        
        // Choice 2: Pattern has a '*'
        if (pat[i] == '*') {
            // Case A: '*' matches empty sequence (i.e. move pattern index i, keep text index j)
            if (solve(i + 1, j, pat, txt)) {
                return true;
            }
            // Case B: '*' matches current text character (i.e. keep pattern index i, move text index j)
            if (solve(i, j + 1, pat, txt)) {
                return true;
            }
        }

        return false;
    }
public:
    bool wildCard(string pat, string txt) {
        return solve(0, 0, pat, txt);
    }
};

// 2. Memoization (Top-Down DP)
// TC: O(N * M), SC: O(N * M) dp state table + O(N + M) recursion stack space
class WildcardMemoization {
private:
    bool solve(int i, int j, const string& pat, const string& txt, vector<vector<int>>& dp) {
        // Base Cases
        if (i == pat.length() && j == txt.length()) {
            return true;
        }
        if (i == pat.length()) {
            return false;
        }
        if (j == txt.length()) {
            for (int k = i; k < pat.length(); k++) {
                if (pat[k] != '*') return false;
            }
            return true;
        }

        // Memoization Lookup
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // Choice 1: Match single character
        if (pat[i] == txt[j] || pat[i] == '?') {
            if (solve(i + 1, j + 1, pat, txt, dp)) {
                return dp[i][j] = true;
            }
        }
        
        // Choice 2: Match wildcard '*'
        if (pat[i] == '*') {
            if (solve(i + 1, j, pat, txt, dp)) {
                return dp[i][j] = true;
            }
            if (solve(i, j + 1, pat, txt, dp)) {
                return dp[i][j] = true;
            }
        }

        return dp[i][j] = false;
    }
public:
    bool wildCard(string pat, string txt) {
        int n = pat.length();
        int m = txt.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solve(0, 0, pat, txt, dp);
    }
};

// 3. Tabulation (Bottom-Up DP)
// TC: O(N * M), SC: O(N * M) dp table
// Let's learn Tabulation step-by-step! 
// Remember the 3 Golden Steps to convert any recursive DP into Tabulation:
// Step 1: Create the DP Table/Array.
// Step 2: Analyze & Initialize the Base Cases.
// Step 3: Run the loops (bottom-up) and write down the state transition.
class WildcardTabulation {
public:
    bool wildCard(string pat, string txt) {
        int n = pat.length();
        int m = txt.length();
        
        /* 
         * Step 1: Create the DP Table.
         * dp[i][j] represents: "Does pat's suffix starting at index i match txt's suffix starting at index j?"
         * Size is (n + 1) x (m + 1) because index i goes up to n and index j goes up to m.
         * Initialize all cells as false.
         */
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        
        /* 
         * Step 2: Analyze & Initialize the Base Cases.
         * 
         * Base Case A: Both pattern and text are empty.
         * dp[n][m] = true (empty pattern matches empty text).
         * 
         * Base Case B: Pattern is empty but text is not.
         * dp[n][j] for j < m is false (since an empty pattern cannot match a non-empty text).
         * This is already initialized to false by default!
         * 
         * Base Case C: Text is empty but pattern has characters remaining.
         * dp[i][m] can only be true if all remaining characters in pat from index i onwards are '*'.
         * We compute this bottom-up from i = n - 1 down to 0:
         * dp[i][m] will be true if current character is '*' AND the next suffix matches (dp[i+1][m] is true).
         */
        dp[n][m] = true;
        for (int i = n - 1; i >= 0; i--) {
            dp[i][m] = (pat[i] == '*') && dp[i + 1][m];
        }
        
        /* 
         * Step 3: Run the loops bottom-up.
         * In recursion, we started from i=0, j=0 and moved towards n, m.
         * In tabulation, we do the exact opposite! We iterate backwards:
         * i goes from n-1 down to 0.
         * j goes from m-1 down to 0.
         * 
         * Transitions for cell dp[i][j]:
         * - Choice 1: If current character matches (pat[i] == txt[j] or pat[i] == '?'):
         *   The match depends on the next state: dp[i][j] = dp[i + 1][j + 1].
         * - Choice 2: If pattern character is '*':
         *   - We can either treat '*' as empty sequence: dp[i + 1][j]
         *   - Or treat '*' as matching one or more characters: dp[i][j + 1]
         *   - Therefore: dp[i][j] = dp[i + 1][j] || dp[i][j + 1].
         * - If neither choice works, it remains false.
         */
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (pat[i] == txt[j] || pat[i] == '?') {
                    dp[i][j] = dp[i + 1][j + 1];
                }
                else if (pat[i] == '*') {
                    dp[i][j] = dp[i + 1][j] || dp[i][j + 1];
                }
                else {
                    dp[i][j] = false;
                }
            }
        }
        
        // Final Answer: Can pattern pat[0...] match text txt[0...]
        return dp[0][0];
    }
};

// 4. Space Optimized (Bottom-Up DP with O(M) space)
// TC: O(N * M), SC: O(M) space optimization
class Solution {
public:
    bool wildCard(string pat, string txt) {
        int n = pat.length();
        int m = txt.length();
        
        // nextRow represents dp[i + 1] (state when pattern suffix starts at index i + 1)
        vector<bool> nextRow(m + 1, false);
        
        // Base Case for nextRow (when pattern is empty i.e. i = n)
        nextRow[m] = true; // empty pattern matches empty text
        // nextRow[j] for j < m is already false (empty pattern cannot match non-empty text)
        
        // Run bottom-up loops
        for (int i = n - 1; i >= 0; i--) {
            vector<bool> currRow(m + 1, false);
            
            // Base Case: when text is empty (j = m), we only match if pat[i] is '*' and nextRow[m] is true
            currRow[m] = (pat[i] == '*') && nextRow[m];
            
            for (int j = m - 1; j >= 0; j--) {
                if (pat[i] == txt[j] || pat[i] == '?') {
                    currRow[j] = nextRow[j + 1];
                }
                else if (pat[i] == '*') {
                    currRow[j] = nextRow[j] || currRow[j + 1];
                }
                else {
                    currRow[j] = false;
                }
            }
            nextRow = currRow;
        }
        
        return nextRow[0];
    }
};

/*
Dry Run — Example:
txt = "abc", pat = "*"
n = 1, m = 3

nextRow size 4: [false, false, false, true] (representing empty pattern matching empty text at index 3)

Loop i = 0 (pat[0] = '*'):
currRow size 4:
  - Base case currRow[3] = (pat[0] == '*') && nextRow[3] = true && true = true.
  
  - j = 2 (txt[2] = 'c'):
    currRow[2] = nextRow[2] || currRow[3] = false || true = true.
    
  - j = 1 (txt[1] = 'b'):
    currRow[1] = nextRow[1] || currRow[2] = false || true = true.
    
  - j = 0 (txt[0] = 'a'):
    currRow[0] = nextRow[0] || currRow[1] = false || true = true.

nextRow = currRow = [true, true, true, true]

Returns nextRow[0] which is true.
Output: true
*/
