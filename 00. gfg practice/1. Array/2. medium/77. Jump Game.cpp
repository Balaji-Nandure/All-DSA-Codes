/*
Problem: Jump Game

GFG: https://www.geeksforgeeks.org/problems/jump-game/1

Description:
Given a array of positive integers arr, where each element denotes the maximum length of jump you can cover. Find out if you can make it to the last index starting from the first index of the list, return true if you can reach the last index.

Examples:

Input: arr = [1, 2, 0, 3, 0, 0] 
Output: true
Explanation: Jump 1 step from first index to second index. Then jump 2 steps to reach 4th index, and now jump 2 steps to reach the end.

Input: arr = [1, 0, 2]
Output: false
Explanation: You can't reach the end of the array.

Constraints:
1 <= arr.size() <= 10^5
0 <= arr[i] <= 10^5

Approach (Greedy - Farthest Reach):
1. maxReach = 0
2. Traverse array:
   for i from 0 → n-1:
   - If i > maxReach → you can't even reach this index → return false
   - Update: maxReach = max(maxReach, i + arr[i])
   - If maxReach >= n-1 → already can reach end → return true

Why it works:
- At every index, track the farthest index you can reach
- If at any point you cannot reach index i, then further indices are impossible
- Greedy approach ensures optimal path selection

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canReachEnd(vector<int>& arr) {
        
        int n = arr.size();
        
        int maxReach = 0;
        
        for (int i = 0; i < n; i++) {
            
            // If current index is not reachable
            if (i > maxReach) {
                return false;
            }
            
            // Update farthest reachable
            maxReach = max(maxReach, i + arr[i]);
            
            // Early exit if end reachable
            if (maxReach >= n - 1) {
                return true;
            }
        }
        
        return true;
    }
};
