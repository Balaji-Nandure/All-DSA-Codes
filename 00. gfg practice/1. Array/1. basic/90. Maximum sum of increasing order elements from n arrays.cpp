/*
PROBLEM: Maximum sum of increasing order elements from n arrays

APPROACH:
1. Start from last row → pick maximum element
2. Move upwards:
   - From current row, pick largest element strictly less than previous chosen
3. Keep adding to sum
4. If at any row no valid element → return 0

WHY IT WORKS:
- Greedy choice: always take the maximum possible valid element
- Going backwards ensures maximum flexibility

TIME COMPLEXITY: O(N * M)
SPACE COMPLEXITY: O(1)

GFG:
https://www.geeksforgeeks.org/problems/maximum-sum-of-increasing-order-elements-from-n-arrays/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSum(int n, int m, vector<vector<int>> &a) {
        
        int prev = INT_MAX;   // previous selected value
        int sum = 0;
        
        // Traverse from last row to first
        for(int i = n - 1; i >= 0; i--) {
            
            int best = -1;
            
            // Find largest element < prev
            for(int j = 0; j < m; j++) {
                if(a[i][j] < prev) {
                    best = max(best, a[i][j]);
                }
            }
            
            // If no valid element found
            if(best == -1) return 0;
            
            sum += best;
            prev = best;  // update constraint
        }
        
        return sum;
    }
};
