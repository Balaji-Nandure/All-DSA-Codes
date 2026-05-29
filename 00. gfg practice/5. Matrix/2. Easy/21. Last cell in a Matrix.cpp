/*
GeeksforGeeks: Last cell in a Matrix
Difficulty: Easy

Problem:
Given a binary matrix of dimensions R x C. Start from cell(0, 0), moving in the right direction. Perform the following operations: 
- If the value of matrix[i][j] is 0, then traverse in the same direction and check the next value.
- If the value of matrix[i][j] is 1, then update matrix[i][j] to 0 and change the current direction clockwise. ie - up, right, down, or left directions change to right, down, left, and up respectively.
Find the index of the cell where you will be forced to exit the matrix while performing the given traversal.

Example 1:
Input:
matrix[][] = {{0,1},
              {1,0}}
R=2, C=2
Output: (1,1)

Example 2:
Input: 
matrix[][] = {{0, 1, 1, 1, 0},
              {1, 0, 1, 0, 1},
              {1, 1, 1, 0, 0}}
R=3, C=5
Output: (2,0)
Explanation: We will leave the grid after visiting the index (2,0).

Core Idea:
We can simulate the entire process. We start at (0, 0) facing Right.
We maintain our current direction using an integer (0: Right, 1: Down, 2: Left, 3: Up).
At each step, we keep track of the current cell before moving. If we encounter a 1, we flip it to 0 and turn 90 degrees clockwise `dir = (dir + 1) % 4`.
Then we move one step in the current direction. When we step out of the bounds of the matrix, the previous valid cell we visited is our answer.

Approach:
1. Define direction arrays for Right, Down, Left, and Up respectively: `dx = {0, 1, 0, -1}` and `dy = {1, 0, -1, 0}`.
2. Initialize `dir = 0` (Right).
3. Initialize current coordinates `i = 0`, `j = 0` and tracking coordinates `prev_i = 0`, `prev_j = 0`.
4. Loop while `i` and `j` are within the matrix boundaries (0 to R-1 and 0 to C-1).
5. Inside the loop, update `prev_i = i` and `prev_j = j`.
6. If `matrix[i][j] == 1`, set it to `0`, and update direction `dir = (dir + 1) % 4`.
7. Move to the next cell: `i += dx[dir]` and `j += dy[dir]`.
8. Once the loop exits, return `{prev_i, prev_j}`.

Time Complexity : O(R * C) — We visit at most every cell in the matrix a few times. Once a 1 is flipped to a 0, it behaves like a straight path, capping the maximum possible steps.
Space Complexity: O(1) — We modify the matrix in-place and use only O(1) extra space.

GFG Link:
https://www.geeksforgeeks.org/problems/last-cell-in-a-matrix/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    pair<int,int> endPoints(vector<vector<int>> matrix, int R, int C) {
        // Directions: 0 = Right, 1 = Down, 2 = Left, 3 = Up
        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};
        
        int dir = 0;
        int i = 0, j = 0;
        int prev_i = 0, prev_j = 0;
        
        while (i >= 0 && i < R && j >= 0 && j < C) {
            // Keep track of the last valid cell
            prev_i = i;
            prev_j = j;
            
            // If we hit a 1, change it to 0 and turn right (clockwise)
            if (matrix[i][j] == 1) {
                matrix[i][j] = 0;
                dir = (dir + 1) % 4;
            }
            
            // Move in the current direction
            i += dx[dir];
            j += dy[dir];
        }
        
        return {prev_i, prev_j};
    }
};

/*
Dry Run — Example 1:
Input:
R = 2, C = 2
matrix = [
  [0, 1],
  [1, 0]
]

Initial state: i = 0, j = 0, dir = 0 (Right)

Step 1:
- prev_i = 0, prev_j = 0
- matrix[0][0] is 0. No direction change.
- Move Right: i = 0 + 0 = 0, j = 0 + 1 = 1
- matrix state: unchanged

Step 2:
- prev_i = 0, prev_j = 1
- matrix[0][1] is 1. Change to 0, dir becomes (0 + 1) % 4 = 1 (Down).
- Move Down: i = 0 + 1 = 1, j = 1 + 0 = 1
- matrix state:
  [0, 0]
  [1, 0]

Step 3:
- prev_i = 1, prev_j = 1
- matrix[1][1] is 0. No direction change.
- Move Down: i = 1 + 1 = 2, j = 1 + 0 = 1
- matrix state: unchanged

Condition `i < R` fails because i = 2.
Loop terminates.

Return {prev_i, prev_j} -> {1, 1}
Final Output matches perfectly. ✓
*/
