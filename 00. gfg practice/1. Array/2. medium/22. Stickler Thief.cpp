/*
Problem: Stickler Thief

GFG: https://www.geeksforgeeks.org/stickler-theif/

Description: Stickler the thief wants to loot money from the houses arranged in a line. He cannot loot two consecutive houses and aims to maximize his total loot.
Given an array, arr[] where arr[i] represents the amount of money in the i-th house. Determine the maximum amount he can loot.

Examples:

Input: arr[] = [6, 7, 1, 3, 8, 2, 4]
Output: 19
Explanation: Maximum amount he can get by looting 1st, 3rd, 5th and 7th house, which is 6 + 1 + 8 + 4 = 19.
Input: arr[] = [5, 3, 4, 11, 2]
Output: 16
Explanation: Maximum amount he can get by looting 1st and 4th house, which is 5 + 11 = 16.

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ arr[i] ≤ 104

Striver Intuition:

This is the classic House Robber problem.

At each house i, we have two choices:
1. Loot current house → cannot loot previous house
2. Skip current house → can consider previous result

DP recurrence:
dp[i] = max(dp[i-1], arr[i] + dp[i-2])

Space optimization:
We only need last two values.

Pattern:
Maximum Sum with No Adjacent Elements → DP with last two states

Time Complexity: O(n)
Space Complexity: O(1)

GFG:
https://www.geeksforgeeks.org/stickler-theif/

LeetCode:
https://leetcode.com/problems/house-robber/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxSum(vector<int>& arr) {
        int n = arr.size();
        if(n == 0) return 0;
        if(n == 1) return arr[0];
        
        int prev2 = arr[0];
        int prev = max(arr[0], arr[1]);
        
        for(int i = 2; i < n; i++){
            int take = arr[i] + prev2;
            int notTake = prev;
            
            int curr = max(take, notTake);
            prev2 = prev;
            prev = curr;
        }
        
        return prev;
    }
};

/*
Final Summary (Interview Revision):

1. Cannot loot adjacent houses.
2. DP recurrence: dp[i] = max(dp[i-1], arr[i] + dp[i-2])
3. Space optimize using last two variables.
4. prev2 = dp[i-2], prev = dp[i-1]
5. curr = max(arr[i] + prev2, prev)
6. Time = O(n), Space = O(1)

Memory Trick:
"House Robber → Take + Skip, Keep Last Two"
*/
