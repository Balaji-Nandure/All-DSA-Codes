/*
GeeksforGeeks: Sum of upper and lower triangles
Difficulty: Easy

Problem:
Given a square matrix mat[][] of size n*n, return an array of two elements 
containing two values: the sum of Upper Triangle elements and the sum of Lower 
Triangle elements. 
- Upper Triangle consists of elements on the diagonal and above it. 
- Lower Triangle consists of elements on the diagonal and below it. 

Example 1:
Input: 
n = 3, 
mat[][] = [[6, 5, 4],
           [1, 2, 5],
           [7, 9, 7]]
Output: [29, 32]
Explanation: 
Upper triangular matrix:
6 5 4
  2 5
    7
Sum = 6 + 5 + 4 + 2 + 5 + 7 = 29.
Lower triangular matrix:
6
1 2
7 9 7
Sum = 6 + 1 + 2 + 7 + 9 + 7 = 32.

Example 2:
Input: 
n = 2, 
mat[][] = [[1, 2],
           [3, 4]]
Output: [7, 8]
Explanation: 
Upper triangular matrix:
1 2
  4
Sum = 1 + 2 + 4 = 7.
Lower triangular matrix:
1
3 4
Sum = 1 + 3 + 4 = 8.

Core Idea:
In a square matrix:
- The **Upper Triangle** (including the diagonal) consists of all elements where 
  the column index `j` is greater than or equal to the row index `i` (`j >= i`).
- The **Lower Triangle** (including the diagonal) consists of all elements where 
  the column index `j` is less than or equal to the row index `i` (`j <= i`).

Instead of looping through the entire matrix and checking `if (j >= i)`, we can 
highly optimize the solution by just running our inner loops directly on the bounds 
of the respective triangles!
- For the Upper Triangle sum, we loop `j` directly from `i` to `n - 1`.
- For the Lower Triangle sum, we loop `j` directly from `0` to `i`.

Approach:
1. Initialize `upperSum = 0` and `lowerSum = 0`.
2. Iterate through each row `i` from `0` to `n - 1`.
3. Inner loop 1 (Upper Triangle): Loop `j` from `i` to `n - 1`, adding `mat[i][j]` to `upperSum`.
4. Inner loop 2 (Lower Triangle): Loop `j` from `0` to `i`, adding `mat[i][j]` to `lowerSum`.
5. Return the vector `{upperSum, lowerSum}`.

Time Complexity : O(N^2) — We iterate over the elements in the upper and lower triangles.
Space Complexity: O(1) — No extra space is used (excluding the size 2 output array).

GFG Link:
https://www.geeksforgeeks.org/problems/sum-of-upper-and-lower-triangles-1587115621/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sumTriangles(const vector<vector<int> >& matrix, int n) {
        int upperSum = 0;
        int lowerSum = 0;
        
        for (int i = 0; i < n; i++) {
            
            // Upper Triangle: column index 'j' starts at 'i' and goes to the end
            for (int j = i; j < n; j++) {
                upperSum += matrix[i][j];
            }
            
            // Lower Triangle: column index 'j' starts at '0' and stops at 'i'
            for (int j = 0; j <= i; j++) {
                lowerSum += matrix[i][j];
            }
        }
        
        return {upperSum, lowerSum};
    }
};

/*
Dry Run — Example 2:
mat[][] = [[1, 2],
           [3, 4]]
n = 2

Initial: upperSum = 0, lowerSum = 0

i = 0:
  - Upper loop (j from 0 to 1):
      j=0: upperSum += mat[0][0] (1) -> 1
      j=1: upperSum += mat[0][1] (2) -> 3
  - Lower loop (j from 0 to 0):
      j=0: lowerSum += mat[0][0] (1) -> 1

i = 1:
  - Upper loop (j from 1 to 1):
      j=1: upperSum += mat[1][1] (4) -> 7
  - Lower loop (j from 0 to 1):
      j=0: lowerSum += mat[1][0] (3) -> 4
      j=1: lowerSum += mat[1][1] (4) -> 8

Final Result:
upperSum = 7
lowerSum = 8
Returns [7, 8]. ✓
*/
