/*
Problem: Product Pair

GFG: https://www.geeksforgeeks.org/problems/product-pair/1

Description:
Given an integer array arr[] and an integer target, determine whether there exists a pair of elements in the array whose product is equal to target.

Return true if such a pair exists; otherwise, return false.

Examples:

Input: arr[] = [10, 20, 9, 40], target = 400
Output: true
Explanation: As 10 * 40 = 400, the answer is true.

Input: arr[] = [-10, 20, 9, -40], target = 30
Output: false
Explanation: No pair exists with product 30.

Input: arr[] = [-10, 0, 9, -40], target = 0
Output: true
Explanation: As -10 * 0 = 0, the answer is true.

Constraints:
2 ≤ arr.size() ≤ 10^5
-10^8 ≤ arr[i] ≤ 10^8
-10^18 ≤ target ≤ 10^18

Approach (Hashing + Complement Logic):
For every number x, we need another number: y = target / x

Cases:
1. x == 0:
   - if target == 0: any previous element forms pair
   - else: impossible

2. x != 0:
   - target must divide exactly by x
   - check whether target / x already exists

Why it works:
- Similar to Two Sum problem but with product
- Hashset provides O(1) lookup for complement
- Handles zero as special case to avoid division issues

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isProduct(vector<int>& arr, long long target) {
        
        unordered_set<long long> seen;
        
        for (long long x : arr) {
            
            // Special handling for zero
            if (x == 0) {
                
                // 0 * anything = 0
                if (target == 0 && !seen.empty()) {
                    return true;
                }
            }
            else {
                
                // target must divide exactly
                if (target % x == 0) {
                    
                    long long needed = target / x;
                    
                    if (seen.count(needed)) {
                        return true;
                    }
                }
            }
            
            seen.insert(x);
        }
        
        return false;
    }
};
