/*
Problem: Pair Sum Closest to 0

GFG: https://www.geeksforgeeks.org/problems/pair-sum-closest-to-zero/1

Description:
Given an integer array of n elements. You need to find the maximum sum of two elements such that sum is closest to zero.

Examples:

Input: arr[] = [-8 -66 -60]
Output: -68
Explanation: Sum of two elements closest to zero is -68 using numbers -60 and -8.

Input: arr[] = [-21 -67 -37 -18 4 -65]
Output: -14
Explanation: Sum of two elements closest to zero is -14 using numbers -18 and 4.

Constraints:
2 ≤ n ≤ 5 * 10^5
-10^6 ≤ arr[i] ≤ 10^6

Approach (Sorting + Two Pointer):
1. Sort array
2. left = 0, right = n-1
3. Track best answer (closest to 0)

4. While left < right:
   sum = arr[left] + arr[right]
   
   Update answer if:
      abs(sum) < abs(best)
   
   Move pointers:
      if sum < 0 → left++ (need bigger sum)
      else → right-- (need smaller sum)

Why it works:
- After sorting, left points to smallest, right to largest
- Two-pointer technique explores all possible pairs efficiently
- Moving pointers based on sum sign ensures we move toward zero
- Guarantees we find pair with sum closest to zero

Time Complexity: O(n log n) → sorting
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int closestToZero(vector<int>& arr) {
    
        int n = arr.size();
        
        sort(arr.begin(), arr.end());
        
        int left = 0;
        int right = n - 1;
        
        int best = INT_MAX;
        
        while (left < right) {
            
            int sum = arr[left] + arr[right];
            
            // Update if closer to zero
            if (abs(sum) < abs(best)) {
                best = sum;
            }
            else if (abs(sum) == abs(best)) {
                best = max(best, sum);   // tie → take maximum
            }
            
            // Move pointers
            if (sum < 0) {
                left++;   // need bigger sum
            } else {
                right--;  // need smaller sum
            }
        }
        
        return best;
    }
};
