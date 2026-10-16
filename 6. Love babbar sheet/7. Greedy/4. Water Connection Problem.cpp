/**
 * ============================================================================
 * Problem: Water Connection Problem
 * Category: Greedy / Graph Traversal
 * 
 * Problem Statement:
 * There are N houses and P pipes in a village. A water distribution company plans
 * to install tanks and taps:
 *   - Every house has at most ONE incoming pipe and at most ONE outgoing pipe.
 *   - A tank is installed on a house that has an OUTGOING pipe but NO INCOMING pipe.
 *   - A tap is installed on a house that has an INCOMING pipe but NO OUTGOING pipe.
 *   - Each pipe has a specified diameter.
 * 
 * For every tank-to-tap path, the effective flow capacity is determined by the
 * MINIMUM pipe diameter along that path (the bottleneck).
 * 
 * Output:
 *   1. The number of tank-tap pairs.
 *   2. For each pair: (tank_house, tap_house, min_diameter), sorted by tank_house.
 * 
 * Example:
 * Input:
 *   N = 9, P = 6
 *   Pipes: (7, 4, 98), (5, 9, 72), (4, 6, 10), (2, 8, 22), (9, 7, 17), (3, 1, 66)
 * Output:
 *   3 pairs:
 *   2 8 22
 *   3 1 66
 *   5 6 10  (Path: 5 -> 9 -> 7 -> 4 -> 6, min diameter = min(72, 17, 98, 10) = 10)
 * 
 * Constraints:
 * 1 <= N <= 20
 * 1 <= P <= 50
 * 1 <= diameter <= 100
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Degree-Constrained Graph Component Decomposition:
 *    - In general graphs, finding paths involves complex cycle checks, branching,
 *      and shortest-path algorithms (Dijkstra/BFS).
 *    - Here, the constraint that in-degree <= 1 and out-degree <= 1 mathematically
 *      guarantees that the graph is composed strictly of disjoint linear chains!
 * 2. Bottleneck Capacity (Min-Edge on Path):
 *    - The flow from source to sink is purely constrained by the weakest link:
 *      `minCapacity = min_{edges} (diameter[edge])`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Linear Path Walking O(N + P) Time, O(N) Space:
 *   - Step 1: Track graph connections:
 *       `outPipe[u] = v;` (outgoing neighbor)
 *       `diameter[u] = d;` (pipe capacity)
 *       `hasIncoming[v] = true;` (track in-degrees)
 *   - Step 2: Iterate over each house `i` from 1 to N:
 *       - If `!hasIncoming[i] && outPipe[i] != 0`:
 *           House `i` is the start of a new tank-tap pipeline!
 *           Traverse the chain:
 *             `curr = i; minD = infinity;`
 *             `while (outPipe[curr] != 0):`
 *                 `minD = min(minD, diameter[curr]);`
 *                 `curr = outPipe[curr];`
 *           Record triplet: `{i, curr, minD}`.
 *   - Step 3: Return collected triplets (naturally sorted by tank index).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    /**
     * Finds all tank-to-tap paths and their bottleneck diameters.
     * @param n Number of houses.
     * @param p Number of pipes.
     * @param a Start houses of pipes.
     * @param b End houses of pipes.
     * @param d Diameters of pipes.
     * @return Vector of triplets [tank, tap, min_diameter].
     */
    vector<vector<int>> solve(int n, int p, vector<int>& a, vector<int>& b, vector<int>& d) {
        vector<int> outPipe(n + 1, 0);
        vector<int> pipeDiameter(n + 1, 0);
        vector<bool> hasIncoming(n + 1, false);

        // Step 1: Construct degree-constrained directed graph
        for (int i = 0; i < p; ++i) {
            outPipe[a[i]] = b[i];
            pipeDiameter[a[i]] = d[i];
            hasIncoming[b[i]] = true;
        }

        vector<vector<int>> results;

        // Step 2: Find all tank houses (in-degree == 0 and out-degree > 0)
        for (int i = 1; i <= n; ++i) {
            if (!hasIncoming[i] && outPipe[i] != 0) {
                int tank = i;
                int curr = i;
                int minDiameter = INT_MAX;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // In a graph with in-degree <= 1 and out-degree <= 1, each component is a
                // single deterministic chain. We walk to the tap while tracking the bottleneck diameter.
                while (outPipe[curr] != 0) {
                    minDiameter = min(minDiameter, pipeDiameter[curr]);
                    curr = outPipe[curr];
                }

                int tap = curr;
                results.push_back({tank, tap, minDiameter});
            }
        }

        return results;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case:
    // N = 9, P = 6
    // Pipes: (7, 4, 98), (5, 9, 72), (4, 6, 10), (2, 8, 22), (9, 7, 17), (3, 1, 66)
    int n = 9, p = 6;
    vector<int> a = {7, 5, 4, 2, 9, 3};
    vector<int> b = {4, 9, 6, 8, 7, 1};
    vector<int> d = {98, 72, 10, 22, 17, 66};

    vector<vector<int>> ans = solver.solve(n, p, a, b, d);

    cout << "Number of Tank-Tap Pairs: " << ans.size() << "\n";
    cout << "Tank -> Tap [Min Diameter]:\n";
    for (auto& row : ans) {
        cout << row[0] << " " << row[1] << " " << row[2] << "\n";
    }
    // Expected:
    // 2 8 22
    // 3 1 66
    // 5 6 10

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Building graph: O(P).
 *   - Path traversal: Each node and pipe is visited at most once: O(N).
 *   - Total Time: O(N + P) optimal linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(N) for outgoing, diameter, and in-degree arrays.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. When in-degree <= 1 and out-degree <= 1, the graph is a collection of disjoint
 *    simple directed paths.
 * 2. Source nodes have in-degree 0 and out-degree 1; Sink nodes have out-degree 0.
 */
