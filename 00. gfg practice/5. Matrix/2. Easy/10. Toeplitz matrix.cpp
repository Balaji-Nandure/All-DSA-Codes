/*
GeeksforGeeks: Toeplitz matrix
Difficulty: Easy

Problem:
A Toeplitz matrix (also known as a diagonal-constant matrix) is a matrix in 
which every descending diagonal from left to right contains the same element.
Given a rectangular matrix mat, determine whether it is a Toeplitz matrix or not.

Example 1:
Input: 
mat[][] = [[6, 7, 8],
           [4, 6, 7],
           [1, 4, 6]]
Output: true
Explanation: 
The matrix is Toeplitz because every diagonal from top-left to bottom-right 
has the same elements. 
- Main diagonal is 6 → 6 → 6
- 7 → 7
- 8
- 4 → 4
- 1
Since all diagonals follow this pattern, the matrix is Toeplitz.

Example 2:
Input: 
mat[][] = [[6, 3, 8],
           [4, 9, 7],
           [1, 4, 6]]
Output: false
Explanation: 
The primary diagonal elements of the given matrix are [6, 9, 6]. 
As the diagonal elements are not the same, the given matrix is not Toeplitz.

Core Idea:
Instead of trying to find the starting point of every single diagonal and manually 
traversing it to check if all its elements are equal, we can use a brilliantly 
simple local property:
If EVERY element is equal to its top-left neighbor, then by definition, ALL 
descending diagonals contain the exact same elements!

This means we only need to compare `mat[i][j]` against `mat[i-1][j-1]`.
If we find even a single mismatch, the matrix is NOT Toeplitz.

Approach:
1. Iterate through the rows `i` starting from `1` to `n - 1`.
2. Iterate through the columns `j` starting from `1` to `m - 1`.
   (We start at index 1 because row 0 and col 0 don't have top-left neighbors).
3. If `mat[i][j] != mat[i - 1][j - 1]`, immediately return `false`.
4. If the nested loops finish without returning false, return `true`.

Time Complexity : O(N * M) — We visit every element in the matrix (except the first row/col) exactly once.
Space Complexity: O(1) — No extra space is required.

GFG Link:
https://www.geeksforgeeks.org/problems/toeplitz-matrix/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool isToeplitz(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        
        // Start from row 1 and col 1 since row 0 and col 0 have no top-left neighbors
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                
                // If the current element doesn't match its top-left neighbor,
                // the matrix cannot be Toeplitz!
                if (mat[i][j] != mat[i - 1][j - 1]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};

/*
Dry Run — Example 1:
mat[][] = [[6, 7, 8],
           [4, 6, 7],
           [1, 4, 6]]
n = 3, m = 3

i = 1:
  - j = 1: mat[1][1] (6) == mat[0][0] (6) -> True.
  - j = 2: mat[1][2] (7) == mat[0][1] (7) -> True.

i = 2:
  - j = 1: mat[2][1] (4) == mat[1][0] (4) -> True.
  - j = 2: mat[2][2] (6) == mat[1][1] (6) -> True.

Loops terminate.
Result: Return true. ✓
*/
