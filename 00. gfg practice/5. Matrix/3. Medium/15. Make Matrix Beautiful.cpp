/*
    Problem Name: Make Matrix Beautiful
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a square matrix mat[][] of size n x n, return the minimum operations required to make
    the matrix beautiful.
    - A beautiful matrix is a square matrix in which the sum of elements in every row and every column is equal.
    - In one operation, you are allowed to increment the value of any single cell by 1.

    Examples:
    Input: mat[][] = [[1, 2],
                      [3, 4]]
    Output: 4
    Explanation: Increment cell (0,0) by 3 and cell (0,1) by 1 -> [[4, 3], [3, 4]].
    Sum of every row and column becomes 7. Total operations = 4.

    Input: mat[][] = [[1, 2, 3],
                      [4, 2, 3],
                      [3, 2, 1]]
    Output: 6
    Explanation: Matrix after operations: [[2, 4, 3], [4, 2, 3], [3, 3, 3]].
    Sum of every row and column becomes 9. Total operations = 6.

    Constraints:
    1 <= n <= 900
    0 <= mat[i][j] <= 10^6

    Expected Complexities:
    Time Complexity: O(N^2), visiting each cell once.
    Space Complexity: O(N), for storing row and column sums.

    Approach 1: Mathematical Sum Formula (Optimal - Striver & Love Babbar)
    Approach 2: Greedy Cell-by-Cell Simulation (Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Target Sum Determination:
       - Since elements can ONLY be incremented (+1), the target sum for every row and column must be
         at least the MAXIMUM row sum or column sum in the initial matrix.
       - Let `maxSum` = max( max(rowSums), max(colSums) ).
    2. Mathematical Proof for Total Operations:
       - The target sum for every row (and column) is `maxSum`.
       - Since there are `n` rows, the total sum of all elements in the final beautiful matrix will be `n * maxSum`.
       - Therefore, the minimum number of increment operations required is:
         `Min Operations = (n * maxSum) - totalMatrixSum`
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: Mathematical Sum Formula (Optimal O(N^2) - Striver & Love Babbar)
// ============================================================================
class SolutionMath {
public:
    int findMinOperation(vector<vector<int>>& mat) {
        int n = mat.size();

        vector<int> rowSum(n, 0);
        vector<int> colSum(n, 0);
        int totalSum = 0;

        // Step 1: Calculate sum of each row, column, and total matrix sum
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rowSum[i] += mat[i][j];
                colSum[j] += mat[i][j];
                totalSum += mat[i][j];
            }
        }

        // Step 2: Find maximum sum among all rows and columns
        int maxSum = 0;
        for (int i = 0; i < n; i++) {
            maxSum = max(maxSum, rowSum[i]);
            maxSum = max(maxSum, colSum[i]);
        }

        // Step 3: Operations required = (n * maxSum) - totalSum
        return (n * maxSum) - totalSum;
    }
};

// ============================================================================
// Approach 2: Greedy Cell-by-Cell Simulation (O(N^2) - Striver & Love Babbar)
// ============================================================================
class SolutionGreedy {
public:
    int findMinOperation(vector<vector<int>>& mat) {
        int n = mat.size();

        vector<int> rowSum(n, 0);
        vector<int> colSum(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rowSum[i] += mat[i][j];
                colSum[j] += mat[i][j];
            }
        }

        int maxSum = 0;
        for (int i = 0; i < n; i++) {
            maxSum = max(maxSum, rowSum[i]);
            maxSum = max(maxSum, colSum[i]);
        }

        // Greedily increment cell (i, j) by min(maxSum - rowSum[i], maxSum - colSum[j])
        int countOps = 0;
        int i = 0, j = 0;

        while (i < n && j < n) {
            int diff = min(maxSum - rowSum[i], maxSum - colSum[j]);
            rowSum[i] += diff;
            colSum[j] += diff;
            countOps += diff;

            if (rowSum[i] == maxSum) i++;
            if (colSum[j] == maxSum) j++;
        }

        return countOps;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int findMinOperation(vector<vector<int>>& mat) {
        SolutionMath solver;
        return solver.findMinOperation(mat);
    }

    int findMinOperation(vector<vector<int>>& mat, int n) {
        return findMinOperation(mat);
    }
};

int main() {
    // Example 1:
    // Expected Output: 4
    vector<vector<int>> mat1 = {
        {1, 2},
        {3, 4}
    };

    SolutionMath mathSolver;
    cout << "Example 1 Min Operations (Math Formula): " << mathSolver.findMinOperation(mat1) << "\n";

    // Example 2:
    // Expected Output: 6
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 2, 3},
        {3, 2, 1}
    };

    SolutionGreedy greedySolver;
    cout << "Example 2 Min Operations (Greedy Simulation): " << greedySolver.findMinOperation(mat2) << "\n";

    return 0;
}
