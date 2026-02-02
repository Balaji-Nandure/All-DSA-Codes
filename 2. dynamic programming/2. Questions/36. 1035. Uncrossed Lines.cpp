/*
Problem:
1035. Uncrossed Lines

Description:
You are given two integer arrays nums1 and nums2. We write the integers of nums1 and nums2 
(in the order they are given) on two separate horizontal lines.

We may draw connecting lines: a straight line connecting two numbers nums1[i] and nums2[j] such that:
- nums1[i] == nums2[j], and
- the line we draw does not intersect any other connecting (non-horizontal) line.

Note that a connecting line cannot intersect even at the endpoints (i.e., each number can only 
belong to one connecting line).

Return the maximum number of connecting lines we can draw in this way.

Approach:
Longest Common Subsequence (LCS) - Tabulation

This problem is equivalent to finding the LCS between nums1 and nums2.
Lines can be drawn without crossing if and only if the elements form a common subsequence.

State:
dp[i][j] = maximum uncrossed lines between nums1[0..i-1] and nums2[0..j-1]

Transition:
If nums1[i-1] == nums2[j-1]:
    dp[i][j] = dp[i-1][j-1] + 1  (draw a line)
Else:
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])  (skip one element)

Base case:
dp[0][j] = 0 and dp[i][0] = 0 (no lines can be drawn with empty array)

LeetCode:
https://leetcode.com/problems/uncrossed-lines/

Time Complexity:
O(m * n) where m = nums1.size(), n = nums2.size()

Space Complexity:
O(m * n) for 2D DP, can be optimized to O(n) using 1D DP
*/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        // dp[i][j] = max uncrossed lines between nums1[0..i-1] and nums2[0..j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    // If elements match, we can draw a line
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // Otherwise, take the max from either skipping nums1[i-1] or nums2[j-1]
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

// Time Complexity: O(m * n) where m = nums1.size(), n = nums2.size()
// Space Complexity: O(m * n)

// Space optimized version using 1D DP
class Solution2 {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= m; i++) {
            int prev = 0;
            for (int j = 1; j <= n; j++) {
                int temp = dp[j];
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                prev = temp;
            }
        }
        
        return dp[n];
    }
};

// Time Complexity: O(m * n)
// Space Complexity: O(n)






