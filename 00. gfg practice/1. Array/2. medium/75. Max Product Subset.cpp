/*
Problem: Max Product Subset

GFG: https://www.geeksforgeeks.org/problems/max-product-subset/1

Description:
Given an array arr. The task is to find and return the maximum product possible with a subset of elements present in the array.

Note:
The maximum product can be of a single element also.
Since the product can be large, return it modulo 10^9 + 7.

Examples:

Input: arr[] = [-1, 0, -2, 4, 3]
Output: 24
Explanation: Maximum product will be (-1 * -2 * 4 * 3) = 24

Input: arr[] = [-1, 0]
Output: 0
Explanation: Maximum product will be (-1 * 0) = 0

Input: arr[] = [5]
Output: 5
Explanation: Maximum product will be 5.

Constraints:
1 ≤ arr.size() ≤ 2 * 10^4
-10 ≤ arr[i] ≤ 10

Approach (Greedy - Sign-based selection):

Case 1: Only one element → return it

Case 2: No positives & no valid negative pair:
- If zero exists → return 0
- Else → return max negative

Case 3: General:
- Multiply all positives
- Multiply negatives (skip one smallest abs if odd count)

Why it works:
- Positive numbers always increase product when multiplied
- Negative numbers: pair of negatives gives positive product
- If odd number of negatives, remove the one with smallest absolute value
- Zeroes are handled as special case to avoid zero product

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProductSubset(vector<int>& arr) {
        
        const int MOD = 1e9 + 7;
        
        int n = arr.size();
        
        // Edge case: single element
        if (n == 1) return arr[0];
        
        long long product = 1;
        
        int countNeg = 0;
        int countZero = 0;
        
        int maxNeg = INT_MIN;   // largest negative (closest to zero)
        
        for (int x : arr) {
            
            if (x == 0) {
                countZero++;
                continue;
            }
            
            if (x < 0) {
                countNeg++;
                maxNeg = max(maxNeg, x);
            }
            
            product = (product * x) % MOD;
        }
        
        // If all zeros
        if (countZero == n) return 0;
        
        // If odd negatives → remove one (the least harmful)
        if (countNeg % 2 == 1) {
            
            // Special case: only one negative and rest zeros
            if (countNeg == 1 && countZero + countNeg == n) {
                return 0;
            }
            
            // Divide by maxNeg (remove smallest absolute negative)
            product = product / maxNeg;
        }
        
        // Make positive modulo
        if (product < 0) product = (product + MOD) % MOD;
        
        return product;
    }
};
