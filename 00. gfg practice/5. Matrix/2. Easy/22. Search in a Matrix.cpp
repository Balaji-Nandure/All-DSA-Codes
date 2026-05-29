/*
GeeksforGeeks: Search in a Matrix
Difficulty: Easy

Problem:
Given a 2D integer array mat[][] of n rows and m columns and a number x, find whether element x is present in the matrix or not.

Example 1:
Input: mat[][] = [[6, 23, 21], [4, 45, 32], [69, 11, 87]], x = 32
Output: true
Explanation: 32 is present in the matrix.

Example 2:
Input: mat[][] = [[14, 34, 23, 95, 43, 28]], x = 55
Output: false
Explanation: 55 is not present in the matrix.

Example 3:
Input: mat[][] = [[87, 9, 99], [101, 3, 111]], x = 101
Output: true
Explanation: 101 is present in the matrix.

Core Idea:
Since the problem does not mention the matrix being sorted in any particular way, the only reliable way to check if an element exists is to perform a linear search through the entire 2D matrix. We check each cell, and if we find the value `x`, we can immediately return `true`.

Approach:
1. Get the number of rows `n` and columns `m`.
2. Use a nested loop to iterate over each row `i` and each column `j`.
3. At each cell, check if `mat[i][j] == x`.
4. If it matches, return `true`.
5. If both loops finish without finding `x`, return `false`.

Time Complexity : O(N * M) — In the worst-case scenario (when `x` is not in the matrix or is at the very end), we check every cell once.
Space Complexity: O(1) — We are only using a couple of variables for iteration, modifying nothing and using no extra space.

GFG Link:
https://www.geeksforgeeks.org/problems/search-in-a-matrix-1587115621/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int x) {
        int n = mat.size();
        if(n == 0) return false;
        int m = mat[0].size();
        
        // Traverse the entire matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                
                // If element is found, return true
                if (mat[i][j] == x) {
                    return true;
                }
            }
        }
        
        // Element was not found
        return false;
    }
};

/*
Dry Run — Example 1:
Input: 
mat = [
  [6, 23, 21],
  [4, 45, 32],
  [69, 11, 87]
]
x = 32

Iteration details:
- i=0, j=0: mat[0][0]=6. Not 32.
- i=0, j=1: mat[0][1]=23. Not 32.
- i=0, j=2: mat[0][2]=21. Not 32.
- i=1, j=0: mat[1][0]=4. Not 32.
- i=1, j=1: mat[1][1]=45. Not 32.
- i=1, j=2: mat[1][2]=32. Matches 32!
Return true.

Final Output matches expected output perfectly. ✓
*/
