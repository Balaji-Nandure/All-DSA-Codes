/*
PROBLEM: Chocolate Station (GFG)

Given:
- arr[i] chocolates at station i
- Moving i → i+1:
    gain/loss = arr[i] - arr[i+1]
- Must always have chocolates >= 0
- Initially 0 chocolates
- Each chocolate costs "price"

Find minimum total cost to reach last station

--------------------------------------------------

APPROACH (Optimal - Greedy Simulation)

Idea:
- Track current chocolates (curr)
- Track total chocolates bought (bought)

Steps:
1. At station 0:
   → need arr[0] chocolates → buy all
2. For each move i → i+1:
   diff = arr[i] - arr[i+1]
   curr += diff

   If curr < 0:
       → need extra chocolates = -curr
       → buy them
       → set curr = 0

--------------------------------------------------

WHY IT WORKS:
- We only buy chocolates when necessary
- Always maintain non-negative balance
- Minimizes total purchases

--------------------------------------------------

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(1)

GFG LINK: https://www.geeksforgeeks.org/problems/chocolate-station/
LEETCODE LINK: No exact match
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& arr, int price) {
        
        int n = arr.size();
        
        long long bought = arr[0];  // initial buy
        long long curr = 0;         // current chocolates
        
        for(int i = 0; i < n - 1; i++){
            
            // gain/loss while moving
            curr += (arr[i] - arr[i+1]);
            
            // if negative → need to buy
            if(curr < 0){
                bought += (-curr);
                curr = 0;
            }
        }
        
        return bought * price;
    }
};
