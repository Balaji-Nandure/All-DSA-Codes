/*
Problem: Minimum Jumps to Reach End

GFG: https://www.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1

Description: You are given an array arr[] of non-negative numbers. Each number tells you the maximum number of steps you can jump forward from that position.

For example:
If arr[i] = 3, you can jump to index i + 1, i + 2, or i + 3 from position i.
If arr[i] = 0, you cannot jump forward from that position.
Your task is to find the minimum number of jumps needed to move from the first position in the array to the last position.

Note: Return -1 if you can't reach the end of the array.

Examples:

Input: arr[] = [1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9]
Output: 3 
Explanation: First jump from 1st element to 2nd element with value 3. From here we jump to 5th element with value 9, and from here we will jump to the last.
Input: arr = [1, 4, 3, 2, 6, 7]
Output: 2 
Explanation: First we jump from the 1st to 2nd element and then jump to the last element.
Input: arr = [0, 10, 20]
Output: -1
Explanation: We cannot go anywhere from the 1st element.

Constraints:
2 ≤ arr.size() ≤ 105
0 ≤ arr[i] ≤ 105

Approach:
GREEDY (OPTIMAL):
Track current range and farthest reachable index.
When range ends → take jump.
TC: O(n)
SC: O(1)

Why Greedy works:
We always jump to the position which gives
maximum reach in the next step.
This minimizes number of jumps.

Algorithm:
1. If n <= 1: return 0
2. If arr[0] == 0: return -1 (can't move)
3. Initialize jumps = 0, currentEnd = 0, farthest = 0
4. For each index i from 0 to n-2:
   - farthest = max(farthest, i + arr[i])
   - If i == currentEnd: 
     * jumps++
     * currentEnd = farthest
     * If currentEnd <= i: return -1 (stuck)
5. Return jumps

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();

        if (n <= 1) return 0;
        if (arr[0] == 0) return -1;

        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;

        for (int i = 0; i < n - 1; i++) {
            // Update farthest reachable index
            farthest = max(farthest, i + arr[i]);

            // When we reach end of current jump range
            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;

                // If we can't move forward
                if (currentEnd <= i)
                    return -1;
            }
        }

        return jumps;
    }
};
