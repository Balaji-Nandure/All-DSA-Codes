/*
 * Problem: 79. Word Search
 * 
 * Given an m x n grid of characters board and a string word, return true if word exists in the grid.
 * 
 * The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are 
 * horizontally or vertically neighboring. The same letter cell may not be used more than once.
 * 
 * Example 1:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
 * Output: true
 * 
 * Example 2:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
 * Output: true
 * 
 * Example 3:
 * Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
 * Output: false
 */

#include <bits/stdc++.h>
using namespace std;

// DFS/backtracking function to search for word in the board
bool dfs(int i, int j, int idx, vector<vector<char>>& board, string& word) {
    // Base case: if all characters matched
    if (idx == (int)word.size()) 
        return true;

    int m = board.size();
    int n = board[0].size();

    // Out of bounds
    if (i < 0 || j < 0 || i >= m || j >= n)
        return false;
    // If cell doesn't match or is already used
    if (board[i][j] != word[idx])
        return false;

    // Mark this cell as used
    char saved = board[i][j];
    board[i][j] = '#';

    // Try all 4 directions manually: LEFT, RIGHT, UP, DOWN

    // LEFT  (i, j-1)
    if (dfs(i, j - 1, idx + 1, board, word)) {
        board[i][j] = saved;   // Backtrack
        return true;
    }
    // RIGHT (i, j+1)
    if (dfs(i, j + 1, idx + 1, board, word)) {
        board[i][j] = saved;
        return true;
    }
    // UP    (i-1, j)
    if (dfs(i - 1, j, idx + 1, board, word)) {
        board[i][j] = saved;
        return true;
    }
    // DOWN  (i+1, j)
    if (dfs(i + 1, j, idx + 1, board, word)) {
        board[i][j] = saved;
        return true;
    }

    // Backtrack: restore cell
    board[i][j] = saved;
    return false;
}

// Main function to check if word exists in board
bool exist(vector<vector<char>>& board, string word) {
    int m = board.size();
    int n = board[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == word[0]) {
                if (dfs(i, j, 0, board, word)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    // Test case 1
    vector<vector<char>> board1 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    string word1 = "ABCCED";

    cout << "Test case 1:" << endl;
    cout << "Board:" << endl;
    for (auto& row : board1) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << "Word: " << word1 << endl;

    bool result1 = exist(board1, word1);
    cout << "Result: " << (result1 ? "true" : "false") << endl;
    cout << endl;

    return 0;
}
