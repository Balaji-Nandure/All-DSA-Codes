/*
Problem: Charul and vessels

GFG: https://www.geeksforgeeks.org/problems/charul-and-vessels/1

Description: Charul has been assigned a challenge by Ishaan. He needs to fill a container with exactly k liters of water using some vessels, each with a different capacity. The capacities of the vessels are given in an array arr[]. The goal is to fill the container without any overflow, and no vessel can be filled partially.

Determine if Charul can fill the container up to exactly k liters using the given vessels. You can assume there is an unlimited supply of water, but each vessel's capacity must be used fully.

Examples:

Input: arr[] = [6, 3, 4, 2, 1], k = 20
Output: true
Explanation: Use the 6-liter vessel 3 times to get 18 liters. Use the 2-liter vessel once to get a total of 20 liters.
Input: arr[] = [2, 4, 3], k = 15
Output: true
Explanation: The container can be filled exactly up to 15 liters using a combination of the given vessels.

Constraints:
1 ≤ arr.size() ≤ 1000
1 ≤ k ≤ 1000
1 ≤ arr[i] ≤ 10^5

Approach:
1. Use DP to track reachable sums
2. Initialize dp[0] = true
3. For each vessel, update dp array
4. Return dp[k]

Why it works:
- This is a classic unbounded knapsack problem
- We check if sum k can be formed using unlimited copies of vessel capacities

Time Complexity: O(n*k)
Space Complexity: O(k)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFill(vector<int>& arr, int k) {
        
        vector<bool> dp(k + 1, false);
        dp[0] = true;  // base case: sum 0 is always possible
        
        for (int i = 0; i < arr.size(); i++) {
            int cap = arr[i];
            for (int j = cap; j <= k; j++) {
                if (dp[j - cap]) {
                    dp[j] = true;
                }
            }
        }
        
        return dp[k];
    }
};
