#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Find if there is a path of more than k length from a source
 * 
 * Given an undirected, weighted graph with V vertices, a source vertex src, 
 * and an integer K. Determine whether there exists a SIMPLE path (a path with no repeated vertices)
 * starting at src whose total edge weight sum is GREATER THAN OR EQUAL TO K.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Finding the SHORTEST path in a weighted graph can be solved in polynomial O(E log V) via Dijkstra.
 * - However, finding the LONGEST SIMPLE path (or checking if a simple path of weight >= K exists) 
 *   is NP-Complete!
 * - Greedy and Dijkstra fail because Dijkstra assumes optimal substructure (subpaths of shortest paths are shortest),
 *   which is FALSE for longest simple paths due to vertex consumption cycles.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Depth-First Search Backtracking:
 *   1. Track visited vertices in a boolean array `visited[V]`.
 *   2. Base case:
 *      If remaining required length k <= 0, we have successfully traversed a simple path 
 *      whose cumulative weight is >= K. Return true immediately!
 *   3. Recursive exploration:
 *      - Mark current vertex: visited[u] = true.
 *      - Iterate through all adjacent edges (v, weight):
 *        If neighbor v is NOT visited:
 *          Recurse: dfs(v, k - weight, visited).
 *          If recursive call returns true: propagate true immediately (path verified).
 *      - *** CRUCIAL BACKTRACKING STEP ***:
 *        visited[u] = false.
 *        We MUST unmark u so that alternative simple paths originating from or passing through 
 *        other branches can consider vertex u.
 *   4. If all neighbor paths fail to reach weight K, return false.
 */

class Solution {
    bool dfs(int u, int k, const vector<vector<pair<int, int>>>& adj, vector<bool>& visited) {
        // Base case: Accumulated weight >= K achieved!
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        if (k <= 0) {
            return true;
        }

        visited[u] = true;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Simple path constraint: Vertex v cannot be already visited
            if (!visited[v]) {
                if (dfs(v, k - weight, adj, visited)) {
                    return true;
                }
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Backtrack: Unmark vertex u so it can be part of other simple path explorations
        visited[u] = false;

        return false;
    }

public:
    bool pathMoreThanK(int V, int E, int k, int* a) {
        // Build adjacency list: pair<neighbor, weight>
        vector<vector<pair<int, int>>> adj(V);
        for (int i = 0; i < 3 * E; i += 3) {
            int u = a[i];
            int v = a[i + 1];
            int w = a[i + 2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<bool> visited(V, false);
        // Start simple path search from vertex 0
        return dfs(0, k, adj, visited);
    }
};

int main() {
    Solution sol;
    int V = 9, E = 14, k = 60;
    // Edge tuples: (u, v, w)
    int edges[] = {
        0, 1, 4,
        0, 7, 8,
        1, 2, 8,
        1, 7, 11,
        2, 3, 7,
        2, 8, 2,
        2, 5, 4,
        3, 4, 9,
        3, 5, 14,
        4, 5, 10,
        5, 6, 2,
        6, 7, 1,
        6, 8, 6,
        7, 8, 7
    };

    bool exists = sol.pathMoreThanK(V, E, k, edges);
    cout << "Path of weight >= " << k << " from source 0: " << (exists ? "EXISTS" : "DOES NOT EXIST") << "\n";
    // Expected: EXISTS (e.g. 0-7-1-2-8-6-5-4-3 has length 8+11+8+2+6+2+10+9 = 56, etc.)

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(V!) in the worst-case complete graph since Longest Simple Path is NP-Complete.
 * - Space Complexity: O(V) for the visited array and recursion stack.
 */
