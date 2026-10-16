#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum sum rectangle in a 2D matrix (2D Kadane's Algorithm)
 * 
 * Given an R x C matrix of positive and negative integers, find the maximum sum 
 * of any rectangular sub-matrix.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "35. Largest Sum Contiguous Subarray", Kadane's algorithm ran on a 1D array.
 * - In "55. Largest rectangular sub-matrix with sum 0", we searched for exact sum 0.
 * - Here, we want to MAXIMIZE the 2D rectangular sum across arbitrary positive and negative numbers.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 2D Kadane's Algorithm via Column Projection:
 *   1. Fix left column c1 and right column c2 (0 <= c1 <= c2 < C).
 *   2. Maintain a 1D vector `row_sum[R]` where row_sum[r] accumulates the elements 
 *      in row r between columns c1 and c2:
 *        row_sum[r] = sum_{col=c1}^{c2} M[r][col]
 *   
 *   3. 1D Kadane on row_sum:
 *      Finding the vertical contiguous slice (r1 to r2) that maximizes the 2D rectangle 
 *      bounded horizontally by [c1, c2] is IDENTICAL to running Kadane's algorithm 
 *      on the 1D projection array `row_sum`!
 *      
 *      current_sum = max(row_sum[r], current_sum + row_sum[r])
 *      max_sum = max(max_sum, current_sum)
 *   
 *   4. Maximize over all O(C^2) column pairs in O(C^2 * R) time.
 */

class Solution {
    // Standard 1D Kadane
    int kadane1D(const vector<int>& arr, int n) {
        int max_so_far = arr[0];
        int current_sum = arr[0];

        for (int i = 1; i < n; i++) {
            current_sum = max(arr[i], current_sum + arr[i]);
            max_so_far = max(max_so_far, current_sum);
        }

        return max_so_far;
    }

public:
    int maximumSumRectangle(int R, int C, vector<vector<int>> M) {
        int global_max_sum = INT_MIN;

        // Iterate over all column pairs (c1, c2)
        for (int c1 = 0; c1 < C; c1++) {
            vector<int> row_sum(R, 0);

            for (int c2 = c1; c2 < C; c2++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Project 2D columns [c1 ... c2] into a 1D compressed row array
                for (int r = 0; r < R; r++) {
                    row_sum[r] += M[r][c2];
                }

                // *** CRUCIAL LINE: Run 1D Kadane on the compressed row array in O(R) time ***
                int current_rectangle_max = kadane1D(row_sum, R);
                global_max_sum = max(global_max_sum, current_rectangle_max);
            }
        }

        return global_max_sum;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> M = {
        { 1,  2, -1, -4, -20},
        {-8, -3,  4,  2,   1},
        { 3,  8, 10,  1,   3},
        {-4, -1,  1,  7,  -6}
    };
    int R = 4, C = 5;

    cout << "Maximum Sum Rectangle: " << sol.maximumSumRectangle(R, C, M) << "\n";
    // Maximum sum rectangle spans rows 1..3, cols 1..3:
    // [-3,  4, 2]
    // [ 8, 10, 1]
    // [-1,  1, 7]
    // Sum = 29. Expected: 29.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(C^2 * R) where C is number of columns and R is number of rows.
 *   (If R < C, looping over row pairs (r1, r2) takes O(R^2 * C)).
 * - Space Complexity: O(R) for the 1D projection array.
 */
