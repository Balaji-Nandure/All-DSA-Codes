/*
GeeksforGeeks: LCS of three strings
Difficulty: Medium

Problem:
Given three strings s1, s2, and s3 containing uppercase letters, lowercase letters, and digits,
find the length of longest common sub-sequence in all three given strings.

Examples:
Input: s1 = "geeks", s2 = "geeksfor", s3 = "geeksforgeeks"
Output: 5
Explanation: "geeks" is the longest common subsequence with length 5.

Input: s1 = "abcd1e2", s2 = "bc12ea", s3 = "bd1ea"
Output: 3
Explanation: Longest common subsequence is "b1e" i.e. length = 3.

Constraints:
1 <= s1.size(), s2.size(), s3.size() <= 100

DP State Design:
- i is current index in s1 (or A)
- j is current index in s2 (or B)
- k is current index in s3 (or C)
- solve(i, j, k) determines the LCS length of A[i...], B[j...], C[k...]

Time Complexity: O(N1 * N2 * N3)
Space Complexity: O(N1 * N2 * N3) for top-down/tabulation, optimized to O(N2 * N3) space.

GFG Link: https://www.geeksforgeeks.org/problems/lcs-of-three-strings0028/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 1. Recursive Approach (Exponential Time)
// TC: O(3^(N1+N2+N3)) in worst case, SC: O(N1+N2+N3) recursion stack space
class LCSof3Recursive {
private:
    int solve(int i, int j, int k, const string& A, const string& B, const string& C) {
        // Base Case: If any of the strings is exhausted, no common subsequence can be formed
        if (i == A.length() || j == B.length() || k == C.length()) {
            return 0;
        }

        // Choice 1: All three characters match
        if (A[i] == B[j] && B[j] == C[k]) {
            return 1 + solve(i + 1, j + 1, k + 1, A, B, C);
        }
        
        // Choice 2: Characters do not match, try shifting index in each string separately
        int choice1 = solve(i + 1, j, k, A, B, C);
        int choice2 = solve(i, j + 1, k, A, B, C);
        int choice3 = solve(i, j, k + 1, A, B, C);

        return max({choice1, choice2, choice3});
    }
public:
    int LCSof3(string A, string B, string C, int n1, int n2, int n3) {
        return solve(0, 0, 0, A, B, C);
    }
};

// 2. Memoization (Top-Down DP)
// TC: O(N1 * N2 * N3), SC: O(N1 * N2 * N3) dp state table + O(N1 + N2 + N3) recursion stack space
class LCSof3Memoization {
private:
    int solve(int i, int j, int k, const string& A, const string& B, const string& C, vector<vector<vector<int>>>& dp) {
        // Base Case
        if (i == A.length() || j == B.length() || k == C.length()) {
            return 0;
        }

        // Return cached result
        if (dp[i][j][k] != -1) {
            return dp[i][j][k];
        }

        // Choice 1: All characters match
        if (A[i] == B[j] && B[j] == C[k]) {
            return dp[i][j][k] = 1 + solve(i + 1, j + 1, k + 1, A, B, C, dp);
        }
        
        // Choice 2: Shift index in A, B, or C
        int choice1 = solve(i + 1, j, k, A, B, C, dp);
        int choice2 = solve(i, j + 1, k, A, B, C, dp);
        int choice3 = solve(i, j, k + 1, A, B, C, dp);

        return dp[i][j][k] = max({choice1, choice2, choice3});
    }
public:
    int LCSof3(string A, string B, string C, int n1, int n2, int n3) {
        vector<vector<vector<int>>> dp(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1, -1)));
        return solve(0, 0, 0, A, B, C, dp);
    }
};

// 3. Tabulation (Bottom-Up DP)
// TC: O(N1 * N2 * N3), SC: O(N1 * N2 * N3) dp table
// Let's learn Tabulation step-by-step! 
// Remember the 3 Golden Steps to convert any recursive DP into Tabulation:
// Step 1: Create the DP Table/Array.
// Step 2: Analyze & Initialize the Base Cases.
// Step 3: Run the loops (bottom-up) and write down the state transition.
class LCSof3Tabulation {
public:
    int LCSof3(string A, string B, string C, int n1, int n2, int n3) {
        /* 
         * Step 1: Create the DP Table.
         * dp[i][j][k] will store: "What is the length of LCS of prefix of A (length i), 
         * prefix of B (length j), and prefix of C (length k)?"
         * Size is (n1 + 1) x (n2 + 1) x (n3 + 1) to accommodate prefix lengths up to n1, n2, n3.
         * Initialize all cells as 0.
         */
        vector<vector<vector<int>>> dp(n1 + 1, vector<vector<int>>(n2 + 1, vector<int>(n3 + 1, 0)));
        
        /* 
         * Step 2: Analyze & Initialize the Base Cases.
         * In recursion, if any index reached the end of the string, we returned 0.
         * In tabulation (using prefix lengths):
         * - If prefix length of A is 0: dp[0][j][k] = 0 for all j, k.
         * - If prefix length of B is 0: dp[i][0][k] = 0 for all i, k.
         * - If prefix length of C is 0: dp[i][j][0] = 0 for all i, j.
         * Since our DP array is already initialized to 0, these base cases are automatically set!
         */
        
        /* 
         * Step 3: Run the loops bottom-up.
         * We iterate forward from prefix length 1 up to n1, n2, and n3.
         * Note that since i, j, k represent prefix lengths, the characters we compare 
         * in 0-indexed strings are A[i-1], B[j-1], and C[k-1].
         * 
         * State Transitions:
         * - Match Condition: If A[i-1] == B[j-1] and B[j-1] == C[k-1]:
         *   All three characters match, so we add 1 to the result of excluding these characters:
         *   dp[i][j][k] = 1 + dp[i-1][j-1][k-1].
         * 
         * - Mismatch Condition:
         *   We must try all three choices of excluding the last character of one of the strings:
         *   - Choice 1: exclude A[i-1] -> dp[i-1][j][k]
         *   - Choice 2: exclude B[j-1] -> dp[i][j-1][k]
         *   - Choice 3: exclude C[k-1] -> dp[i][j][k-1]
         *   We take the maximum of these three choices: dp[i][j][k] = max({choice1, choice2, choice3}).
         */
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                for (int k = 1; k <= n3; k++) {
                    if (A[i - 1] == B[j - 1] && B[j - 1] == C[k - 1]) {
                        dp[i][j][k] = 1 + dp[i - 1][j - 1][k - 1];
                    }
                    else {
                        int choice1 = dp[i - 1][j][k];
                        int choice2 = dp[i][j - 1][k];
                        int choice3 = dp[i][j][k - 1];
                        dp[i][j][k] = max({choice1, choice2, choice3});
                    }
                }
            }
        }
        
        // Final Answer: LCS of prefixes of full lengths n1, n2, n3
        return dp[n1][n2][n3];
    }
};

// 4. Space Optimized (Bottom-Up DP with O(N2 * N3) space)
// TC: O(N1 * N2 * N3), SC: O(N2 * N3) space optimization
class Solution {
public:
    int LCSof3(string A, string B, string C, int n1, int n2, int n3) {
        // We only need two rows of the 3D table along the 'i' dimension:
        // prev[j][k] representing dp[i-1][j][k] and curr[j][k] representing dp[i][j][k]
        vector<vector<int>> prev(n2 + 1, vector<int>(n3 + 1, 0));
        
        for (int i = 1; i <= n1; i++) {
            vector<vector<int>> curr(n2 + 1, vector<int>(n3 + 1, 0));
            for (int j = 1; j <= n2; j++) {
                for (int k = 1; k <= n3; k++) {
                    if (A[i - 1] == B[j - 1] && B[j - 1] == C[k - 1]) {
                        curr[j][k] = 1 + prev[j - 1][k - 1];
                    }
                    else {
                        int choice1 = prev[j][k];
                        int choice2 = curr[j - 1][k];
                        int choice3 = curr[j][k - 1];
                        curr[j][k] = max({choice1, choice2, choice3});
                    }
                }
            }
            prev = curr;
        }
        
        return prev[n2][n3];
    }
};

/*
Dry Run — Example:
A = "geeks", B = "geeksfor", C = "geeksforgeeks"
n1 = 5, n2 = 8, n3 = 13

Initially, prev array size 9x14 initialized to 0.

Outer loop runs for i = 1 to 5 (each character of A):
Inside loops, we check matches:
- For i=1 ('g'), j=1 ('g'), k=1 ('g'):
  Match! curr[1][1] = 1 + prev[0][0] = 1.
  Since 'g' matches all three strings.
  
- For i=2 ('e'), j=2 ('e'), k=2 ('e'):
  Match! curr[2][2] = 1 + prev[1][1] = 2.
  
- Continuing this, for i=5 ('s'), j=5 ('s'), k=5 ('s'):
  Match! curr[5][5] = 1 + prev[4][4] = 5.
  
All subsequent characters after index 5 in B and C do not match any further characters in A, 
so the max LCS length remains 5.

Returns prev[8][13] which is 5.
Output: 5
*/
