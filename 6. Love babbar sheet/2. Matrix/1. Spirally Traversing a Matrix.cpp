// Problem: Spirally Traversing a Matrix
// Link (GFG): https://www.geeksforgeeks.org/problems/spirally-traversing-a-matrix-1587115621/1
// Article: https://www.geeksforgeeks.org/dsa/print-a-given-matrix-in-spiral-form/
// Difficulty: Medium
// Topic: Matrix, Simulation, Two Pointers / Boundaries

/*
Problem Statement:
Given a matrix of size r*c. Traverse the matrix in spiral form.
Start from top-left, move right across top row, then downwards along right column, 
then left across bottom row, then upwards along left column, and repeat inward until 
all elements have been visited.

Example 1:
Input:
r = 4, c = 4
matrix = [[1, 2, 3, 4],
          [5, 6, 7, 8],
          [9, 10, 11, 12],
          [13, 14, 15, 16]]
Output: 
1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10

Example 2:
Input:
r = 3, c = 4
matrix = [[1, 2, 3, 4],
          [5, 6, 7, 8],
          [9, 10, 11, 12]]
Output: 
1 2 3 4 8 12 11 10 9 5 6 7

Constraints:
- 1 <= r, c <= 1000
- -100 <= matrix[i][j] <= 100
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In 1D Array Traversals (Problems 1-36):
//   * Traversal was linear (from 0 to N-1, or converging two pointers left -> <- right).
// - In 2D Matrix Spiral Traversal:
//   * Traversal is 2-dimensional and changes directional momentum 4 times per outer layer 
//     (Right -> Down -> Left -> Up).
//   * Key trap: In rectangular matrices (r != c), after moving Right and Down, the inner row 
//     or column might already be exhausted! If you blindly traverse Left and Up without checking 
//     `top <= bottom` and `left <= right`, elements get printed multiple times.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Visited Matrix / State Machine
//   - Maintain a boolean `visited[r][c]` and a direction vector `(dr, dc)` rotating clockwise.
//   - Why Suboptimal: Requires O(r * c) extra auxiliary memory for visited flags.
//
// Approach 2: 4-Boundary Layer Peeling (Optimal & Chosen)
//   - Maintain four boundary pointers: `top = 0`, `bottom = r - 1`, `left = 0`, `right = c - 1`.
//   - While `top <= bottom && left <= right`:
//     1. Traverse from `left` to `right` along `top` row. Then increment `top++`.
//     2. Traverse from `top` to `bottom` along `right` col. Then decrement `right--`.
//     3. If `top <= bottom`, traverse from `right` to `left` along `bottom` row. Then decrement `bottom--`.
//     4. If `left <= right`, traverse from `bottom` to `top` along `left` col. Then increment `left++`.
//   - Space Complexity is O(1) auxiliary (excluding output array).
//   - Why this approach: Eliminates any extra memory and gracefully terminates when boundaries cross.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spirallyTraverse(vector<vector<int>>& mat) {
        vector<int> result;
        if (mat.empty() || mat[0].empty()) return result;

        int r = mat.size();
        int c = mat[0].size();

        int top = 0;
        int bottom = r - 1;
        int left = 0;
        int right = c - 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // The loop continues as long as valid rows and columns remain unpeeled.
        while (top <= bottom && left <= right) {

            // Step 1: Move Left to Right along the current top boundary
            for (int j = left; j <= right; ++j) {
                result.push_back(mat[top][j]);
            }
            top++; // Top row fully consumed, contract inward

            // Step 2: Move Top to Bottom along the current right boundary
            for (int i = top; i <= bottom; ++i) {
                result.push_back(mat[i][right]);
            }
            right--; // Right column fully consumed, contract inward

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Must check if `top <= bottom` because `top++` above may have crossed `bottom`
            // in a single-row matrix! Without this check, the single row will be read again backwards!
            if (top <= bottom) {
                for (int j = right; j >= left; --j) {
                    result.push_back(mat[bottom][j]);
                }
                bottom--; // Bottom row fully consumed, contract inward
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Must check if `left <= right` because `right--` above may have crossed `left`
            // in a single-column matrix! Without this check, the single column will be read again upwards!
            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    result.push_back(mat[i][left]);
                }
                left++; // Left column fully consumed, contract inward
            }
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    vector<int> res = sol.spirallyTraverse(mat);
    cout << "Spiral Traversal: ";
    for (int x : res) cout << x << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(R * C), every single cell is visited exactly once.
- Space Complexity: O(1) auxiliary space (excluding the output storage vector of size R * C).

Key Takeaways:
- Boundary contraction peeling eliminates visited matrices.
- The two guard conditions (`if (top <= bottom)` and `if (left <= right)`) are the #1 source of bugs
  in interviews when dealing with non-square rectangular matrices.
*/
