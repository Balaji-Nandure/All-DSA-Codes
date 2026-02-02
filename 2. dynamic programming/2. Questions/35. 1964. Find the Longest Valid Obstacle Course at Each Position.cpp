#include <bits/stdc++.h>
using namespace std;


/*
Problem:
1964. Find the Longest Valid Obstacle Course at Each Position

Description:
You want to build some obstacle courses. You are given a 0-indexed integer array obstacles of length n, 
where obstacles[i] describes the height of the ith obstacle.

For every index i between 0 and n - 1 (inclusive), find the length of the longest obstacle course in 
obstacles such that:
- You choose any number of obstacles between 0 and i inclusive.
- You must include the ith obstacle in the course.
- You must put the chosen obstacles in the same order as they appear in obstacles.
- Every obstacle (except the first) is taller than or equal to the obstacle immediately before it.

Return an array ans of length n, where ans[i] is the length of the longest obstacle course for index i.

Approach:
Longest Increasing Subsequence (LIS) with Binary Search
- Use a list to maintain the smallest tail element for each length
- For each obstacle, find the position where it can extend or replace
- Use upper_bound to find the rightmost position where obstacle can be placed (allows equal heights)

LeetCode:
https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/

Time Complexity:
O(n log n) - binary search for each element

Space Complexity:
O(n) - for the lis array and result array
*/


/*
Dry Run:
Input: obstacles = [2, 2, 1]

Initial state:
lis = []
obstacles = [2, 2, 1]

Iteration 0: obstacles[0] = 2
- lis is empty (Case 1)
- lis.push_back(2) → lis = [2]
- obstacles[0] = 1
- State: lis = [2], obstacles = [1, 2, 1]

Iteration 1: obstacles[1] = 2
- lis is not empty
- obstacles[1] = 2 >= lis.back() = 2 (Case 2)
- lis.push_back(2) → lis = [2, 2]
- obstacles[1] = lis.size() = 2
- State: lis = [2, 2], obstacles = [1, 2, 1]

Iteration 2: obstacles[2] = 1
- lis is not empty
- obstacles[2] = 1 < lis.back() = 2 (Case 3)
- upper_bound(lis.begin(), lis.end(), 1) finds first element > 1
- j = 0 (position of first element > 1, which is 2)
- lis[0] = 1 → lis = [1, 2]
- obstacles[2] = j + 1 = 1
- State: lis = [1, 2], obstacles = [1, 2, 1]

Final result: [1, 2, 1]

Explanation:
- At position 0: longest course is [2], length = 1
- At position 1: longest course is [2, 2], length = 2
- At position 2: longest course is [1], length = 1
*/

class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        // lis[i] stores the smallest tail element for obstacle course of length i+1
        vector<int> lis;
        
        // Process each obstacle
        for (int i = 0; i < obstacles.size(); i++) {
            
            // Case 1: First obstacle - start a new course
            if (lis.empty()) {
                lis.push_back(obstacles[i]);
                obstacles[i] = 1;  // Length of course ending at position i
            }
            
            // Case 2: Current obstacle >= last element in lis
            // Can extend the longest course
            else if (obstacles[i] >= lis.back()) {
                lis.push_back(obstacles[i]);
                obstacles[i] = lis.size();  // New length
            }
            
            // Case 3: Current obstacle < last element
            // Find position to replace using binary search
            else {
                // upper_bound finds first element > obstacles[i]
                // This allows equal heights (non-strictly increasing)
                int j = upper_bound(lis.begin(), lis.end(), obstacles[i]) - lis.begin();
                lis[j] = obstacles[i];  // Replace with smaller value
                obstacles[i] = j + 1;   // Length of course ending here
            }
        }
        
        return obstacles;  // Reused as result array
    }
};


