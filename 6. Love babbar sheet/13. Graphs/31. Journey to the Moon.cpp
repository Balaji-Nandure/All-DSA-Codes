/**
 * Problem: Journey to the Moon (Valid Pairs of Astronauts from Different Countries)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - We are not merely checking connectivity; we must group astronauts into connected components (countries).
 * - Two astronauts can form a valid pair if and only if they belong to DIFFERENT connected components.
 * - Naively checking all O(N^2) pairs causes TLE for N = 100,000.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Connected Components via DFS / DSU + Combinatorial Prefix Sum:
 *   1. Use DFS or DSU to identify all connected components and compute their sizes: `s1, s2, ..., sk`.
 *   2. Sum of all sizes is `N`.
 *   3. Total pairs of astronauts from different countries:
 *      `Total = sum_{i < j} (s_i * s_j)`
 *   4. An efficient O(K) way to compute this without nested loops:
 *      Maintain `runningSum = 0`.
 *      For each component size `s`:
 *        `validPairs += runningSum * s;`
 *        `runningSum += s;`
 * 
 * TIME COMPLEXITY:
 * - O(N + P) where N is number of astronauts and P is number of pairs given.
 * 
 * SPACE COMPLEXITY:
 * - O(N + P) for adjacency list and visited boolean array.
 */

#include <iostream>
#include <vector>

void dfs(int u, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, long long& compSize) {
    visited[u] = true;
    compSize++;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited, compSize);
        }
    }
}

long long journeyToMoon(int n, const std::vector<std::vector<int>>& astronaut) {
    std::vector<std::vector<int>> adj(n);
    for (const auto& pair : astronaut) {
        adj[pair[0]].push_back(pair[1]);
        adj[pair[1]].push_back(pair[0]);
    }

    std::vector<bool> visited(n, false);
    std::vector<long long> componentSizes;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            long long compSize = 0;
            dfs(i, adj, visited, compSize);
            componentSizes.push_back(compSize);
        }
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Multiply each new component size by the sum of all previously encountered astronaut components in O(K).
    long long totalPairs = 0;
    long long runningSum = 0;

    for (long long size : componentSizes) {
        totalPairs += runningSum * size;
        runningSum += size;
    }

    return totalPairs;
}

int main() {
    int n = 5;
    std::vector<std::vector<int>> astronaut = {
        {0, 1},
        {2, 3},
        {0, 4}
    };
    // Components: {0, 1, 4} (size 3) and {2, 3} (size 2)
    // Valid pairs: 3 * 2 = 6

    long long pairs = journeyToMoon(n, astronaut);
    std::cout << "Valid astronaut pairs: " << pairs << "\n"; // Expected: 6

    return 0;
}
