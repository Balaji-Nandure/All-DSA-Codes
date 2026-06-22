/*
GeeksforGeeks: Substring with Max Zero-One Diff
Difficulty: Medium

Problem:
Given a binary string s consisting of 0s and 1s. Find the maximum difference of the number of 0s and the number of 1s 
(number of 0s - number of 1s) in a substring of the string.
Note: In the case of all 1s, the answer will be -1.

Examples:
Input : s = "11000010001" 
Output : 6 
Explanation: From index 2 to index 9, there are 7 0s and 1 1s, so number of 0s - number of 1s is 6. 

Input: s = "111111"
Output: -1

Constraints:
1 <= s.length() <= 10^5

DP State Design:
- We can convert character '0' to +1 (positive impact) and '1' to -1 (negative impact).
- The problem is then reduced to finding the maximum sum of a non-empty subarray (Kadane's Algorithm).
- Let dp[i] represent the maximum subarray sum ending at index i.
- Recurrence: dp[i] = max(val[i], val[i] + dp[i-1]) where val[i] = (s[i] == '0') ? 1 : -1.
- The overall answer is the maximum of dp[i] over all 0 <= i < n.

Time Complexity: O(N) where N is the length of string s.
Space Complexity: O(N) for top-down/tabulation, optimized to O(1) space.

GFG Link: https://www.geeksforgeeks.org/problems/substring-with-maximum-difference-of-0s-and-1s2035/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 4. Space Optimized (Bottom-Up DP with O(1) space)
// TC: O(N), SC: O(1) space optimization (Standard Kadane's Algorithm)
class Solution {
public:
    int maxSubstring(string s) {
        int n = s.size();
        if (n == 0) return 0;
        
        // We only need the max sum ending at the previous position (prev) 
        // to compute the max sum ending at the current position.
        int prev = (s[0] == '0') ? 1 : -1;
        int max_diff = prev;
        
        for (int i = 1; i < n; i++) {
            int val = (s[i] == '0') ? 1 : -1;
            int curr = max(val, val + prev);
            max_diff = max(max_diff, curr);
            prev = curr;
        }
        
        return max_diff;
    }
};

/*
Dry Run — Example:
s = "11000010001"
n = 11

1. Initialize prev = (s[0] == '0') ? 1 : -1 = -1
   max_diff = -1

2. Loop i = 1 to 10:
   - i = 1 (s[1] = '1' -> val = -1):
     curr = max(-1, -1 + -1) = -1
     max_diff = max(-1, -1) = -1
     prev = -1
   - i = 2 (s[2] = '0' -> val = 1):
     curr = max(1, 1 + -1) = 1
     max_diff = max(-1, 1) = 1
     prev = 1
   - i = 3 (s[3] = '0' -> val = 1):
     curr = max(1, 1 + 1) = 2
     max_diff = max(1, 2) = 2
     prev = 2
   - i = 4 (s[4] = '0' -> val = 1):
     curr = max(1, 1 + 2) = 3
     max_diff = max(2, 3) = 3
     prev = 3
   - i = 5 (s[5] = '0' -> val = 1):
     curr = max(1, 1 + 3) = 4
     max_diff = max(3, 4) = 4
     prev = 4
   - i = 6 (s[6] = '1' -> val = -1):
     curr = max(-1, -1 + 4) = 3
     max_diff = max(4, 3) = 4
     prev = 3
   - i = 7 (s[7] = '0' -> val = 1):
     curr = max(1, 1 + 3) = 4
     max_diff = max(4, 4) = 4
     prev = 4
   - i = 8 (s[8] = '0' -> val = 1):
     curr = max(1, 1 + 4) = 5
     max_diff = max(4, 5) = 5
     prev = 5
   - i = 9 (s[9] = '0' -> val = 1):
     curr = max(1, 1 + 5) = 6
     max_diff = max(5, 6) = 6
     prev = 6
   - i = 10 (s[10] = '1' -> val = -1):
     curr = max(-1, -1 + 6) = 5
     max_diff = max(6, 5) = 6
     prev = 5

Returns max_diff = 6.
Output: 6
*/
