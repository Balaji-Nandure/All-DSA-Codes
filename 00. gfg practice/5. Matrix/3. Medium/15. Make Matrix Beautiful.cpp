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

    Love Babbar / Striver Approach:
    Max Row/Col Sum Difference Accumulation (Single-Pass Matrix Sum + Row Difference Accumulation)

    INTUITION & STRATEGY:
    1. Traverse the matrix cell by cell to compute:
       - `row[i]`: sum of elements in row `i`
       - `col[j]`: sum of elements in column `j`
       - `maxSum`: maximum sum seen among all rows and columns.
    2. Since every row must reach `maxSum`, the number of operations needed for row `i` is `maxSum - row[i]`.
    3. Accumulate `ans += (maxSum - row[i])` for all `i` from `0` to `n - 1`.
    4. Return `ans`.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinOperation(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int maxSum = 0;

        vector<int> row(n, 0);
        vector<int> col(n, 0);

        // Step 1: Calculate row sums, col sums, and track maximum sum
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                row[i] += matrix[i][j];
                maxSum = max(row[i], maxSum);

                col[j] += matrix[i][j];
                maxSum = max(col[j], maxSum);
            }
        }

        int ans = 0;

        // Step 2: Accumulate difference between maxSum and row[i] for each row
        for (int i = 0; i < n; i++) {
            row[i] = maxSum - row[i];
            col[i] = maxSum - col[i];

            ans += row[i];
        }

        return ans;
    }

    // Overload for (n, matrix) signature
    int findMinOperation(int n, vector<vector<int>>& matrix) {
        return findMinOperation(matrix);
    }
};

int main() {
    Solution ob;

    // Example 1:
    // Expected Output: 4
    vector<vector<int>> mat1 = {
        {1, 2},
        {3, 4}
    };
    cout << "Example 1 Min Operations: " << ob.findMinOperation(mat1) << "\n";

    // Example 2:
    // Expected Output: 6
    vector<vector<int>> mat2 = {
        {1, 2, 3},
        {4, 2, 3},
        {3, 2, 1}
    };
    cout << "Example 2 Min Operations: " << ob.findMinOperation(mat2) << "\n";

    return 0;
}
