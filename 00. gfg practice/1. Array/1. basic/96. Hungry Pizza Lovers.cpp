/*
Problem: Hungry Pizza Lovers

GFG: https://www.geeksforgeeks.org/problems/hungry-pizza-lovers/1

Description: Dominos Pizza has hungry customers waiting in the queue. Each unique order is placed by a customer at time x[i], and the order takes y[i] units of time to complete. You have information on all n orders, Find the order in which all customers will receive their pizza and return it. If two or more orders are completed at the same time then sort them by non-decreasing order number.

Examples:

Example 1:

Input : arr[ ] = {{4,1}, {6,2}, {7,6}, {8,1}, {1,3}}
Output : 5 1 2 4 3
Explanation:
Here an array can be transform to 
{5, 8, 13, 9, 4}. Here 5th index order 
received first then 1st order, 2nd order...
return {5, 1, 2, 4, 3}

Example 2:

Input : arr[ ] = {{1,1}, {1,1}, {1,1}} 
Output :  1 2 3 

Constraints:
1 ≤ N ≤ 105
1 ≤ arr[i][0], arr[i][1] ≤ 105

Approach:
1. Compute completion time = arrival + cook time
2. Store (completion_time, index)
3. Sort by:
   - completion_time
   - index (for tie)
4. Return indices

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> permute(vector<vector<int>>& arr, int n) {
        
        vector<pair<int,int>> orders;

        // Step 1: Compute completion time
        for (int i = 0; i < n; i++) {
            int completion = arr[i][0] + arr[i][1];
            orders.push_back({completion, i + 1}); // 1-based index
        }

        // Step 2: Sort
        sort(orders.begin(), orders.end());

        // Step 3: Extract result
        vector<int> result;
        for (auto &p : orders) {
            result.push_back(p.second);
        }

        return result;
    }
};
