/*
PROBLEM: Partitions with Given Difference

We need to partition array into two subsets S1 and S2 such that:
S1 - S2 = diff

MATHEMATICAL DERIVATION:
S1 - S2 = diff
S1 + S2 = totalSum
----------------------
2*S1 = totalSum + diff
S1 = (totalSum + diff) / 2

So the problem reduces to:
COUNT number of subsets with sum = (totalSum + diff)/2

This is a standard "Count Subsets with Given Sum" DP problem.

EDGE CASE:
If (totalSum + diff) is odd → return 0

APPROACH (DP):
dp[i][j] = number of ways to get sum j using first i elements

If we take element:
    dp[i][j] += dp[i-1][j - arr[i-1]]

If we don't take element:
    dp[i][j] += dp[i-1][j]

TIME COMPLEXITY: O(N * target)
SPACE COMPLEXITY: O(target)

GFG:
https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1
Visualizer (HTML, same folder): 24. partition-visualizer.html

Related:
https://leetcode.com/problems/target-sum/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPartitions(vector<int>& arr, int diff) {
        int n = arr.size();
        
        int totalSum = 0;
        for(int x : arr) totalSum += x;
        
        // Edge case
        if((totalSum + diff) % 2 != 0) return 0;
        
        int target = (totalSum + diff) / 2;
        
        // DP array
        vector<int> dp(target + 1, 0);
        
        dp[0] = 1; // One way to make sum 0
        
        for(int i = 0; i < n; i++){
            for(int j = target; j >= arr[i]; j--){
                // Meaning:
                // Number of ways to make sum j increases by number of ways to make sum (j - current element)
                dp[j] = dp[j] + dp[j - arr[i]];
            }
            
            // WHY WE LOOP BACKWARD (target → arr[i]) - CRITICAL DP CONCEPT
            // We are solving 0/1 Knapsack → each element can be used only once.
            // If we loop forward (arr[i] → target), the same element gets reused in the same iteration.
            // This becomes Unbounded Knapsack (infinite supply of each element).
            
            // PROOF BY EXAMPLE:
            // Array: arr = [1, 2], target = 3
            // Correct subsets: [1,2] → only 1 way
            
            // Case 1 - Backward Loop (Correct): for j = target → arr[i]
            // Start: dp = [1,0,0,0]
            // After processing 1: dp = [1,1,0,0]
            // After processing 2: dp[3] += dp[1] → 1, dp[2] += dp[0] → 1
            // Final: dp = [1,1,1,1], Answer = 1 ✅
            
            // Case 2 - Forward Loop (Wrong): for j = arr[i] → target
            // After processing 1:
            // dp[1] = 1
            // dp[2] = dp[1] = 1   ← reused same 1 again ❌
            // dp[3] = dp[2] = 1   ← reused again ❌
            // This means we used 1 multiple times, which violates 0/1 constraint.
        }
        
        return dp[target];
    }
};


