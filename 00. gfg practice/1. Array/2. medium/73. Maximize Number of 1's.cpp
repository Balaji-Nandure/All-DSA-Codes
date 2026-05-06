/*
Problem: Maximize Number of 1's

GFG: https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1

Description:
Given a binary array arr[] containing only 0s and 1s and an integer k, you are allowed to flip at most k 0s to 1s. Find the maximum number of consecutive 1's that can be obtained in the array after performing the operation at most k times.

Examples:

Input: arr[] = [1, 0, 1], k = 1
Output: 3
Explanation: By flipping the zero at index 1, we get the longest subarray from index 0 to 2 containing all 1's.

Input: arr[] = [1, 0, 0, 1, 0, 1, 0, 1], k = 2
Output: 5
Explanation: By flipping the zeroes at indices 4 and 6, we get the longest subarray from index 3 to 7 containing all 1's.

Input: arr[] = [1, 1], k = 2
Output: 2
Explanation: Since the array is already having the max consecutive 1's, hence we dont need to perform any operation. Hence answer is 2.

Constraints:
1 ≤ arr.size() ≤ 10^5
0 ≤ k ≤ arr.size()
0 ≤ arr[i] ≤ 1

Approach (Sliding Window):
1. left = 0, zeros = 0
2. Iterate right from 0 → n-1
3. If arr[right] == 0 → zeros++
4. While zeros > k:
   if arr[left] == 0 → zeros--
   left++

5. Update max length:
   maxLen = max(maxLen, right - left + 1)

Why it works:
- Window always valid (≤ k zero flips)
- Maintains maximum window size with at most k zeros
- Expands right pointer greedily, shrinks left when needed
- Guarantees maximum consecutive 1's possible

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        int left = 0;
        int zeros = 0;
        int maxLen = 0;
        
        for (int right = 0; right < n; right++) {
            
            // Include current element
            if (arr[right] == 0) {
                zeros++;
            }
            
            // Shrink window if invalid
            while (zeros > k) {
                if (arr[left] == 0) {
                    zeros--;
                }
                left++;
            }
            
            // Update answer
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};
