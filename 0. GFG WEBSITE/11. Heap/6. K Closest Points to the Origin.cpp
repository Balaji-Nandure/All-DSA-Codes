/*
Problem:
K Closest Points to the Origin

Given an array of points where points[i] = [xi, yi],
return the K points closest to the origin (0, 0).

Distance Formula:
distance = x^2 + y^2
(Note: Square root is NOT required for comparison)

Rules:
- Return any order.
- Use Euclidean distance.
- K ≤ N.

Example:
Input:
points = [[1,3],[-2,2],[5,8],[0,1]]
K = 2

Output:
[[-2,2],[0,1]]

Approach (Optimal – Max Heap of Size K):
- Maintain a Max Heap (priority_queue) of size K.
- Heap stores {distance, point}.
- For each point:
  - Compute squared distance.
  - Push into heap.
  - If heap size exceeds K, pop the farthest point.
- At the end, heap contains K closest points.

Why this works:
- Keeping only K points ensures minimal space.
- Max heap ensures farthest among current K is removed first.

LeetCode:
https://leetcode.com/problems/k-closest-points-to-origin/

GeeksforGeeks:
https://www.geeksforgeeks.org/k-closest-points-to-origin/

Time Complexity:
O(N log K)

Space Complexity:
O(K)
*/

class Solution {
    public:
        vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
    
            priority_queue<
                pair<long long, vector<int>>
            > pq;   // max heap on distance
    
            for (auto& p : points) {
    
                long long dist =
                    1LL * p[0] * p[0] + 1LL * p[1] * p[1];
    
                pq.push({dist, p});
    
                if (pq.size() > K)
                    pq.pop();
            }
    
            vector<vector<int>> res;
            while (!pq.empty()) {
                res.push_back(pq.top().second);
                pq.pop();
            }
    
            return res;
        }
    };
    