#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Problem: Largest rectangular sub-matrix whose sum is 0
 * 
 * Given an R x C matrix, find the largest rectangular sub-matrix whose sum of elements is 0.
 * "Largest" is measured by area (number of cells = (r2 - r1 + 1) * (c2 - c1 + 1)).
 * Return the sub-matrix elements or its boundary coordinates.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "25. Maximum square with all 1s", the shape was strictly a SQUARE (equal height & width).
 * - Here, the sub-matrix is an arbitrary RECTANGLE, and the condition is algebraic: sum == 0.
 * - This 2D problem reduces to 1D via column-pair compression.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 2D Column Compression + 1D Zero-Sum Subarray Hash Map:
 *   1. Fix the top row r1 and bottom row r2 (or left col c1 and right col c2).
 *      Assume we fix left column c1 and right column c2:
 *      Maintain a 1D array `temp[R]` where temp[r] is the sum of row r between cols c1 and c2:
 *        temp[r] = sum_{col = c1}^{c2} mat[r][col]
 *   
 *   2. The problem in 1D:
 *      Find the LONGEST subarray in `temp` whose elements sum to 0!
 *      Using a hash map (prefix_sum -> earliest_seen_index):
 *      - If prefix_sum == 0: length is (r + 1).
 *      - If prefix_sum was previously seen at index prev: length is (r - prev).
 *      - Area = (c2 - c1 + 1) * length.
 *   
 *   3. Global Tracking:
 *      Track the maximum area found so far, updating best_r1, best_r2, best_c1, best_c2.
 */

class Solution {
    // Helper to find the longest subarray with sum 0 in 1D array
    bool maxZeroSumSubarray(const vector<int>& arr, int n, int& up, int& down) {
        unordered_map<int, int> prefix_map;
        int sum = 0;
        int max_len = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (sum == 0) {
                max_len = i + 1;
                up = 0;
                down = i;
            } else if (prefix_map.find(sum) != prefix_map.end()) {
                int len = i - prefix_map[sum];
                if (len > max_len) {
                    max_len = len;
                    up = prefix_map[sum] + 1;
                    down = i;
                }
            } else {
                prefix_map[sum] = i;
            }
        }

        return max_len > 0;
    }

public:
    vector<vector<int>> sumZeroMatrix(vector<vector<int>>& a) {
        int R = a.size();
        if (R == 0) return {};
        int C = a[0].size();

        int max_area = 0;
        int best_r1 = -1, best_r2 = -1, best_c1 = -1, best_c2 = -1;

        // Iterate over all column pairs (c1, c2)
        for (int c1 = 0; c1 < C; c1++) {
            vector<int> row_sum(R, 0);

            for (int c2 = c1; c2 < C; c2++) {
                // Accumulate row values into 1D projection
                for (int r = 0; r < R; r++) {
                    row_sum[r] += a[r][c2];
                }

                int up = -1, down = -1;
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Find longest contiguous zero-sum slice in the compressed 1D row array
                if (maxZeroSumSubarray(row_sum, R, up, down)) {
                    int area = (down - up + 1) * (c2 - c1 + 1);
                    if (area > max_area) {
                        max_area = area;
                        best_r1 = up;
                        best_r2 = down;
                        best_c1 = c1;
                        best_c2 = c2;
                    }
                }
            }
        }

        if (max_area == 0) return {};

        // Extract sub-matrix
        vector<vector<int>> result;
        for (int i = best_r1; i <= best_r2; i++) {
            vector<int> row;
            for (int j = best_c1; j <= best_c2; j++) {
                row.push_back(a[i][j]);
            }
            result.push_back(row);
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1,  2,  3},
        {-3, -2, 0}
    };

    vector<vector<int>> res = sol.sumZeroMatrix(mat);
    cout << "Largest Zero-Sum Sub-matrix:\n";
    for (const auto& row : res) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    // Submatrix covering rows 0..1 and cols 0..1:
    // [ 1,  2]
    // [-3, -2] -> sum = 1 + 2 - 3 - 2 = -2.
    // What about cols 0..2? row 0 = 6, row 1 = -5.
    // What about (0,0) to (1,1)? 1 + 2 - 3 - 2 = -2.
    // (0,1) to (1,1): 2 - 2 = 0! Area = 2.
    // (1,2) alone: 0! Area = 1.
    // (0,0) to (1,0): 1 - 3 = -2.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(C^2 * R). Fixing column pairs takes O(C^2), and 1D prefix map scan takes O(R).
 * - Space Complexity: O(R) for 1D row_sum vector and hash map.
 */
