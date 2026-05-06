/*
Problem: Flip to Maximize 1s

GFG: https://www.geeksforgeeks.org/problems/flip-bits-to-maximize-ones0952/1

Description:
Given an array arr[] consisting of 0's and 1's. A flip operation involves changing all 0's to 1's and all 1's to 0's within a contiguous subarray. Formally, select a range (l, r) in array arr[], such that (0 ≤ l ≤ r < n) holds and flip elements in this range.

Return maximum number of 1's you can get in array after doing at most 1 flip operation.

Examples:

Input: arr[] = [1, 0, 0, 1, 0]
Output: 4
Explanation: By flipping subarray from index 1 to 2, array becomes [1, 1, 1, 1, 0]. This results in a total of 4 ones, which is maximum possible after at most one flip.

Input: arr[] = [1, 0, 0, 1, 0, 0, 1]
Output: 6
Explanation: By flipping subarray from index 1 to 5, array becomes [1, 1, 1, 0, 1, 1, 1]. This results in a total of 6 ones, which is maximum possible after at most one flip.

Constraints:
1 ≤ n ≤ 10^6
0 ≤ arr[i] ≤ 1

Approach (Kadane's Algorithm):
Since flipping:
- 0 -> increases ones by +1
- 1 -> decreases ones by -1

Transform problem into finding subarray with maximum gain:

1. Count total existing 1s
2. Convert array:
   0 -> +1 (gain)
   1 -> -1 (loss)
3. Find maximum subarray sum using Kadane's algorithm
4. Answer = totalOnes + maxGain

Edge case: If all 1s, maxGain will be negative, so we use max(0, kadane)

Why it works:
- Kadane finds the subarray with maximum sum
- This sum represents the maximum gain from flipping
- Adding to existing ones gives final answer

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOnes(vector<int>& arr) {
        
        int ones = 0;
        for(int x : arr) if(x) ones++;
        
        int curr = 0;
        int maxGain = 0;
        
        for(int x : arr){
            int val = x == 0 ? 1 : -1;
            
            curr = max(val, curr + val);
            maxGain = max(maxGain, curr);
        }
        
        return ones + max(maxGain, 0);
    }
};
