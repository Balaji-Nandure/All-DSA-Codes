/*
 * Problem: Rat in a Maze
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/rat-in-a-maze-problem/1
 *
 * Consider a rat placed at position (0, 0) in an n x n square matrix maze[][].
 * The rat's goal is to reach the destination at position (n-1, n-1).
 * The rat can move in four possible directions: 'U'(up), 'D'(down), 'L' (left), 'R' (right).
 * 
 * The matrix contains only two possible values:
 * 0: A blocked cell through which the rat cannot travel.
 * 1: A free cell that the rat can pass through.
 * 
 * Find all possible paths the rat can take to reach the destination.
 * The rat cannot revisit any cell along the same path.
 * Return the final result vector in lexicographically smallest order.
 * 
 * Example 1:
 * Input: maze[][] = [[1, 0, 0, 0], [1, 1, 0, 1], [1, 1, 0, 0], [0, 1, 1, 1]]
 * Output: ["DDRDRR", "DRDDRR"]
 * 
 * Example 2:
 * Input: maze[][] = [[1, 0], [1, 0]]
 * Output: []
 * 
 * Example 3:
 * Input: maze[][] = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
 * Output: ["DDRR", "RRDD"]
 */

#include <bits/stdc++.h>
using namespace std;

void solve(int row, int col, vector<vector<int>> &maze, int n,
           vector<string> &result, string &path,
           vector<vector<bool>> &visited) {
    // Base case: reached destination (n-1, n-1)
    if (row == n - 1 && col == n - 1) {
        result.push_back(path);
        return;
    }

    // Try all 4 directions in lexicographic order: D, L, R, U
    // This ensures paths are generated in lexicographically smallest order

    // DOWN (D): Move to row+1
    if (row + 1 < n && !visited[row + 1][col] && maze[row + 1][col] == 1) {
        visited[row + 1][col] = true;
        path.push_back('D');
        solve(row + 1, col, maze, n, result, path, visited);
        path.pop_back(); // Backtrack
        visited[row + 1][col] = false; // Backtrack
    }

    // LEFT (L): Move to col-1
    if (col - 1 >= 0 && !visited[row][col - 1] && maze[row][col - 1] == 1) {
        visited[row][col - 1] = true;
        path.push_back('L');
        solve(row, col - 1, maze, n, result, path, visited);
        path.pop_back(); // Backtrack
        visited[row][col - 1] = false; // Backtrack
    }

    // RIGHT (R): Move to col+1
    if (col + 1 < n && !visited[row][col + 1] && maze[row][col + 1] == 1) {
        visited[row][col + 1] = true;
        path.push_back('R');
        solve(row, col + 1, maze, n, result, path, visited);
        path.pop_back(); // Backtrack
        visited[row][col + 1] = false; // Backtrack
    }

    // UP (U): Move to row-1
    if (row - 1 >= 0 && !visited[row - 1][col] && maze[row - 1][col] == 1) {
        visited[row - 1][col] = true;
        path.push_back('U');
        solve(row - 1, col, maze, n, result, path, visited);
        path.pop_back(); // Backtrack
        visited[row - 1][col] = false; // Backtrack
    }
}

vector<string> findPath(vector<vector<int>> &maze, int n) {
    vector<string> result;
    
    // If start or destination is blocked, return empty
    if (maze[0][0] == 0 || maze[n - 1][n - 1] == 0) {
        return result;
    }

    vector<vector<bool>> visited(n, vector<bool>(n, false));
    string path = "";
    
    // Mark starting position as visited
    visited[0][0] = true;
    
    solve(0, 0, maze, n, result, path, visited);
    
    return result;
}

int main() {
    // Test case 1
    int n1 = 4;
    vector<vector<int>> maze1 = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    
    cout << "Test case 1:\n";
    cout << "Input maze:\n";
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            cout << maze1[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    
    vector<string> res1 = findPath(maze1, n1);
    cout << "Output: ";
    if (res1.empty()) {
        cout << "[]\n";
    } else {
        for (int i = 0; i < (int)res1.size(); i++) {
            cout << "\"" << res1[i] << "\"";
            if (i < (int)res1.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
    cout << "\n";

    // Test case 2
    int n2 = 2;
    vector<vector<int>> maze2 = {
        {1, 0},
        {1, 0}
    };
    
    cout << "Test case 2:\n";
    cout << "Input maze:\n";
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++) {
            cout << maze2[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    
    vector<string> res2 = findPath(maze2, n2);
    cout << "Output: ";
    if (res2.empty()) {
        cout << "[]\n";
    } else {
        for (int i = 0; i < (int)res2.size(); i++) {
            cout << "\"" << res2[i] << "\"";
            if (i < (int)res2.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
    cout << "\n";

    // Test case 3
    int n3 = 3;
    vector<vector<int>> maze3 = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    
    cout << "Test case 3:\n";
    cout << "Input maze:\n";
    for (int i = 0; i < n3; i++) {
        for (int j = 0; j < n3; j++) {
            cout << maze3[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    
    vector<string> res3 = findPath(maze3, n3);
    cout << "Output: ";
    if (res3.empty()) {
        cout << "[]\n";
    } else {
        for (int i = 0; i < (int)res3.size(); i++) {
            cout << "\"" << res3[i] << "\"";
            if (i < (int)res3.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
    cout << "\n";

    return 0;
}

