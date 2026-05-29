/*
GeeksforGeeks: Print Diagonally
Difficulty: Easy

Problem:
Given a n * n square matrix mat[][], return all the elements of its 
anti-diagonals from top to bottom.

Example 1:
Input: 
n = 3 
mat[][] = [[1, 2, 3],
           [4, 5, 6],
           [7, 8, 9]]
Output: [1, 2, 4, 3, 5, 7, 6, 8, 9]
Explanation: 
The anti-diagonals are:
- 1 (from mat[0][0])
- 2, 4 (from mat[0][1], mat[1][0])
- 3, 5, 7 (from mat[0][2], mat[1][1], mat[2][0])
- 6, 8 (from mat[1][2], mat[2][1])
- 9 (from mat[2][2])

Example 2:
Input: 
n = 2
mat[][] = [[1, 2],
           [3, 4]]
Output: [1, 2, 3, 4]
Explanation: 
The anti-diagonals are:
- 1
- 2, 3
- 4

Core Idea:
In any matrix, the elements of an anti-diagonal share a very special mathematical 
property: the sum of their row index `i` and column index `j` is constant!
- For the 1st anti-diagonal (1), `i + j = 0 + 0 = 0`
- For the 2nd anti-diagonal (2, 4), `i + j = 0 + 1 = 1` and `1 + 0 = 1`. Sum is 1.
- For the 3rd anti-diagonal (3, 5, 7), `i + j` is always 2.

Since the matrix is of size `n * n`, the sum `s = i + j` will range from `0` 
(top-left corner) all the way up to `2n - 2` (bottom-right corner).
Therefore, there are exactly `2n - 1` anti-diagonals in total!

For a given sum `s`, we can easily find the starting coordinates of the traversal:
- The starting column `j` is simply `s`, but it cannot exceed `n - 1`. So, `j = min(s, n - 1)`.
- The starting row `i` is usually `0`, but for the lower half of the matrix (when `s >= n`), 
  the row index must shift downwards. So, `i = max(0, s - n + 1)`.

Once we have our starting `(i, j)`, we just traverse downwards and leftwards by doing 
`i++` and `j--` until we go out of bounds!

Approach:
1. Initialize an empty vector `ans`.
2. Loop `s` from `0` to `2 * n - 2`.
3. Inside the loop, find the starting point of the current anti-diagonal:
   a. `i = max(0, s - n + 1)`
   b. `j = min(s, n - 1)`
4. Using a `while` loop, traverse the diagonal as long as `i < n` and `j >= 0`:
   a. Push `mat[i][j]` to `ans`.
   b. Increment `i` (move down).
   c. Decrement `j` (move left).
5. Return the populated `ans` vector.

Time Complexity : O(N^2) — Every element in the N x N matrix is visited exactly once.
Space Complexity: O(N^2) — To store the traversal sequence (O(1) auxiliary space).

GFG Link:
https://www.geeksforgeeks.org/problems/print-diagonally1623/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> downwardDiagonal(int n, vector<vector<int>>& mat) {
        vector<int> ans;
        
        // The sum of indices (i + j) ranges from 0 to 2*n - 2
        // This corresponds to the 2*n - 1 total anti-diagonals.
        for (int s = 0; s < 2 * n - 1; s++) {
          
            // Calculate starting coordinates for the current diagonal sum `s`
            int i = max(0, s - n + 1);
            int j = min(s, n - 1);
            
            // Traverse the diagonal: move down (i++) and left (j--)
            while (i < n && j >= 0) {
                ans.push_back(mat[i][j]);
                i++;
                j--;
            }
        }
        
        return ans;
    }
};

/*
Dry Run — Example 1:
mat[][] = [[1, 2, 3],
           [4, 5, 6],
           [7, 8, 9]]
n = 3

s = 0: 
  - i = max(0, -2) = 0. j = min(0, 2) = 0.
  - ans pushes mat[0][0] = 1. i=1, j=-1 (loop ends)

s = 1: 
  - i = max(0, -1) = 0. j = min(1, 2) = 1.
  - ans pushes mat[0][1] = 2. i=1, j=0.
  - ans pushes mat[1][0] = 4. i=2, j=-1 (loop ends)

s = 2: 
  - i = max(0, 0) = 0. j = min(2, 2) = 2.
  - ans pushes mat[0][2] = 3. i=1, j=1.
  - ans pushes mat[1][1] = 5. i=2, j=0.
  - ans pushes mat[2][0] = 7. i=3, j=-1 (loop ends)

s = 3: 
  - i = max(0, 1) = 1. j = min(3, 2) = 2. (Notice `i` shifted downwards)
  - ans pushes mat[1][2] = 6. i=2, j=1.
  - ans pushes mat[2][1] = 8. i=3, j=0 (loop ends)

s = 4:
  - i = max(0, 2) = 2. j = min(4, 2) = 2.
  - ans pushes mat[2][2] = 9. i=3, j=1 (loop ends)

Resulting Output:
[1, 2, 4, 3, 5, 7, 6, 8, 9] ✓
*/
