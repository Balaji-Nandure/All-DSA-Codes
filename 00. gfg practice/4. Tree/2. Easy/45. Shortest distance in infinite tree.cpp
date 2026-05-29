/*
GeeksforGeeks: Shortest distance in infinite tree
Difficulty: Easy

Problem:
Consider you have an infinitely long binary tree having the pattern as below:
               1
            /     \
           2      3  
         /  \    /  \
        4    5  6    7
Given two nodes with values x and y, the task is to find the length of the 
shortest path between the two nodes.

Example 1:
Input: x = 1, y = 3
Output: 1
Explanation: 3 is the child of 1, so the distance between them is 1.

Example 2:
Input: x = 5, y = 9
Output: 3
Explanation: 
The path between 5 and 9 is: 5 -> 2 -> 4 -> 9.
Number of edges = 3.

Core Idea:
In this specific infinite binary tree, the nodes are numbered sequentially 
level by level. This gives us a very beautiful mathematical property:
For any node `n`, its parent is ALWAYS `n / 2` (integer division).
- Parent of 2 is 2 / 2 = 1.
- Parent of 3 is 3 / 2 = 1.
- Parent of 4 is 4 / 2 = 2.
- Parent of 5 is 5 / 2 = 2.
- Parent of 9 is 9 / 2 = 4.

Because of this, to find the shortest distance between any two nodes `x` and `y`, 
we can simply trace their paths upwards towards their Lowest Common Ancestor (LCA).
At any point, we look at `x` and `y`:
- If they are equal, we've found their LCA and we are done.
- If `x > y`, it means `x` is deeper in the tree, so we move `x` up to its parent (`x = x / 2`) 
  and increment the distance.
- If `y > x`, we move `y` up to its parent (`y = y / 2`) and increment the distance.

Approach:
1. Initialize `dist = 0`.
2. While `x != y`:
   a. If `x > y`, `x = x / 2`.
   b. Else, `y = y / 2`.
   c. `dist++`.
3. Return `dist`.

Time Complexity : O(log(max(x, y))) — At every step, the larger number is halved.
Space Complexity: O(1) — No extra space is used.

GFG Link:
https://www.geeksforgeeks.org/problems/shortest-distance-in-infinite-tree1559/1
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int distance(int x, int y) {
        int dist = 0;
        
        // Keep tracing paths upwards until x and y meet at their Lowest Common Ancestor
        while (x != y) {
            if (x > y) {
                // x is deeper, move it up to its parent
                x = x / 2;
            } else {
                // y is deeper, move it up to its parent
                y = y / 2;
            }
            // Each move upwards represents 1 edge traversed
            dist++;
        }
        
        return dist;
    }
};

/*
Dry Run — Example 2:
x = 5, y = 9

Initial: dist = 0

Iteration 1:
- x (5) != y (9).
- y > x, so y = 9 / 2 = 4.
- dist = 1.

Iteration 2:
- x (5) != y (4).
- x > y, so x = 5 / 2 = 2.
- dist = 2.

Iteration 3:
- x (2) != y (4).
- y > x, so y = 4 / 2 = 2.
- dist = 3.

Iteration 4:
- x (2) == y (2). Loop terminates!

Return dist = 3. ✓
*/
