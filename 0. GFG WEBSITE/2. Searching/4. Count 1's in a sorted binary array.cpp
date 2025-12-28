/*
 * Problem: Count 1's in a sorted binary array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/count-1s-sorted-binary-array/
 * Practice: https://practice.geeksforgeeks.org/problems/count-1s-in-binary-array-1587115620/1
 * 
 * Given a binary array sorted in non-increasing order, count the number of 1's in it.
 * 
 * Example 1:
 * Input: arr[] = {1, 1, 1, 1, 1, 0, 0}
 * Output: 5
 * Explanation: There are 5 ones in the array
 * 
 * Example 2:
 * Input: arr[] = {1, 1, 0, 0, 0, 0, 0}
 * Output: 2
 * Explanation: There are 2 ones in the array
 * 
 * Example 3:
 * Input: arr[] = {0, 0, 0, 0, 0}
 * Output: 0
 * Explanation: No ones in the array
 * 
 * Constraints:
 * - 1 <= n <= 10^6
 * - arr[i] is either 0 or 1
 * - Array is sorted in non-increasing order (all 1's come before 0's)
 * 
 * Approach:
 * - Method 1: Binary Search (Optimal) - O(log n) time, O(1) space
 *   Find the first occurrence of 0, count = index of first 0
 *   Or find last occurrence of 1, count = last index of 1 + 1
 * 
 * - Method 2: Iterative Search - O(n) time, O(1) space
 *   Traverse array and count 1's until we encounter first 0
 * 
 * Time: O(log n) - binary search (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int countOnes(vector<int>& arr) {
        int n = arr.size();
        int l = 0, r = n - 1;
        
        while(l <= r){
            int mid = l + (r - l) / 2;
            if(arr[mid] == 0){
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        
        return l;
    }
};