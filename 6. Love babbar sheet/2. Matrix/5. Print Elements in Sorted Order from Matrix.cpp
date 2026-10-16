// Problem: Print Elements in Sorted Order from Matrix (Sorted Matrix)
// Link (GFG): https://www.geeksforgeeks.org/problems/sorted-matrix2333/1
// Article: https://www.geeksforgeeks.org/dsa/print-elements-sorted-order-row-column-wise-sorted-matrix/
// Difficulty: Basic / Medium
// Topic: Matrix, Heap (Priority Queue), K-Way Merge

/*
Problem Statement:
Given an N x N matrix Mat, where every row and column is sorted in increasing order. 
Return all elements of the matrix in strictly sorted order.

Example 1:
Input:
N = 4
Mat = [[10, 20, 30, 40],
       [15, 25, 35, 45], 
       [27, 29, 37, 48], 
       [32, 33, 39, 50]]
Output: 
10 15 20 25 27 29 30 32 33 35 37 39 40 45 48 50

Example 2:
Input:
N = 3
Mat = [[1, 5, 3], 
       [2, 8, 7], 
       [4, 6, 9]]
Output:
1 2 3 4 5 6 7 8 9

Constraints:
- 1 <= N <= 1000
- 1 <= Mat[i][j] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 3 (Median in Row-Wise Sorted Matrix):
//   * We only needed a single element (the middle rank), which we found via Binary Search on values.
// - In Problem 5 (Sorted Matrix):
//   * We must output ALL N*N elements in sorted order.
//   * Because every row is sorted, this is mathematically identical to the classic problem:
//     "Merge K Sorted Lists / Arrays" where K = N and each array has size N!
//   * Min-Heap provides the streaming solution using only O(N) auxiliary memory.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Flatten and Sort
//   - Flatten the N x N matrix into a 1D vector of size N^2 and call `std::sort`.
//   - Complexity: O(N^2 log(N^2)) = O(N^2 log N) time, O(N^2) space.
//   - Simple, but allocates O(N^2) space and doesn't take advantage of streaming.
//
// Approach 2: Min-Heap K-Way Merge (Optimal for Streaming & Memory-Constrained)
//   - Initialize a min-heap with the first element of each of the N rows: `{value, row, col}`.
//   - At each step:
//     1. Extract the minimum element from the heap and append it to `result`.
//     2. If that row has a next element (`col + 1 < N`), push `{Mat[row][col + 1], row, col + 1}`.
//   - Heap size is never more than N at any moment!
//   - Total elements processed: N^2. Each heap push/pop takes O(log N).
//   - Complexity: O(N^2 log N) time, O(N) auxiliary space!
//   - Why this approach: Standard industry pattern for streaming data from multiple sorted sources.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to store element in Min-Heap
struct HeapNode {
    int val;
    int row;
    int col;

    // Operator for Min-Heap (smallest val on top)
    bool operator>(const HeapNode& other) const {
        return val > other.val;
    }
};

class Solution {
public:
    // Approach 2: K-Way Merge using Min-Heap (Streaming O(N) auxiliary space)
    vector<int> sortedMatrixHeap(const vector<vector<int>>& mat, int n) {
        vector<int> result;
        result.reserve(n * n);

        priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode>> minHeap;

        // Push first element of each row into min-heap
        for (int i = 0; i < n; ++i) {
            if (n > 0) {
                minHeap.push({mat[i][0], i, 0});
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Continually pop the smallest element across all rows, then advance that row's pointer.
        // Heap size is strictly bounded by N, so memory overhead is O(N) instead of O(N^2)!
        while (!minHeap.empty()) {
            HeapNode curr = minHeap.top();
            minHeap.pop();

            result.push_back(curr.val);

            // If the current row has a subsequent element, push it into the heap
            if (curr.col + 1 < n) {
                minHeap.push({mat[curr.row][curr.col + 1], curr.row, curr.col + 1});
            }
        }

        return result;
    }

    // Approach 1: Direct Flatten and Sort (Alternative for simple competitive programming)
    vector<int> sortedMatrixSort(vector<vector<int>>& mat, int n) {
        vector<int> result;
        result.reserve(n * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result.push_back(mat[i][j]);
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> mat = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {27, 29, 37, 48},
        {32, 33, 39, 50}
    };
    int n = 4;

    vector<int> res = sol.sortedMatrixHeap(mat, n);
    cout << "Sorted Matrix Elements: ";
    for (int x : res) cout << x << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Min-Heap K-Way Merge:
  * Time Complexity: O(N^2 * log N). N^2 total extractions, each takes O(log N) heapify.
  * Space Complexity: O(N) auxiliary space for the heap of size N.
- Flatten and Sort:
  * Time Complexity: O(N^2 * log N).
  * Space Complexity: O(N^2) space to store all elements.

Key Takeaways:
- Min-Heap is ideal when rows are streams (e.g., merging sorted files from disk where all data
  cannot fit into RAM at once).
*/
