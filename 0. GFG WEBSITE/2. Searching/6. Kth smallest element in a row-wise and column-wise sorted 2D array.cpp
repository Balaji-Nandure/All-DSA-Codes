/*
 * Problem: Kth smallest element in a row-wise and column-wise sorted 2D array
 *
 * GeeksforGeeks: https://www.geeksforgeeks.org/kth-smallest-element-in-a-row-wise-column-wise-sorted-2d-array/
 * Practice: https://practice.geeksforgeeks.org/problems/kth-element-in-matrix/1
 *
 * Given an n x n matrix where each of the rows and columns is sorted in ascending order,
 * find the kth smallest element in the matrix.
 *
 * Example 1:
 * Input: matrix = [[10, 20, 30, 40],
 *                  [15, 25, 35, 45],
 *                  [24, 29, 37, 48],
 *                  [32, 33, 39, 50]],
 *        k = 7
 * Output: 30
 *
 * Example 2:
 * Input: matrix = [[1, 5, 9],
 *                  [10, 11, 13],
 *                  [12, 13, 15]],
 *        k = 8
 * Output: 13
 *
 * Constraints:
 * - 1 <= n <= 300
 * - 1 <= matrix[i][j] <= 10^9
 * - 1 <= k <= n*n
 *
 * Approach:
 *   - Binary Search on value: O(n log(max-min))
 *     Search for the smallest value such that there are at least k elements less than or equal to it.
 *     Use a helper to count the number of elements ≤ mid in O(n) time per row.
 *   - Min Heap approach: O(k log n) (not implemented here)
 *
 * Time: O(n log(max-min))
 * Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Helper to count number of elements ≤ mid in the matrix
    int countLessEqual(vector<vector<int>>& matrix, int mid, int n) {
        int count = 0;
        int row = n - 1, col = 0;
        // Start from bottom left corner
        while (row >= 0 && col < n) {
            if (matrix[row][col] <= mid) {
                count += row + 1;
                col++;
            } else {
                row--;
            }
        }
        return count;
    }

    // Binary Search on Value
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int low = matrix[0][0];
        int high = matrix[n-1][n-1];

        while (low < high) {
            int mid = low + (high - low) / 2;
            int cnt = countLessEqual(matrix, mid, n);
            if (cnt < k)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }
};