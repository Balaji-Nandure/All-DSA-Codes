// Problem: Find Median in a Row Wise Sorted Matrix
// Link (GFG): https://www.geeksforgeeks.org/problems/median-in-a-row-wise-sorted-matrix1527/1
// Article: https://www.geeksforgeeks.org/dsa/find-median-row-wise-sorted-matrix/
// Difficulty: Hard
// Topic: Matrix, Binary Search on Answer Range

/*
Problem Statement:
Given a row-wise sorted matrix of size R*C where R and C are always odd, 
find the median of the matrix.

The median of an odd-sized collection of N elements (where N = R * C) is the element 
at index (N / 2) when all elements are sorted in non-decreasing order.
Equivalently, exactly (R * C + 1) / 2 elements are less than or equal to the median.

Example 1:
Input:
R = 3, C = 3
mat = [[1, 3, 5], 
       [2, 6, 9], 
       [3, 6, 9]]
Output: 5
Explanation: Sorting all elements yields [1, 2, 3, 3, 5, 6, 6, 9, 9]. 
The middle element (5th element) is 5.

Example 2:
Input:
R = 3, C = 3
mat = [[1, 3, 4], 
       [2, 5, 6], 
       [7, 8, 9]]
Output: 5

Constraints:
- 1 <= R, C <= 500 (R and C are always odd)
- 1 <= mat[i][j] <= 2000
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 2 (Search an Element in a Matrix):
//   * The target value was known upfront. We checked whether `target` exists in O(R + C).
// - In Problem 3 (Find Matrix Median):
//   * The target value is UNKNOWN. We must find the element that occupies the exact middle rank!
//   * Crucially, the columns are NOT sorted—only the individual rows are sorted!
//   * Therefore, we cannot perform staircase search or 1D index mapping.
//   * Instead, we use "Binary Search on the Value Range" [minVal, maxVal], transforming 
//     an optimization/ranking problem into a monotonic counting predicate:
//     "How many elements in the entire matrix are <= mid?"

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Flatten to 1D Array and Sort
//   - Copy all R * C elements into a vector and sort it. Return vector[(R * C) / 2].
//   - Complexity: O(R * C * log(R * C)) time, O(R * C) auxiliary space.
//   - Why Suboptimal: Violates O(1) auxiliary space requirement and ignores row-sorted property.
//
// Approach 2: Min-Heap / K-Way Merge
//   - Push first element of each row into min-heap. Pop (R * C)/2 times.
//   - Complexity: O((R * C / 2) * log R) time, O(R) space.
//   - Why Suboptimal: Still linear in R * C. For large C, it does too much work.
//
// Approach 3: Binary Search on Answer Range [minVal, maxVal] (Optimal & Chosen)
//   - Range: `low = min(first element of all rows)`, `high = max(last element of all rows)`.
//   - The median must have at least `required = (R * C + 1) / 2` elements `<= median`.
//   - For a guess `mid`:
//     * In each row, use `upper_bound` to count elements `<= mid` in O(log C) time.
//     * Sum the counts across all R rows: `totalCount = sum(upper_bound - row.begin())`.
//     * If `totalCount < required`: `mid` is too small, median must be larger -> `low = mid + 1`.
//     * If `totalCount >= required`: `mid` might be median or median is smaller -> `high = mid`.
//   - When `low == high`, `low` is guaranteed to be the exact median present in the matrix!
//   - Complexity: O(32 * R * log C) time, O(1) auxiliary space.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function: counts how many elements in the matrix are <= mid
    int countLessOrEqual(const vector<vector<int>>& mat, int mid) {
        int count = 0;
        int r = mat.size();
        for (int i = 0; i < r; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // upper_bound returns an iterator to the first element strictly > mid.
            // Subtracting mat[i].begin() gives the number of elements <= mid in O(log C).
            count += upper_bound(mat[i].begin(), mat[i].end(), mid) - mat[i].begin();
        }
        return count;
    }

public:
    int median(vector<vector<int>>& mat, int r, int c) {
        // Find minimum possible value (must be in the first column)
        // and maximum possible value (must be in the last column)
        int low = mat[0][0];
        int high = mat[0][c - 1];

        for (int i = 1; i < r; ++i) {
            low = min(low, mat[i][0]);
            high = max(high, mat[i][c - 1]);
        }

        // The median element has at least (r * c + 1) / 2 elements <= itself
        int required = (r * c + 1) / 2;

        // Binary search on the answer range [low, high]
        while (low < high) {
            int mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If the total count of elements <= mid is strictly less than the median's required rank,
            // the true median CANNOT be <= mid. We must search strictly higher (`low = mid + 1`).
            // Otherwise, mid is a candidate and could be the median or too high (`high = mid`).
            if (countLessOrEqual(mat, mid) < required) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        // When low == high, low is the exact median value
        return low;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    int r = 3, c = 3;

    cout << "Median in row-wise sorted matrix: " << sol.median(mat, r, c) << "\n";
    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(log(maxVal - minVal) * R * log C).
  * Finding initial min and max: O(R).
  * Range of values is at most 2000 (or 10^9), meaning at most ~32 iterations.
  * In each iteration, we do R binary searches (`upper_bound`), costing R * log C.
  * For R=500, C=500: ~32 * 500 * 9 ≈ 1.4 * 10^5 operations (executes in milliseconds!).
- Space Complexity: O(1) auxiliary space (no arrays, heaps, or extra vectors).

Key Takeaways:
- "Binary Search on Answer" is one of the most powerful techniques in DSA when an array/matrix
  is partially sorted and finding an element by rank is required.
*/
