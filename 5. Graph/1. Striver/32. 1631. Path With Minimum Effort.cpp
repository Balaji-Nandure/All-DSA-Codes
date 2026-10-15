// Problem: 1631. Path With Minimum Effort
// Link (LeetCode): https://leetcode.com/problems/path-with-minimum-effort/
// Link (GFG): https://www.geeksforgeeks.org/problems/path-with-minimum-effort/1
// Difficulty: Medium
// Topic: Graph, Dijkstra's Algorithm, Priority Queue, Min-Heap, Matrix

/*
Problem Statement:
You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, 
where heights[row][col] represents the height of cell (row, col). 

You are situated at the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, 
(rows - 1, columns - 1). You can move up, down, left, or right.

You wish to find a route that requires the minimum effort.
A route's effort is the MAXIMUM absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Example 1:
Input: heights = [[1,2,2],
                  [3,8,2],
                  [5,3,5]]
Output: 2
Explanation: The route [1,3,5,3,5] has a maximum absolute difference of 2 between consecutive cells.
This is better than route [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:
Input: heights = [[1,2,3],
                  [3,8,4],
                  [5,3,5]]
Output: 1
Explanation: The route [1,2,3,4,5] has a maximum absolute difference of 1 between consecutive cells, 
which is better than route [1,3,5,3,5].

Example 3:
Input: heights = [[1,2,1,1,1],
                  [1,2,1,2,1],
                  [1,2,1,2,1],
                  [1,2,1,2,1],
                  [1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort since all heights are 1 along the path.

Constraints:
- rows == heights.length
- columns == heights[i].length
- 1 <= rows, columns <= 100
- 1 <= heights[i][j] <= 10^6
*/

// Approach: Modified Dijkstra's Algorithm
// 1. Why Dijkstra?
//    - Standard Dijkstra minimizes the SUM of edge weights along a path:
//      dist[v] = min(dist[v], dist[u] + weight)
//    - Here, the problem asks to minimize the MAXIMUM edge difference along a path:
//      newEffort = max(currentEffort, abs(heights[r][c] - heights[nr][nc]))
//    - This satisfies the greedy property of Dijkstra: moving to a neighbor can never reduce 
//      the effort accumulated so far (non-decreasing monotonicity).
//    - A min-heap priority queue ensures we always expand the path with the smallest maximum effort first.
// 2. Algorithm Steps:
//    Step 1: Initialize 2D distance/effort array `dist[n][m]` with infinity (1e9), and `dist[0][0] = 0`.
//    Step 2: Min-heap storing `{effort, {row, col}}`:
//            `priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<...>> pq;`
//            Push `{0, {0, 0}}` into pq.
//    Step 3: While pq is not empty:
//            - Extract the top element: `auto [diff, cell] = pq.top(); pq.pop();`
//            - Early Exit: If `r == n - 1 && c == m - 1`, return `diff`!
//              (Because min-heap always pops the smallest effort, the first time target is popped, 
//               its effort is guaranteed to be minimal).
//            - If `diff > dist[r][c]`, continue (stale entry).
//            - Explore 4 adjacent neighbors (up, down, left, right):
//              * Calculate `newEffort = max(diff, abs(heights[r][c] - heights[nr][nc]))`
//              * If `newEffort < dist[nr][nc]`:
//                `dist[nr][nc] = newEffort;`
//                `pq.push({newEffort, {nr, nc}});`
//    Step 4: Return `0` (fallback for 1x1 matrix).

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        // 2D distance array storing minimum effort to reach each cell
        const int INF = 1e9;
        vector<vector<int>> dist(n, vector<int>(m, INF));
        dist[0][0] = 0;

        // -------------------------------------------------------------------------
        // DATA STRUCTURE CHOICE EXPLANATION:
        // 1. Why `priority_queue` (min-heap) instead of `queue`?
        //    - Unlike the Binary Maze where all steps cost 1, here the effort difference
        //      between adjacent cells varies arbitrarily (e.g. 0, 5, 2, 8...).
        //    - A simple FIFO queue CANNOT guarantee exploring the minimum effort path first.
        //    - A min-heap (`greater<...>`) ensures we greedily expand the path with the smallest
        //      maximum effort first, preserving the optimal substructure of Dijkstra.
        //
        // 2. Why `pair<int, pair<int, int>>` storing `{effort, {row, col}}`?
        //    - `effort` is placed FIRST in the outer pair so C++'s default `pair` comparison
        //      automatically sorts by minimum effort without needing a custom comparator!
        //    - `{row, col}` represents the grid coordinates of the node.
        // -------------------------------------------------------------------------
        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>,
                       greater<pair<int, pair<int, int>>>> pq;

        pq.push({0, {0, 0}});

        // 4 directions: Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!pq.empty()) {
            auto [diff, cell] = pq.top();
            auto [r, c] = cell;
            pq.pop();

            // Destination reached: guaranteed minimum effort due to min-heap ordering
            if (r == n - 1 && c == m - 1) {
                return diff;
            }

            // Stale entry check
            if (diff > dist[r][c]) continue;

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    // Effort to cross to the neighbor is the max of path effort and edge difference
                    int newEffort = max(diff, abs(heights[r][c] - heights[nr][nc]));

                    // If a lower effort path to (nr, nc) is discovered
                    if (newEffort < dist[nr][nc]) {
                        dist[nr][nc] = newEffort;
                        pq.push({newEffort, {nr, nc}});
                    }
                }
            }
        }

        return 0; // Fallback for 1x1 grid
    }
};

/*
Time Complexity: O(E * log V)
- V = N * M (total cells in the matrix).
- E = 4 * N * M (each cell connects to at most 4 neighbors).
- In the worst case, every edge relaxation can push into the min-heap: at most 4 * N * M pushes.
- Size of heap is at most N * M.
- Each push/pop takes O(log(N * M)).
- Total Time Complexity: O((N * M) * log(N * M)).
- For N, M <= 100, N * M <= 10,000, and 10,000 * log2(10,000) ≈ 1.4 * 10^5 operations (super fast, ~15ms).

Space Complexity: O(N * M)
- 2D distance array `dist`: O(N * M).
- Priority queue `pq`: at most O(N * M) entries.
- Overall Auxiliary Space: O(N * M).

Key Insights:
1. Difference from Standard Dijkstra:
   - Standard: `dist[v] = min(dist[v], dist[u] + wt)` (minimizes sum of weights).
   - Effort: `dist[v] = min(dist[v], max(dist[u], abs(diff)))` (minimizes maximum single edge).
2. Why Min-Heap Guarantees Optimality:
   - Since edge effort is `max(current_effort, abs_diff)` and `abs_diff >= 0`, path effort is monotonic.
   - Popping `(n-1, m-1)` from the min-heap guarantees that no remaining or future path in the heap
     can ever achieve a smaller effort.
3. Alternative Solution (Binary Search + BFS/DFS):
   - We could also binary search the answer in range [0, 10^6] and check reachability with BFS/DFS in O(N * M).
   - Time: O(N * M * log(max_diff)) ≈ O(N * M * 20).
   - Dijkstra is cleaner and directly stops as soon as the target is popped.
*/
