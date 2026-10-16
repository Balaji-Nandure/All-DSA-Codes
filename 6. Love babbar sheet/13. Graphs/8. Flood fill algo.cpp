/**
 * Problem: Flood Fill Algorithm
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Search in a Maze", we navigated towards a destination cell.
 * - Flood Fill recolors an entire 4-directionally CONNECTED COMPONENT of pixels sharing the exact
 *   same initial color (analogous to the Paint Bucket tool in Photoshop/MS Paint).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Connected Component DFS / BFS:
 *   - Record initial color: `oldColor = image[sr][sc]`.
 *   - Edge Case: If `oldColor == newColor`, return immediately to prevent infinite recursive cycles!
 *   - Recurse on cell `(r, c)`:
 *     - If `(r, c)` is out of bounds or `image[r][c] != oldColor`: return.
 *     - Recolor: `image[r][c] = newColor`.
 *     - Recurse in 4 cardinal directions: Up, Down, Left, Right.
 * 
 * TIME COMPLEXITY:
 * - O(M * N): In the worst case, every pixel in the grid is visited once.
 * 
 * SPACE COMPLEXITY:
 * - O(M * N) recursion stack depth in worst case (e.g. spiral/homogeneous image).
 */

#include <iostream>
#include <vector>

void dfsFlood(int r, int c, std::vector<std::vector<int>>& image, int oldColor, int newColor) {
    int rows = image.size();
    int cols = image[0].size();

    if (r < 0 || r >= rows || c < 0 || c >= cols || image[r][c] != oldColor) {
        return;
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Overwrite with newColor immediately before recursing to act as the visited marker.
    image[r][c] = newColor;

    dfsFlood(r + 1, c, image, oldColor, newColor);
    dfsFlood(r - 1, c, image, oldColor, newColor);
    dfsFlood(r, c + 1, image, oldColor, newColor);
    dfsFlood(r, c - 1, image, oldColor, newColor);
}

std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>>& image, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];
    if (oldColor != newColor) {
        dfsFlood(sr, sc, image, oldColor, newColor);
    }
    return image;
}

int main() {
    std::vector<std::vector<int>> image = {
        {1, 1, 1},
        {1, 1, 0},
        {1, 0, 1}
    };
    int sr = 1, sc = 1, newColor = 2;

    std::vector<std::vector<int>> result = floodFill(image, sr, sc, newColor);

    std::cout << "Recolored image:\n";
    for (const auto& row : result) {
        for (int p : row) {
            std::cout << p << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
