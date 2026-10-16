// Problem: Search an Element in a Matrix
// Link (GFG): https://www.geeksforgeeks.org/problems/search-in-a-matrix-1587115621/1
// Article: https://www.geeksforgeeks.org/dsa/search-in-row-wise-and-column-wise-sorted-matrix/
// Difficulty: Medium
// Topic: Matrix, Binary Search, Two Pointers (Staircase Search)

/*
Problem Statement:
Given a 2D matrix `mat` and an integer `x`. Find whether element `x` is present in the matrix.
There are two standard interview variations of this problem:
  Variation 1 (Fully Sorted / Row-Major Sorted - LeetCode 74):
    - Integers in each row are sorted from left to right.
    - The first integer of each row is greater than the last integer of the previous row.
  Variation 2 (Row-wise and Column-wise Sorted / Young Tableau - LeetCode 240):
    - Each row is sorted left to right.
    - Each column is sorted top to bottom.

Both variations are implemented below.

Example 1 (Variation 1):
Input: 
mat = [[1, 3, 5, 7],
       [10, 11, 16, 20],
       [23, 30, 34, 60]], x = 3
Output: true

Example 2 (Variation 2):
Input: 
mat = [[1, 4, 7, 11],
       [2, 5, 8, 12],
       [3, 6, 9, 16],
       [10, 13, 14, 17]], x = 5
Output: true

Constraints:
- 1 <= n, m <= 1000
- -10^9 <= mat[i][j], x <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Spirally Traversing a Matrix):
//   * The goal was exhaustive traversal of all R*C cells without skipping.
// - In Problem 2 (Search in Sorted Matrix):
//   * We do NOT want to visit all R*C cells (which would be O(R*C)).
//   * We must exploit the 2D monotonic sorting properties to prune entire rows/columns 
//     in logarithmic or linear time!
//   * If starting from (0,0), both moving right and moving down INCREASE the value, 
//     so you cannot make a deterministic binary decision. 
//   * But if you start from the TOP-RIGHT corner (0, C-1):
//       Moving LEFT DECREASES the value.
//       Moving DOWN INCREASES the value.
//     This gives a clean, branchable decision tree at every step!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force Linear Scan
//   - Iterate through every cell (i, j).
//   - Complexity: O(R * C) time, O(1) space.
//   - Why NOT: Completely ignores the sorted structure of the matrix.
//
// Approach 2: Binary Search per Row
//   - Binary search each of the R rows individually.
//   - Complexity: O(R * log C) time.
//   - Why Suboptimal: Doesn't exploit the column-wise ordering across rows.
//
// Approach 3 (For Variation 1 - Fully Sorted): Flattened 1D Binary Search
//   - Treat the entire R*C grid as a virtual 1D array of size N = R * C.
//   - Index `mid` in 1D maps to 2D cell: `row = mid / C`, `col = mid % C`.
//   - Complexity: O(log(R * C)) time, O(1) space.
//
// Approach 4 (For Variation 2 - Row & Col Sorted): Top-Right Staircase Search
//   - Start at `row = 0`, `col = C - 1`.
//   - If `mat[row][col] == x`: Found!
//   - If `mat[row][col] > x`: Current is too large, eliminate entire current column (`col--`).
//   - If `mat[row][col] < x`: Current is too small, eliminate entire current row (`row++`).
//   - Complexity: O(R + C) time, O(1) space.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Variation 1: Fully Sorted Matrix (LeetCode 74 / GFG)
    // -------------------------------------------------------------------------
    bool searchMatrixFullySorted(const vector<vector<int>>& mat, int target) {
        if (mat.empty() || mat[0].empty()) return false;
        int r = mat.size();
        int c = mat[0].size();

        int low = 0;
        int high = r * c - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 1D to 2D coordinate mapping formula:
            // Row is integer division by number of columns; Col is modulo by number of columns.
            int midVal = mat[mid / c][mid % c];

            if (midVal == target) {
                return true;
            } else if (midVal < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return false;
    }

    // -------------------------------------------------------------------------
    // Variation 2: Row-wise & Column-wise Sorted Matrix (LeetCode 240 / GFG)
    // -------------------------------------------------------------------------
    bool searchRowColSorted(const vector<vector<int>>& mat, int target) {
        if (mat.empty() || mat[0].empty()) return false;
        int r = mat.size();
        int c = mat[0].size();

        // Start from Top-Right Corner (or alternatively Bottom-Left Corner)
        int row = 0;
        int col = c - 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // At (row, col): Left is strictly smaller, Down is strictly greater.
        // This creates an unequivocal branch at each comparison, eliminating a row or col!
        while (row < r && col >= 0) {
            if (mat[row][col] == target) {
                return true;
            } else if (mat[row][col] > target) {
                col--; // Target must be smaller, eliminate this column
            } else {
                row++; // Target must be greater, eliminate this row
            }
        }
        return false;
    }
};

int main() {
    Solution sol;

    // Fully sorted matrix
    vector<vector<int>> mat1 = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    cout << "Variation 1 (Fully sorted) Search 3: " 
         << (sol.searchMatrixFullySorted(mat1, 3) ? "Found" : "Not Found") << "\n";
    cout << "Variation 1 (Fully sorted) Search 13: " 
         << (sol.searchMatrixFullySorted(mat1, 13) ? "Found" : "Not Found") << "\n";

    // Row & Col sorted matrix
    vector<vector<int>> mat2 = {
        {1, 4, 7, 11},
        {2, 5, 8, 12},
        {3, 6, 9, 16},
        {10, 13, 14, 17}
    };
    cout << "Variation 2 (Row-Col sorted) Search 5: " 
         << (sol.searchRowColSorted(mat2, 5) ? "Found" : "Not Found") << "\n";
    cout << "Variation 2 (Row-Col sorted) Search 20: " 
         << (sol.searchRowColSorted(mat2, 20) ? "Found" : "Not Found") << "\n";

    return 0;
}

/*
Complexity Analysis:
- Variation 1 (Fully Sorted):
  * Time Complexity: O(log(R * C)), single binary search over R*C elements.
  * Space Complexity: O(1) auxiliary space.

- Variation 2 (Row & Col Sorted):
  * Time Complexity: O(R + C), each comparison either moves down (row++) or left (col--).
  * Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Never start at (0, 0) or (R-1, C-1) in row-col sorted matrices because both directions 
  increase (or decrease) the value. Always start at saddle points (0, C-1) or (R-1, 0).
*/
