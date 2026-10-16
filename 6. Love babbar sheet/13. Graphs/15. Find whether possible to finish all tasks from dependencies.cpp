/**
 * Problem: Find Whether Possible to Finish All Tasks from Given Dependencies (Course Schedule)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Instead of computing an optimal schedule, we must ascertain whether ANY valid topological ordering exists.
 * - If there is a cyclic prerequisite chain (e.g., A needs B, B needs C, C needs A), deadlocking occurs and not all tasks can be finished.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Kahn's Algorithm for Topological Sort & Cycle Detection:
 *   - Construct a directed graph where dependency pair `[u, v]` implies prerequisite `v -> u` (must complete `v` before `u`).
 *   - Compute in-degrees of all tasks `0` to `numTasks - 1`.
 *   - Enqueue all tasks with `inDegree == 0` (no unmet prerequisites).
 *   - Process queue, decrementing in-degrees of dependent tasks.
 *   - Maintain a count of processed tasks.
 *   - If `count == numTasks`, all tasks can be completed; otherwise, a cycle exists.
 * 
 * TIME COMPLEXITY:
 * - O(V + E) where V is numTasks and E is number of dependency pairs.
 * 
 * SPACE COMPLEXITY:
 * - O(V + E) for adjacency list, in-degree array, and queue.
 */

#include <iostream>
#include <vector>
#include <queue>

bool canFinish(int numTasks, std::vector<std::pair<int, int>>& prerequisites) {
    std::vector<std::vector<int>> adj(numTasks);
    std::vector<int> inDegree(numTasks, 0);

    for (const auto& req : prerequisites) {
        int task = req.first;
        int prereq = req.second;
        adj[prereq].push_back(task); // prereq -> task
        inDegree[task]++;
    }

    std::queue<int> q;
    for (int i = 0; i < numTasks; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int completedTasks = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        completedTasks++;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Decrement dependency counts; when a task's prerequisites reach 0, it can be unlocked.
        for (int v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // If all tasks were dequeued, no circular dependency existed
    return completedTasks == numTasks;
}

int main() {
    int numTasks = 4;
    // Task dependencies: [task, prereq]
    std::vector<std::pair<int, int>> prerequisites = {
        {1, 0}, {2, 1}, {3, 2}
    };

    bool possible = canFinish(numTasks, prerequisites);
    std::cout << "Can finish all tasks: " << (possible ? "YES" : "NO") << "\n"; // Expected: YES

    // Introducing a cycle: 0 -> 3
    prerequisites.push_back({0, 3});
    bool cyclicPossible = canFinish(numTasks, prerequisites);
    std::cout << "Can finish with cycle added: " << (cyclicPossible ? "YES" : "NO") << "\n"; // Expected: NO

    return 0;
}
