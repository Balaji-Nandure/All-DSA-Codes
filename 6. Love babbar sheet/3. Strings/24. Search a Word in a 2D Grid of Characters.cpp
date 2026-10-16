// Problem: Search a Word in a 2D Grid of Characters (Word Search in 8 Directions)
// Link (GFG): https://www.geeksforgeeks.org/problems/find-the-string-in-grid0111/1
// Article: https://www.geeksforgeeks.org/dsa/search-a-word-in-a-2d-grid-of-characters/
// Difficulty: Medium
// Topic: String, 2D Matrix, Directional Ray Casting

/*
Problem Statement:
Given a 2D grid of characters and a word, find all starting coordinates of the word in the grid.
The word can match in any of the 8 directions (Horizontal, Vertical, and Diagonals), 
BUT unlike snake-like backtracking, ALL characters of the word must proceed in the 
EXACT SAME STRAIGHT LINE DIRECTION.

If a word starts at a cell (r, c) in multiple directions, (r, c) should be listed only once.
Return the coordinates sorted in row-major order.

Example 1:
Input:
grid = [['a', 'b', 'a', 'b'],
        ['a', 'b', 'e', 'b'],
        ['e', 'b', 'e', 'b']]
word = "abe"
Output: 
[[0, 0], [0, 2], [1, 0]]
Explanation: 
From (0, 0) moving down-right diagonally: 'a' -> 'b' -> 'e'.
From (0, 2) moving down-left diagonally: 'a' -> 'b' -> 'e'.
From (1, 0) moving right horizontally: 'a' -> 'b' -> 'e'.

Constraints:
- 1 <= R, C <= 100
- 1 <= word.length() <= 15
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 23 (Count Word in 2D Array):
//   * A word could turn and bend at every step in 4 directions (meandering snake-path).
//   * Required full recursive DFS with backtracking.
// - In Problem 24 (Search a Word in Grid - Straight Line):
//   * The word must move in a STRICT STRAIGHT LINE along ONE of the 8 directions.
//   * Once direction `d` is chosen, the path is completely rigid and deterministic!
//   * No backtracking stack is needed; simple ray-casting in O(L) time per direction suffices.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// 8-Directional Straight Line Ray Casting (Optimal & Chosen):
//   - Define 8 direction vectors covering cardinal and diagonal moves:
//       `dr = {-1, -1, -1, 0, 0, 1, 1, 1}`
//       `dc = {-1, 0, 1, -1, 1, -1, 0, 1}`
//   - For each cell `(r, c)`:
//       * If `grid[r][c] != word[0]`: skip.
//       * For each direction `d` from 0 to 7:
//           - Step `k` from 1 to `L - 1`:
//               `nr = r + k * dr[d]`, `nc = c + k * dc[d]`.
//               If out of bounds or `grid[nr][nc] != word[k]`: break mismatch.
//           - If all L characters matched: Record `(r, c)` as a valid starting coordinate 
//             and break (to prevent duplicate entries for the same cell)!
//   - Complexity: O(R * C * 8 * L) time, O(1) auxiliary space.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    // 8 Directions: Up-Left, Up, Up-Right, Left, Right, Down-Left, Down, Down-Right
    const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    bool searchInDirection(const vector<vector<char>>& grid, const string& word, 
                           int r, int c, int dirIdx, int R, int C) {
        int len = word.length();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Pure linear ray-casting: Direction is FIXED.
        // Coordinate at step k is (r + k * dr[dirIdx], c + k * dc[dirIdx]).
        for (int k = 1; k < len; ++k) {
            int nr = r + k * dr[dirIdx];
            int nc = c + k * dc[dirIdx];

            if (nr < 0 || nr >= R || nc < 0 || nc >= C || grid[nr][nc] != word[k]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<int>> searchWord(vector<vector<char>> grid, string word) {
        vector<vector<int>> result;
        if (grid.empty() || grid[0].empty() || word.empty()) return result;

        int R = grid.size();
        int C = grid[0].size();

        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                // If first letter matches, test all 8 straight-line ray trajectories
                if (grid[i][j] == word[0]) {
                    for (int d = 0; d < 8; ++d) {
                        if (searchInDirection(grid, word, i, j, d, R, C)) {
                            result.push_back({i, j});
                            break; // Avoid inserting the same starting cell multiple times
                        }
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> grid = {
        {'a', 'b', 'a', 'b'},
        {'a', 'b', 'e', 'b'},
        {'e', 'b', 'e', 'b'}
    };
    string word = "abe";

    vector<vector<int>> starts = sol.searchWord(grid, word);
    cout << "Word \"" << word << "\" starts at:\n";
    for (const auto& pt : starts) {
        cout << "[" << pt[0] << ", " << pt[1] << "] ";
    }
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(R * C * 8 * L).
  * For each cell, we test at most 8 directions, each checking up to L characters.
  * For R=100, C=100, L=15: 100 * 100 * 8 * 15 ≈ 1.2 * 10^6 ops (takes ~5 ms).
- Space Complexity: O(1) auxiliary space (excluding result coordinates).

Key Takeaways:
- Straight-line ray casting is vastly faster and simpler than backtracking DFS 
  because there is no state exploration branching.
*/
