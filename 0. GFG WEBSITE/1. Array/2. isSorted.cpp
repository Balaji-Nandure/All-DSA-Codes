/*
 * Problem: Check if Array is Sorted
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/program-check-array-sorted-not-iterative-recursive/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/check-if-an-array-is-sorted/1
 * 
 * Given an array arr[] of size N, check if it is sorted in non-decreasing order.
 * 
 * Example 1:
 * Input: N = 5, arr[] = {10, 20, 30, 40, 50}
 * Output: 1
 * Explanation: The given array is sorted.
 * 
 * Example 2:
 * Input: N = 6, arr[] = {90, 80, 100, 70, 40, 30}
 * Output: 0
 * Explanation: The given array is not sorted.
 * 
 * Constraints:
 * - 1 <= N <= 10^6
 * - 1 <= arr[i] <= 10^6
 * 
 * Approach:
 * - Traverse the array and check if each element is less than or equal to the next element
 * - If any element is greater than the next, array is not sorted
 * - For non-decreasing order: arr[i] <= arr[i+1] for all i
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

// APPROACH 1: Iterative (Optimal)
bool arraySortedOrNot(int arr[], int n) {
    // Array with 0 or 1 element is always sorted
    if (n == 0 || n == 1) {
        return true;
    }
    
    // Check if each element is <= next element
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    
    return true;
}

// APPROACH 2: Recursive
bool arraySortedOrNotRecursive(int arr[], int n) {
    // Base case: array with 0 or 1 element is sorted
    if (n == 0 || n == 1) {
        return true;
    }
    
    // Check if last two elements are in order
    if (arr[n - 2] > arr[n - 1]) {
        return false;
    }
    
    // Recursively check the rest
    return arraySortedOrNotRecursive(arr, n - 1);
}
