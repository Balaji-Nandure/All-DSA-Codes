/*
LeetCode 2058: Find the Minimum and Maximum Number of Nodes Between Critical Points

A critical point in a linked list is defined as either a local maxima or a local minima.
A node is a local maxima if the current node has a value strictly greater than the previous node and the next node.
A node is a local minima if the current node has a value strictly less than the previous node and the next node.
Note that a node can only be a local maxima/minima if there exists both a previous node and a next node.

Given a linked list head, return an array of length 2 containing [minDistance, maxDistance] where:
- minDistance is the minimum distance between any two distinct critical points.
- maxDistance is the maximum distance between the first and last critical points.
If there are fewer than two critical points, return [-1, -1].

Example:
Input: head = [5,3,1,2,5,1,2]
Output: [1,3]
Explanation: There are three critical points:
- [5,3,1,2,5,1,2]: The node with value 1 is a local minima because 1 is less than 3 and 2.
- [5,3,1,2,5,1,2]: The node with value 5 is a local maxima because 5 is greater than 2 and 5.
- [5,3,1,2,5,1,2]: The node with value 1 is a local minima because 1 is less than 5 and 2.
The minimum distance is between the first and the second critical points is 1.
The maximum distance is between the first and the third critical points is 3.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

 // steps
 // 1. find all critical points
 // 2. if less than 2 critical points, return [-1, -1]
 // 3. calculate minimum distance
 // 4. calculate maximum distance
 // 5. return the result

class Solution {
public:
/*
 * Problem: Find the Minimum and Maximum Number of Nodes Between Critical Points
 *
 * LeetCode 2058: Find the Minimum and Maximum Number of Nodes Between Critical Points
 *
 * Critical point = local maxima or minima.
 * Find min distance between any two critical points, and max distance between first and last.
 * Example: [5,3,1,2,5,1,2] -> critical points at indices 2,4,5 -> [1,3]
 *
 * Time: O(n) - single pass to find critical points
 * Space: O(k) - where k is number of critical points
 */

    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        vector<int> criticalPoints;
        
        ListNode* prev = nullptr;
        ListNode* current = head;
        int index = 0;
        
        // Find all critical points (local maxima or minima)
        while (current != nullptr && current->next != nullptr) {
            if (prev != nullptr) {
                // Check if current is local maxima or minima
                bool isMaxima = current->val > prev->val && current->val > current->next->val;
                bool isMinima = current->val < prev->val && current->val < current->next->val;
                
                if (isMaxima || isMinima) {
                    criticalPoints.push_back(index);
                }
            }
            
            prev = current;
            current = current->next;
            index++;
        }
        
        // Need at least 2 critical points
        if (criticalPoints.size() < 2) {
            return {-1, -1};
        }
        
        // Calculate minimum distance: smallest gap between consecutive critical points
        int minDistance = INT_MAX;
        for (int i = 1; i < criticalPoints.size(); i++) {
            minDistance = min(minDistance, criticalPoints[i] - criticalPoints[i - 1]);
        }
        
        // Maximum distance: between first and last critical point
        int maxDistance = criticalPoints.back() - criticalPoints.front();
        
        return {minDistance, maxDistance};
    }
};

/*
Approach: Find Critical Points and Calculate Distances
- Traverse the list and identify all critical points (local maxima or minima)
- Store the indices of all critical points
- If we have less than 2 critical points, return [-1, -1]
- Calculate minimum distance: minimum gap between consecutive critical points
- Calculate maximum distance: distance between first and last critical point

Time Complexity: O(n) - single pass to find critical points, O(k) to calculate distances where k is number of critical points
Space Complexity: O(k) - vector to store critical point indices

Key Insight:
- A critical point is either:
  - Local maxima: current > prev AND current > next
  - Local minima: current < prev AND current < next
- We need at least 2 critical points to calculate distances
- Minimum distance is the smallest gap between any two consecutive critical points
- Maximum distance is always between the first and last critical point

Example Walkthrough:
Input: head = [5,3,1,2,5,1,2]
Indices:      [0,1,2,3,4,5,6]
Critical points:
  - Index 2 (value 1): local minima (1 < 3 and 1 < 2)
  - Index 4 (value 5): local maxima (5 > 2 and 5 > 1)
  - Index 5 (value 1): local minima (1 < 5 and 1 < 2)
Critical points: [2, 4, 5]
minDistance = min(4-2, 5-4) = min(2, 1) = 1
maxDistance = 5 - 2 = 3
Output: [1, 3]
*/

