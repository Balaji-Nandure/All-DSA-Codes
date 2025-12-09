/*
 * Problem: Knight's Tour
 * 
 * Given an n x n chessboard, find a sequence of moves for a knight such that it visits 
 * every square exactly once. A knight moves in an L-shape: 2 squares in one direction 
 * and 1 square perpendicular to it.
 * 
 * The knight has 8 possible moves:
 * - (row-2, col-1), (row-2, col+1)
 * - (row-1, col-2), (row-1, col+2)
 * - (row+1, col-2), (row+1, col+2)
 * - (row+2, col-1), (row+2, col+1)
 * 
 * Return a 2D array showing the order in which squares are visited (1 to n*n),
 * or return empty if no solution exists.
 * 
 * Example for 5x5 board:
 * One possible solution exists starting from (0,0)
 */


#include <bits/stdc++.h>
using namespace std;

// All 8 possible moves for a knight
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// Recursive backtracking function to solve Knight's Tour
bool solveKnightTour(int row, int col, int move, int n, vector<vector<int>>& board) {
    // Base case: all squares visited
    if (move == n * n) {
        return true;
    }
    
    // Try all 8 possible moves
    for (int i = 0; i < 8; i++) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        
        // Check if the move is valid
        if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && 
            board[newRow][newCol] == -1) {
            
            // Mark this square as visited
            board[newRow][newCol] = move;
            
            // Recurse for next move
            if (solveKnightTour(newRow, newCol, move + 1, n, board)) {
                return true;
            }
            
            // Backtrack: unmark this square
            board[newRow][newCol] = -1;
        }
    }
    
    return false;
}

// Main function to solve Knight's Tour
// Returns true if a knight's tour exists, false otherwise (using only backtracking version)
bool knightTourExists(int n, int startRow = 0, int startCol = 0) {
    vector<vector<int>> board(n, vector<int>(n, -1)); // -1 means unvisited

    // Mark starting position
    board[startRow][startCol] = 0;

    // Try to solve with standard backtracking
    if (solveKnightTour(startRow, startCol, 1, n, board)) {
        return true;
    }

    // If no solution found
    return false;
}

int main() {
    int n = 5;
    cout << "Knight's Tour for " << n << "x" << n << " board" << endl;
    cout << "Starting from position (0, 0)" << endl;
    cout << endl;

    // Standard backtracking approach
    cout << "=== Standard Backtracking Approach ===" << endl;

    bool found = knightTourExists(n, 0, 0);

    if (found) {
        cout << "Solution exists!" << endl;
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
