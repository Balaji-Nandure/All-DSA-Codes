// Problem: Count of Number of Given String in 2D Character Array
// Link (GFG): https://www.geeksforgeeks.org/problems/count-occurences-of-a-given-word-in-a-2-d-array/1
// Article: https://www.geeksforgeeks.org/dsa/find-count-number-given-string-present-2d-character-array/
// Difficulty: Hard
// Topic: String, 2D Matrix, DFS & Backtracking

/*
Problem Statement:
Find the count of occurrences of a given target word in an N x M 2D grid of characters.
The word can be formed by sequential letters along 4 orthogonal directions (up, down, left, right).
The same cell cannot be reused more than once within the same occurrence of the word.

Example 1:
Input:
R = 4, C = 5
grid = [
  ['S', 'N', 'B', 'S', 'N'],
  ['B', 'A', 'K', 'E', 'A'],
  ['B', 'K', 'B', 'B', 'K'],
  ['S', 'E', 'B', 'S', 'E']
]
target = "SNAKES"
Output: 3

Constraints:
- 1 <= R, C <= 100
- 1 <= target.length() <= 15
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In 1D String Matching (Rabin-Karp, KMP):
//   * Search was strictly 1-dimensional and unidirectional (left-to-right).
// - In 2D Character Grid Search:
//   * Search branches into 4 cardinal directions at each character.
//   * We must enforce non-reusability within the same path: A cell used for 'S' cannot 
//     be reused for a later 'S' in the same word occurrence.
//   * In-place masking (`grid[r][c] = '#'`) eliminates the need for allocating visited sets!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// DFS with In-Place Backtracking (Optimal & Chosen):
//   - Find every cell `(i, j)` where `grid[i][j] == target[0]`.
//   - Launch `dfs(i, j, 0)`:
//       1. Base case: If `idx == target.length() - 1`, a complete valid path is formed -> return 1.
//       2. Save original character: `char original = grid[r][c]`.
//       3. Mask cell: `grid[r][c] = '#'` (prevents self-looping on the current path).
//       4. Explore all 4 neighbors:
//            If neighbor `(nr, nc)` is valid and `grid[nr][nc] == target[idx + 1]`:
//              `matches += dfs(nr, nc, idx + 1)`.
//       5. Backtrack: Restore `grid[r][c] = original`.
//   - Complexity: O(R * C * 3^L) where L is the length of target word.
//   - Space Complexity: O(L) recursion stack depth (zero heap memory).

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    // 4 Cardinal directions: Up, Down, Left, Right
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    int dfs(vector<vector<char>>& mat, const string& target, int r, int c, int idx) {
        // Base case: entire word successfully matched
        if (idx == (int)target.length() - 1) {
            return 1;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // In-place masking: Temporarily replace character with '#' to prevent circular re-visitation
        // within this specific search path, without allocating an auxiliary visited matrix!
        char originalChar = mat[r][c];
        mat[r][c] = '#';

        int pathsFound = 0;
        int n = mat.size();
        int m = mat[0].size();

        // Explore all 4 adjacent cells
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && mat[nr][nc] == target[idx + 1]) {
                pathsFound += dfs(mat, target, nr, nc, idx + 1);
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Backtracking: Unmask cell so other parallel search paths can utilize it
        mat[r][c] = originalChar;

        return pathsFound;
    }

public:
    int findOccurrence(vector<vector<char>>& mat, string target) {
        if (mat.empty() || mat[0].empty() || target.empty()) return 0;

        int n = mat.size();
        int m = mat[0].size();
        int totalOccurrences = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // Launch DFS whenever the starting letter matches
                if (mat[i][j] == target[0]) {
                    totalOccurrences += dfs(mat, target, i, j, 0);
                }
            }
        }

        return totalOccurrences;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> mat = {
        {'S', 'N', 'B', 'S', 'N'},
        {'B', 'A', 'K', 'E', 'A'},
        {'B', 'K', 'B', 'B', 'K'},
        {'S', 'E', 'B', 'S', 'E'}
    };
    string target = "SNAKES";

    cout << "Occurrences of \"" << target << "\" in grid: " 
         << sol.findOccurrence(mat, target) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(R * C * 3^L) where L is the length of the word (since we don't turn back, branching is at most 3).
  * For L <= 15, recursion finishes rapidly.
- Space Complexity: O(L) for the recursion stack frame depth (O(1) auxiliary heap space).

Key Takeaways:
- In-place char modification (`#` and restore) is the standard high-performance idiom 
  for path backtracking in 2D grids.
*/
