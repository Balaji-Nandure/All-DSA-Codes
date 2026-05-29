/*
GeeksforGeeks: Search in a Row-Column Sorted Matrix
Difficulty: Easy

Problem:
Given a 2D integer matrix mat[][] of size n x m, where every row and column is 
sorted in increasing order, and a number x, the task is to find whether element 
x is present in the matrix.

Example 1:
Input: 
mat[][] = [[3,  30, 38],
           [20, 52, 54],
           [35, 60, 69]]
x = 62
Output: false
Explanation: 62 is not present in the matrix.

Example 2:
Input: 
mat[][] = [[18, 21, 27],
           [38, 55, 67]]
x = 55
Output: true
Explanation: 55 is present in the matrix.

Core Idea:
Because the matrix is sorted both row-wise and column-wise, we can use a highly 
efficient "Staircase Search" starting from the Top-Right corner of the matrix.

Why the Top-Right corner? 
If we stand at `mat[0][m-1]`:
- Everything to the **left** in the same row is **smaller** than the current element.
- Everything **below** in the same column is **larger** than the current element.

This gives us a binary-search-like decision tree:
1. If `mat[i][j] == x`, we found it!
2. If `mat[i][j] > x`, the current element is too big. Since everything below it 
   is even bigger, `x` cannot possibly be in this column. So, we move left (`j--`).
3. If `mat[i][j] < x`, the current element is too small. Since everything to its 
   left is even smaller, `x` cannot possibly be in this row. So, we move down (`i++`).

Approach:
1. Handle edge cases (empty matrix).
2. Set pointers: `i = 0` (first row), `j = m - 1` (last column).
3. Loop while `i < n` and `j >= 0`:
   a. If `mat[i][j] == x`, return `true`.
   b. If `mat[i][j] > x`, move left (`j--`).
   c. If `mat[i][j] < x`, move down (`i++`).
4. If the loop ends without returning true, the element is not in the matrix. Return `false`.

Time Complexity : O(N + M) — In the worst case, we travel from the top-right to the bottom-left, traversing at most N rows and M columns.
Space Complexity: O(1) — No extra space is used.

GFG Link:
https://www.geeksforgeeks.org/problems/search-in-a-matrix1720/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool matSearch(vector<vector<int>> &mat, int x) {
        if (mat.empty() || mat[0].empty()) {
            return false;
        }
        
        int n = mat.size();
        int m = mat[0].size();
        
        // Start from the Top-Right corner
        int i = 0;
        int j = m - 1;
        
        while (i < n && j >= 0) {
            if (mat[i][j] == x) {
                return true; // Found the element
            } 
            else if (mat[i][j] > x) {
                // Current element is too large, move left to find smaller elements
                j--;
            } 
            else {
                // Current element is too small, move down to find larger elements
                i++;
            }
        }
        
        // If we exit the loop, the element doesn't exist
        return false;
    }
};

/*
Dry Run — Example 2:
mat[][] = [[18, 21, 27],
           [38, 55, 67]]
x = 55

Initial:
i = 0, j = 2 (Top-Right corner)
mat[0][2] = 27

Iteration 1:
- mat[0][2] (27) < 55.
- 27 is too small. Move down.
- i = 1, j = 2.

Iteration 2:
- mat[1][2] (67) > 55.
- 67 is too large. Move left.
- i = 1, j = 1.

Iteration 3:
- mat[1][1] (55) == 55!
- Match found! Return true. ✓
*/
