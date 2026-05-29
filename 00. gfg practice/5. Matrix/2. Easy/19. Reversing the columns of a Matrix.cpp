/*
    Problem Name: Reversing the columns of a Matrix
    Difficulty: Easy
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
            
            // Note: Alternatively, we can use the built-in reverse function:
            // reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

/*
Time Complexity: O(n * m), where n is the number of rows and m is the number of columns. We iterate through half of the columns for each row.
Space Complexity: O(1), as we are modifying the matrix in-place without using any extra space.

Dry Run:
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
*/
