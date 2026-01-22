#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Build Array Where You Can Find The Maximum Exactly K Comparisons
LeetCode 1420: https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/

You are given three integers n, m and k. Consider the following algorithm to find the maximum element in an array of positive integers:

max = arr[0]
comparisons = 0
for i from 1 to n-1:
    comparisons++
    if arr[i] > max:
        max = arr[i]

You should build an array arr which has the following properties:
- arr has exactly n integers
- 1 <= arr[i] <= m (0 <= i < n)
- After applying the algorithm, comparisons == k

Return the number of ways to build such an array. Since the answer may be large, return it modulo 10^9 + 7.

Constraints:
- 1 <= n <= 50
- 1 <= m <= 100
- 0 <= k < n

Example:
n = 2, m = 5, k = 1
We need arrays where exactly 1 comparison results in an update
arr = [1, 2] -> comparisons=1, max updates from 1 to 2 (1 update)
arr = [1, 3] -> comparisons=1, max updates from 1 to 3 (1 update)
...
arr = [1, 5] -> comparisons=1, max updates from 1 to 5 (1 update)
arr = [2, 3] -> comparisons=1, max updates from 2 to 3 (1 update)
...
Total: 5 ways for [1, x>1] + 4 ways for [2, x>2] + ... = many ways

Key Insight:
- We need exactly k positions where arr[i] > max_so_far (new maximums found)
- The first element doesn't require a comparison, so we have n-1 comparisons total
- But k represents the number of times we find a NEW maximum (updates)
- For each position i, we can:
  1. Put a value <= current_max: no new maximum (comparison made but no update)
  2. Put a value > current_max: new maximum found (comparison made and update, k decreases)

DP State: 
- dp[i][maxVal][k] = number of ways to build array[0..i] with maximum value maxVal and exactly k comparisons that resulted in updates remaining

Recurrence:
- For position i (i > 0, since first element has no comparison):
  - Option 1: Put value v <= maxVal: 
      dp[i][maxVal][k] += dp[i-1][maxVal][k] * maxVal
      (maxVal choices, no update, k stays same)
  - Option 2: Put value v > maxVal:
      dp[i][v][k-1] += dp[i-1][maxVal][k] for all v from maxVal+1 to m
      (m - maxVal choices, update happens, k decreases by 1)

Base Cases:
- dp[0][v][k] = 1 for all v from 1 to m (first element can be any value, k comparisons remaining)
- dp[i][maxVal][0] = 0 if k was supposed to be 0 but we still have positions (invalid)

Time Complexity: O(n * m^2 * k)
Space Complexity: O(n * m * k)
*/

// 1. Recursive approach
class BuildArrayRecursive {
public:
    // TC: O(m^n) exponential, SC: O(n) recursion stack
    iint solve(int idx, int maxVal, int k, int n, int m) {
        // Base case: built all n elements
        if (idx == n) {
            // Valid if we used exactly k comparisons (k should be 0)
            return (k == 0) ? 1 : 0;
        }
        
        // If we've already used more comparisons than allowed, invalid
        if (k < 0) return 0;
        
        int ways = 0;
        
        for (int v = 1; v <= m; v++) {
            if (v <= maxVal) {
                // No new max, k stays the same
                ways = (ways + solve(idx + 1, maxVal, k, n, m)) % MOD;
            } else {
                // New max found, k decreases by 1
                ways = (ways + solve(idx + 1, v, k - 1, n, m)) % MOD;
            }
        }
        
        return ways;
    }
    
    int numOfArrays(int n, int m, int k) {
        return solve(0, 0, k, n, m);
    }
};

