/*
GeeksforGeeks: Coverage of all Zeros in a Binary Matrix
Difficulty: Easy

Problem:
Given a binary matrix mat[][] containing only 0s and 1s, find the total coverage 
of all 0's. The coverage of a particular 0 cell is defined by checking its four 
directions (left, right, up, and down). For each direction, if there is at least 
one 1 anywhere between the 0 and the boundary of the matrix, the coverage increases by one.

Return the sum of the coverage values for all 0 cells in the matrix.

Example 1:
Input : 
matrix = [[1, 1, 1, 0],
          [1, 0, 0, 1]]
Output : 8
Explanation: 
Zeros are at (0,3), (1,1), and (1,2).
- Zero at (0,3): 
  - Left: sees a 1 at (0,2). (+1)
  - Right: boundary.
  - Up: boundary.
  - Down: sees a 1 at (1,3). (+1)
  Coverage = 2.
- Zero at (1,1): 
  - Left: sees a 1 at (1,0). (+1)
  - Right: sees a 1 at (1,3). (+1)
  - Up: sees a 1 at (0,1). (+1)
  - Down: boundary.
  Coverage = 3.
- Zero at (1,2):
  - Left: sees a 1 at (1,0). (+1)
  - Right: sees a 1 at (1,3). (+1)
  - Up: sees a 1 at (0,2). (+1)
  - Down: boundary.
  Coverage = 3.
Total coverage = 2 + 3 + 3 = 8.

Example 2:
Input: 
matrix = [[0, 1, 0],
          [0, 1, 1],
          [0, 0, 0]]
Output: 6

Core Idea:
For every single `0` in the matrix, we need to look strictly to its Left, Right, 
Up, and Down. We send out a "ray" in each of those 4 directions. 
If the ray hits a `1` before hitting the edge of the matrix, we increment the 
coverage for that `0` and immediately stop looking in that specific direction 
(because we only care if *at least one* 1 exists, multiple 1s in the same 
direction don't grant extra coverage).

Since the matrix size is small (N, M <= 100), we can just manually loop out in 
all 4 directions for every single `0`. 

Approach:
1. Initialize `coverage = 0`.
2. Iterate through every cell `(i, j)` in the matrix.
3. If `matrix[i][j] == 0`:
   - Loop left `c` from `j-1` down to 0. If `mat[i][c] == 1`, `coverage++` and `break`.
   - Loop right `c` from `j+1` up to m-1. If `mat[i][c] == 1`, `coverage++` and `break`.
   - Loop up `r` from `i-1` down to 0. If `mat[r][j] == 1`, `coverage++` and `break`.
   - Loop down `r` from `i+1` up to n-1. If `mat[r][j] == 1`, `coverage++` and `break`.
4. Return `coverage`.

Time Complexity : O(N * M * (N + M)) — For each 0, we might scan up to N elements vertically and M elements horizontally. For constraints <= 100, this is extremely fast.
Space Complexity: O(1) — No extra space is required.

GFG Link:
https://www.geeksforgeeks.org/problems/coverage-of-all-zeros-in-a-binary-matrix4024/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findCoverage(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        int m = matrix[0].size();
        
        int coverage = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                
                // We only calculate coverage for cells that contain a 0
                if (matrix[i][j] == 0) {
                    
                    // 1. Send a ray LEFT
                    for (int c = j - 1; c >= 0; c--) {
                        if (matrix[i][c] == 1) {
                            coverage++;
                            break; // Stop looking further left
                        }
                    }
                    
                    // 2. Send a ray RIGHT
                    for (int c = j + 1; c < m; c++) {
                        if (matrix[i][c] == 1) {
                            coverage++;
                            break; // Stop looking further right
                        }
                    }
                    
                    // 3. Send a ray UP
                    for (int r = i - 1; r >= 0; r--) {
                        if (matrix[r][j] == 1) {
                            coverage++;
                            break; // Stop looking further up
                        }
                    }
                    
                    // 4. Send a ray DOWN
                    for (int r = i + 1; r < n; r++) {
                        if (matrix[r][j] == 1) {
                            coverage++;
                            break; // Stop looking further down
                        }
                    }
                    
                }
            }
        }
        
        return coverage;
    }
};

/*
Dry Run — Example 2:
matrix = [[0, 1, 0],
          [0, 1, 1],
          [0, 0, 0]]

- Zero at (0,0):
  - Left: none
  - Right: hits 1 at (0,1). (+1)
  - Up: none
  - Down: checks (1,0)=0, (2,0)=0. Hits boundary.
  Cov = 1

- Zero at (0,2):
  - Left: hits 1 at (0,1). (+1)
  - Right: none
  - Up: none
  - Down: hits 1 at (1,2). (+1)
  Cov = 2

- Zero at (1,0):
  - Left: none
  - Right: hits 1 at (1,1). (+1)
  - Up: checks (0,0)=0.
  - Down: checks (2,0)=0.
  Cov = 1

- Zero at (2,0):
  - Left/Right/Up/Down: all 0s. 
  Cov = 0

- Zero at (2,1):
  - Up: hits 1 at (1,1). (+1)
  Cov = 1

- Zero at (2,2):
  - Up: hits 1 at (1,2). (+1)
  Cov = 1

Total Coverage = 1 + 2 + 1 + 0 + 1 + 1 = 6. ✓
*/
