/*
GeeksforGeeks: Reversing the columns of a Matrix
Difficulty: Easy

Problem:
Given a matrix of size n x m, reverse the order of its columns in-place so that the last column becomes the first, the second-last becomes the second, and so on.

Example 1:
Input: n = 4, m = 3, matrix[][] = [[1, 2, 3], [5, 6, 7], [11, 10, 9], [13, 14, 15]]
Output: [[3, 2, 1], [7, 6, 5], [9, 10, 11], [15, 14, 13]]
Explanation: Array after exchanging columns:
              [[3, 2, 1],
               [7, 6, 5],
               [9, 10, 11],
               [15, 14, 13]]

Core Idea:
Since we are reversing the columns of the matrix in-place, we can simply iterate through each row of the matrix and reverse the elements of that row using a two-pointer approach (swapping the first and last elements, then moving inwards).

Approach:
1. Iterate over each row `i` from 0 to `n-1`.
2. For each row, use two pointers `left = 0` and `right = m - 1`.
3. Swap `matrix[i][left]` and `matrix[i][right]`.
4. Increment `left` and decrement `right` until `left >= right`.
5. The matrix is modified in-place.

Time Complexity : O(N * M) — We iterate through half of the columns for each row, visiting every element exactly once.
Space Complexity: O(1) — We are modifying the matrix in-place without using any extra space.

GFG Link:
https://www.geeksforgeeks.org/problems/reversing-the-columns-of-a-matrix-1587115621/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void reverseCol(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if(n == 0) return;
        int m = matrix[0].size();
        
        // Iterate through each row
        for (int i = 0; i < n; i++) {
            int left = 0;
            int right = m - 1;
            
            // Swap elements from the ends towards the center for each row
            while (left < right) {
                swap(matrix[i][left], matrix[i][right]);
                left++;
                right--;
            }
        }
    }
};

/*
Dry Run — Example 1:
Input: 
n = 4, m = 3
matrix = [
  [1, 2, 3],
  [5, 6, 7],
  [11, 10, 9],
  [13, 14, 15]
]

Row 0: [1, 2, 3] -> left = 0, right = 2 -> swap(1, 3) -> [3, 2, 1]
Row 1: [5, 6, 7] -> left = 0, right = 2 -> swap(5, 7) -> [7, 6, 5]
Row 2: [11, 10, 9] -> left = 0, right = 2 -> swap(11, 9) -> [9, 10, 11]
Row 3: [13, 14, 15] -> left = 0, right = 2 -> swap(13, 15) -> [15, 14, 13]

Output:
[
  [3, 2, 1],
  [7, 6, 5],
  [9, 10, 11],
  [15, 14, 13]
]

Final matrix matches the required output perfectly. ✓
*/
