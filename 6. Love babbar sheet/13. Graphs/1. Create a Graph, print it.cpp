/**
 * Problem: Create a Graph and Print It (Adjacency Matrix & Adjacency List)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Trees were acyclic, connected, and directed strictly from root to leaves with parent-child links.
 * - Graphs are generalized networks: edges can be directed or undirected, cyclic or acyclic, weighted or unweighted,
 *   with arbitrary degree connectivity requiring adjacency representations.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Representation 1: Adjacency List (Vector of Vectors):
 *   - Space-optimal: O(V + E) memory.
 *   - Fast neighbor iteration in O(degree(u)) time.
 *   - The industry and competitive programming standard.
 * - Representation 2: Adjacency Matrix (2D Array):
 *   - O(1) edge existence query: `matrix[u][v] == 1`.
 *   - Uses O(V^2) memory (ideal only for dense graphs).
 * 
 * TIME COMPLEXITY:
 * - Add edge: O(1)
 * - Print graph: O(V + E) for list, O(V^2) for matrix.
 * 
 * SPACE COMPLEXITY:
 * - Adjacency List: O(V + E)
 * - Adjacency Matrix: O(V^2)
 */

#include <iostream>
#include <vector>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adjList;
    std::vector<std::vector<int>> adjMatrix;

public:
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
        adjMatrix.assign(V, std::vector<int>(V, 0));
    }

    void addEdge(int u, int v, bool isDirected = false) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Adjacency List records directed u->v (and symmetrically v->u if undirected) in minimal O(V + E) space.
        adjList[u].push_back(v);
        adjMatrix[u][v] = 1;

        if (!isDirected) {
            adjList[v].push_back(u);
            adjMatrix[v][u] = 1;
        }
    }

    void printAdjList() const {
        std::cout << "Adjacency List Representation:\n";
        for (int i = 0; i < V; i++) {
            std::cout << "Vertex " << i << " -> ";
            for (int neighbor : adjList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }

    void printAdjMatrix() const {
        std::cout << "\nAdjacency Matrix Representation:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printAdjList();
    g.printAdjMatrix();

    return 0;
}
