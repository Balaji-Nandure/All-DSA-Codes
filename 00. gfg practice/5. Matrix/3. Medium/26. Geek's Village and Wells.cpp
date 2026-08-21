/*
    Problem Name: Geek's Village and Wells (Chef and Wells)
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a matrix mat[][] of size n x m representing Geek's village:
    - 'H' represents a House.
    - 'W' represents a Well.
    - '.' represents Open Ground.
    - 'N' represents a Restricted Area (cannot be entered).

    For each house ('H'), find the minimum ROUND-TRIP distance to reach the nearest well and return back (2 * dist).
    - If a house cannot reach any well, store -1.
    - For wells ('W'), open grounds ('.'), and restricted cells ('N'), store 0.

    Examples:
    Input: n = 3, m = 3, mat[][] = [['H', 'H', 'H'],
                                    ['H', 'W', 'H'],
                                    ['H', 'H', 'H']]
    Output: [[4, 2, 4],
             [2, 0, 2],
             [4, 2, 4]]

    Input: n = 4, m = 5, mat[][] = [['H', 'N', 'H', 'N', 'H'],
                                    ['N', 'N', '.', 'H', 'W'],
                                    ['W', 'H', 'H', 'H', '.'],
                                    ['H', '.', '.', 'N', 'H']]
    Output: [[-1, 0, 6, 0, 2],
             [0, 0, 0, 2, 0],
             [0, 2, 4, 4, 0],
             [2, 0, 0, 0, 4]]

    Constraints:
    1 <= n, m <= 10^4
    Total n * m <= 10^5

    Expected Complexities:
    Time Complexity: O(N * M), single-pass Multi-Source BFS.
    Space Complexity: O(N * M), for distance matrix and BFS queue.

    Approach 1: Multi-Source BFS from All Wells (Optimal O(N * M) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Why Multi-Source BFS?
       - Running BFS from each house individually takes O(Houses * N * M), causing TLE.
       - By pushing ALL wells ('W') into the BFS queue simultaneously at distance 0, we can compute the
         shortest distance from ANY well to every cell in a single O(N * M) pass!
    2. BFS Traversal:
       - Restrict movement into 'N' (restricted cells) and out-of-bound grid coordinates.
       - Traverse 4-directionally (Up, Down, Left, Right).
    3. Final Result Formatting:
       - For 'H' cells: `ans[i][j] = (dist[i][j] != -1) ? 2 * dist[i][j] : -1`.
       - For 'W', '.', 'N' cells: `ans[i][j] = 0`.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ============================================================================
// Approach 1: Multi-Source BFS from All Wells (Optimal O(N * M) - Striver & Love Babbar)
// ============================================================================
class SolutionMultiSourceBFS {
public:
    vector<vector<int>> chefAndWells(int n, int m, vector<vector<char>>& mat) {
        queue<pair<int, int>> q;
        vector<vector<int>> dist(n, vector<int>(m, -1));

        // Step 1: Push all Wells ('W') into queue as Multi-Sources
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 'W') {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }

        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Step 2: Perform Multi-Source BFS
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + delRow[i];
                int nc = c + delCol[i];

                // Check bounds and ensure not a restricted cell 'N' and unvisited
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && mat[nr][nc] != 'N' && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Step 3: Construct output matrix
        vector<vector<int>> ans(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 'H') {
                    ans[i][j] = (dist[i][j] != -1) ? 2 * dist[i][j] : -1;
                } else {
                    ans[i][j] = 0; // Wells, Open Grounds, and Restricted cells
                }
            }
        }

        return ans;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<vector<int>> chefAndWells(int n, int m, vector<vector<char>>& mat) {
        SolutionMultiSourceBFS solver;
        return solver.chefAndWells(n, m, mat);
    }

    vector<vector<int>> chefAndWells(vector<vector<char>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        return chefAndWells(n, m, mat);
    }
};

// Helper function to print 2D matrix
void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << "\n";
    }
}

int main() {
    // Example 1:
    // Expected Output:
    // 4 2 4
    // 2 0 2
    // 4 2 4
    vector<vector<char>> mat1 = {
        {'H', 'H', 'H'},
        {'H', 'W', 'H'},
        {'H', 'H', 'H'}
    };
    int n1 = 3, m1 = 3;

    SolutionMultiSourceBFS solver;
    cout << "Example 1 Output Matrix:\n";
    printMatrix(solver.chefAndWells(n1, m1, mat1));
    cout << "\n";

    // Example 2:
    // Expected Output:
    // -1 0 6 0 2
    //  0 0 0 2 0
    //  0 2 4 4 0
    //  2 0 0 0 4
    vector<vector<char>> mat2 = {
        {'H', 'N', 'H', 'N', 'H'},
        {'N', 'N', '.', 'H', 'W'},
        {'W', 'H', 'H', 'H', '.'},
        {'H', '.', '.', 'N', 'H'}
    };
    int n2 = 4, m2 = 5;

    cout << "Example 2 Output Matrix:\n";
    printMatrix(solver.chefAndWells(n2, m2, mat2));

    return 0;
}
