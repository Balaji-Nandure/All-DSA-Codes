/*
    Problem Name: Rectangle with Corners as 1 in Binary Matrix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an n x m binary matrix mat[][] containing only 0s and 1s, determine if there exists a rectangle
    within the matrix such that all four corners of the rectangle are 1.
    If such a rectangle exists, return true; otherwise, return false.

    Examples:
    Input: mat[][] = [[1, 0, 0, 1, 0],
                      [0, 0, 1, 0, 1],
                      [0, 0, 0, 1, 0],
                      [1, 0, 1, 0, 1]]
    Output: true
    Explanation: Valid corners are at rows 1 & 3, cols 2 & 4:
    (1,2) = 1, (1,4) = 1, (3,2) = 1, (3,4) = 1.

    Input: mat[][] = [[0, 0, 0],
                      [0, 0, 0],
                      [0, 0, 0]]
    Output: false

    Constraints:
    1 <= n, m <= 200
    mat[i][j] = {0, 1}

    Expected Complexities:
    Time Complexity: O(N * M^2), checking column pairs for each row.
    Space Complexity: O(M^2), 2D boolean grid tracking seen column pairs.

    Love Babbar / Striver Easy Approach:
    Column-Pair Tracking via Direct Nested Loops (O(N * M^2) Time, O(M^2) Space)

    INTUITION & STRATEGY:
    1. If rows r1 and r2 both contain 1 at columns j and k:
       (r1, j) ---- (r1, k)
          |            |
       (r2, j) ---- (r2, k)
       All four corners are 1, forming a valid rectangle!
    2. Maintain `seen[j][k]` boolean array:
       - Stores whether a previous row has 1s at both column `j` and column `k`.
    3. Loop over all rows `i` from `0` to `n - 1`:
       - Loop `j` from `0` to `m - 1`. If `mat[i][j] == 0`, continue.
       - Loop `k` from `j + 1` to `m - 1`. If `mat[i][k] == 1`:
         * If `seen[j][k]` is ALREADY true, return `true` (rectangle found!).
         * Else, mark `seen[j][k] = true`.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool ValidCorner(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        // seen[j][k] = whether we have already seen a previous row with 1s at both columns j and k
        vector<vector<bool>> seen(m, vector<bool>(m, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) continue;

                for (int k = j + 1; k < m; k++) {
                    if (mat[i][k] == 1) {
                        // Same column pair found in another row
                        if (seen[j][k])
                            return true;

                        seen[j][k] = true;
                    }
                }
            }
        }

        return false;
    }
};

int main() {
    Solution solver;

    // Example 1:
    // Expected Output: true
    vector<vector<int>> mat1 = {
        {1, 0, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0},
        {1, 0, 1, 0, 1}
    };
    cout << "Example 1 Valid Corner Rectangle: " << (solver.ValidCorner(mat1) ? "true" : "false") << "\n";

    // Example 2:
    // Expected Output: false
    vector<vector<int>> mat2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    cout << "Example 2 Valid Corner Rectangle: " << (solver.ValidCorner(mat2) ? "true" : "false") << "\n";

    return 0;
}
