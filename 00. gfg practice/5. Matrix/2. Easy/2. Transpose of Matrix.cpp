/*
GeeksforGeeks: Transpose of Matrix
Difficulty: Easy

Problem:
You are given a square matrix of size n x n. Your task is to find the transpose 
of the given matrix. The transpose of a matrix is obtained by converting all the 
rows to columns and all the columns to rows.

Example 1:
Input: 
mat[][] = [[1, 1, 1, 1],
           [2, 2, 2, 2],
           [3, 3, 3, 3],
           [4, 4, 4, 4]]
Output: 
[[1, 2, 3, 4],
 [1, 2, 3, 4],
 [1, 2, 3, 4],
 [1, 2, 3, 4]]
Explanation: Converting rows into columns and columns into rows.

Example 2:
Input: 
mat[][] = [[1, 2],
           [9, -2]]
Output: 
[[1, 9],
 [2, -2]]
Explanation: Converting rows into columns and columns into rows.

Core Idea:
Since the given matrix is a **square matrix** (n x n), we don't need to create a 
new 2D array to store the result. We can achieve the transpose perfectly **in-place**.

If you think about what a transpose does, it mathematically swaps the elements 
across the main diagonal.
The element at `mat[i][j]` gets swapped with the element at `mat[j][i]`.

To do this in-place without double-swapping elements back to their original 
positions, we must only iterate over the **upper triangle** (or lower triangle) 
of the matrix. This means for any row `i`, we only iterate columns `j` starting 
from `i + 1`.

Approach:
1. Get the size `n` of the square matrix.
2. Loop `i` from `0` to `n - 1` (iterating through rows).
3. Loop `j` from `i + 1` to `n - 1` (iterating strictly through the upper triangle).
4. Inside the loop, simply swap `mat[i][j]` with `mat[j][i]`.
5. Return nothing, as the matrix is modified in-place.

Time Complexity : O(N^2) — We visit exactly half the elements in the matrix to swap them.
Space Complexity: O(1) — No extra space is used; the modifications are done in-place.

GFG Link:
https://www.geeksforgeeks.org/problems/transpose-of-matrix-1587115621/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void transpose(vector<vector<int>>& mat) {
        int n = mat.size();
        
        // Traverse only the upper triangle of the matrix to swap elements across the diagonal
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Swap the element at (i, j) with the element at (j, i)
                swap(mat[i][j], mat[j][i]);
            }
        }
    }
};

/*
Dry Run — Example 2:
mat[][] = [[1,  2],
           [9, -2]]
n = 2

i = 0:
  j starts from i + 1 = 1:
    - swap(mat[0][1], mat[1][0])
    - mat[0][1] is 2, mat[1][0] is 9.
    - After swap, matrix becomes:
      [[1,  9],
       [2, -2]]

i = 1:
  j starts from i + 1 = 2:
    - Loop condition j < 2 is false. Loop doesn't run.

Resulting Matrix:
[[1, 9],
 [2, -2]]
✓ Matches expected output.
*/
