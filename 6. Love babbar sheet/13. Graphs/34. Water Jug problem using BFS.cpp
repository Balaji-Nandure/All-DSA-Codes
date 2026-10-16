/**
 * Problem: Water Jug Problem using BFS (Two Water Jug Problem)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - The graph is not a collection of explicitly defined vertices and edges.
 * - Vertices are states `(a, b)` representing the current volume of water in Jug 1 (capacity m) and Jug 2 (capacity n).
 * - BFS in this implicit state-space discovers the minimum number of filling, emptying, and pouring operations to reach volume `d`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - State-Space BFS on 6 Fundamental Operations:
 *   1. Check feasibility: If `d > max(m, n)` or `d % gcd(m, n) != 0`, measuring `d` is mathematically impossible; return -1.
 *   2. State is `(a, b)` where `0 <= a <= m` and `0 <= b <= n`.
 *   3. From state `(a, b)`, there are 6 possible transitions:
 *      - Fill Jug 1: `(m, b)`
 *      - Fill Jug 2: `(a, n)`
 *      - Empty Jug 1: `(0, b)`
 *      - Empty Jug 2: `(a, 0)`
 *      - Pour Jug 1 -> Jug 2: `(a - min(a, n - b), b + min(a, n - b))`
 *      - Pour Jug 2 -> Jug 1: `(a + min(b, m - a), b - min(b, m - a))`
 *   4. Use a 2D boolean array `visited[m + 1][n + 1]` to prune visited configurations.
 *   5. The first state dequeued with `a == d` or `b == d` yields the minimum operation count.
 * 
 * TIME COMPLEXITY:
 * - O(m * n): Total reachable discrete states bounded by (m + 1) * (n + 1).
 * 
 * SPACE COMPLEXITY:
 * - O(m * n) for the visited table and BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>

struct State {
    int a, b, steps;
};

int minStepsWaterJug(int m, int n, int d) {
    if (d > std::max(m, n)) return -1;
    if (d % std::gcd(m, n) != 0) return -1;

    std::vector<std::vector<bool>> visited(m + 1, std::vector<bool>(n + 1, false));
    std::queue<State> q;

    q.push({0, 0, 0});
    visited[0][0] = true;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        if (curr.a == d || curr.b == d) {
            return curr.steps;
        }

        // Generate all 6 possible subsequent states
        std::vector<std::pair<int, int>> nextStates;

        // 1. Fill jug 1
        nextStates.push_back({m, curr.b});
        // 2. Fill jug 2
        nextStates.push_back({curr.a, n});
        // 3. Empty jug 1
        nextStates.push_back({0, curr.b});
        // 4. Empty jug 2
        nextStates.push_back({curr.a, 0});
        // 5. Pour jug 1 -> jug 2
        int pour1to2 = std::min(curr.a, n - curr.b);
        nextStates.push_back({curr.a - pour1to2, curr.b + pour1to2});
        // 6. Pour jug 2 -> jug 1
        int pour2to1 = std::min(curr.b, m - curr.a);
        nextStates.push_back({curr.a + pour2to1, curr.b - pour2to1});

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Explore all 6 physical water operations; BFS guarantees finding the minimum number of actions.
        for (const auto& [nextA, nextB] : nextStates) {
            if (!visited[nextA][nextB]) {
                visited[nextA][nextB] = true;
                q.push({nextA, nextB, curr.steps + 1});
            }
        }
    }

    return -1;
}

int main() {
    int m = 4, n = 3, d = 2;
    int steps = minStepsWaterJug(m, n, d);

    std::cout << "Minimum steps to measure " << d << " liters using (" << m << ", " << n << ") jugs: " << steps << "\n"; // Expected: 4

    return 0;
}
