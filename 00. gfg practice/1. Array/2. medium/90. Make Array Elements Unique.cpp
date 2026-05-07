/*
Problem: Make Array Elements Unique

GFG: https://www.geeksforgeeks.org/problems/make-array-elements-unique--170645/1

Description:
Given an integer array arr[ ], your task is to find the minimum number of increment operations required to make all the array elements unique. i.e. no value in the array should occur more than once. In one operation, a value can be incremented by 1 only.

Examples:

Input: arr[] = [3, 2, 1, 2, 1, 7]
Output: 6
Explanation: After 6 moves, the array could be [3, 4, 1, 2, 5, 7]. It can be shown that it is impossible for the array to have All unique values with 5 or less operations.

Input: arr[] = [1, 2, 2]
Output: 1
Explanation: After one operation [2 -> 3], the array could be [1, 2, 3].

Input: arr[] = [5, 4, 3, 2, 1]
Output: 0
Explanation: All elements are unique.

Constraints:
1 ≤ arr.size() ≤ 10^6
0 ≤ arr[i] ≤ 10^6

Approach (Greedy + Sorting):
Since we can only increment elements, we should sort and process duplicates greedily.

Key insight: After sorting, duplicates become adjacent. To minimize operations, make each element just one more than the previous.

Algorithm:
1. Sort array
2. Traverse from left to right
3. If current element <= previous element:
   operations += (previous + 1) - current
   current = previous + 1
4. Else: keep current as is

Why it works:
- Sorting ensures duplicates are adjacent
- Greedy approach makes each element the minimum valid value
- Each increment operation is used efficiently

Time Complexity: O(n log n)
Space Complexity: O(1) // ignoring sorting space
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minIncrements(vector<int>& arr) {
        
        sort(arr.begin(), arr.end());
        
        long long operations = 0;
        
        for (int i = 1; i < arr.size(); i++) {
            
            // Duplicate or smaller
            if (arr[i] <= arr[i - 1]) {
                
                int required = arr[i - 1] + 1;
                
                operations += (required - arr[i]);
                
                arr[i] = required;
            }
        }
        
        return operations;
    }
};
