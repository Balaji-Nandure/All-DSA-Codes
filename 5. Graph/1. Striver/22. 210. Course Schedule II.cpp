// Problem: 210. Course Schedule II
// Link (LeetCode): https://leetcode.com/problems/course-schedule-ii/
// Link (GFG): https://www.geeksforgeeks.org/problems/course-schedule/1
// Difficulty: Medium
// Topic: Graph, BFS, Kahn's Algorithm, Topological Sort, Directed Graph

/*
Problem Statement:
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. 
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must 
take course bi first if you want to take course ai.

Return the ordering of courses you should take to finish all courses. 
If there are many valid answers, return any of them. 
If it is impossible to finish all courses, return an empty array.

Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So the correct course order is [0,1].

Example 2:
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3] (or [0,1,2,3])
Explanation: 
- Course 0 has no prerequisites, so it comes first.
- To take 3, you must finish 1 and 2.
- Both 1 and 2 require 0.
Valid orders are [0,1,2,3] or [0,2,1,3].

Example 3:
Input: numCourses = 1, prerequisites = []
Output: [0]

Constraints:
- 1 <= numCourses <= 2000
- 0 <= prerequisites.length <= numCourses * (numCourses - 1)
- prerequisites[i].length == 2
- 0 <= ai, bi < numCourses
- ai != bi
- All the pairs [ai, bi] are distinct.
*/

// Approach: Kahn's Algorithm (BFS Topological Sort)
// 1. Dependency Modeling:
//    - [a, b] means b must be taken before a -> directed edge: b -> a.
// 2. Goal:
//    - Find a linear order of all courses such that for every edge b -> a, b appears before a.
//    - This is the exact definition of Topological Sort.
//    - If a cycle exists, no topological sort is possible -> return empty array [].
// 3. Algorithm Steps:
//    Step 1: Build the adjacency list: for each [a, b], add directed edge b -> a.
//    Step 2: Calculate in-degree for all vertices using Striver's loop:
//            `for (auto it : adj[i]) indegree[it]++;`
//    Step 3: Push all courses with indegree == 0 (no prerequisites needed) into a BFS queue.
//    Step 4: BFS traversal:
//            - Pop `node`, append it to `topo` result vector.
//            - For each dependent course `it` in `adj[node]`:
//              - Decrement `indegree[it]--`.
//              - If `indegree[it] == 0`, all prerequisites for `it` are completed -> push `it` to queue.
//    Step 5: If `topo.size() == numCourses`, a valid ordering exists -> return `topo`.
//            Otherwise (topo.size() < numCourses), a cycle exists -> return `{}`.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // Step 1: Build adjacency list (prereq -> course)
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

        // Step 3: Push all courses with 0 prerequisites into queue
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo;

        // Step 4: BFS Traversal (Kahn's Algorithm)
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        // If all courses were successfully ordered, return topo sort
        if (topo.size() == numCourses) {
            return topo;
        }

        // Cycle detected: impossible to finish all courses
        return {};
    }
};

/*
Time Complexity: O(V + E)
- Building the adjacency list: O(E) where E = prerequisites.size().
- Computing in-degrees: O(V + E).
- BFS traversal: each course is pushed/popped once: O(V).
- Each edge is traversed once: O(E).
- Total Time Complexity: O(V + E), where V = numCourses, E = prerequisites.size().

Space Complexity: O(V + E)
- Adjacency list: O(V + E).
- In-degree array: O(V).
- BFS queue: O(V).
- Output vector topo: O(V).
- Total Auxiliary Space: O(V + E).

Key Insights:
1. Difference between Course Schedule I & II:
   - Part I asks if it is POSSIBLE (returns bool: true/false).
   - Part II asks for the ACTUAL ORDER (returns vector<int>: topo order or empty vector if impossible).
2. Edge Direction:
   - [a, b] $\implies$ edge is `b -> a`. Reversing this direction would result in taking advanced 
     courses before their prerequisites!
*/
