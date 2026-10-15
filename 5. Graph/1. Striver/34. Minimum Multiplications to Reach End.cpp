// Problem: Minimum Multiplications to Reach End
// Link: https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1
// Difficulty: Medium
// Topic: Graph, BFS, Shortest Path, Dijkstra, Queue, Modular Arithmetic

/*
Problem Statement:
Given start, end, and an array arr of n numbers. At each step, start is multiplied with any number 
in the array and then modded with 100000:
    new_value = (start * arr[i]) % 100000

Find the minimum number of multiplications to reach end from start. 
If it is impossible to reach end, return -1.

Example 1:
Input: arr = [2, 5, 7], start = 3, end = 30
Output: 2
Explanation:
- Step 1: 3 * 2 = 6 % 100000 = 6
- Step 2: 6 * 5 = 30 % 100000 = 30
Minimum multiplications = 2.

Example 2:
Input: arr = [3, 4, 65], start = 7, end = 66175
Output: 4
Explanation:
- 7 * 3 = 21
- 21 * 3 = 63
- 63 * 65 = 4095
- 4095 * 65 = 266175 % 100000 = 66175
Minimum multiplications = 4.

Example 3:
Input: arr = [2, 4], start = 3, end = 5
Output: -1
Explanation: It is impossible to reach 5 from 3.

Constraints:
- 1 <= n <= 10^4
- 1 <= arr[i] <= 10^4
- 1 <= start, end < 10^5
*/

// Approach: BFS (Shortest Path with Uniform Edge Weights)
// 1. Graph Formulation:
//    - The nodes are all possible values modulo 100000, i.e., range [0, 99999].
//    - Total number of vertices V = 100,000.
//    - From any node `u`, multiplying by `arr[i]` leads to directed neighbor `(u * arr[i]) % 100000`.
//    - Every multiplication takes exactly 1 step (uniform edge weight = 1).
// 2. Data Structure Choice:
//    - Why `queue` instead of `priority_queue`?
//      * Since every multiplication costs exactly 1 step, steps strictly increase level-by-level
//        (0 -> 1 -> 2 -> ...).
//      * A FIFO queue naturally processes in non-decreasing order of steps.
//      * A min-heap (priority_queue) is completely redundant and adds unnecessary O(log V) overhead.
//    - Queue stores: `{steps, node}` where:
//      * `steps`: Number of multiplications performed so far.
//      * `node`: The current numerical value in [0, 99999].
// 3. Algorithm Steps:
//    Step 1: If `start == end`, return 0 immediately.
//    Step 2: Maintain a `dist` array of size 100,000 initialized to infinity (1e9), with `dist[start] = 0`.
//    Step 3: Queue stores `{steps, node}`. Push `{0, start}`.
//    Step 4: While queue is not empty:
//            - Pop `{steps, node}`.
//            - For each multiplier `it` in `arr`:
//              * Compute `num = (node * it) % 100000`.
//              * If `steps + 1 < dist[num]`:
//                - `dist[num] = steps + 1;`
//                - Early Exit: If `num == end`, return `steps + 1`!
//                - Push `{steps + 1, num}` into queue.
//    Step 5: If queue empties without reaching `end`, return -1.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        // Base case: already at destination
        if (start == end) return 0;

        const int MOD = 100000;

        // Distance array storing minimum steps to reach each number in [0, 99999]
        const int INF = 1e9;
        vector<int> dist(MOD, INF);
        dist[start] = 0;

        // -------------------------------------------------------------------------
        // DATA STRUCTURE CHOICE EXPLANATION:
        // 1. Why `queue` instead of `priority_queue`?
        //    - Each multiplication costs exactly 1 step (uniform edge weight = 1).
        //    - BFS with a standard FIFO `queue` guarantees level-by-level exploration.
        //    - A min-heap (priority_queue) is unnecessary and would add O(log MOD) overhead.
        //
        // 2. Why `pair<int, int>` storing `{steps, node}`?
        //    - `steps` (first): Tracks the distance (number of multiplications).
        //    - `node` (second): Current value mod 100000.
        // -------------------------------------------------------------------------
        queue<pair<int, int>> q;
        q.push({0, start});

        while (!q.empty()) {
            auto [steps, node] = q.front();
            q.pop();

            // Try all possible multiplication choices
            for (auto it : arr) {
                int num = (1LL * node * it) % MOD;

                // Relaxation step
                if (steps + 1 < dist[num]) {
                    dist[num] = steps + 1;

                    // Early exit optimization
                    if (num == end) {
                        return steps + 1;
                    }

                    q.push({steps + 1, num});
                }
            }
        }

        // Destination is unreachable
        return -1;
    }
};

/*
Time Complexity: O(100,000 * N)
- In the worst case, every integer from 0 to 99,999 is visited at most once: 10^5 states.
- From each state, we try all N multipliers from arr.
- Total operations: at most 10^5 * N.
- Given N <= 10^4 (and in practice, reachable states are far fewer), this executes well within time limit.

Space Complexity: O(MOD)
- `dist` array of size 100,000: O(100,000).
- Queue storing at most 100,000 states: O(100,000).
- Overall Auxiliary Space: O(100,000) ≈ 800 KB (constant auxiliary space).

Key Insights:
1. Finite State Space:
   - Modulo 100,000 restricts the infinite space of numbers to exactly 100,000 distinct vertices.
   - This transforms what looks like an unbounded arithmetic search into a bounded shortest-path graph problem!
2. Level-order Shortest Path:
   - Because all step costs are equal to 1, the first time `num == end` is generated, its step 
     count is guaranteed to be optimal.
3. Overflow Protection:
   - `(1LL * node * it) % MOD` prevents integer overflow when multiplying large values before modulo.
*/
