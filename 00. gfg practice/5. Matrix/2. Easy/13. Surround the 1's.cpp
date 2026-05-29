/*
GeeksforGeeks: Surround the 1's
Difficulty: Easy

Problem:
Given a matrix of order nxm, composed of only 0's and 1's, find the number of 
1's in the matrix that are surrounded by an even number (>0) of 0's. 
The surrounding of a cell in the matrix is defined as the 8 elements around it 
(above, below, left, right, and 4 diagonals). 
Find the number of such 1's.

Example 1:
Input: 
matrix = {{1, 0, 0}, 
          {1, 1, 0}, 
          {0, 1, 0}}
Output: 1
Explanation: 
- 1 at (0, 0) has surrounding elements 0, 1, 1. Occurrences of zero = 1 (odd).
- 1 at (1, 0) has surrounding elements 1, 0, 1, 1, 0. Occurrences of zero = 2 (even!).
- 1 at (1, 1) has an odd number of surrounding 0's.
- 1 at (2, 1) has an odd number of surrounding 0's.
Only 1 such element exists.

Example 2:
Input: 
matrix = {{1}}
Output: 0
Explanation: 
There is only 1 element in the matrix. Hence, it has no surroundings. Count of 0's 
is 0. 0 is even, but the problem strictly requires an even number (>0) of 0's!
Hence, output is 0.

Core Idea:
This is a classic 2D grid traversal problem where we need to check the 8 adjacent 
neighbors of specific cells. 

Instead of writing 8 different messy `if` statements to check bounds and values 
(which is extremely error-prone), we can use **Direction Arrays**. 
By creating two arrays `dx` and `dy` that store the offsets for all 8 directions, 
we can simply loop through these arrays and easily compute the coordinates of 
all valid neighbors in a clean and organized way.

Approach:
1. Define the 8 directional offsets for rows (`dx`) and columns (`dy`).
2. Initialize `ans = 0`.
3. Loop through every element `(i, j)` in the matrix.
4. If `mat[i][j] == 1`:
   a. Initialize `zeroCount = 0`.
   b. Loop `k` from 0 to 7 to check the 8 surrounding cells.
   c. For each direction, compute `ni = i + dx[k]` and `nj = j + dy[k]`.
   d. Check if `(ni, nj)` is within the bounds of the matrix.
   e. If valid and `mat[ni][nj] == 0`, increment `zeroCount`.
5. After checking all 8 neighbors, if `zeroCount > 0` AND `zeroCount % 2 == 0`, 
   increment our final answer `ans`.
6. Return `ans`.

Time Complexity : O(N * M) — We visit each element once and do exactly 8 constant-time checks for each 1.
Space Complexity: O(1) — No extra space is required (except for the tiny size-8 direction arrays).

GFG Link:
https://www.geeksforgeeks.org/problems/surround-the-1s2505/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int Count(vector<vector<int> >& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int ans = 0;
        
        // 8 possible directions (Top-Left, Top, Top-Right, Left, Right, Bottom-Left, Bottom, Bottom-Right)
        int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
        int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                
                // We only care about checking the surroundings of 1's
                if (matrix[i][j] == 1) {
                    int zeroCount = 0;
                    
                    // Check all 8 neighbors cleanly using our direction arrays
                    for (int k = 0; k < 8; k++) {
                        int ni = i + dx[k]; // Neighbor's row
                        int nj = j + dy[k]; // Neighbor's column
                        
                        // Ensure the neighbor coordinate is actually within the matrix bounds
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            
                            // If it's a valid neighbor and it is a 0
                            if (matrix[ni][nj] == 0) {
                                zeroCount++;
                            }
                        }
                    }
                    
                    // Condition: even number (>0) of 0's
                    if (zeroCount > 0 && zeroCount % 2 == 0) {
                        ans++;
                    }
                }
            }
        }
        
        return ans;
    }
};

/*
Dry Run — Example 1:
matrix = {{1, 0, 0}, 
          {1, 1, 0}, 
          {0, 1, 0}}
n = 3, m = 3

i = 1, j = 0: 
  - Cell is 1.
  - Surroundings:
    (0, -1) -> out of bounds
    (0, 0)  -> 1
    (0, 1)  -> 0 (zeroCount = 1)
    (1, -1) -> out of bounds
    (1, 1)  -> 1
    (2, -1) -> out of bounds
    (2, 0)  -> 0 (zeroCount = 2)
    (2, 1)  -> 1
  - zeroCount is 2. 
  - 2 > 0 and 2 % 2 == 0. 
  - ans = 1

Return ans = 1 ✓
*/
