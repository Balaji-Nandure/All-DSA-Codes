// Problem: 207. Course Schedule (Course Schedule I)
// Link (LeetCode): https://leetcode.com/problems/course-schedule/
// Link (GFG): https://www.geeksforgeeks.org/problems/prerequisite-tasks/1
// Difficulty: Medium
// Topic: Graph, BFS, Kahn's Algorithm, Topological Sort, Directed Graph, Cycle Detection

/*
Problem Statement:
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must 
take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.

Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:
Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: To take course 1 you should have finished course 0, and to take course 0 you should 
also have finished course 1. So it is impossible (cycle exists: 0 -> 1 -> 0).

Constraints:
- 1 <= numCourses <= 2000
- 0 <= prerequisites.length <= 5000
- prerequisites[i].length == 2
- 0 <= ai, bi < numCourses
- All the pairs prerequisites[i] are unique.
*/

// Approach: Kahn's Algorithm (BFS Cycle Detection)
// 1. Dependency Modeling:
//    - prerequisites[i] = [a, b] means course b must be completed before course a.
//    - This forms a directed edge: b -> a.
// 2. Cycle Detection Principle:
//    - If there is a cycle of dependencies (e.g., A needs B, B needs C, C needs A), 
//      none of those courses can ever be started.
//    - It is possible to finish all courses if and only if the dependency graph is a DAG (has NO cycle).
// 3. Algorithm Steps:
//    Step 1: Build the adjacency list: for each [a, b], add directed edge b -> a.
//    Step 2: Calculate in-degree for all vertices using Striver's loop:
//            `for (auto it : adj[i]) indegree[it]++;`
//    Step 3: Push all courses with indegree == 0 (courses with no prerequisites) into a BFS queue.
//    Step 4: Process queue with Kahn's algorithm, keeping a count of completed courses:
//            - Pop `node`, increment `count++`.
//            - For each dependent course `it` in `adj[node]`:
//              - Decrement `indegree[it]--`.
//              - If `indegree[it] == 0`, all prerequisites for `it` are fulfilled -> push to queue.
//    Step 5: If `count == numCourses`, all courses can be finished -> return true.
//            Otherwise (count < numCourses), a cycle exists -> return false.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Step 1: Build adjacency list (b -> a)
        vector<vector<int>> adj(numCourses);
        for (auto& pre : prerequisites) {
            int course = pre[0];
            int prereq = pre[1];
            adj[prereq].push_back(course);
        }

        // Step 2: Calculate indegree for all courses
        vector<int> indegree(numCourses, 0);
        for (int i = 0; i < numCourses; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 3: Push courses with 0 prerequisites into queue
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int count = 0;

        // Step 4: BFS Traversal (Kahn's Algorithm)
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;

            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        // If count == numCourses, all courses can be taken (DAG, no cycle)
        return count == numCourses;
    }
};

/*
Time Complexity: O(V + E)
- Building the adjacency list: O(E) where E = prerequisites.size().
- Computing in-degrees: O(V + E).
- BFS traversal: each course is pushed/popped at most once: O(V).
- Each edge is traversed once: O(E).
- Total Time Complexity: O(V + E), where V = numCourses, E = prerequisites.size().

Space Complexity: O(V + E)
- Adjacency list: O(V + E).
- In-degree array: O(V).
- BFS queue: O(V).
- Total Auxiliary Space: O(V + E).

Key Insights:
1. Direction of Edges:
   - Carefully identify the direction: [a, b] means b is prerequisite for a, so the edge is b -> a.
2. Cycle Detection Equivalent:
   - "Can we finish all courses?" is mathematically identical to "Does the directed graph have NO cycles?".
   - Kahn's algorithm seamlessly solves this with in-degrees in linear time.
*/
