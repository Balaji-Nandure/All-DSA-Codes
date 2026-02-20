#include <iostream>
#include <vector>
using namespace std;

// Function to take graph input using adjacency matrix
// n: number of vertices
// m: number of edges
// directed: true for directed graph, false for undirected graph
vector<vector<int>> inputGraphAdjMatrix(int n, int m, bool directed = false) {
    // Initialize adjacency matrix with 0s
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // Add edge from u to v
        adjMatrix[u][v] = 1;
        
        // If undirected, add edge from v to u as well
        if (!directed) {
            adjMatrix[v][u] = 1;
        }
    }
    
    return adjMatrix;
}

// Function to take graph input using adjacency list
// n: number of vertices
// m: number of edges
// directed: true for directed graph, false for undirected graph
vector<vector<int>> inputGraphAdjList(int n, int m, bool directed = false) {
    // Initialize adjacency list
    vector<vector<int>> adjList(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // Add edge from u to v
        adjList[u].push_back(v);
        
        // If undirected, add edge from v to u as well
        if (!directed) {
            adjList[v].push_back(u);
        }
    }
    
    return adjList;
}

// Function to take weighted graph input using adjacency matrix
// n: number of vertices
// m: number of edges
// directed: true for directed graph, false for undirected graph
vector<vector<int>> inputWeightedGraphAdjMatrix(int n, int m, bool directed = false) {
    // Initialize adjacency matrix with 0s (0 means no edge)
    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // Add edge from u to v with weight w
        adjMatrix[u][v] = w;
        
        // If undirected, add edge from v to u as well
        if (!directed) {
            adjMatrix[v][u] = w;
        }
    }
    
    return adjMatrix;
}

// Function to take weighted graph input using adjacency list
// n: number of vertices
// m: number of edges
// directed: true for directed graph, false for undirected graph
// Returns adjacency list where each element is a pair {node, weight}
vector<vector<pair<int, int>>> inputWeightedGraphAdjList(int n, int m, bool directed = false) {
    // Initialize adjacency list
    vector<vector<pair<int, int>>> adjList(n);
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // Add edge from u to v with weight w
        adjList[u].push_back({v, w});
        
        // If undirected, add edge from v to u as well
        if (!directed) {
            adjList[v].push_back({u, w});
        }
    }
    
    return adjList;
}

int main() {
    int n, m;
    cin >> n;
    cin >> m;
    
    // For undirected graph using adjacency matrix
    vector<vector<int>> adjMatrix = inputGraphAdjMatrix(n, m, false);
    
    // For undirected graph using adjacency list
    vector<vector<int>> adjList = inputGraphAdjList(n, m, false);
    
    // For weighted undirected graph using adjacency matrix
    vector<vector<int>> weightedAdjMatrix = inputWeightedGraphAdjMatrix(n, m, false);
    
    // For weighted undirected graph using adjacency list
    vector<vector<pair<int, int>>> weightedAdjList = inputWeightedGraphAdjList(n, m, false);
    
    return 0;
}