/*
 * Problem: Bitonic Point - Maximum in Increasing Decreasing Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-the-maximum-element-in-an-increasing-and-decreasing-array/
 * Practice: https://practice.geeksforgeeks.org/problems/maximum-value-in-a-bitonic-array3001/1
 *
 * Given a bitonic sequence (an array that increases and then decreases),
 * find the maximum element.
 * Examples:
 *   Input: arr[] = {1, 3, 8, 12, 4, 2}
 *   Output: 12
 *   Input: arr[] = {10, 20, 30, 40, 50}
 *   Output: 50
 *   Input: arr[] = {120, 100, 80, 20, 0}
 *   Output: 120
 *
 * Constraints:
 * - 1 <= n <= 10^6
 * - 1 <= arr[i] <= 10^9
 *
 * Approaches:
 * 1. Naive: Linear search for max
 * 2. Optimal: Binary search for bitonic point (maximum)
 */

#include <bits/stdc++.h>
using namespace std;

// Naive Approach: Linear Search - O(n) time, O(1) space
int findBitonicPointNaive(vector<int>& arr) {
    int n = arr.size();
    int maxi = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxi)
            maxi = arr[i];
    }
    return maxi;
}

// Binary Search Approach: O(log n) time, O(1) space
int findMaximum(vector<int> &arr) {
    // code here
    int n = arr.size();
    int left = 0, right = n - 1;
    
    while(left <= right){
        int mid = left + (right - left) / 2;
        int prev, next;
        
        if(mid == 0) prev = INT_MIN;
        else prev = arr[mid - 1];
        
        if(mid == n - 1) next = INT_MIN;
        else next = arr[mid + 1];
        
        if(arr[mid] > prev && arr[mid] > next){
            return arr[mid];
        } else if(prev < arr[mid] && arr[mid] < next){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
    
}
