/*
GeeksforGeeks: Print Matrix in snake Pattern
Difficulty: Easy

Problem:
Given a matrix mat[][] of size n x n. Print the elements of the matrix 
in the snake like pattern.

Example 1:
Input: n = 3, 
mat[][] = [[45, 48, 54], 
           [21, 89, 87], 
           [70, 78, 15]]
Output: [45, 48, 54, 87, 89, 21, 70, 78, 15] 
Explanation: 
Printing it in snake pattern goes:
- Row 0 (left to right): 45, 48, 54
- Row 1 (right to left): 87, 89, 21
- Row 2 (left to right): 70, 78, 15

Example 2:
Input: n = 2, 
mat[][] = [[1, 2], 
           [3, 4]]
Output: [1, 2, 4, 3] 
Explanation: 
- Row 0 (left to right): 1, 2
- Row 1 (right to left): 4, 3

Core Idea:
A "snake pattern" simply means we alternate the direction in which we read 
each row. 
- The 0th row (even) is read normally from left to right.
- The 1st row (odd) is read backwards from right to left.
- The 2nd row (even) is read normally from left to right.

By just checking if the current row index `i` is even or odd (`i % 2`), 
we can decide whether to run our inner column loop forwards or backwards!

Approach:
1. Initialize an empty vector `ans`.
2. Loop through each row `i` from `0` to `n - 1`.
3. If `i % 2 == 0` (even row):
   - Loop `j` from `0` to `n - 1` and push `matrix[i][j]` into `ans`.
4. Else if `i % 2 != 0` (odd row):
   - Loop `j` from `n - 1` down to `0` and push `matrix[i][j]` into `ans`.
5. Return the populated `ans` vector.

Time Complexity : O(N^2) — We visit each element of the N x N matrix exactly once.
Space Complexity: O(N^2) — To store the sequence in the result vector (O(1) auxiliary space).

GFG Link:
https://www.geeksforgeeks.org/problems/print-matrix-in-snake-pattern-1587115621/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {   
public:
    // Function to return list of integers visited in snake pattern in matrix.
    vector<int> snakePattern(vector<vector<int>>& matrix) {   
        vector<int> ans;
        int n = matrix.size();
        
        for (int i = 0; i < n; i++) {
            // Even rows: Traverse Left to Right
            if (i % 2 == 0) {
                for (int j = 0; j < n; j++) {
                    ans.push_back(matrix[i][j]);
                }
            } 
            // Odd rows: Traverse Right to Left
            else {
                for (int j = n - 1; j >= 0; j--) {
                    ans.push_back(matrix[i][j]);
                }
            }
        }
        
        return ans;
    }
};

/*
Dry Run — Example 1:
mat[][] = [[45, 48, 54], 
           [21, 89, 87], 
           [70, 78, 15]]
n = 3

i = 0 (Even Row):
  - Left to Right loop: j = 0 to 2
  - ans = [45, 48, 54]

i = 1 (Odd Row):
  - Right to Left loop: j = 2 to 0
  - ans = [45, 48, 54, 87, 89, 21]

i = 2 (Even Row):
  - Left to Right loop: j = 0 to 2
  - ans = [45, 48, 54, 87, 89, 21, 70, 78, 15]

Return [45, 48, 54, 87, 89, 21, 70, 78, 15] ✓
*/
