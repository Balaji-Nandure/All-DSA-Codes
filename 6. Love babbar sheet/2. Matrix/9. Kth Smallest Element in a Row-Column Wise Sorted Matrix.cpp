// Problem: Kth Smallest Element in a Row-Column Wise Sorted Matrix
// Link (GFG): https://www.geeksforgeeks.org/problems/kth-element-in-matrix/1
// Article: https://www.geeksforgeeks.org/dsa/kth-smallest-element-in-a-row-wise-and-column-wise-sorted-2d-array/
// Difficulty: Medium / Hard
// Topic: Matrix, Binary Search on Answer, Min-Heap

/*
Problem Statement:
Given an N x N matrix where every row and column is sorted in non-decreasing order.
Find the kth smallest element in the matrix.

Example 1:
Input:
N = 4, mat = [[16, 28, 60, 64],
              [22, 41, 63, 91],
              [27, 50, 87, 93],
              [36, 78, 87, 94]], k = 3
Output: 27
Explanation: 3rd smallest element is 27 (16, 22, 27).

Example 2:
Input:
N = 4, mat = [[10, 20, 30, 40],
              [15, 25, 35, 45],
              [24, 29, 37, 48],
              [32, 33, 39, 50]], k = 7
Output: 30

Constraints:
- 1 <= N <= 1000
- 1 <= mat[i][j] <= 10^9
- 1 <= k <= N * N
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 3 (Median in Row-Wise Sorted Matrix):
//   * Only rows were sorted; columns were arbitrary.
//   * Counting elements `<= mid` required calling `upper_bound` on every row -> O(R * log C).
// - In Problem 9 (Kth Smallest in Row AND Column Sorted Matrix):
//   * BOTH rows and columns are sorted!
//   * This enables the O(N) staircase ladder counting method (starting at bottom-left corner).
//   * In each step, if `mat[row][col] <= mid`, all elements above it in the same column 
//     are also `<= mid` (batch count `row + 1` in O(1)!), eliminating binary search per row!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Min-Heap / K-Way Merge
//   - Push first element of each row into min-heap. Pop k times.
//   - Complexity: O(k * log N) time, O(N) space.
//   - Why Suboptimal when k is close to N^2: Takes O(N^2 log N) time!
//
// Approach 2: Binary Search on Answer with O(N) Staircase Count (Optimal & Chosen)
//   - Value search range: `low = mat[0][0]`, `high = mat[N-1][N-1]`.
//   - For a midpoint guess `mid`:
//     * Count how many elements in the matrix are `<= mid`.
//     * Use staircase walk starting at bottom-left `(n-1, 0)`:
//         - If `mat[row][col] <= mid`: all elements `mat[0..row][col]` are `<= mid`.
//           Add `(row + 1)` to count and move right: `col++`.
//         - Else: `mat[row][col] > mid`, so move up: `row--`.
//     * Staircase walk takes O(N) time!
//     * If `count < k`: `low = mid + 1` (mid is too small).
//     * Else: `high = mid` (candidate found, search lower).
//   - Total Time: O(N * log(maxVal - minVal)), Space: O(1)!
//   - Why this approach: Outperforms heap significantly when k is large and uses zero extra space.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function: Counts elements <= mid in O(N) time using staircase walk
    int countLessOrEqual(const vector<vector<int>>& mat, int n, int mid) {
        int count = 0;
        int row = n - 1; // Start at bottom-left corner
        int col = 0;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Because columns are sorted top-down and rows are sorted left-right,
        // if mat[row][col] <= mid, then EVERY element above it in the same column
        // (from index 0 up to row) is guaranteed to be <= mid.
        // We add (row + 1) in O(1) and shift right!
        while (row >= 0 && col < n) {
            if (mat[row][col] <= mid) {
                count += (row + 1); // Add all elements in this column up to current row
                col++;              // Move to next column
            } else {
                row--;              // Current element is too large, move up
            }
        }
        return count;
    }

public:
    int kthSmallest(vector<vector<int>>& mat, int n, int k) {
        int low = mat[0][0];
        int high = mat[n - 1][n - 1];

        // Binary search on the numeric range of matrix values
        while (low < high) {
            int mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If the count of numbers <= mid is less than k, the k-th smallest element
            // must be strictly larger than mid.
            if (countLessOrEqual(mat, n, mid) < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {16, 28, 60, 64},
        {22, 41, 63, 91},
        {27, 50, 87, 93},
        {36, 78, 87, 94}
    };
    int n = 4, k = 3;

    cout << "3rd Smallest Element: " << sol.kthSmallest(mat, n, k) << "\n";
    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * log(maxVal - minVal)).
  * The range of values is at most 10^9, so the binary search executes at most ~32-60 times.
  * In each iteration, `countLessOrEqual` runs the staircase traversal in at most 2N steps = O(N).
  * For N = 1000, 32 * 2000 ≈ 64,000 operations, which finishes in < 2 milliseconds!
- Space Complexity: O(1) auxiliary space (no heap, no extra arrays).

Key Takeaways:
- Staircase counting is the crown jewel of row-column sorted matrix algorithms, reducing 
  counting from O(N * log N) to O(N).
*/
