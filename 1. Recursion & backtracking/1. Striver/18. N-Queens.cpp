/*
 * Problem: N-Queens
 * 
 * LeetCode 51: N-Queens
 * GeeksforGeeks: https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/
 *
 * The n-queens puzzle is the problem of placing n queens on an n x n chessboard
 * such that no two queens attack each other.
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * You may return the answer in any order.
 * 
 * Each solution contains a distinct board configuration of the n-queens' placement,
 * where 'Q' and '.' both indicate a queen and an empty space, respectively.
 * 
 * Example 1:
 * Input: n = 4
 * Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
 * 
 * Example 2:
 * Input: n = 1
 * Output: [["Q"]]
 */

// 1. Basic Backtracking Method (O(n) isSafe check)
//     Uses a function to check if a position is safe
//     Checks column, upper-left diagonal, and upper-right diagonal
//     More intuitive but slower
//     Time: O(n! × n), Space: O(n²)
// 2. Optimized Method with HashMaps (O(1) isSafe check)
//     Uses hash maps to track:
//     colUsed: columns already occupied
//     diag1Used: diagonal \ (row - col + n - 1)
//     diag2Used: diagonal / (row + col)
//     Faster than the basic method
//     Time: O(n!), Space: O(n)
// 3. Count Only Method
//     Counts total solutions without storing boards
//     Useful when only the count is needed
//     Same optimization as method 2

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// METHOD 1: Basic Backtracking with O(n) isSafe check
// -------------------------------------------------------
bool isSafe(int row, int col, vector<string>& board, int n) {
    // Check column above
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }

    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }

    return true;
}

void solveNQueens_basic(int row, int n, vector<string>& board, 
                       vector<vector<string>>& result) {
    // Base case: all queens placed
    if (row == n) {
        result.push_back(board);
        return;
    }

    // Try placing queen in each column of current row
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, board, n)) {
            // Place queen
            board[row][col] = 'Q';
            // Recurse for next row
            solveNQueens_basic(row + 1, n, board, result);
            // Backtrack: remove queen
            board[row][col] = '.';
        }
    }
}

vector<vector<string>> solveNQueens_basic_method(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.')); // Initialize board with '.'
    solveNQueens_basic(0, n, board, result);
    return result;
}

// -------------------------------------------------------
// METHOD 2: Optimized with HashMaps (O(1) isSafe check)
// -------------------------------------------------------
void solveNQueens_optimized(int row, int n, vector<string>& board,
                           vector<vector<string>>& result,
                           vector<bool>& colUsed,
                           vector<bool>& diag1Used,  // diagonal: row - col + n - 1
                           vector<bool>& diag2Used) { // diagonal: row + col
    // Base case: all queens placed
    if (row == n) {
        result.push_back(board);
        return;
    }

    // Try placing queen in each column of current row
    for (int col = 0; col < n; col++) {
        int diag1 = row - col + n - 1; // for diagonal (row-col direction)
        int diag2 = row + col;         // for diagonal (row+col direction)

        // Check if position is safe using hash maps
        if (!colUsed[col] && !diag1Used[diag1] && !diag2Used[diag2]) {
            // Place queen
            board[row][col] = 'Q';
            colUsed[col] = true;
            diag1Used[diag1] = true;
            diag2Used[diag2] = true;

            // Recurse for next row
            solveNQueens_optimized(row + 1, n, board, result, 
                                  colUsed, diag1Used, diag2Used);

            // Backtrack: remove queen
            board[row][col] = '.';
            colUsed[col] = false;
            diag1Used[diag1] = false;
            diag2Used[diag2] = false;
        }
    }
}

vector<vector<string>> solveNQueens_optimized_method(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.')); // Initialize board with '.'
    vector<bool> colUsed(n, false);
    vector<bool> diag1Used(2 * n - 1, false); // diagonal (row-col direction)
    vector<bool> diag2Used(2 * n - 1, false); // diagonal (row+col direction)
    
    solveNQueens_optimized(0, n, board, result, colUsed, diag1Used, diag2Used);
    return result;
}

// -------------------------------------------------------
// METHOD 3: Count only (without storing boards)
// -------------------------------------------------------
void countNQueens(int row, int n, vector<bool>& colUsed,
                  vector<bool>& diag1Used, vector<bool>& diag2Used, int& count) {
    // Base case: all queens placed
    if (row == n) {
        count++;
        return;
    }

    // Try placing queen in each column of current row
    for (int col = 0; col < n; col++) {
        int diag1 = row - col + n - 1;
        int diag2 = row + col;

        if (!colUsed[col] && !diag1Used[diag1] && !diag2Used[diag2]) {
            colUsed[col] = true;
            diag1Used[diag1] = true;
            diag2Used[diag2] = true;

            countNQueens(row + 1, n, colUsed, diag1Used, diag2Used, count);

            colUsed[col] = false;
            diag1Used[diag1] = false;
            diag2Used[diag2] = false;
        }
    }
}

int totalNQueens(int n) {
    int count = 0;
    vector<bool> colUsed(n, false);
    vector<bool> diag1Used(2 * n - 1, false);
    vector<bool> diag2Used(2 * n - 1, false);
    
    countNQueens(0, n, colUsed, diag1Used, diag2Used, count);
    return count;
}

// -------------------------------------------------------
// Helper function to print board
// -------------------------------------------------------
void printBoard(vector<string>& board) {
    for (string& row : board) {
        cout << row << "\n";
    }
}

// -------------------------------------------------------
// MAIN FUNCTION
// -------------------------------------------------------
int main() {
    int n = 4;
    cout << "N-Queens Problem for n = " << n << "\n\n";

    cout << "Using Basic Method (O(n) isSafe check):\n";
    vector<vector<string>> res1 = solveNQueens_basic_method(n);
    cout << "Total solutions: " << res1.size() << "\n\n";
    
    for (int i = 0; i < (int)res1.size(); i++) {
        cout << "Solution " << (i + 1) << ":\n";
        printBoard(res1[i]);
        cout << "\n";
    }

    cout << "Using Optimized Method (O(1) isSafe check with HashMaps):\n";
    vector<vector<string>> res2 = solveNQueens_optimized_method(n);
    cout << "Total solutions: " << res2.size() << "\n\n";
    
    for (int i = 0; i < (int)res2.size(); i++) {
        cout << "Solution " << (i + 1) << ":\n";
        printBoard(res2[i]);
        cout << "\n";
    }

    cout << "Count only (without storing boards):\n";
    int count = totalNQueens(n);
    cout << "Total solutions: " << count << "\n\n";

    // Test with different values
    cout << "Testing for different values of n:\n";
    for (int testN = 1; testN <= 8; testN++) {
        int testCount = totalNQueens(testN);
        cout << "n = " << testN << ": " << testCount << " solutions\n";
    }

    return 0;
}

