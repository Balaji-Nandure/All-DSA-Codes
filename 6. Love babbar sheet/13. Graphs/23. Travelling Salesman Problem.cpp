/**
 * Problem: Travelling Salesman Problem (TSP) using Dynamic Programming with Bitmasking
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Shortest path algorithms visit nodes to reach a target.
 * - TSP requires visiting EVERY vertex in the graph EXACTLY ONCE and returning to the starting vertex, minimizing total edge weight (NP-hard).
 * - Naive permutation check runs in O(N!), which becomes infeasible for N > 11.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Held-Karp Bitmask DP:
 *   - Represent the set of visited cities as an integer bitmask of length `N`.
 *   - State: `dp(city, mask)`: minimum cost to visit all remaining unvisited cities starting from `city` with subset `mask` already visited, and finally returning to city 0.
 *   - Base Case:
 *     - If `mask == (1 << N) - 1` (all cities visited), return cost to return home: `cost[city][0]`.
 *   - Transition:
 *     - For every unvisited city `next` where `(mask & (1 << next)) == 0`:
 *       `cost[city][next] + dp(next, mask | (1 << next))`
 *     - Take the minimum over all valid transitions.
 * 
 * TIME COMPLEXITY:
 * - O(N^2 * 2^N): Number of states is N * 2^N, and each state transitions in O(N).
 * 
 * SPACE COMPLEXITY:
 * - O(N * 2^N) for the memoization table.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class TSP {
    int n;
    std::vector<std::vector<int>> cost;
    std::vector<std::vector<int>> memo;

    int solve(int u, int mask) {
        // Base case: All vertices have been visited
        if (mask == (1 << n) - 1) {
            return cost[u][0]; // Return to starting city 0
        }

        if (memo[u][mask] != -1) {
            return memo[u][mask];
        }

        int minCost = 1e9;

        // Try transitioning to every unvisited vertex
        for (int v = 0; v < n; v++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Bitwise test (mask & (1 << v)) == 0 ensures city v has not yet been visited in this Hamiltonian tour.
            if (!(mask & (1 << v))) {
                int currentCost = cost[u][v] + solve(v, mask | (1 << v));
                minCost = std::min(minCost, currentCost);
            }
        }

        return memo[u][mask] = minCost;
    }

public:
    int totalCost(std::vector<std::vector<int>>& costMatrix) {
        cost = costMatrix;
        n = cost.size();
        memo.assign(n, std::vector<int>(1 << n, -1));

        // Start from city 0, with only city 0 visited initially (mask = 1)
        return solve(0, 1);
    }
};

int main() {
    std::vector<std::vector<int>> costMatrix = {
        {0, 1000, 5000},
        {5000, 0, 1000},
        {1000, 5000, 0}
    };

    TSP tsp;
    int minCycleCost = tsp.totalCost(costMatrix);
    std::cout << "Minimum TSP Tour Cost: " << minCycleCost << "\n"; // Expected: 3000 (0 -> 1 -> 2 -> 0)

    return 0;
}
