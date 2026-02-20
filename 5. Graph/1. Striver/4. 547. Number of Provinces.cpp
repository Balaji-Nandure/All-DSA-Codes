#include <bits/stdc++.h>
using namespace std;

// LeetCode 547: Number of Provinces
// https://leetcode.com/problems/number-of-provinces/

// Problem: Given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city 
// and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
// A province is a group of directly or indirectly connected cities.
// Return the total number of provinces.

// Solution 1: DFS Approach
// Approach: Treat the problem as finding connected components in a graph.
// - Iterate through each city
// - If a city hasn't been visited, it's the start of a new province
// - Use DFS to mark all cities in the same province as visited
// - Count the number of times we start a new DFS (number of provinces)
// Time Complexity: O(n^2) where n is the number of cities
// Space Complexity: O(n) for the visited array and recursion stack
class Solution {
private:
    // DFS helper function to mark all cities in the current province as visited
    void dfs(int node, vector<vector<int>>& isConnected, vector<bool>& visited) {
        // Mark current city as visited
        visited[node] = true;
        
        // Visit all connected cities
        for (int i = 0; i < isConnected.size(); i++) {
            // If there's a connection and the city hasn't been visited
            if (isConnected[node][i] == 1 && !visited[i]) {
                dfs(i, isConnected, visited);
            }
        }
    }
    
public:
    // Main function to count number of provinces
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;
        
        // Iterate through all cities
        for (int i = 0; i < n; i++) {
            // If city hasn't been visited, it's a new province
            if (!visited[i]) {
                provinces++;
                // Mark all cities in this province as visited using DFS
                dfs(i, isConnected, visited);
            }
        }
        
        return provinces;
    }
};

// Solution 2: BFS Approach
// Approach: Similar to DFS but uses a queue for iterative traversal.
// - Iterate through each city
// - If a city hasn't been visited, start BFS from that city
// - Use a queue to explore all connected cities level by level
// - Mark all cities in the same province as visited
// - Count the number of times we start a new BFS (number of provinces)
// Time Complexity: O(n^2) where n is the number of cities
// Space Complexity: O(n) for the visited array and queue
class SolutionBFS {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                provinces++;
                queue<int> q;
                q.push(i);
                visited[i] = true;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    for (int j = 0; j < n; j++) {
                        if (isConnected[node][j] == 1 && !visited[j]) {
                            visited[j] = true;
                            q.push(j);
                        }
                    }
                }
            }
        }
        
        return provinces;
    }
};
