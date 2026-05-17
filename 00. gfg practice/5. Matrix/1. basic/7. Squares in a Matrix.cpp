/*
Problem: Squares in a Matrix

GFG: https://www.geeksforgeeks.org/problems/squares-in-a-matrix/1

Description:
Given dimensions m x n, count total number of square submatrices.

Examples:
Input: m = 2, n = 2
Output: 5

Input: m = 4, n = 3
Output: 20

Constraints:
1 <= m, n <= 10^4

Approach:
For each possible square size k (1 to min(m, n)):
Number of k x k squares = (m - k + 1) * (n - k + 1)

Add this for all k.

Time Complexity: O(min(m, n))
Space Complexity: O(1)

Pattern: Mathematical Counting
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long squaresInMatrix(int m, int n) {
        int limit = min(m, n);
        long long total = 0;

        for (int k = 1; k <= limit; k++) {
            total += 1LL * (m - k + 1) * (n - k + 1);
        }

        return total;
    }
};

