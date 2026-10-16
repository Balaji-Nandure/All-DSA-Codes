/**
 * Problem: Implement Floyd-Warshall Algorithm (All-Pairs Shortest Path)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Dijkstra and Bellman-Ford compute shortest paths from a SINGLE source.
 * - Floyd-Warshall is an all-pairs dynamic programming algorithm that simultaneously computes shortest paths between every pair of vertices (i, j).
 * - Can detect negative cycles (if `dist[i][i] < 0` for any vertex).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dynamic Programming over Intermediate Vertices:
 *   - Let `dist[i][j]` be the shortest path from `i` to `j` using only intermediate vertices from the set `{0, 1, ..., k-1}`.
 *   - When considering vertex `k` as a potential intermediate hop:
 *     `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`
 *   - We execute 3 nested loops: outer loop on `k`, inner loops on `i` and `j`.
 *   - Matrix input typically uses `-1` or `INF` for absent edges.
 * 
 * TIME COMPLEXITY:
 * - O(V^3): 3 nested loops from 0 to V - 1.
 * 
 * SPACE COMPLEXITY:
 * - O(1) auxiliary space beyond the in-place distance matrix.
 */

#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e8;

void shortestDistance(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();

    // Convert -1 representation to INF for calculation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == -1) matrix[i][j] = INF;
            if (i == j) matrix[i][j] = 0;
        }
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Outer loop selects the intermediate vertex k; update path (i -> j) if detouring via k is cheaper.
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][k] != INF && matrix[k][j] != INF) {
                    matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] < 0) {
            std::cout << "Negative cycle detected involving node " << i << "\n";
        }
    }

    // Revert INF back to -1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] >= INF) {
                matrix[i][j] = -1;
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> matrix = {
        {0, 2, -1, -1},
        {1, 0, 3, -1},
        {-1, -1, 0, -1},
        {3, 5, 4, 0}
    };

    shortestDistance(matrix);

    std::cout << "All-Pairs Shortest Distances:\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}
