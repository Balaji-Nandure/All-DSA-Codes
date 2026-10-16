/**
 * Problem: Total Number of Spanning Trees in a Graph (Kirchhoff's Matrix Tree Theorem)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Prim's and Kruskal's algorithms find ONE minimum-weight spanning tree.
 * - This problem counts the TOTAL combinatorial count of all distinct spanning trees that exist in an unweighted/weighted graph.
 * - Enumeration is exponential; Kirchhoff's Theorem enables algebraic polynomial-time computation via determinants.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Kirchhoff's Theorem & Laplacian Matrix Cofactor Determinant:
 *   1. Form Degree Matrix `D` where `D[i][i] = degree(vertex i)`.
 *   2. Form Adjacency Matrix `A` where `A[i][j] = number of edges between i and j`.
 *   3. Form the Laplacian Matrix `L = D - A`:
 *      - `L[i][i] = degree(i)`
 *      - `L[i][j] = -A[i][j]` (for i != j)
 *   4. Delete any single row `r` and column `c` (typically row 0 and column 0) to obtain submatrix `M` of size `(V-1) x (V-1)`.
 *   5. The number of spanning trees equals `det(M)`.
 *   6. Compute `det(M)` using Gaussian Elimination with partial pivoting.
 * 
 * TIME COMPLEXITY:
 * - O(V^3): Dominated by Gaussian elimination on a (V-1) x (V-1) matrix.
 * 
 * SPACE COMPLEXITY:
 * - O(V^2) for the Laplacian submatrix.
 */

#include <iostream>
#include <vector>
#include <cmath>

double determinant(std::vector<std::vector<double>>& mat, int n) {
    double det = 1.0;

    for (int i = 0; i < n; i++) {
        // Pivot selection
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (std::abs(mat[j][i]) > std::abs(mat[pivot][i])) {
                pivot = j;
            }
        }

        if (std::abs(mat[pivot][i]) < 1e-9) return 0.0; // Singular matrix

        if (pivot != i) {
            std::swap(mat[i], mat[pivot]);
            det = -det;
        }

        det *= mat[i][i];

        // Elimination
        for (int j = i + 1; j < n; j++) {
            double factor = mat[j][i] / mat[i][i];
            for (int k = i; k < n; k++) {
                mat[j][k] -= factor * mat[i][k];
            }
        }
    }

    return std::abs(det);
}

long long countSpanningTrees(int V, const std::vector<std::vector<int>>& adjMatrix) {
    if (V <= 1) return 1;

    // Build Laplacian matrix L = D - A
    std::vector<std::vector<double>> L(V, std::vector<double>(V, 0.0));

    for (int i = 0; i < V; i++) {
        int degree = 0;
        for (int j = 0; j < V; j++) {
            if (adjMatrix[i][j]) {
                degree += adjMatrix[i][j];
                L[i][j] = -adjMatrix[i][j];
            }
        }
        L[i][i] = degree;
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Kirchhoff's Matrix Tree Theorem: Number of spanning trees = determinant of any (V-1)x(V-1) cofactor of L.
    std::vector<std::vector<double>> submatrix(V - 1, std::vector<double>(V - 1, 0.0));
    for (int i = 1; i < V; i++) {
        for (int j = 1; j < V; j++) {
            submatrix[i - 1][j - 1] = L[i][j];
        }
    }

    double det = determinant(submatrix, V - 1);
    return std::llround(det);
}

int main() {
    // Complete graph K4 has n^(n-2) = 4^(4-2) = 16 spanning trees (Cayley's formula)
    int V = 4;
    std::vector<std::vector<int>> adj = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };

    long long trees = countSpanningTrees(V, adj);
    std::cout << "Total number of spanning trees in K4: " << trees << "\n"; // Expected: 16

    return 0;
}
