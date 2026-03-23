/*
Problem: Count increasing Subarrays

GFG: https://www.geeksforgeeks.org/problems/count-increasing-subarrays/1

Description: Given an array arr[] of integers, count the number of subarrays in arr[] which are strictly increasing with size greater or equal to 2. A subarray is a contiguous part of array. A subarray is strictly increasing if each element is greater then it's previous element if it exists.

Examples:

Input: arr[] = [1, 3, 3, 2, 3, 5]
Output: 4
Explanation: Increasing Subarrays are : arr[0,1], arr[3,4], arr[3,5], arr[4,5].
Input: arr[] = [1, 5] 
Output: 1
Explanation:The only Increasing Subarray is arr[0,1].

Constraints:
1 <= arr.size() <= 106
1 <= arri <= 107

Approach:
1. Track length of increasing streak
2. When streak breaks, add (len*(len-1))/2
3. Reset len = 1
4. Add last streak at end

Why it works:
- Each increasing streak contributes multiple subarrays

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countIncreasing(vector<int>& arr) {
        
        int n = arr.size();
        int curr = 0;
        long long ans = 0;
        for(int i = 1; i < n; i++){
            if(arr[i] > arr[i - 1]){
                curr++;
                ans += curr;
            } else {
                curr = 0;
            }
        }
        
        return ans;
    }
};
