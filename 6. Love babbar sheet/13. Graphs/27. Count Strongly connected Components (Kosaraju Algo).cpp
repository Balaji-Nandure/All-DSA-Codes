/**
 * Problem: Strongly Connected Components (Kosaraju's Algorithm)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In undirected graphs, connected components are trivial via standard BFS/DFS.
 * - In directed graphs, connectivity is asymmetric: u might reach v, but v might not reach u.
 * - A Strongly Connected Component (SCC) is a maximal subgraph where every vertex can reach every other vertex.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Kosaraju's Two-Pass DFS Algorithm:
 *   1. Step 1: Run DFS on the original graph. Push vertices onto a stack as their recursive calls finish (post-order finish times).
 *      Vertices in "source" SCCs will finish after vertices in "sink" SCCs, placing source SCCs at the top of the stack.
 *   2. Step 2: Compute the Transpose Graph (reverse every directed edge u -> v to v -> u).
 *      Reversing edges prevents transitions between distinct SCCs while preserving internal SCC connectivity.
 *   3. Step 3: Pop vertices from the stack. If a vertex is not yet visited in the transposed graph, launch DFS from it.
 *      Each DFS traversal discovers exactly ONE complete Strongly Connected Component!
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Two linear DFS traversals and graph transposition.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for the transposed adjacency list and finish-time stack.
 */

#include <iostream>
#include <vector>
#include <stack>

class Kosaraju {
    void dfsOrder(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::stack<int>& st) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsOrder(v, adj, visited, st);
            }
        }
        st.push(u); // Finish time ordering
    }

    void dfsTranspose(int u, const std::vector<std::vector<int>>& transposeAdj, std::vector<bool>& visited, std::vector<int>& component) {
        visited[u] = true;
        component.push_back(u);
        for (int v : transposeAdj[u]) {
            if (!visited[v]) {
                dfsTranspose(v, transposeAdj, visited, component);
            }
        }
    }

public:
    int countSCCs(int V, const std::vector<std::vector<int>>& adj, std::vector<std::vector<int>>& allSCCs) {
        std::stack<int> st;
        std::vector<bool> visited(V, false);

        // Step 1: Order vertices by finishing time
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfsOrder(i, adj, visited, st);
            }
        }

        // Step 2: Transpose the graph (reverse all edges)
        std::vector<std::vector<int>> transposeAdj(V);
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                transposeAdj[v].push_back(u);
            }
        }

        // Step 3: DFS on transposed graph in decreasing order of finish time
        std::fill(visited.begin(), visited.end(), false);
        int sccCount = 0;

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Processing nodes in reverse post-order on the transposed graph confines DFS strictly within its own SCC.
            if (!visited[u]) {
                sccCount++;
                std::vector<int> currentComponent;
                dfsTranspose(u, transposeAdj, visited, currentComponent);
                allSCCs.push_back(currentComponent);
            }
        }

        return sccCount;
    }
};

int main() {
    int V = 5;
    std::vector<std::vector<int>> adj(V);

    adj[1].push_back(0);
    adj[0].push_back(2);
    adj[2].push_back(1);
    adj[0].push_back(3);
    adj[3].push_back(4);

    Kosaraju solver;
    std::vector<std::vector<int>> sccs;
    int count = solver.countSCCs(V, adj, sccs);

    std::cout << "Number of Strongly Connected Components: " << count << "\n"; // Expected: 3
    std::cout << "SCC Groups:\n";
    for (int i = 0; i < (int)sccs.size(); i++) {
        std::cout << "SCC " << (i + 1) << ": ";
        for (int node : sccs[i]) std::cout << node << " ";
        std::cout << "\n";
    }

    return 0;
}
