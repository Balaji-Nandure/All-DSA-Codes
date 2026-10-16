// Problem: Maximum Size Rectangle in Binary Sub-matrix (Max Rectangle)
// Link (GFG): https://www.geeksforgeeks.org/problems/max-rectangle/1
// Article: https://www.geeksforgeeks.org/dsa/maximum-size-rectangle-binary-sub-matrix-1s/
// Difficulty: Hard
// Topic: Matrix, Dynamic Programming, Monotonic Stack (Histogram Reduction)

/*
Problem Statement:
Given a binary matrix M of size n x m. Find the maximum area of a rectangle 
formed only of 1s in the given matrix.

Example 1:
Input:
n = 4, m = 4
M = [[0, 1, 1, 0],
     [1, 1, 1, 1],
     [1, 1, 1, 1],
     [1, 1, 0, 0]]
Output: 8
Explanation: The largest rectangle with only 1s is from row 1 to row 2 and column 0 to 3:
height = 2, width = 4, area = 2 * 4 = 8.

Example 2:
Input:
n = 2, m = 3
M = [[0, 1, 1],
     [1, 1, 1]]
Output: 4
Explanation: The largest rectangle is from row 0 to 1, col 1 to 2, area = 2 * 2 = 4.

Constraints:
- 1 <= n, m <= 1000
- 0 <= M[i][j] <= 1
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In 1D Subarray problems (Kadane's algorithm, Problem 8 in Arrays):
//   * We maximized the 1D sum over contiguous elements.
// - In 2D Maximum Rectangle:
//   * A 2D sub-matrix requires BOTH width (contiguous columns) and height (contiguous rows) 
//     of ALL 1s.
//   * A naive 2D search tests O(N^2 * M^2) rectangles, which is TLE.
//   * The breakthrough reduction: Treat each row as the floor/ground of a HISTOGRAM!
//     As we move down row by row, the consecutive 1s in column `j` accumulate into bar heights.
//     Whenever a 0 is hit, the bar height resets to 0.
//     Then, the problem reduces to solving "Largest Rectangle in Histogram" N times!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force
//   - Enumerate all possible top-left (r1, c1) and bottom-right (r2, c2) pairs.
//   - Check if all cells are 1.
//   - Complexity: O(N^3 * M^3) time. Completely unusable.
//
// Approach 2: Row-wise Histogram Reduction with Monotonic Stack (Optimal & Chosen)
//   - Maintain an array `heights[m]` initialized to 0.
//   - For each row `i` from 0 to `n - 1`:
//     1. For each column `j`:
//        * If `M[i][j] == 1`: `heights[j] += 1` (extends vertical bar).
//        * If `M[i][j] == 0`: `heights[j] = 0` (continuity broken, bar collapses).
//     2. Compute `maxAreaInHistogram(heights)` using a Monotonic Increasing Stack:
//        * Each bar is pushed and popped at most once -> O(M) time per row!
//     3. Update global `maxArea = max(maxArea, currentRowArea)`.
//   - Complexity: N rows * O(M) stack time = O(N * M) total time!
//   - Auxiliary Space: O(M) for heights array and stack.
//   - Why this approach: Achieves optimal O(N * M) time complexity, matching the theoretical 
//     lower bound of reading the matrix.

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function: Finds the largest rectangle area in a histogram in O(M) time
    int largestRectangleArea(const vector<int>& heights) {
        int m = heights.size();
        stack<int> st; // Stores indices of increasing bar heights
        int maxArea = 0;

        for (int i = 0; i <= m; ++i) {
            // When reaching the end, use a virtual bar of height 0 to flush the stack
            int currentHeight = (i == m) ? 0 : heights[i];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // When current bar is shorter than the bar at stack top, the top bar can NO LONGER
            // extend further to the right. We pop it and calculate its maximal rectangular area!
            while (!st.empty() && currentHeight < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();

                // Width is determined by the previous smaller element on left (st.top())
                // and current smaller element on right (i)
                int width = st.empty() ? i : (i - st.top() - 1);
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }

        return maxArea;
    }

public:
    int maxArea(vector<vector<int>>& mat, int n, int m) {
        if (n == 0 || m == 0) return 0;

        vector<int> heights(m, 0);
        int maxRectangle = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Consecutive 1s accumulate vertically. A single 0 immediately resets the height to 0!
                if (mat[i][j] == 1) {
                    heights[j] += 1;
                } else {
                    heights[j] = 0;
                }
            }

            // Calculate max rectangular area for the current histogram baseline
            int area = largestRectangleArea(heights);
            maxRectangle = max(maxRectangle, area);
        }

        return maxRectangle;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0}
    };
    int n = 4, m = 4;

    cout << "Maximum Size Rectangle in Binary Sub-matrix: " 
         << sol.maxArea(mat, n, m) << "\n";
    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * M).
  * Updating heights for each row: O(M).
  * Monotonic stack histogram pass: O(M) because each index is pushed and popped at most once.
  * For N rows, total time is N * O(M) = O(N * M).
- Space Complexity: O(M) auxiliary space for the `heights` vector and stack.

Key Takeaways:
- Reducing a 2D problem to repeated 1D problems using DP accumulator + Monotonic Stack 
  is a premier interview technique (used in LeetCode 85 & 84).
*/
