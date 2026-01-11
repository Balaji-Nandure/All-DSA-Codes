/*
Problem:
Number of Buildings Facing the Sun

Given an array of integers where each element represents the height
of a building in a row from east to west, determine how many buildings
can see the sun.

The sun rises in the east and sets in the west.

A building can see the sun if all buildings before it (towards east)
are shorter than it.

Rules:
- Buildings are in a straight line.
- Compare heights from east to west.

Example:
Input:
heights = [7, 4, 8, 2, 9]

Output:
3

Explanation:
Buildings with heights 7, 8, and 9 can see the sun.

Approach:
- Traverse from left to right.
- Maintain the maximum height seen so far.
- If current building height is greater than maxHeight, it can see the sun.

GeeksforGeeks:
https://www.geeksforgeeks.org/count-buildings-facing-the-sun/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(1)
*/

class Solution {
    public:
        int countBuildings(vector<int>& heights) {
    
            int count = 0;
            int maxHeight = 0;
    
            for (int h : heights) {
                if (h > maxHeight) {
                    count++;
                    maxHeight = h;
                }
            }
    
            return count;
        }
    };
    