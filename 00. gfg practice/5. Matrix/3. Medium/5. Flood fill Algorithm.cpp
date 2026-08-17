/*
    Problem Name: Flood fill Algorithm
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a 2D grid image[][], where each image[i][j] represents the color of a pixel in the image.
    Also provided a starting coordinate (sr, sc) and a newColor value.
    Perform a flood fill starting from (sr, sc), changing its color to newColor and all 4-directionally
    connected pixels (Up, Down, Left, Right) that share the same initial color (initColor).

    Examples:
    Input: image[][] = [[1, 1, 1, 0],
                        [0, 1, 1, 1],
                        [1, 0, 1, 1]], sr = 1, sc = 2, newColor = 2
    Output: [[2, 2, 2, 0],
             [0, 2, 2, 2],
             [1, 0, 2, 2]]

    Input: image[][] = [[0, 1, 0],
                        [0, 1, 0]], sr = 0, sc = 1, newColor = 0
    Output: [[0, 0, 0],
             [0, 0, 0]]

    Constraints:
    1 <= n, m <= 500
    0 <= image[i][j] <= 10
    0 <= newColor <= 10
    0 <= sr <= n - 1
    0 <= sc <= m - 1

    Expected Complexities:
    Time Complexity: O(N * M), where N is rows and M is columns.
    Space Complexity: O(N * M), for call stack / queue.

    Approach 1: DFS (Depth First Search - Striver / Love Babbar Style)
    Approach 2: BFS (Breadth First Search - Striver / Love Babbar Style)

    INTUITION & STRATEGY:
    1. Base Edge Case:
       - If `image[sr][sc] == newColor`, no color change is required. Returning `image` as is
         prevents infinite recursion/loops.
    2. Store original color: `initColor = image[sr][sc]`.
    3. Traversal (DFS / BFS):
       - Change current pixel color to `newColor`.
       - Check all 4-directional neighbours (Up: -1,0; Down: +1,0; Left: 0,-1; Right: 0,+1).
       - If neighbour is within bounds and has `image[nr][nc] == initColor`, visit and recolor it.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ============================================================================
// Approach 1: Depth First Search (DFS Recursion - Striver & Love Babbar Style)
// ============================================================================
class SolutionDFS {
private:
    void dfs(int r, int c, int initColor, int newColor,
             vector<vector<int>>& image, int delRow[], int delCol[], int n, int m) {
        // Color current pixel
        image[r][c] = newColor;

        // Traverse 4 directions
        for (int i = 0; i < 4; i++) {
            int nr = r + delRow[i];
            int nc = c + delCol[i];

            // Check boundary and if neighbour color equals initColor
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && image[nr][nc] == initColor) {
                dfs(nr, nc, initColor, newColor, image, delRow, delCol, n, m);
            }
        }
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int initColor = image[sr][sc];

        // Edge case: if starting pixel already has newColor, return image as is
        if (initColor == newColor) {
            return image;
        }

        int n = image.size();
        int m = image[0].size();

        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        dfs(sr, sc, initColor, newColor, image, delRow, delCol, n, m);

        return image;
    }
};

// ============================================================================
// Approach 2: Breadth First Search (BFS Queue Iterative - Striver & Love Babbar Style)
// ============================================================================
class SolutionBFS {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int initColor = image[sr][sc];

        // Edge case
        if (initColor == newColor) {
            return image;
        }

        int n = image.size();
        int m = image[0].size();

        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = newColor;

        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nr = r + delRow[i];
                int nc = c + delCol[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m && image[nr][nc] == initColor) {
                    image[nr][nc] = newColor; // Recolor before pushing into queue
                    q.push({nr, nc});
                }
            }
        }

        return image;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        SolutionDFS solver;
        return solver.floodFill(image, sr, sc, newColor);
    }
};

// Helper function to print matrix
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
    vector<vector<int>> image1 = {
        {1, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 1, 1}
    };
    int sr1 = 1, sc1 = 2, newColor1 = 2;

    SolutionDFS dfsSolver;
    vector<vector<int>> res1 = dfsSolver.floodFill(image1, sr1, sc1, newColor1);
    cout << "Example 1 Output (DFS):\n";
    printMatrix(res1);
    cout << "\n";

    // Example 2:
    vector<vector<int>> image2 = {
        {0, 1, 0},
        {0, 1, 0}
    };
    int sr2 = 0, sc2 = 1, newColor2 = 0;

    SolutionBFS bfsSolver;
    vector<vector<int>> res2 = bfsSolver.floodFill(image2, sr2, sc2, newColor2);
    cout << "Example 2 Output (BFS):\n";
    printMatrix(res2);

    return 0;
}
