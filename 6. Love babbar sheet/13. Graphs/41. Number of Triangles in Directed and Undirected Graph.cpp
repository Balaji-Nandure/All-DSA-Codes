/**
 * Problem: Number of Triangles in Directed and Undirected Graph
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Detecting simple cycles of length 3 can be done by brute-force search.
 * - However, algebraic graph theory provides an elegant connection:
 *   If A is the adjacency matrix, the (i, i)-th entry of A^3 is the number of closed walks of length 3 starting and ending at vertex i.
 * - In an undirected graph, each triangle is counted 6 times (3 vertices * 2 orientations).
 * - In a directed graph, each directed triangle is counted 3 times (1 cycle orientation * 3 vertices).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Matrix Multiplication (Trace of A^3) & Fast 3-Hop Counting:
 *   1. Compute `A^2 = A * A`.
 *   2. Compute `A^3 = A^2 * A`.
 *   3. Compute `trace(A^3) = sum_{i=0}^{V-1} (A^3)[i][i]`.
 *   4. For Undirected Graphs:
 *      `triangles = trace(A^3) / 6`
 *   5. For Directed Graphs:
 *      `triangles = trace(A^3) / 3`
 *   - Also provides a direct combinatorial triple loop `(i, j, k)` for sparse/small graphs:
 *     Check if `adj[i][j] && adj[j][k] && adj[k][i]`.
 * 
 * TIME COMPLEXITY:
 * - O(V^3): Standard matrix multiplication.
 * 
 * SPACE COMPLEXITY:
 * - O(V^2) for adjacency and multiplication matrices.
 */

#include <iostream>
#include <vector>

std::vector<std::vector<int>> multiply(int V, const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    std::vector<std::vector<int>> C(V, std::vector<int>(V, 0));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            for (int k = 0; k < V; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int countTriangles(int V, const std::vector<std::vector<int>>& adj, bool isDirected) {
    // Compute A^2
    auto A2 = multiply(V, adj, adj);
    // Compute A^3
    auto A3 = multiply(V, A2, adj);

    // Compute Trace(A^3)
    int trace = 0;
    for (int i = 0; i < V; i++) {
        trace += A3[i][i];
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // In undirected graphs each triangle has 6 closed walks of length 3; in directed graphs each has 3.
    if (isDirected) {
        return trace / 3;
    } else {
        return trace / 6;
    }
}

int main() {
    int V = 4;
    // Undirected graph with complete 4 vertices has 4 triangles
    std::vector<std::vector<int>> undirectedAdj = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    int uCount = countTriangles(V, undirectedAdj, false);
    std::cout << "Number of triangles in undirected graph: " << uCount << "\n"; // Expected: 2 (0-1-2 and 1-2-3)

    // Directed graph
    std::vector<std::vector<int>> directedAdj = {
        {0, 0, 1, 0},
        {1, 0, 0, 1},
        {0, 1, 0, 0},
        {0, 0, 1, 0}
    };
    int dCount = countTriangles(V, directedAdj, true);
    std::cout << "Number of triangles in directed graph: " << dCount << "\n"; // Expected: 2

    return 0;
}
