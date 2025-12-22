/*
 * Problem: Knight's Tour
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/knight-tour/0
 *
 * Find a sequence of moves for a knight to visit every square exactly once.
 * Knight moves in L-shape: 2 squares in one direction, 1 square perpendicular.
 *
 * Knight has 8 possible moves from any position.
 *
 * Time: O(8^(n²)) - exponential backtracking
 * Space: O(n²) - board storage
 */


#include <bits/stdc++.h>
using namespace std;

// All 8 possible knight moves (L-shaped)
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// Recursive backtracking to solve Knight's Tour
bool solveKnightTour(int row, int col, int move, int n, vector<vector<int>>& board) {
    // Base case: visited all n*n squares
    if (move == n * n) {
        return true;
    }
    
    // Try all 8 possible knight moves
    for (int i = 0; i < 8; i++) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        
        // Check if move is valid (within bounds and unvisited)
        if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && 
            board[newRow][newCol] == -1) {
            
            // Mark square as visited with move number
            board[newRow][newCol] = move;
            
            // Recurse to find next move
            if (solveKnightTour(newRow, newCol, move + 1, n, board)) {
                return true;
            }
            
            // Backtrack: unmark square if path doesn't lead to solution
            board[newRow][newCol] = -1;
        }
    }
    
    return false; // No valid move found
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

    bool found = knightTourExists(n, 0, 0);
    cout << found << endl;
    return 0;
}
