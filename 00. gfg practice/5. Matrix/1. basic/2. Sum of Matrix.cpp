/*
Problem: Sum of Matrix

GFG: https://www.geeksforgeeks.org/problems/sum-of-matrix/1

Description:
Given an integer matrix mat[][] of size n x m, return the sum of all elements.

Examples:

Input:
[[1, 0, 1],
 [-8, 9, -2]]
Output: 1

Input:
[[1, 0, 1, 0, 1],
 [0, 1, 0, 1, 0],
 [-1, -1, -1, -1, -1]]
Output: 0

Constraints:
1 <= n, m <= 10^3
-10^3 <= mat[i][j] <= 10^3

Approach:
Traverse every cell of the matrix and keep adding values into a running sum.

Time Complexity: O(n * m)
Space Complexity: O(1)

Pattern: Matrix Traversal
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int sumOfMatrix(vector<vector<int>> &mat) {
        int n = (int)mat.size();
        int m = (int)mat[0].size();

        int sum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                sum += mat[i][j];
            }
        }

        return sum;
    }
};

