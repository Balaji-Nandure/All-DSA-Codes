// Problem: 1976. Number of Ways to Arrive at Destination
// Link (LeetCode): https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/
// Link (GFG): https://www.geeksforgeeks.org/problems/number-of-ways-to-arrive-at-destination/1
// Difficulty: Medium
// Topic: Graph, Shortest Path, Dijkstra's Algorithm, Priority Queue, Dynamic Programming

/*
Problem Statement:
You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads 
between some intersections. The inputs are generated such that you can reach any intersection from 
any other intersection and that there is at most one road between any two intersections.

You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that 
there is a road between intersections ui and vi that takes timei minutes to travel. You want to know 
in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.

Return the number of ways you can travel from intersection 0 to intersection n - 1 in the shortest 
amount of time. Since the answer may be large, return it modulo 10^9 + 7.

Example 1:
Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
Output: 4
Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
The four ways to get there in 7 minutes are:
- 0 -> 6 (time 7)
- 0 -> 4 -> 6 (time 5 + 2 = 7)
- 0 -> 1 -> 2 -> 5 -> 6 (time 2 + 3 + 1 + 1 = 7)
- 0 -> 1 -> 3 -> 5 -> 6 (time 2 + 3 + 1 + 1 = 7)

Example 2:
Input: n = 2, roads = [[1,0,10]]
Output: 1
Explanation: There is only one way to go from 0 to 1, taking 10 minutes.

Constraints:
- 1 <= n <= 200
- n - 1 <= roads.length <= n * (n - 1) / 2
- roads[i].length == 3
- 0 <= ui, vi <= n - 1
- 1 <= timei <= 10^9
- ui != vi
- There is at most one road between any two intersections.
- You can reach any intersection from any other intersection.
*/

// Approach: Modified Dijkstra's Algorithm + DP (Path Counting)
// 1. Dual Arrays:
//    - `dist[i]`: Stores the minimum time required to travel from node 0 to node i.
//                 Because edge weights are up to 10^9 and n <= 200, cumulative distances can reach
//                 200 * 10^9 = 2 * 10^11, which overflows standard 32-bit signed integers.
//                 Hence, `dist` MUST be of type `long long`.
//    - `ways[i]`: Stores the total number of shortest paths from node 0 to node i modulo (10^9 + 7).
// 2. Base Setup:
//    - `dist[0] = 0`, `ways[0] = 1`, and all other `dist[i] = LLONG_MAX`, `ways[i] = 0`.
// 3. Relaxation Conditions in Dijkstra:
//    When examining an edge from `node` to `adjNode` with weight `time`:
//    - Case 1: `d + time < dist[adjNode]` (Strictly shorter path discovered):
//      * Update shortest distance: `dist[adjNode] = d + time`.
//      * Reset ways: Since all previous paths to `adjNode` were strictly longer, discard them.
//        Inherit ways from current node: `ways[adjNode] = ways[node]`.
//      * Push `{dist[adjNode], adjNode}` into the priority queue for further exploration.
//    - Case 2: `d + time == dist[adjNode]` (Alternative shortest path discovered):
//      * Accumulate ways: Add ways from current node to existing ways:
//        `ways[adjNode] = (ways[adjNode] + ways[node]) % MOD`.
//      * CRITICAL: Do NOT push `{dist[adjNode], adjNode}` into the priority queue again!
//        Pushing duplicate entries would cause exponential state explosion and TLE.
// 4. Returning Answer:
//    - Destination node is `n - 1`. Return `ways[n - 1]`.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const int MOD = 1e9 + 7;

        // Step 1: Build adjacency list for undirected graph: u -> {v, time}
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& road : roads) {
            int u = road[0];
            int v = road[1];
            int time = road[2];
            adj[u].push_back({v, time});
            adj[v].push_back({u, time});
        }

        // Step 2: Distance array (long long) and Ways array (long long / int)
        // LLONG_MAX used because cumulative distance can exceed 2 * 10^11
        vector<long long> dist(n, LLONG_MAX);
        vector<long long> ways(n, 0);

        dist[0] = 0;
        ways[0] = 1;

        // -------------------------------------------------------------------------
        // DATA STRUCTURE CHOICE EXPLANATION:
        // 1. Why `priority_queue` instead of `queue`?
        //    - The edge weights (road travel times) are non-uniform and vary up to 10^9.
        //    - A standard FIFO queue cannot guarantee that nodes are visited in increasing
        //      order of cumulative travel time.
        //    - Dijkstra's min-heap greedily processes the currently closest intersection first.
        //      This guarantees that when a node's distance is finalized, all shortest paths
        //      leading to it have already contributed their path counts.
        //
        // 2. Why `pair<long long, int>` storing `{dist, node}`?
        //    - `dist` (first): Distance metric used by `greater<pair<long long, int>>`
        //      to order elements such that `pq.top()` always yields the smallest travel time.
        //      Must be `long long` to prevent 32-bit overflow.
        //    - `node` (second): The intersection identifier (0 to n - 1).
        // -------------------------------------------------------------------------
        priority_queue<pair<long long, int>, 
                       vector<pair<long long, int>>, 
                       greater<pair<long long, int>>> pq;

        pq.push({0, 0});

        while (!pq.empty()) {
            auto [d, node] = pq.top();
            pq.pop();

            // Optimization: Skip stale heap entries if already found a strictly shorter path
            if (d > dist[node]) continue;

            for (const auto& [adjNode, travelTime] : adj[node]) {
                long long newDist = d + travelTime;

                // Case 1: Found a strictly shorter path to adjNode
                if (newDist < dist[adjNode]) {
                    dist[adjNode] = newDist;
                    ways[adjNode] = ways[node]; // Reset ways count to current node's ways
                    pq.push({newDist, adjNode});
                }
                // Case 2: Found an alternative path with the same shortest distance
                else if (newDist == dist[adjNode]) {
                    ways[adjNode] = (ways[adjNode] + ways[node]) % MOD;
                    // Note: Do NOT push to pq again! The node has already been scheduled
                    // with this optimal distance. Pushing again leads to duplicate traversals.
                }
            }
        }

        return ways[n - 1];
    }
};

/*
Time Complexity: O(M * log N)
- N = number of intersections (nodes <= 200), M = number of roads (edges <= N * (N - 1) / 2).
- Building the adjacency list: O(M).
- Each node is pushed to the priority queue at most once per strictly shorter path: at most O(N) pushes.
- Every edge is relaxed: O(M * log N) priority queue operations.
- Overall Time Complexity: O(M * log N), running in mere milliseconds for N <= 200.

Space Complexity: O(N + M)
- Adjacency list: O(2 * M) = O(M).
- `dist` array of size N: O(N).
- `ways` array of size N: O(N).
- Priority queue storing at most O(N) active elements: O(N).
- Overall Auxiliary Space: O(N + M).

Key Insights:
1. Dynamic Programming over Dijkstra's DAG:
   - The shortest paths from a single source form a Directed Acyclic Graph (DAG) of shortest path edges.
   - We count paths on this DAG dynamically during the Dijkstra relaxation step:
     * If distance improves: overwrite `ways[v] = ways[u]`.
     * If distance matches: accumulate `ways[v] = (ways[v] + ways[u]) % MOD`.
2. Crucial Anti-TLE Pruning:
   - When `newDist == dist[adjNode]`, we ONLY accumulate `ways[adjNode]`. We NEVER push `{newDist, adjNode}`
     back into the priority queue. Pushing duplicate nodes on equality causes exponential queue expansion!
3. 64-Bit Integer (long long) Requirement:
   - Edge times up to 10^9 can cause path distances to reach up to ~2 * 10^11, exceeding 32-bit INT_MAX (~2 * 10^9).
   - `dist` array and priority queue distances must use `long long`.
*/
