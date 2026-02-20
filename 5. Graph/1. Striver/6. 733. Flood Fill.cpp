// LeetCode 733. Flood Fill
// Problem: Given an image represented by an m x n integer grid, a starting pixel (sr, sc), and a color,
// perform a flood fill on the image starting from the pixel (sr, sc).

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    // Approach 1: DFS
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];
        
        // If the starting pixel is already the target color, no need to fill
        if (originalColor == color) {
            return image;
        }
        
        dfs(image, sr, sc, originalColor, color);
        return image;
    }
    
private:
    void dfs(vector<vector<int>>& image, int row, int col, int originalColor, int newColor) {
        // Boundary checks and color check
        if (row < 0 || row >= image.size() || col < 0 || col >= image[0].size() || 
            image[row][col] != originalColor) {
            return;
        }
        
        // Change the color
        image[row][col] = newColor;
        
        // Recursively fill in all 4 directions
        dfs(image, row + 1, col, originalColor, newColor); // down
        dfs(image, row - 1, col, originalColor, newColor); // up
        dfs(image, row, col + 1, originalColor, newColor); // right
        dfs(image, row, col - 1, originalColor, newColor); // left
    }
};

// Approach 2: BFS
class Solution2 {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int originalColor = image[sr][sc];
        
        // If the starting pixel is already the target color, no need to fill
        if (originalColor == color) {
            return image;
        }
        
        int m = image.size();
        int n = image[0].size();
        
        queue<pair<int, int>> q;
        q.push({sr, sc});
        image[sr][sc] = color;
        
        // Direction vectors for 4-directional movement
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();
            
            // Check all 4 directions
            for (int i = 0; i < 4; i++) {
                int newRow = row + dx[i];
                int newCol = col + dy[i];
                
                // Check boundaries and if the pixel has the original color
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && 
                    image[newRow][newCol] == originalColor) {
                    image[newRow][newCol] = color;
                    q.push({newRow, newCol});
                }
            }
        }
        
        return image;
    }
};

// Time Complexity: O(m * n) where m is number of rows and n is number of columns
// Space Complexity: O(m * n) for the recursion stack (DFS) or queue (BFS) in worst case

