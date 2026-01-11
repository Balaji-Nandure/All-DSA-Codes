/*
Problem:
Breadth First Search (BFS) for a Graph

Given an undirected graph represented using an adjacency list,
perform Breadth First Search (BFS) traversal starting from a given
source vertex.

Rules:
- Visit all vertices reachable from the source.
- Traverse level by level.
- Use a queue to maintain traversal order.
- Mark vertices as visited to avoid revisiting.

Example:
Input:
V = 5
Adjacency List:
0 -> 1 2
1 -> 0 3
2 -> 0 4
3 -> 1
4 -> 2

Start = 0

Output:
0 1 2 3 4

Approach (Optimized – Queue / BFS):
- Maintain a visited array of size V.
- Push the starting vertex into a queue and mark it visited.
- While queue is not empty:
  - Pop a vertex, add it to result.
  - For each unvisited neighbour, mark visited and push into queue.

GeeksforGeeks:
https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(V + E)

Space Complexity:
O(V)
*/

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
    