/*
Problem: Addition of two square matrices

GFG: https://www.geeksforgeeks.org/problems/addition-of-two-square-matrices/1

Description:
Given two square matrices a[][] and b[][] of size n x n, add corresponding
elements and store the result in a[][] itself.

Examples:

Input:
a = [[1, 2],
     [3, 4]]
b = [[4, 3],
     [2, 1]]
Output:
[[5, 5],
 [5, 5]]

Input:
a = [[7, 8],
     [9, 10]]
b = [[1, 2],
     [3, 4]]
Output:
[[8, 10],
 [12, 14]]

Constraints:
1 <= n <= 100

Approach:
Traverse all cells (i, j) and do:
a[i][j] = a[i][j] + b[i][j]

Time Complexity: O(n^2)
Space Complexity: O(1) extra

Pattern: Matrix Traversal / In-place Update
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void Addition(vector<vector<int>>& a, vector<vector<int>>& b) {
          int n = (int)a.size();

          for (int i = 0; i < n; i++) {
               for (int j = 0; j < n; j++) {
                    a[i][j] += b[i][j];
               }
          }
    }
};

