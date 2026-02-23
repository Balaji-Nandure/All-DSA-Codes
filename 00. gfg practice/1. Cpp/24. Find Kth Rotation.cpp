/*
 * Problem: Find Kth Rotation
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/find-kth-rotation/0
 * 
 * Given an increasing sorted rotated array arr[] of distinct integers. The array is 
 * right-rotated k times. Find the value of k.
 * Let's suppose we have an array arr[] = [2, 4, 6, 9], if we rotate it by 2 times 
 * it will look like this:
 * After 1st Rotation : [9, 2, 4, 6]
 * After 2nd Rotation : [6, 9, 2, 4]
 * 
 * Examples:
 * Input: arr[] = [5, 1, 2, 3, 4]
 * Output: 1
 * Explanation: The given array is [5, 1, 2, 3, 4]. The original sorted array is [1, 2, 3, 4, 5]. 
 *              We can see that array was rotated 1 times to the right.
 * 
 * Input: arr = [1, 2, 3, 4, 5]
 * Output: 0
 * Explanation: The given array is not rotated.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^7
 * 
 * Expected Time Complexity: O(log n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Find the index of the minimum element in the array
 * - In a sorted rotated array, the minimum element is the pivot point
 * - The number of rotations equals the index of the minimum element
 * - This works because each right rotation moves the last element to front
 * - The minimum element's position indicates how many elements moved from end to front
 * - Use binary search to find minimum element in O(log n) time
 * 
 * Time: O(log n) - binary search for minimum element
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKRotation(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        
        int left = 0, right = n - 1;
        
        // If array is not rotated (already sorted)
        if (arr[left] <= arr[right]) {
            return 0;
        }
        
        // Binary search for minimum element
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int next = (mid + 1) % n;
            int prev = (mid - 1 + n) % n;
            
            // Check if mid is the minimum element
            if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
                return mid;
            }
            // Decide which half to search
            else if (arr[mid] <= arr[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return 0;
    }
};
