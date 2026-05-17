/*
Problem: Diagonal Sum in Matrix

GFG: https://www.geeksforgeeks.org/problems/diagonal-sum-in-matrix/1

Description:
Given a square matrix of size n x n, return the sum of both diagonals.

Note:
If n is odd, the center element belongs to both diagonals and is counted twice.

Examples:

Input: [[1, 0, 1],
        [0, 1, 0],
        [1, 0, 1]]
Output: 6

Input: [[1, 2],
        [3, 4]]
Output: 10

Constraints:
1 <= n <= 100
1 <= mat[i][j] <= 10000

Approach:
For each row i:
- Primary diagonal element is mat[i][i]
- Secondary diagonal element is mat[i][n - 1 - i]
Add both.

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: Matrix Diagonal Traversal
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int diagonalSum(vector<vector<int>>& mat) {
        int n = (int)mat.size();
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += mat[i][i];
            sum += mat[i][n - 1 - i];
        }

        return sum;
    }
};

