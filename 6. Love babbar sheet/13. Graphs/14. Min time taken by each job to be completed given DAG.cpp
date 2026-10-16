/**
 * Problem: Minimum Time Taken by Each Job to be Completed Given a DAG
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Standard topological sort outputs a single valid linear sequence of jobs.
 * - Here, multiple independent jobs can execute in parallel at the same time step.
 * - Each job takes 1 unit of time; a job can only start at `max(completion_time_of_prerequisites) + 1`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Level-Synchronized Kahn's Algorithm (DAG Dynamic Programming):
 *   - Calculate in-degrees for all jobs `1` through `N`.
 *   - Initialize `time[i] = 1` for all nodes.
 *   - Push all jobs with `inDegree == 0` into a queue (these start at time 1).
 *   - For each dequeued job `u`:
 *     - For each dependent job `v` where `u -> v`:
 *       - Update `time[v] = max(time[v], time[u] + 1)`.
 *       - Decrement `inDegree[v]`.
 *       - If `inDegree[v] == 0`, push `v` into the queue.
 * 
 * TIME COMPLEXITY:
 * - O(V + E): Standard Kahn's algorithm traversal.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for adjacency list, in-degree array, and time array.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

std::vector<int> minimumTime(int n, int m, std::vector<std::vector<int>>& edges) {
    std::vector<std::vector<int>> adj(n + 1);
    std::vector<int> inDegree(n + 1, 0);

    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        adj[u].push_back(v);
        inDegree[v]++;
    }

    std::vector<int> jobTime(n + 1, 1);
    std::queue<int> q;

    // Jobs with no dependencies start at time unit 1
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Job v cannot begin until all prerequisite jobs finish; its time is at least time[u] + 1.
            jobTime[v] = std::max(jobTime[v], jobTime[u] + 1);
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Return 1-based results [1..n]
    std::vector<int> result(jobTime.begin() + 1, jobTime.end());
    return result;
}

int main() {
    int n = 10, m = 13;
    std::vector<std::vector<int>> edges = {
        {1, 3}, {1, 4}, {1, 5},
        {2, 3}, {2, 8}, {2, 9},
        {3, 6}, {4, 6}, {4, 8},
        {5, 8}, {6, 7}, {7, 8},
        {8, 10}
    };

    std::vector<int> completionTimes = minimumTime(n, m, edges);
    std::cout << "Minimum time taken by each job (1 to " << n << "):\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Job " << (i + 1) << " -> Time: " << completionTimes[i] << "\n";
    }

    return 0;
}
