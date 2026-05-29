/*
GeeksforGeeks: Swap diagonals
Difficulty: Easy

Problem:
Given a square matrix mat[][], the task is to swap the elements of the major and minor diagonals.
- Major Diagonal: Elements that lie from the top-left corner to the bottom-right corner of the matrix (i.e., where row index equals column index).
- Minor Diagonal: Elements that lie from the top-right corner to the bottom-left corner (i.e., where the sum of row and column indices equals n - 1).

Example 1:
Input: 
mat[][] = [[0, 1, 2],
           [3, 4, 5],
           [6, 7, 8]]
Output: [[2, 1, 0],
         [3, 4, 5],
         [8, 7, 6]]
Explanation: 
Major Diagonal = [0, 4, 8], Minor Diagonal = [2, 4, 6]. 
We swap the diagonal elements of the same row, so for row 0: swap(0, 2), for row 1: swap(4, 4), for row 2: swap(8, 6).

Example 2:
Input: 
mat[][] = [[2, 3],
           [5, 4]]
Output: [[3, 2],
         [4, 5]] 
Explanation: 
Major Diagonal = [2, 4], Minor Diagonal = [3, 5]. Swap them per row.

Core Idea:
Since we need to swap the elements of the major and minor diagonals in the same row, we can simply iterate through each row `i` from `0` to `n-1`. For a given row `i`, the major diagonal element is at column `i` and the minor diagonal element is at column `n - 1 - i`. We just swap these two elements for every row. 
Note: If `n` is odd, the middle row's major and minor diagonal element will be the same (the center of the matrix), and swapping it with itself will have no effect, which is perfectly fine.

Approach:
1. Get the size of the square matrix `n = mat.size()`.
2. Iterate `i` from `0` to `n - 1`.
3. In each iteration, swap `mat[i][i]` with `mat[i][n - 1 - i]`.
4. The matrix is modified in-place.

Time Complexity : O(N) — Where N is the number of rows/columns. We perform exactly one swap per row.
Space Complexity: O(1) — We are modifying the matrix in-place without using any extra space.

GFG Link:
https://www.geeksforgeeks.org/problems/swap-diagonals1636/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void swapDiagonal(vector<vector<int>>& mat) {
        int n = mat.size();
        
        // Iterate through each row and swap the diagonal elements
        for (int i = 0; i < n; i++) {
            swap(mat[i][i], mat[i][n - 1 - i]);
        }
    }
};

/*
Dry Run — Example 1:
Input: 
mat = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8]
]
n = 3

i = 0:
- Major diagonal element: mat[0][0] = 0
- Minor diagonal element: mat[0][2] = 2
- Swap(mat[0][0], mat[0][2])
- Matrix becomes:
  [2, 1, 0]
  [3, 4, 5]
  [6, 7, 8]

i = 1:
- Major diagonal element: mat[1][1] = 4
- Minor diagonal element: mat[1][1] = 4
- Swap(mat[1][1], mat[1][1]) (no visible change)
- Matrix remains:
  [2, 1, 0]
  [3, 4, 5]
  [6, 7, 8]

i = 2:
- Major diagonal element: mat[2][2] = 8
- Minor diagonal element: mat[2][0] = 6
- Swap(mat[2][2], mat[2][0])
- Matrix becomes:
  [2, 1, 0]
  [3, 4, 5]
  [8, 7, 6]

Loop ends.

Output:
[
  [2, 1, 0],
  [3, 4, 5],
  [8, 7, 6]
]
Final matrix perfectly matches the expected output. ✓
*/
