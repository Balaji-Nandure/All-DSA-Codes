/*
 * Problem: Pair Sum in a Sorted and Rotated Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/given-a-sorted-and-rotated-array-find-if-there-is-a-pair-with-a-given-sum/
 * Practice: https://practice.geeksforgeeks.org/problems/pair-sum-in-rotated-array/1
 * 
 * Given an array that is sorted and then rotated around an unknown point. 
 * Find if the array has a pair with a given sum 'x'. 
 * It may be assumed that all elements in the array are distinct.
 * 
 * Example 1:
 * Input: arr[] = {11, 15, 6, 8, 9, 10}, x = 16
 * Output: true
 * Explanation: There is a pair (6, 10) with sum 16
 * 
 * Example 2:
 * Input: arr[] = {11, 15, 26, 38, 9, 10}, x = 35
 * Output: true
 * Explanation: There is a pair (26, 9) with sum 35
 * 
 * Example 3:
 * Input: arr[] = {11, 15, 26, 38, 9, 10}, x = 45
 * Output: false
 * Explanation: No pair exists with sum 45
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - 1 <= arr[i] <= 10^6
 * - 1 <= x <= 10^6
 * - All elements are distinct
 * 
 * Approach:
 * - Method 1: Two Pointers with Modular Arithmetic (Optimal) - O(n) time, O(1) space
 *   Find pivot point, then use two pointers starting from pivot and pivot-1
 *   Use modular arithmetic to wrap around the array
 * 
 * - Method 2: Hash Map - O(n) time, O(n) space
 *   Works regardless of rotation, similar to regular two sum
 * 
 * - Method 3: Brute Force - O(n^2) time, O(1) space
 * 
 * Time: O(n) - two pointers with pivot (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;
bool pairInSortedRotated(vector<int>& arr, int target) {
    /*
    Approach:
    1. Find the index of the maximum element (pivot) where rotation happens.
    2. Set two pointers:
       - left  = (pivot + 1) % n   → smallest element
       - right = pivot             → largest element
    3. While left != right:
       - If arr[left] + arr[right] == target → return true
       - If sum < target → move left forward (circularly)
       - If sum > target → move right backward (circularly)
    4. If pointers meet and no pair found → return false

    Time: O(n)
    Space: O(1)
    */

    int n = arr.size();
    if (n < 2) return false;

    // Step 1: find pivot (max element index)
    int pivot = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            pivot = i;
            break;
        }
    }

    // Step 2: initialize two pointers
    int left = (pivot + 1) % n; // smallest
    int right = pivot;          // largest

    // Step 3: circular two-pointer search
    while (left != right) {
        int sum = arr[left] + arr[right];

        if (sum == target) {
            return true;
        }
        else if (sum < target) {
            left = (left + 1) % n;
        }
        else {
            right = (right - 1 + n) % n;
        }
    }

    return false;
}
