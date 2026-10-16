/**
 * Problem: Paths to Travel Each Node Using Each Edge Exactly Once (Seven Bridges of Königsberg / Eulerian Path & Circuit)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Hamiltonian paths visit every VERTEX once (NP-hard).
 * - Eulerian paths visit every EDGE once (solvable in linear time).
 * - The Königsberg bridge problem proved that a graph has an Eulerian path iff it is connected and has either 0 or 2 vertices with odd degree.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Euler's Theorem & Hierholzer's Algorithm:
 *   1. Check degrees:
 *      - Count vertices with odd degrees.
 *      - If odd count == 0: Eulerian Circuit exists (can start and end at any vertex).
 *      - If odd count == 2: Eulerian Path exists (must start at one odd degree vertex and end at the other).
 *      - If odd count != 0 and odd count != 2: Neither exists.
 *   2. Hierholzer's Algorithm:
 *      - Use a stack to trace out cycles.
 *      - Follow edges from the current vertex, removing each traversed edge from the graph.
 *      - When a vertex has no more unused incident edges, pop it from the stack and add it to the final Eulerian path.
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Each vertex and edge is traversed a constant number of times.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for adjacency representation and path tracking stack.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>

class EulerianTrail {
public:
    static void findEulerianPath(int V, std::vector<std::vector<int>>& adj) {
        int oddCount = 0;
        int startVertex = 0;

        for (int i = 0; i < V; i++) {
            if ((int)adj[i].size() % 2 != 0) {
                oddCount++;
                startVertex = i; // If 2 odd vertices exist, we must start at one of them
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // An Eulerian path traversing every edge once exists iff the count of odd-degree vertices is exactly 0 or 2.
        if (oddCount != 0 && oddCount != 2) {
            std::cout << "No Eulerian Path or Circuit exists (Odd degree count = " << oddCount << ")\n";
            return;
        }

        std::stack<int> st;
        std::vector<int> path;
        st.push(startVertex);

        // Copy of adjacency for edge removal
        std::vector<std::vector<int>> g = adj;

        while (!st.empty()) {
            int u = st.top();

            if (!g[u].empty()) {
                int v = g[u].back();
                g[u].pop_back();

                // Remove reciprocal undirected edge
                auto it = std::find(g[v].begin(), g[v].end(), u);
                if (it != g[v].end()) {
                    g[v].erase(it);
                }

                st.push(v);
            } else {
                path.push_back(u);
                st.pop();
            }
        }

        std::reverse(path.begin(), path.end());
        std::cout << (oddCount == 0 ? "Eulerian Circuit: " : "Eulerian Path: ");
        for (int node : path) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    int V = 5;
    std::vector<std::vector<int>> adj(V);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    // Eulerian Path graph (vertices 0 and 3 have odd degrees 3 and 1)
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 0);
    addEdge(0, 4);
    addEdge(4, 3);

    EulerianTrail::findEulerianPath(V, adj);

    return 0;
}
