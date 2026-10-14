// Problem: 130. Surrounded Regions / Replace O's with X's
// Link (LeetCode): https://leetcode.com/problems/surrounded-regions/
// Link (GFG): https://www.geeksforgeeks.org/problems/replace-os-with-xs0052/1
// Difficulty: Medium
// Topic: DFS, BFS, Matrix, Graph, Connected Components

/*
Problem Statement:
Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Notice:
- An 'O' is NOT surrounded if it is on the boundary or connected to an 'O' on the boundary.
- Any 'O' that is not connected to a boundary 'O' will be flipped to 'X'.

Example 1:
Input: board = [["X","X","X","X"],
                ["X","O","O","X"],
                ["X","X","O","X"],
                ["X","O","X","X"]]
Output: [["X","X","X","X"],
         ["X","X","X","X"],
         ["X","X","X","X"],
         ["X","O","X","X"]]
Explanation:
- The 'O's in the interior are completely enclosed by 'X's and thus converted to 'X's.
- The 'O' at board[3][1] is on the boundary, so it and any 'O' connected to it cannot be captured.

Example 2:
Input: board = [["X"]]
Output: [["X"]]

Constraints:
- m == board.length
- n == board[i].length
- 1 <= m, n <= 200
- board[i][j] is 'X' or 'O'.
*/

// Approach: Boundary Traversal (Inverse Thinking)
// 1. Core Insight: Instead of checking which interior 'O's are surrounded, identify which 'O's CANNOT be captured.
// 2. Any 'O' lying on the boundary (row 0, row m-1, col 0, col n-1) can NEVER be surrounded.
// 3. Any 'O' connected (directly or transitively) to a boundary 'O' can also never be captured.
// 4. Start DFS/BFS from all boundary 'O's and temporarily mark them (e.g. '#' or visited).
// 5. After traversal:
//    - Any remaining 'O' is strictly surrounded by 'X' -> convert to 'X'.
//    - Any '#' was safe -> revert back to 'O'.

#include <bits/stdc++.h>
using namespace std;

// Approach 1: In-place DFS (Boundary Traversal)
class Solution {
private:
    void dfs(vector<vector<char>>& board, int r, int c) {
        int m = board.size();
        int n = board[0].size();

        // Base conditions: out of bounds or not an unvisited 'O'
        if (r < 0 || c < 0 || r >= m || c >= n || board[r][c] != 'O') {
            return;
        }

        // Mark current boundary-connected 'O' with temporary marker '#'
        board[r][c] = '#';

        // Traverse in all 4 directions
        dfs(board, r + 1, c); // Down
        dfs(board, r - 1, c); // Up
        dfs(board, r, c + 1); // Right
        dfs(board, r, c - 1); // Left
    }

public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;

        int m = board.size();
        int n = board[0].size();

        // Step 1: Traverse the boundary rows (first and last column)
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') dfs(board, i, 0);
            if (board[i][n - 1] == 'O') dfs(board, i, n - 1);
        }

        // Step 2: Traverse the boundary columns (first and last row)
        for (int j = 0; j < n; j++) {
            if (board[0][j] == 'O') dfs(board, 0, j);
            if (board[m - 1][j] == 'O') dfs(board, m - 1, j);
        }

        // Step 3: Flip surrounded 'O's to 'X', and restore '#' back to 'O'
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X'; // Captured
                } else if (board[i][j] == '#') {
                    board[i][j] = 'O'; // Boundary-connected (escaped)
                }
            }
        }
    }
};

// Approach 2: BFS Approach (Alternative using Queue)
class SolutionBFS {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;

        int m = board.size();
        int n = board[0].size();
        queue<pair<int, int>> q;

        // Push all boundary 'O's into the queue and mark as '#'
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') { board[i][0] = '#'; q.push({i, 0}); }
            if (board[i][n - 1] == 'O') { board[i][n - 1] = '#'; q.push({i, n - 1}); }
        }
        for (int j = 0; j < n; j++) {
            if (board[0][j] == 'O') { board[0][j] = '#'; q.push({0, j}); }
            if (board[m - 1][j] == 'O') { board[m - 1][j] = '#'; q.push({m - 1, j}); }
        }

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'O') {
                    board[nr][nc] = '#';
                    q.push({nr, nc});
                }
            }
        }

        // Final pass: flip and restore
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                else if (board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }
};

/*
Time Complexity: O(M * N)
- Traversing the boundary cells takes O(M + N).
- DFS / BFS visits each cell at most once: O(M * N).
- Final nested loop traverses the entire board: O(M * N).
- Overall Time Complexity: O(M * N)

Space Complexity:
- DFS Recursion Stack: O(M * N) in the worst case (e.g. board filled with 'O's).
- BFS Queue: O(M * N) in the worst case.
- Auxiliary Space: O(1) extra space because we mark directly in the input board using '#'.

Key Insights:
1. Reverse Thinking is Key:
   - Trying to explore inward from every 'O' to see if it reaches an edge leads to redundant revisits.
   - Starting from the boundary and moving inward ensures we only explore cells that are guaranteed to escape capture.
2. In-place marking with '#' eliminates the need for an additional `vector<vector<bool>> visited`, keeping auxiliary space O(1) (excluding the call stack).
*/
