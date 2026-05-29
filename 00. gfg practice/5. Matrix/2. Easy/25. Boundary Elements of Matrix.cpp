/*
GeeksforGeeks: Boundary Elements of Matrix
Difficulty: Easy

Problem:
Given an nxn matrix. In the given matrix, you have to find the boundary elements of the matrix.
Return a list containing the boundary elements of the matrix in the same order in which they appear in the input matrix (row-wise).

Example 1:
Input: 
[[1, 2, 3] 
 [4, 5, 6] 
 [7, 8, 9]]
Output: 1 2 3 4 6 7 8 9
Explanation: 
The boundary elements are the elements in the first row, last row, first column, and last column. 
Reading them row by row, we get 1, 2, 3, 4, 6, 7, 8, 9.

Example 2:
Input: 
[[1, 2]
 [3, 4]]
Output: 1 2 3 4

Core Idea:
Since we need to return the boundary elements in the same order they appear in the matrix (which implies row-wise order), we can simply iterate through the entire matrix using two nested loops (row `i` and column `j`).
For each element, we check if it lies on the boundary. An element is on the boundary if:
- It is in the first row (`i == 0`)
- It is in the last row (`i == n - 1`)
- It is in the first column (`j == 0`)
- It is in the last column (`j == n - 1`)
If any of these conditions are met, we add it to our result array.

Approach:
1. Initialize a `result` vector.
2. Get the matrix size `n`.
3. Loop `i` from 0 to `n - 1`.
4. Loop `j` from 0 to `n - 1`.
5. If `i == 0` or `i == n - 1` or `j == 0` or `j == n - 1`, append `matrix[i][j]` to `result`.
6. Return `result`.

Time Complexity : O(n^2) — We visit every single element in the matrix exactly once to check if it's a boundary element.
Space Complexity: O(1) — We don't use any extra auxiliary space (excluding the array required to return the result).

GFG Link:
https://www.geeksforgeeks.org/problems/boundary-elements-of-matrix/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> BoundaryElements(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> result;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Check if current cell is on the boundary
                if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                    result.push_back(matrix[i][j]);
                }
            }
        }
        
        return result;
    }
};

/*
Dry Run — Example 1:
Input: 
matrix = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9]
]
n = 3

Iteration details:
- Row i = 0:
  - j = 0: (i=0) -> boundary. add 1. result = [1]
  - j = 1: (i=0) -> boundary. add 2. result = [1, 2]
  - j = 2: (i=0) -> boundary. add 3. result = [1, 2, 3]
- Row i = 1:
  - j = 0: (j=0) -> boundary. add 4. result = [1, 2, 3, 4]
  - j = 1: not boundary. skip 5.
  - j = 2: (j=2) -> boundary. add 6. result = [1, 2, 3, 4, 6]
- Row i = 2:
  - j = 0: (i=2) -> boundary. add 7. result = [1, 2, 3, 4, 6, 7]
  - j = 1: (i=2) -> boundary. add 8. result = [1, 2, 3, 4, 6, 7, 8]
  - j = 2: (i=2) -> boundary. add 9. result = [1, 2, 3, 4, 6, 7, 8, 9]

Output: [1, 2, 3, 4, 6, 7, 8, 9]
Matches expected output perfectly! ✓
*/
