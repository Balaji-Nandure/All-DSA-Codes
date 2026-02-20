#include <bits/stdc++.h>
using namespace std;

// BFS traversal of a graph
// adj: adjacency list representation of the graph
// start: starting vertex for BFS
// Returns: vector containing BFS traversal order
vector<int> bfs(int n, vector<vector<int>>& adj, int start = 0) {
    vector<int> result;
    vector<bool> visited(n, false);
    queue<int> q;
    
    // Start BFS from the starting vertex
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        
        // Visit all adjacent vertices
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    
    return result;
}

// BFS traversal for disconnected graph (handles multiple components)
// NOTE: This method works for BOTH connected and disconnected graphs!
// - For connected graphs: It will traverse all nodes starting from vertex 0
// - For disconnected graphs: It will traverse all components one by one
vector<int> bfsDisconnected(int n, vector<vector<int>>& adj) {
    vector<int> result;
    vector<bool> visited(n, false);
    
    // Traverse all components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = true;
            
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                result.push_back(node);
                
                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
    
    return result;
}


//  GFG = https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1

class Solution {
public:
    vector<int> bfs(vector<vector<int>> &adj) {

        int V = adj.size();
        vector<int> res;
        vector<int> visited(V, 0);
        queue<int> q;

        q.push(0);
        visited[0] = 1;

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            res.push_back(node);

            for (int nbr : adj[node]) {
                if (!visited[nbr]) {
                    visited[nbr] = 1;
                    q.push(nbr);
                }
            }
        }

        return res;
    }
};
    