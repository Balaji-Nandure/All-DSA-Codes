#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Problem: Largest area rectangular sub-matrix with equal 1s and 0s
 * 
 * Given a binary matrix of size R x C containing only 0s and 1s,
 * find the maximum area of a rectangular sub-matrix that contains 
 * an EQUAL number of 0s and 1s (count(0) == count(1)).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This maps directly to "55. Largest rectangular sub-matrix with sum 0"!
 * - In "28. Maximum difference of zeros and ones", we mapped '0' -> +1 and '1' -> -1 on a 1D string.
 * - Here, we perform the exact same mathematical transformation on a 2D matrix:
 *   Map 0 -> -1 and 1 -> +1.
 *   Equal number of 0s and 1s: count(1) - count(0) = 0 <=> Sub-matrix sum = 0!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Mapping + 2D Column Compression + 1D Zero-Sum Subarray:
 *   1. Transform matrix:
 *      mat[r][c] = (mat[r][c] == 0) ? -1 : 1.
 *   
 *   2. Fix left column c1 and right column c2:
 *      Maintain row_sum[R] where row_sum[r] accumulates values in row r between cols c1 and c2.
 *   
 *   3. In 1D:
 *      Find the longest contiguous subarray in row_sum with sum 0 using a prefix hash map.
 *      Area = (c2 - c1 + 1) * max_len.
 *   
 *   4. Maximize area over all column pairs (c1, c2).
 */

class Solution {
    int maxZeroSumLength(const vector<int>& arr, int n) {
        unordered_map<int, int> mp;
        int sum = 0;
        int max_len = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (sum == 0) {
                max_len = i + 1;
            } else if (mp.find(sum) != mp.end()) {
                max_len = max(max_len, i - mp[sum]);
            } else {
                mp[sum] = i;
            }
        }

        return max_len;
    }

public:
    int maxArea(vector<vector<int>>& mat) {
        int R = mat.size();
        if (R == 0) return 0;
        int C = mat[0].size();

        int max_area = 0;

        // Iterate over all column pairs (c1, c2)
        for (int c1 = 0; c1 < C; c1++) {
            vector<int> row_sum(R, 0);

            for (int c2 = c1; c2 < C; c2++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Transform 0 -> -1 and 1 -> +1 so equal count is algebraically equivalent to zero sum
                for (int r = 0; r < R; r++) {
                    row_sum[r] += (mat[r][c2] == 0 ? -1 : 1);
                }

                // *** CRUCIAL LINE: Longest zero-sum slice in 1D array gives max height ***
                int height = maxZeroSumLength(row_sum, R);
                int width = c2 - c1 + 1;
                max_area = max(max_area, height * width);
            }
        }

        return max_area;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {0, 0, 1, 1},
        {0, 1, 1, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 1}
    };

    cout << "Max Rectangular Area with Equal 0s and 1s: " << sol.maxArea(mat) << "\n";
    // Expected: 16 (entire 4x4 matrix has eight 0s and eight 1s!)

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(C^2 * R). O(C^2) column pairs, each running an O(R) linear hash map scan.
 * - Space Complexity: O(R) auxiliary space for row_sum and hash map.
 */
