/*
GeeksforGeeks: Make Zeroes
Difficulty: Easy

Problem:
Given a matrix mat[][] of size n x m. Your task is to process Zeroes, that means 
in the whole matrix when you find a zero, change that element to the sum of the 
upper, lower, left and right value and make its four adjacent (upper, lower, 
left, and right) values zero.

Example 1:
Input: 
mat[][] = [[1, 2, 3, 4]
           [5, 6, 0, 7] 
           [8, 9, 4, 6]
           [8, 4, 5, 2]]
Output: 
mat[][] = [[1, 2, 0, 4]
           [5, 0, 20, 0]
           [8, 9, 0, 6] 
           [8, 4, 5, 2]]
Explanation: 
mat[1][2] = 0. We perform the operation here. 
mat[1][2] becomes the sum of its neighbors (3 + 6 + 7 + 4 = 20).
Its neighbors (0,2), (2,2), (1,1), and (1,3) all become 0.

Core Idea:
Because there might be multiple zeros in the matrix, if we process them directly 
on the original matrix, the changes from the first zero might incorrectly alter 
the sums for the subsequent zeros!

To process all zeros "simultaneously" and independently, we absolutely must read 
the values from an untouched, original version of the matrix, while writing the 
updates and zeros into the actual `mat` array.
So, we can simply create a clone of the matrix (`temp`). We will loop through 
`temp`, and whenever we find a 0, we sum up its neighbors in `temp`, and then 
modify the actual `matrix` to reflect the zeroed-out neighbors and the new sum.

Approach:
1. Create a full copy of the matrix: `vector<vector<int>> temp = matrix`.
2. Define the 4 directions (up, down, left, right) using `dx` and `dy` arrays.
3. Loop through every element `(i, j)` in `temp`.
4. If `temp[i][j] == 0`:
   a. Initialize `sum = 0`.
   b. Loop through the 4 directions.
   c. If a neighbor `(ni, nj)` is valid, add `temp[ni][nj]` to `sum`.
   d. Set the neighbor in the actual `matrix` to 0: `matrix[ni][nj] = 0`.
   e. Set the current cell in the actual `matrix` to the sum: `matrix[i][j] = sum`.
5. Return (matrix is modified in-place).

Time Complexity : O(N * M) — We visit every element once and do up to 4 constant-time neighbor checks.
Space Complexity: O(N * M) — We create a copy of the matrix to read original values safely.

GFG Link:
https://www.geeksforgeeks.org/problems/make-zeroes4042/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void MakeZeros(vector<vector<int> >& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        // Create a copy of the matrix to read untouched original values
        vector<vector<int>> temp = matrix;
        
        // 4 directions: Up, Down, Left, Right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                
                // If we find a 0 in the original matrix
                if (temp[i][j] == 0) {
                    int sum = 0;
                    
                    // Check all 4 adjacent neighbors
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        
                        // If neighbor is within bounds
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            
                            // Add the ORIGINAL neighbor's value to the sum
                            sum += temp[ni][nj];
                            
                            // Set the ACTUAL matrix's neighbor to 0
                            matrix[ni][nj] = 0;
                        }
                    }
                    
                    // Set the actual matrix's current cell to the calculated sum
                    matrix[i][j] = sum;
                }
            }
        }
    }
};

/*
Dry Run — Example 1:
temp[][] = [[1, 2, 3, 4]
            [5, 6, 0, 7] 
            [8, 9, 4, 6]
            [8, 4, 5, 2]]

We find a 0 at i=1, j=2.
Neighbors of (1, 2):
- Up (0, 2): temp is 3. matrix[0][2] = 0. sum = 3
- Down (2, 2): temp is 4. matrix[2][2] = 0. sum = 3 + 4 = 7
- Left (1, 1): temp is 6. matrix[1][1] = 0. sum = 7 + 6 = 13
- Right (1, 3): temp is 7. matrix[1][3] = 0. sum = 13 + 7 = 20

Current cell: matrix[1][2] = 20.

Final matrix matches the required output perfectly. ✓
*/
