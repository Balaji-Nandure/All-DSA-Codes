#include <bits/stdc++.h>
using namespace std;

// GFG = https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1

class Solution {
private:
    // Helper function to perform DFS traversal recursively
    // node: current node being visited
    // adj: adjacency list representation of the graph
    // visited: array to track visited nodes
    // res: result vector to store DFS traversal order
    void dfsHelper(int node, vector<vector<int>>& adj, vector<int>& visited, vector<int>& res) {
        // Mark the current node as visited
        visited[node] = 1;
        // Add the current node to the result
        res.push_back(node);
        
        // Explore all neighbors of the current node
        for (int nbr : adj[node]) {
            // If neighbor is not visited, recursively visit it
            if (!visited[nbr]) {
                dfsHelper(nbr, adj, visited, res);
            }
        }
    }
    
public:
    // Main function to perform DFS traversal of the graph
    // adj: adjacency list where adj[i] contains all neighbors of node i
    // Returns: vector containing nodes in DFS traversal order starting from node 0
    vector<int> dfsOfGraph(vector<vector<int>>& adj) {
        // Get the number of vertices in the graph
        int V = adj.size();
        // Result vector to store the DFS traversal
        vector<int> res;
        // Visited array to keep track of visited nodes (0 = not visited, 1 = visited)
        vector<int> visited(V, 0);
        
        // Start DFS from node 0
        dfsHelper(0, adj, visited, res);
        
        // Return the DFS traversal order
        return res;
    }
};
