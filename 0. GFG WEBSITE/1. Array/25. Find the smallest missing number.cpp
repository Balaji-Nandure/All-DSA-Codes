/*
 * Problem: Find the Smallest Missing Number in Sorted Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-the-first-missing-number/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/smallest-number-missing-from-unsorted-array/1
 * 
 * Given a sorted array of n distinct integers where each integer is in the 
 * range from 0 to m-1 and m > n. Find the smallest number that is missing from the array.
 * 
 * Example 1:
 * Input: arr[] = {0, 1, 2, 6, 9}, n = 5, m = 10
 * Output: 3
 * Explanation: The smallest missing number is 3
 * 
 * Example 2:
 * Input: arr[] = {4, 5, 10, 11}, n = 4, m = 12
 * Output: 0
 * Explanation: The smallest missing number is 0
 * 
 * Example 3:
 * Input: arr[] = {0, 1, 2, 3}, n = 4, m = 5
 * Output: 4
 * Explanation: All numbers 0 to 3 are present, so 4 is missing
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - n < m <= 10^6
 * - 0 <= arr[i] < m
 * - Array is sorted
 * 
 * Approach:
 * - Method 1: Binary Search (Optimal for sorted) - O(log n) time, O(1) space
 *   Use binary search to find first index where arr[i] != i
 *   If arr[i] == i, missing number is in right half
 *   If arr[i] > i, missing number is in left half or at current position
 * 
 * - Method 2: Linear Search - O(n) time, O(1) space
 *   Traverse array and find first index where arr[i] != i
 * 
 * - Method 3: Hash Set - O(n) time, O(n) space
 *   Store all numbers in set, check from 0 to m-1
 * 
 * Time: O(log n) - binary search (optimal for sorted array)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Binary Search (Optimal for sorted array) - O(log n) time, O(1) space
    /*
     * Binary Search to Find the Smallest Missing Number
     * DRY RUN EXAMPLE:
     * Let arr = {0, 1, 2, 6, 9}, n = 5, m = 10
     * We want to find the smallest missing number.
     * 
     * Step 1: arr[0] == 0 → proceed.
     * Step 2: Initialize left = 0, right = 4
     * 
     *       | left=0 | right=4
     * Iter1: mid = (0+4)/2 = 2, arr[2]=2, 2==2 ⇒ left=mid+1=3
     *       | left=3 | right=4
     * Iter2: mid = (3+4)/2 = 3, arr[3]=6, 6!=3 ⇒ right=mid-1=2
     * Now: left=3, right=2 → loop ends.
     * 
     * Since left=3<n, smallest missing number is 3.
     * 
     * Example 2: arr={4,5,10,11}, n=4, m=12
     * Step 1: arr[0]=4≠0 ⇒ return 0
     * 
     * Example 3: arr={0,1,2,3}, n=4, m=5
     * Step 1: arr[0]=0
     * left=0, right=3
     * mid=1, arr[1]=1→left=2
     * mid=2, arr[2]=2→left=3
     * mid=3, arr[3]=3→left=4
     * left=4==n→all present, return 4
     */

    int findSmallestMissing(vector<int>& arr, int n, int m) {
        // If first element is not 0, return 0
        if (arr[0] != 0) {
            return 0;
        }
        
        // Binary search for first missing number
        int left = 0, right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // If arr[mid] == mid, all numbers from 0 to mid are present
            // Missing number is in right half
            if (arr[mid] == mid) {
                left = mid + 1;
            } else {
                // arr[mid] > mid, missing number is at mid or in left half
                right = mid - 1;
            }
        }
        
        // left is the first index where arr[i] != i
        // If left < n, missing number is left
        // If left == n, all numbers 0 to n-1 are present, missing is n (if n < m)
        return left;
    }

};