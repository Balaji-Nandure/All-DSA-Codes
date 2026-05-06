/*
Problem: Unique Number III

GFG: https://www.geeksforgeeks.org/problems/finding-the-numbers0215/1

Description:
Given an array of integers arr[] where, every element appears thrice except for one which occurs once.
Find that element which occurs once.

Examples:

Input: arr[] = [1, 10, 1, 1]
Output: 10
Explanation: 10 occurs once in the array while the other element 1 occurs thrice.

Input: arr[] = [3, 2, 1, 34, 34, 1, 2, 34, 2, 1]
Output: 3
Explanation: All elements except 3 occurs thrice in the array.

Constraints:
1 ≤ arr.size() ≤ 10^5
arr.size() % 3 = 1
-10^9 ≤ arr[i] ≤ 10^9

Approach (Bit Manipulation):
Since every number appears exactly 3 times except one, we can use bit properties.

Key insight: For each bit position, if a number appears 3 times, its bits contribute multiples of 3. Only the unique number contributes a remainder.

Algorithm:
For each bit from 0 to 31:
1. Count how many numbers have that bit set
2. If count % 3 != 0, set that bit in answer

Why it works:
- Triplicated numbers contribute multiples of 3 to bit counts
- Only unique number leaves remainder when count % 3 != 0
- Works for negative numbers too (using signed bit operations)

Time Complexity: O(32 * n) ≈ O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getSingle(vector<int>& arr) {
        
        int ans = 0;
        
        // Check all 32 bits
        for (int bit = 0; bit < 32; bit++) {
            
            int count = 0;
            
            // Count set bits at current position
            for (int num : arr) {
                
                if ((num >> bit) & 1) {
                    count++;
                }
            }
            
            // Unique number contributes remainder
            if (count % 3 != 0) {
                ans |= (1LL << bit);
            }
        }
        
        return ans;
    }
};
