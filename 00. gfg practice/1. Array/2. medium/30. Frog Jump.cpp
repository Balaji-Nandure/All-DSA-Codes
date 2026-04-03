/*
Problem: Frog Jump (minimum cost to reach last stair)

GFG: https://www.geeksforgeeks.org/problems/geek-jump/1
Visualizer (HTML, same folder): 30. Frog Jump - visualizer.html

Description: Given an integer array height[] where height[i] is the height of stair i, a frog starts on the
first stair (index 0) and must reach the last stair (index n−1). From stair i the frog may jump only to
stair i+1 or i+2. The cost of a jump equals the absolute difference in height between the two stairs.
Return the minimum total cost.

Example:

Input: heights[] = [20, 30, 40, 20]
Output: 20
Explanation: Optimal path 0 → 1 → 3: |30−20| + |20−30| = 10 + 10 = 20.

Input: heights[] = [30, 20, 50, 10, 40]
Output: 30
Explanation: Optimal path 0 → 2 → 4: |50−30| + |40−50| = 20 + 10 = 30.

Constraints:
1 ≤ height.size() ≤ 10^5
0 ≤ height[i] ≤ 10^4

Striver Intuition:

This is a classic 1D Dynamic Programming (Fibonacci-style) problem.

Brute Force:
Try all jump sequences (recursion with two choices each step). Overlapping subproblems → exponential time.

Optimal — DP:
Let dp[i] = minimum cost to land exactly on stair i (starting from 0).
- dp[0] = 0 (already there).
- dp[1] = |height[1] − height[0]| (only from 0).
- For i ≥ 2: dp[i] = min(
    dp[i−1] + |height[i] − height[i−1]|,   // last jump was one step
    dp[i−2] + |height[i] − height[i−2]|    // last jump was two steps
  )

Answer = dp[n−1].

Space optimization: only dp[i−1] and dp[i−2] are needed → O(1) extra space.

Pattern:
Linear DP / climbing stairs variant — transition from i−1 and i−2.

Time Complexity: O(n)
Space Complexity: O(1) with rolling variables (or O(n) with full dp array)

GFG:
https://www.geeksforgeeks.org/problems/geek-jump/1

Related (similar vibe, different cost rule):
https://leetcode.com/problems/min-cost-climbing-stairs/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& height) {
        int n = height.size();
        if (n == 1) {
            return 0;
        }

        int prev2 = 0;
        int prev1 = abs(height[1] - height[0]);

        for (int i = 2; i < n; i++) {
            int one = prev1 + abs(height[i] - height[i - 1]);
            int two = prev2 + abs(height[i] - height[i - 2]);
            int curr = min(one, two);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

/*
Final Summary (Interview Revision):

1. dp[i] from i−1 or i−2 with cost = |h[i] − h[j]|.
2. Base: n==1 → 0; else prev2=0, prev1=|h[1]−h[0]|.
3. For i from 2 to n−1: one = prev1+|h[i]−h[i−1]|, two = prev2+|h[i]−h[i−2]|, curr = min(one,two), then shift prev2,prev1.
4. O(n) time, O(1) space.

Memory Trick:
"one / two / curr — shift prev2, prev1 — abs height diff"
*/
