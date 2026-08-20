/*
    Problem Name: Kth smallest element in a Matrix
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 378

    Problem Statement:
    Given a matrix mat[][] of size n x n, where each row and column is sorted in non-decreasing order.
    Find the kth smallest element in the matrix.

    Examples:
    Input: mat[][] = [[16, 28, 60, 64],
                      [22, 41, 63, 91],
                      [27, 50, 87, 93],
                      [36, 78, 87, 94]], k = 3
    Output: 27
    Explanation: Sorted array = [16, 22, 27, 28, 36, 41, ...]. 3rd smallest element is 27.

    Input: mat[][] = [[10, 20, 30, 40],
                      [15, 25, 35, 45],
                      [24, 29, 37, 48],
                      [32, 33, 39, 50]], k = 7
    Output: 30
    Explanation: 7th smallest element is 30.

    Constraints:
    1 <= n <= 500
    1 <= mat[i][j] <= 10^4
    1 <= k <= n * n

    Expected Complexities:
    Time Complexity: O(N * log(maxVal - minVal)), using Binary Search on Range + Staircase Count.
    Space Complexity: O(1), no extra space.

    Approach 1: Min Heap / Priority Queue (O(K * log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Binary Search on Value Range (Optimal O(N * log(Range)) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Min Heap Approach (Approach 1):
       - Since each row is sorted, push the first element of all N rows `{mat[i][0], i, 0}` into a Min Heap.
       - Pop the minimum element K times.
       - When popping `{val, r, c}`, push its right neighbour `{mat[r][c+1], r, c+1}` if `c + 1 < n`.
       - The K-th popped value is the K-th smallest element!
    2. Binary Search on Range (Approach 2 - Optimal):
       - Search space `[low, high]` = `[mat[0][0], mat[n-1][n-1]]`.
       - For candidate `mid`:
         * Count elements `<= mid` in O(N) using top-right corner staircase iteration.
         * If `count < k`: `low = mid + 1`.
         * Else: `high = mid - 1`.
       - Returns `low`.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// ============================================================================
// Approach 1: Min Heap / Priority Queue (O(K * log N) - Striver & Love Babbar)
// ============================================================================
class SolutionMinHeap {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int n = mat.size();

        // Min Heap storing tuple <val, row, col>
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

        // Step 1: Push first element of each row
        for (int i = 0; i < n; i++) {
            pq.push({mat[i][0], i, 0});
        }

        // Step 2: Extract minimum element K times
        int val = 0;
        for (int step = 0; step < k; step++) {
            auto [currVal, r, c] = pq.top();
            pq.pop();

            val = currVal;

            // Push next column element from same row
            if (c + 1 < n) {
                pq.push({mat[r][c + 1], r, c + 1});
            }
        }

        return val;
    }
};

// ============================================================================
// Approach 2: Binary Search on Range (Optimal O(N * log(Range)) - Striver & Love Babbar)
// ============================================================================
class SolutionBinarySearch {
private:
    // Helper function to count elements <= mid in O(N) time using Staircase search
    int countLessEqual(const vector<vector<int>>& mat, int mid, int n) {
        int count = 0;
        int r = 0;
        int c = n - 1;

        // Start at top-right corner
        while (r < n && c >= 0) {
            if (mat[r][c] <= mid) {
                count += (c + 1); // All elements in row r from col 0 to c are <= mid
                r++;              // Move down
            } else {
                c--;              // Move left
            }
        }

        return count;
    }

public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        int n = mat.size();

        int low = mat[0][0];
        int high = mat[n - 1][n - 1];

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = countLessEqual(mat, mid, n);

            if (count < k) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return low;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        SolutionBinarySearch solver;
        return solver.kthSmallest(mat, k);
    }

    int kthSmallest(vector<vector<int>>& mat, int n, int k) {
        return kthSmallest(mat, k);
    }
};

int main() {
    // Example 1:
    // Expected Output: 27
    vector<vector<int>> mat1 = {
        {16, 28, 60, 64},
        {22, 41, 63, 91},
        {27, 50, 87, 93},
        {36, 78, 87, 94}
    };
    int k1 = 3;

    SolutionMinHeap heapSolver;
    cout << "Example 1 (3rd Smallest via MinHeap): " << heapSolver.kthSmallest(mat1, k1) << "\n";

    // Example 2:
    // Expected Output: 30
    vector<vector<int>> mat2 = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {24, 29, 37, 48},
        {32, 33, 39, 50}
    };
    int k2 = 7;

    SolutionBinarySearch bsSolver;
    cout << "Example 2 (7th Smallest via BinarySearch): " << bsSolver.kthSmallest(mat2, k2) << "\n";

    return 0;
}
