/*
    Problem Name: Rotten Oranges
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a matrix mat[][], where each cell can have values:
    - 0 : Empty cell
    - 1 : Cell having fresh orange
    - 2 : Cell having rotten orange

    Determine the minimum time required so that all fresh oranges become rotten.
    A rotten orange at index (i, j) can rot adjacent fresh oranges at (i-1, j), (i+1, j),
    (i, j-1), and (i, j+1) in 1 unit of time.
    If it is impossible to rot all fresh oranges, return -1.

    Examples:
    Input: mat[][] = [[2, 1, 0, 2, 1],
                      [1, 0, 1, 2, 1],
                      [1, 0, 0, 2, 1]]
    Output: 2
    Explanation: All fresh oranges become rotten after 2 units of time.

    Input: mat[][] = [[2, 1, 0, 2, 1],
                      [0, 0, 1, 2, 1],
                      [1, 0, 0, 2, 1]]
    Output: -1
    Explanation: Fresh orange at (2,0) cannot be reached by any rotten orange.

    Constraints:
    1 <= mat.size() <= 500
    1 <= mat[0].size() <= 500
    mat[i][j] = {0, 1, 2}

    Expected Complexities:
    Time Complexity: O(N * M), where N is number of rows and M is number of columns.
    Space Complexity: O(N * M), for the multi-source BFS queue.

    Love Babbar Style Approach:
    Multi-Source Breadth-First Search (BFS):

    1. INTUITION:
       - Since ALL initial rotten oranges (value 2) rot their adjacent fresh oranges simultaneously
         at unit time steps, this problem represents a shortest path / wave propagation on a grid.
       - Standard BFS initialized with ALL rotten oranges at time 0 (Multi-Source BFS) naturally
         simulates time-step rotting layer by layer!
       - Step 1: Scan grid, push all initial rotten oranges into a `queue<pair<int, int>>` and count `freshCount`.
       - Step 2: If `freshCount == 0`, return 0 immediately.
       - Step 3: While queue is not empty and `freshCount > 0`:
         * Increment `time++`.
         * Process all rotten oranges of the current level (`sz = q.size()`).
         * For each rotten orange, inspect 4-directional neighbours (Up, Down, Left, Right).
         * If a neighbour has a fresh orange (value 1):
           - Mark it rotten (value 2).
           - Decrement `freshCount--`.
           - Push neighbour into queue.
       - Step 4: If `freshCount == 0`, return `time`. Otherwise return `-1` (some fresh oranges unreachable).

    2. ALGORITHM:
       - `orangesRotting(mat)`:
         * `int n = mat.size(), m = mat[0].size();`
         * `queue<pair<int, int>> q;`
         * `int freshCount = 0;`
         * Populate `q` with initial rotten oranges and count `freshCount`.
         * `if (freshCount == 0) return 0;`
         * `int time = 0;`
         * Direction arrays: `dx[] = {-1, 1, 0, 0}`, `dy[] = {0, 0, -1, 1}`.
         * While (`!q.empty() && freshCount > 0`):
           - `int sz = q.size(); time++;`
           - Loop `i` from `0` to `sz - 1`:
             * `auto [r, c] = q.front(); q.pop();`
             * For `d` from 0 to 3:
               - `int nr = r + dx[d], nc = c + dy[d];`
               - `if (valid(nr, nc) && mat[nr][nc] == 1)`:
                 `mat[nr][nc] = 2; freshCount--; q.push({nr, nc});`
         * Return `freshCount == 0 ? time : -1;`

    Dry Run:
    mat = [[2, 1, 0, 2, 1], [1, 0, 1, 2, 1], [1, 0, 0, 2, 1]]
    - Rotten q = [(0,0), (0,3), (1,3), (2,3)], freshCount = 7.
    - time 1: Rots (0,1), (1,0), (0,4), (1,2), (1,4), (2,4). freshCount = 1.
    - time 2: Rots (2,0). freshCount = 0.
    - Loop ends. Returns 2 ✓
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // GFG Signature - Multi-Source BFS
    int orangesRotting(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        queue<pair<int, int>> q;
        int freshCount = 0;

        // Step 1: Push all rotten oranges into queue and count fresh oranges
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 2) {
                    q.push({i, j});
                } else if (mat[i][j] == 1) {
                    freshCount++;
                }
            }
        }

        // If no fresh oranges exist initially, time required is 0
        if (freshCount == 0) return 0;

        int time = 0;
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        // Step 2: Multi-Source BFS level by level
        while (!q.empty() && freshCount > 0) {
            int sz = q.size();
            time++;

            for (int i = 0; i < sz; i++) {
                auto [r, c] = q.front();
                q.pop();

                // Explore 4-directional adjacent cells
                for (int d = 0; d < 4; d++) {
                    int nr = r + dx[d];
                    int nc = c + dy[d];

                    if (nr >= 0 && nr < n && nc >= 0 && nc < m && mat[nr][nc] == 1) {
                        mat[nr][nc] = 2; // Rot the fresh orange
                        freshCount--;
                        q.push({nr, nc});
                    }
                }
            }
        }

        // Return minimum time if all oranges rotten, else -1
        return (freshCount == 0) ? time : -1;
    }
};

int main() {
    Solution ob;

    // Example 1:
    // Expected Output: 2
    vector<vector<int>> mat1 = {
        {2, 1, 0, 2, 1},
        {1, 0, 1, 2, 1},
        {1, 0, 0, 2, 1}
    };
    cout << "Example 1 Min Time: " << ob.orangesRotting(mat1) << "\n";

    // Example 2:
    // Expected Output: -1
    vector<vector<int>> mat2 = {
        {2, 1, 0, 2, 1},
        {0, 0, 1, 2, 1},
        {1, 0, 0, 2, 1}
    };
    cout << "Example 2 Min Time: " << ob.orangesRotting(mat2) << "\n";

    return 0;
}
