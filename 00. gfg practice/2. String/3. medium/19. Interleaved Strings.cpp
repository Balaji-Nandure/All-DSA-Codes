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

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    int n = s1.length();
    int m = s2.length();
    
    // Length of s3 must be exactly the sum of lengths of s1 and s2
    if (n + m != s3.length()) {
        return false;
    }
    
    // dp[i][j] stores whether s3[0...i+j-1] is interleaved from s1[0...i-1] and s2[0...j-1]
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    
    dp[0][0] = true;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i > 0 && s1[i - 1] == s3[i + j - 1]) {
                dp[i][j] = dp[i][j] || dp[i - 1][j];
            }
            if (j > 0 && s2[j - 1] == s3[i + j - 1]) {
                dp[i][j] = dp[i][j] || dp[i][j - 1];
            }
        }
    }
    
    return dp[n][m];
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
