/*
    Problem Name: Word in Grid - All Occurrences (Search Word in 2D Grid)
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a 2D grid mat[][] of size n x m consisting of characters and a string word, find all starting
    positions where the word occurs in the grid.
    - The word can be formed from any cell by moving in ANY of the 8 directions (2 horizontal, 2 vertical, 4 diagonal)
      in a STRAIGHT LINE without changing direction.
    - Return all unique starting coordinates [row, col] in lexicographically smallest order.

    Examples:
    Input: mat[][] = [['a','b','a','b'],
                      ['a','b','e','b'],
                      ['e','b','e','b']], word = "abe"
    Output: [[0, 0], [0, 2], [1, 0]]
    Explanation:
    - From (0,0): "abe" in right-down diagonal.
    - From (0,2): "abe" in left-down diagonal.
    - From (1,0): "abe" in horizontal right direction.

    Input: mat[][] = [['G','E','E','K','S','F','O','R','G','E','E','K','S'],
                      ['G','E','E','K','S','Q','U','I','Z','G','E','E','K'],
                      ['I','D','E','Q','A','P','R','A','C','T','I','C','E']], word = "GEEKS"
    Output: [[0, 0], [0, 8], [1, 0]]

    Constraints:
    1 <= n <= m <= 50
    1 <= |word| <= 20

    Expected Complexities:
    Time Complexity: O(N * M * 8 * L), where N, M are grid dimensions and L is word length.
    Space Complexity: O(1) auxiliary space.

    Approach 1: 8-Directional Straight Line Iterative Search (Optimal - Striver & Love Babbar)
    Approach 2: Fixed Direction DFS Recursion (Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. 8 Directions:
       - dx = {-1, -1, -1,  0, 0,  1, 1, 1}
       - dy = {-1,  0,  1, -1, 1, -1, 0, 1}
    2. Straight-Line Constraint:
       - Once a direction `d` (from 0 to 7) is chosen for a starting cell `(r, c)`, we must move
         strictly in direction `d` for all characters of `word` (`k = 0` to `L-1`).
    3. Lexicographical Order & Uniqueness:
       - By iterating `r` from `0` to `n-1` and `c` from `0` to `m-1`, coordinates `[r, c]` are
         naturally evaluated in lexicographical order.
       - As soon as cell `(r, c)` matches `word` in AT LEAST ONE direction, we add `[r, c]` to our answer
         and break to avoid duplicate starting cell entries!
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ============================================================================
// Approach 1: 8-Directional Straight Line Iterative Search (Optimal - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
public:
    vector<vector<int>> searchWord(vector<vector<char>>& mat, string word) {
        int n = mat.size();
        int m = mat[0].size();
        int L = word.length();

        vector<vector<int>> ans;

        // 8 Directional offsets (Up-Left, Up, Up-Right, Left, Right, Down-Left, Down, Down-Right)
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                // Quick check: starting character must match word[0]
                if (mat[r][c] != word[0]) continue;

                bool found = false;

                // Try all 8 straight-line directions
                for (int dir = 0; dir < 8; dir++) {
                    int currR = r;
                    int currC = c;
                    bool match = true;

                    for (int k = 0; k < L; k++) {
                        if (currR < 0 || currR >= n || currC < 0 || currC >= m || mat[currR][currC] != word[k]) {
                            match = false;
                            break;
                        }
                        currR += dx[dir];
                        currC += dy[dir];
                    }

                    if (match) {
                        found = true;
                        break; // Found match from starting cell (r, c) in at least one direction
                    }
                }

                if (found) {
                    ans.push_back({r, c});
                }
            }
        }

        return ans;
    }
};

// ============================================================================
// Approach 2: Fixed Direction DFS Recursion (Striver & Love Babbar Style)
// ============================================================================
class SolutionDFS {
private:
    bool searchDirectionDFS(int r, int c, int index, int dir, const vector<vector<char>>& mat,
                            const string& word, const int dx[], const int dy[], int n, int m, int L) {
        if (index == L) return true;

        if (r < 0 || r >= n || c < 0 || c >= m || mat[r][c] != word[index]) {
            return false;
        }

        return searchDirectionDFS(r + dx[dir], c + dy[dir], index + 1, dir, mat, word, dx, dy, n, m, L);
    }

public:
    vector<vector<int>> searchWord(vector<vector<char>>& mat, string word) {
        int n = mat.size();
        int m = mat[0].size();
        int L = word.length();

        vector<vector<int>> ans;

        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (mat[r][c] != word[0]) continue;

                bool found = false;
                for (int dir = 0; dir < 8; dir++) {
                    if (searchDirectionDFS(r, c, 0, dir, mat, word, dx, dy, n, m, L)) {
                        found = true;
                        break;
                    }
                }

                if (found) {
                    ans.push_back({r, c});
                }
            }
        }

        return ans;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<vector<int>> searchWord(vector<vector<char>>& mat, string word) {
        SolutionOptimal solver;
        return solver.searchWord(mat, word);
    }
};

// Helper function to print 2D coordinates
void printCoordinates(const vector<vector<int>>& coords) {
    cout << "[ ";
    for (const auto& pt : coords) {
        cout << "[" << pt[0] << ", " << pt[1] << "] ";
    }
    cout << "]\n";
}

int main() {
    // Example 1:
    // Expected Output: [[0, 0], [0, 2], [1, 0]]
    vector<vector<char>> mat1 = {
        {'a', 'b', 'a', 'b'},
        {'a', 'b', 'e', 'b'},
        {'e', 'b', 'e', 'b'}
    };
    string word1 = "abe";

    SolutionOptimal solver1;
    cout << "Example 1 Starting Coordinates (Iterative): ";
    printCoordinates(solver1.searchWord(mat1, word1));

    // Example 2:
    // Expected Output: [[0, 0], [0, 8], [1, 0]]
    vector<vector<char>> mat2 = {
        {'G','E','E','K','S','F','O','R','G','E','E','K','S'},
        {'G','E','E','K','S','Q','U','I','Z','G','E','E','K'},
        {'I','D','E','Q','A','P','R','A','C','T','I','C','E'}
    };
    string word2 = "GEEKS";

    SolutionDFS solver2;
    cout << "Example 2 Starting Coordinates (DFS): ";
    printCoordinates(solver2.searchWord(mat2, word2));

    return 0;
}
