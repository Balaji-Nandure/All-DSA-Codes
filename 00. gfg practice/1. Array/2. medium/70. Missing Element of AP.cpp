/*
Problem: Missing Element of AP

GFG: https://www.geeksforgeeks.org/problems/missing-element-of-ap2328/1

Description:
Given a sorted array arr[] that represents an Arithmetic Progression (AP) with exactly one missing element, find the missing number.
The array arr[] is sorted in either ascending or descending order.

Note: An element will always exist that, upon inserting into a sequence forms Arithmetic progression. If the given sequence already forms a valid complete AP, return the (n+1)-th element that would come next in the sequence.

Examples:

Input: arr[] = [2, 4, 8, 10, 12, 14]
Output: 6
Explanation: Actual AP should be 2, 4, 6, 8, 10, 12, 14.

Input: arr[] = [1, 6, 11, 16, 21, 31]
Output: 26
Explanation: Actual AP should be 1, 6, 11, 16, 21, 26, 31.

Input: arr[] = [4, 7, 10, 13, 16]
Output: 19
Explanation: Since the sequence already forms a valid AP, the next element after 16 in the sequence would be 19. Therefore, the output is 19.

Constraints:
2 ≤ arr.size() ≤ 10^5
0 ≤ arr[i] ≤ 2*10^7

Approach (Binary Search):
1. Compute common difference:
   d = (arr[n-1] - arr[0]) / n

2. Binary search:
   - expected = arr[0] + mid * d
   - if equal → go right
   - else → go left

3. Answer = arr[0] + low * d

Why it works:
- In a complete AP, arr[i] = arr[0] + i * d
- If arr[mid] != expected, missing element is in left half
- If arr[mid] == expected, missing element is in right half
- Binary search finds the first position where arr[i] != expected
- The missing element is arr[0] + position * d

Time Complexity: O(log n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMissing(vector<int>& arr) {
        
        int n = arr.size();
        
        // 🔴 EDGE CASE: only 2 elements
        if (n == 2) {
            return arr[1] + (arr[1] - arr[0]);
        }
        
        // Step 1: Find correct common difference
        int d1 = arr[1] - arr[0];
        int d2 = arr[2] - arr[1];
        
        int d = abs(d1) < abs(d2) ? d1 : d2;
        
        int low = 0, high = n - 1;
        
        while (low <= high) {
            
            int mid = low + (high - low) / 2;
            
            int expected = arr[0] + mid * d;
            
            if (arr[mid] == expected) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        // Missing inside array
        if (low < n) {
            return arr[0] + low * d;
        }
        
        // No missing → return next element
        return arr[n - 1] + d;
    }
};
