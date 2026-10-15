// Problem: 787. Cheapest Flights Within K Stops
// Link (LeetCode): https://leetcode.com/problems/cheapest-flights-within-k-stops/
// Link (GFG): https://www.geeksforgeeks.org/problems/cheapest-flights-within-k-stops/1
// Difficulty: Medium
// Topic: Graph, BFS, Dijkstra's Algorithm, Shortest Path, Queue

/*
Problem Statement:
There are n cities connected by some number of flights. You are given an array flights where 
flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k, return the cheapest price from src to dst with 
at most k stops. If there is no such route, return -1.

Notice:
- A "stop" is an intermediate city between src and dst.
- At most k stops means the total path can have at most (k + 1) edges/flights.

Example 1:
Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
- Path 0 -> 1 -> 3 has cost 100 + 600 = 700 with 1 stop.
- Path 0 -> 1 -> 2 -> 3 has cost 100 + 100 + 200 = 400, but has 2 stops (exceeds k = 1).
- Cheapest within 1 stop is 700.

Example 2:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation: Path 0 -> 1 -> 2 has cost 200 with 1 stop.

Example 3:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation: Path 0 -> 2 is direct (0 stops) with cost 500.

Constraints:
- 1 <= n <= 100
- 0 <= flights.length <= (n * (n - 1) / 2)
- flights[i].length == 3
- 0 <= fromi, toi < n
- fromi != toi
- 1 <= pricei <= 10^4
- There will not be any multiple flights between two cities.
- 0 <= src, dst, k < n
- src != dst
*/

// Approach: Modified Dijkstra (Prioritizing by STOPS using a Simple Queue)
// 1. Why Standard Dijkstra (by Cost) Fails:
//    - If we prioritize by cost, a cheaper path that uses MORE stops might reach a node X first, 
//      updating dist[X] with a low cost but exhausting all allowed stops.
//    - A slightly more expensive path that reaches X with FEWER stops would be discarded, 
//      even though it might be the ONLY path able to reach the destination within k stops!
// 2. The Solution - Prioritize by STOPS:
//    - Instead of prioritizing by cost, we process level-by-level based on the number of stops!
//    - Since stops strictly increment by +1 (0, 1, 2, ..., k), we do NOT need a priority_queue.
//    - A simple FIFO `std::queue` naturally maintains elements ordered by stops!
// 3. Algorithm Steps:
//    Step 1: Build the directed adjacency list: u -> {v, price}.
//    Step 2: Initialize distance array `dist` with infinity (1e9), and `dist[src] = 0`.
//    Step 3: Queue stores `{stops, {node, cost}}`. Push `{0, {src, 0}}`.
//    Step 4: While queue is not empty:
//            - Pop `{stops, {node, cost}}`.
//            - If `stops > k`, we cannot take any more intermediate flights -> continue.
//            - For every neighbor `{adjNode, price}` of `node`:
//              - If `cost + price < dist[adjNode] && stops <= k`:
//                * `dist[adjNode] = cost + price;`
//                * `q.push({stops + 1, {adjNode, cost + price}});`
//    Step 5: Return `dist[dst] == 1e9 ? -1 : dist[dst]`.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Step 1: Build adjacency list: u -> {v, price}
        vector<vector<pair<int, int>>> adj(n);
        for (auto& flight : flights) {
            int u = flight[0];
            int v = flight[1];
            int price = flight[2];
            adj[u].push_back({v, price});
        }

        // Step 2: Distance array initialized to infinity
        const int INF = 1e9;
        vector<int> dist(n, INF);
        dist[src] = 0;

        // -------------------------------------------------------------------------
        // DATA STRUCTURE CHOICE EXPLANATION:
        // 1. Why `queue` instead of `priority_queue`?
        //    - In standard Dijkstra, we sort by `cost`. But here, sorting by cost is WRONG:
        //      a cheaper path that takes 3 stops might reach node X first, blocking a slightly
        //      more expensive path that took only 1 stop. If k=1, the cheaper path fails later!
        //    - Instead, we must prioritize by STOPS.
        //    - Since stops strictly increment by +1 (0, 1, 2, ..., k), elements naturally arrive
        //      in non-decreasing order of stops. A simple FIFO `queue` maintains this order
        //      automatically without needing an expensive O(log V) min-heap!
        //
        // 2. Why `pair<int, pair<int, int>>` storing `{stops, {node, cost}}`?
        //    - `stops` (outer/first int): Tracks the current depth / flight hops.
        //    - `node` (inner first int): The current city we have arrived at.
        //    - `cost` (inner second int): The total accumulated fare to reach this city.
        // -------------------------------------------------------------------------
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {src, 0}});

        // Step 3: BFS level traversal
        while (!q.empty()) {
            auto [stops, p] = q.front();
            auto [node, cost] = p;
            q.pop();

            // If we have already used k stops, we cannot take any more intermediate flights
            if (stops > k) continue;

            // Traverse all outgoing flights from current city
            for (auto& edge : adj[node]) {
                int adjNode = edge.first;
                int price = edge.second;

                // If a cheaper path within allowed stops is found
                if (cost + price < dist[adjNode] && stops <= k) {
                    dist[adjNode] = cost + price;
                    q.push({stops + 1, {adjNode, cost + price}});
                }
            }
        }

        // If destination is reachable, return min price; else -1
        return dist[dst] == INF ? -1 : dist[dst];
    }
};

/*
Time Complexity: O(K * E)
- E = number of flights (edges).
- In the worst case, each flight can be traversed at most K times across the K stop levels.
- Since K <= N <= 100 and E <= 5000, max operations ≈ 100 * 5000 = 5 * 10^5 (executes in ~5ms).
- Total Time Complexity: O(K * E).

Space Complexity: O(V + E)
- Adjacency list: O(V + E).
- Distance array: O(V).
- BFS queue: stores at most O(V * K) entries in worst case.
- Total Auxiliary Space: O(V + E).

Key Insights:
1. Why Queue instead of Priority Queue?
   - Sorting by cost is incorrect because it greedily consumes stops.
   - Sorting by stops is trivial because stops increase by +1 at each step.
   - A regular queue naturally processes in non-decreasing order of stops, eliminating 
     the O(log V) heap factor.
2. Stops vs Flights:
   - "At most k stops" means at most (k + 1) flights/edges.
   - Pushing `{stops + 1, ...}` and checking `if (stops > k) continue;` guarantees that 
     destinations reached with exactly (k + 1) edges are considered, but no further hops are taken.
*/
