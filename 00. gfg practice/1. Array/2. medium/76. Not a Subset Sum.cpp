/*
Problem: Not a Subset Sum

GFG: https://www.geeksforgeeks.org/problems/smallest-positive-number-missing-from-subset-sum/1

Description:
Given a array arr[] of positive integers, find the smallest positive integer such that it cannot be represented as the sum of elements of any subset of the given array set.

Examples:

Input: arr[] = [3, 1, 2]
Output: 7
Explanation: 7 is the smallest positive number for which no subset is there with sum 7.

Input: arr[] = [3, 10, 9, 6, 20, 28]
Output: 1
Explanation: 1 is the smallest positive number for which no subset is there with sum 1.

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^3

Approach (Greedy - Range Expansion):
1. Sort array
2. Maintain variable "reachable" = smallest value we CANNOT form yet
3. Initially reachable = 1 (means we can form [0, reachable-1] = [0,0])
4. Traverse elements:
   - If x > reachable → gap found → answer = reachable
   - Else → extend range: reachable += x

Why it works:
- If we can make all values up to (reachable - 1)
- And next number x ≤ reachable
- Then we can now make up to: reachable + x - 1
- This greedy approach ensures we find the smallest gap

Time Complexity: O(n log n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long smallestNotRepresentable(vector<int>& arr) {
        
        sort(arr.begin(), arr.end());
        
        long long reachable = 1;  // smallest missing sum
        
        for (int x : arr) {
            
            // If gap found
            if (x > reachable) {
                return reachable;
            }
            
            // Extend reachable range
            reachable += x;
        }
        
        return reachable;
    }
};
