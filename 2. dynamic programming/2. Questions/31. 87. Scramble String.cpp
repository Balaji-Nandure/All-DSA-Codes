/*
Problem:
87. Scramble String

Description:
We can scramble a string s to get a string t using the following algorithm:
1. If the length of the string is 1, stop.
2. If the length of the string is > 1, do the following:
   - Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
   - Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
   - Apply step 1 recursively on each of the two substrings x and y.

Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.

Example 1:
Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at index 2
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at index 0 for "gr" and divide at index 1 for "eat"
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now and the result string is "rgeat" which is s2.

Example 2:
Input: s1 = "abcde", s2 = "caebd"
Output: false

Example 3:
Input: s1 = "a", s2 = "a"
Output: true

Constraints:
- s1.length == s2.length
- 1 <= s1.length <= 30
- s1 and s2 consist of lowercase English letters.

Approach:
3D DP with Memoization

State:
dp[i][j][k] = whether substring s1[i...i+k-1] can be scrambled to s2[j...j+k-1]

For each substring of length k, try all possible split points l (1 to k-1):
- Case 1 (no swap): 
  * Left part: s1[i...i+l-1] matches s2[j...j+l-1]
  * Right part: s1[i+l...i+k-1] matches s2[j+l...j+k-1]
  
- Case 2 (swap):
  * Left part: s1[i...i+l-1] matches s2[j+k-l...j+k-1] (right side of s2)
  * Right part: s1[i+l...i+k-1] matches s2[j...j+k-l-1] (left side of s2)

Base case: k == 1, just compare characters

LeetCode:
https://leetcode.com/problems/scramble-string/

Time Complexity:
O(n^4) - for each (i, j, k) state, we try n split points

Space Complexity:
O(n^3) - 3D DP array
*/

class Solution {
private:
    int solve(int i, int j, int k, string& s1, string& s2, vector<vector<vector<int>>>& dp) {
        
        // Base case: single character
        if (k == 1) {
            return s1[i] == s2[j];
        }

        // Check memoized result
        if (dp[i][j][k] != -1) {
            return dp[i][j][k];
        }

        // Try all split points l (1 to k-1)
        for (int l = 1; l < k; l++) {
            
            // Case 1: no swap
            // s1[i...i+l-1] matches s2[j...j+l-1]
            // s1[i+l...i+k-1] matches s2[j+l...j+k-1]
            if (solve(i, j, l, s1, s2, dp) && 
                solve(i + l, j + l, k - l, s1, s2, dp)) {
                return dp[i][j][k] = 1;
            }

            // Case 2: swap
            // s1[i...i+l-1] matches s2[j+k-l...j+k-1] (right side of s2)
            // s1[i+l...i+k-1] matches s2[j...j+k-l-1] (left side of s2)
            if (solve(i, j + k - l, l, s1, s2, dp) && 
                solve(i + l, j, k - l, s1, s2, dp)) {
                return dp[i][j][k] = 1;
            }
        }

        return dp[i][j][k] = 0;
    }

public:
    bool isScramble(string s1, string s2) {
        
        if (s1.size() != s2.size())
            return false;

        int n = s1.length();
        // Initialize DP array with -1
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));
        
        return solve(0, 0, n, s1, s2, dp);
    }
};



/*
Problem:
2218. Maximum Value of K Coins From Piles

Approach:
Recursion + Memoization

State:
solve(i, k) = maximum value from piles[i..] using k coins

Transition:
Try taking x coins from pile i (x = 0 to min(pile[i].size(), k))
Add prefix sum of x coins + solve(i+1, k-x)

LeetCode:
https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/

Time Complexity:
O(n * k * avg_pile_size)

Space Complexity:
O(n * k)
*/

