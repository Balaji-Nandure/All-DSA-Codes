/*
PROBLEM: Minimum Energy (GFG)

Given an array arr[] with positive & negative values (energy gain/loss),
find minimum initial energy such that:
- Energy NEVER becomes <= 0 at any point
- Final answer >= 1

EXAMPLE:
arr = [4, -10, 4, 4, 4]
→ prefix sums: [4, -6, -2, 2, 6]
→ minimum prefix = -6
→ need at least 7 energy

APPROACH (Optimal - Prefix Sum Tracking)

Idea:
- Track running sum (prefix sum)
- Track minimum prefix encountered
- If minimum prefix = minSum
  → we need initial energy = (1 - minSum)

WHY IT WORKS:
- We ensure: initial + prefix >= 1
- Worst case is when prefix is minimum
- So: initial >= 1 - minPrefix

TIME COMPLEXITY: O(n)
SPACE COMPLEXITY: O(1)

GFG LINK: https://www.geeksforgeeks.org/problems/minimum-energy/
LEETCODE LINK: Similar → https://leetcode.com/problems/minimum-starting-value/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minEnergy(vector<int>& arr) {
        
        int prefixSum = 0;
        int minPrefix = 0;
        
        for(int x : arr){
            prefixSum += x;
            minPrefix = min(minPrefix, prefixSum);
        }
        
        // ensure energy never goes <= 0
        return max(1, 1 - minPrefix);
    }
};
