/*
Problem: Subarrays with Equal 1s and 0s

GFG: https://www.geeksforgeeks.org/problems/count-subarrays-with-equal-number-of-1s-and-0s4051/1

Description:
Given an array arr[] containing 0s and 1s. Count the number of subarrays having equal number of 0s and 1s.

Examples:

Input: arr[] = [1, 0, 0, 1, 0, 1, 1]
Output: 8
Explanation: The index range for the 8 sub-arrays are: (0, 1), (2, 3), (0, 3), (3, 4), (4, 5) ,(2, 5), (0, 5), (1, 6)

Input: arr[] = [1, 1, 1, 1, 0]
Output: 1
Explanation: The index range for the subarray is (3,4).

Constraints:
1 ≤ arr.size() ≤ 10^5
0 ≤ arr[i] ≤ 1

Approach (Prefix Sum + HashMap):
Key insight: Equal number of 0s and 1s means count(1) - count(0) = 0

Transformation trick:
- Convert 0 → -1
- Convert 1 → +1

Now problem becomes: Count subarrays with SUM = 0

Algorithm:
1. Transform array: 0 → -1, 1 → +1
2. Maintain prefix sum and hashmap of frequencies
3. If current prefix sum seen before, add its frequency to answer
4. Initialize freq[0] = 1 for subarrays starting from index 0

Why it works:
- If prefix sum repeats, subarray between those positions has sum 0
- Frequency counts how many previous positions had same prefix sum
- Each repetition creates that many zero-sum subarrays

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countSubarrWithEqualZeroAndOne(vector<int>& arr, int n) {
        
        unordered_map<int, int> freq;
        
        freq[0] = 1;
        
        int prefixSum = 0;
        
        long long ans = 0;
        
        for (int x : arr) {
            
            // Transform
            if (x == 0) {
                prefixSum += -1;
            } else {
                prefixSum += 1;
            }
            
            // If seen before
            if (freq.count(prefixSum)) {
                ans += freq[prefixSum];
            }
            
            freq[prefixSum]++;
        }
        
        return ans;
    }
};
