/**
 * Problem: Longest Path in a Directed Acyclic Graph (DAG)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Finding the longest simple path in a general graph is NP-hard (reduces to the Hamiltonian Path problem).
 * - However, in a Directed Acyclic Graph (DAG), the absence of cycles allows linear topological ordering.
 * - This enables dynamic programming to find the single-source LONGEST path in O(V + E) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Topological Ordering + Dynamic Programming:
 *   1. Compute topological sort of the DAG (using DFS or Kahn's algorithm).
 *   2. Initialize `dist[v] = -INF` for all `v`, with `dist[src] = 0`.
 *   3. Iterate through vertices in topological order:
 *      - If `dist[u] != -INF` (reachable from source):
 *        - For each outgoing directed edge `(u -> v)` with weight `w`:
 *          `dist[v] = max(dist[v], dist[u] + w)`
 *   4. Because nodes are processed in topological order, by the time we relax outgoing edges from `u`,
 *      `dist[u]` is already mathematically guaranteed to be finalized and maximal.
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Topological sort takes O(V + E) and edge relaxation takes O(V + E).
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for adjacency list and distance array.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

struct Edge {
    int to;
    int weight;
};

void topoDFS(int u, const std::vector<std::vector<Edge>>& adj, std::vector<bool>& visited, std::stack<int>& st) {
    visited[u] = true;
    for (const auto& edge : adj[u]) {
        if (!visited[edge.to]) {
            topoDFS(edge.to, adj, visited, st);
        }
    }
    st.push(u);
}

std::vector<int> longestPathInDAG(int V, const std::vector<std::vector<Edge>>& adj, int src) {
    std::stack<int> st;
    std::vector<bool> visited(V, false);

    // Step 1: Topological Sort
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topoDFS(i, adj, visited, st);
        }
    }

    // Step 2: Initialize distances to negative infinity
    const int N_INF = -1e9;
    std::vector<int> dist(V, N_INF);
    dist[src] = 0;

    // Step 3: Process nodes in topological order
    while (!st.empty()) {
        int u = st.top();
        st.pop();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // In topological order, all predecessors of u have finished; hence dist[u] is optimal and can safely maximize dist[v].
        if (dist[u] != N_INF) {
            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight > dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    return dist;
}

int main() {
    int V = 6;
    std::vector<std::vector<Edge>> adj(V);

    adj[0].push_back({1, 5});
    adj[0].push_back({2, 3});
    adj[1].push_back({3, 6});
    adj[1].push_back({2, 2});
    adj[2].push_back({4, 4});
    adj[2].push_back({5, 2});
    adj[2].push_back({3, 7});
    adj[3].push_back({5, 1});
    adj[3].push_back({4, -1});
    adj[4].push_back({5, -2});

    int src = 1;
    std::vector<int> distances = longestPathInDAG(V, adj, src);

    std::cout << "Longest distances in DAG from source " << src << ":\n";
    for (int i = 0; i < V; i++) {
        if (distances[i] <= -1e8) {
            std::cout << "Node " << i << " -> INF (Unreachable)\n";
        } else {
            std::cout << "Node " << i << " -> " << distances[i] << "\n";
        }
    }

    return 0;
}
