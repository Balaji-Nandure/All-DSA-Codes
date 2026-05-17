/*
Problem: Count zeros in a sorted matrix

GFG: https://www.geeksforgeeks.org/problems/count-zeros-in-a-sorted-matrix/1

Description:
Given an n x n binary matrix where each row and each column is sorted in
ascending order, return the total count of zeroes.

Examples:

Input: [[0,0,0],
        [0,0,1],
        [0,1,1]]
Output: 6

Input: [[1,1],
        [1,1]]
Output: 0

Constraints:
0 < n <= 10^3
0 <= mat[i][j] <= 1

Approach (Top-Right Traversal):
Start from top-right cell (row = 0, col = n-1):
- If current cell is 0:
  all elements to its left in that row are also 0
  => add (col + 1), move to next row
- Else (current cell is 1):
  move left (col--)

This visits at most 2n cells.

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: Matrix Traversal / Sorted Matrix Pointer Walk
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int countZeros(vector<vector<int>>& mat) {
      int n = (int)mat.size();
      int row = 0;
      int col = n - 1;
      int zeros = 0;

      while (row < n && col >= 0) {
          if (mat[row][col] == 0) {
              zeros += (col + 1);
              row++;
          } else {
              col--;
          }
      }

      return zeros;
    }
};

