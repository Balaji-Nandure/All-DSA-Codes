/*
GeeksforGeeks: Interchanging the rows of a Matrix
Difficulty: Easy

Problem:
Given a matrix of dimensions n1 x m1. Interchange its rows in-place such that the first row will become the last row and so on.

Example 1:
Input:
n1 = 4, m1 = 4
matrix[][] = {{1, 2, 3, 4},
             {5, 6, 7, 8},
             {9, 10, 11, 12},
             {13, 14, 15,16}}
Output: 
13 14 15 16 9 10 11 12 5 6 7 8 1 2 3 4
Explanation:
Matrix after exchanging rows:
13 14 15 16
 9 10 11 12
 5  6  7  8
 1  2  3  4

Core Idea:
To interchange the rows such that the first becomes the last, the second becomes the second last, and so on, we can use a two-pointer approach on the rows. We swap the 0th row with the (n1-1)th row, the 1st row with the (n1-2)th row, continuing until we reach the middle of the matrix.

Approach:
1. Initialize two pointers: `top = 0` and `bottom = n1 - 1`.
2. While `top < bottom`, swap the entire row `matrix[top]` with `matrix[bottom]`.
3. In C++, `std::swap` on vectors is highly optimized (O(1) time), making the row swap extremely efficient.
4. Increment `top` and decrement `bottom`.
5. The matrix is modified in-place.

Time Complexity : O(N) — Swapping two vectors takes O(1) time in C++, and we do this N/2 times. The expected complexity is O(N * M), which this comfortably beats.
Space Complexity: O(1) — We are modifying the matrix in-place without using any extra space.

GFG Link:
https://www.geeksforgeeks.org/problems/interchanging-the-rows-of-a-matrix/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void interchangeRows(vector<vector<int>>& matrix) {
        int n1 = matrix.size();
        if(n1 == 0) return;
        
        int top = 0;
        int bottom = n1 - 1;
        
        // Swap rows from top and bottom moving towards the center
        while (top < bottom) {
            swap(matrix[top], matrix[bottom]);
            top++;
            bottom--;
        }
    }
};

/*
Dry Run — Example 1:
Input: 
n1 = 4, m1 = 4
matrix = [
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9, 10, 11, 12],
  [13, 14, 15, 16]
]

top = 0, bottom = 3
- swap(matrix[0], matrix[3])
matrix becomes:
  [13, 14, 15, 16]
  [5, 6, 7, 8]
  [9, 10, 11, 12]
  [1, 2, 3, 4]
top = 1, bottom = 2

top = 1, bottom = 2
- swap(matrix[1], matrix[2])
matrix becomes:
  [13, 14, 15, 16]
  [9, 10, 11, 12]
  [5, 6, 7, 8]
  [1, 2, 3, 4]
top = 2, bottom = 1

Loop terminates since top (2) is not less than bottom (1).

Output:
[
  [13, 14, 15, 16],
  [9, 10, 11, 12],
  [5, 6, 7, 8],
  [1, 2, 3, 4]
]

Final matrix matches the required output perfectly. ✓
*/
