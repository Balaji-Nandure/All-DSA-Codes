/*
 * Problem: Search in an Almost Sorted Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/search-almost-sorted-array/
 * Practice: https://practice.geeksforgeeks.org/problems/search-in-an-almost-sorted-array/1
 * 
 * Given an array which is sorted, but after sorting some elements are moved to either 
 * of the adjacent positions, i.e., arr[i] may be present at arr[i+1] or arr[i-1]. 
 * Write an efficient function to search an element in this array. 
 * Basically the element arr[i] can only be swapped with either arr[i+1] or arr[i-1].
 * 
 * Example 1:
 * Input: arr[] = {10, 3, 40, 20, 50, 80, 70}, key = 40
 * Output: 2
 * Explanation: 40 is present at index 2
 * 
 * Example 2:
 * Input: arr[] = {10, 3, 40, 20, 50, 80, 70}, key = 90
 * Output: -1
 * Explanation: 90 is not present
 * 
 * Example 3:
 * Input: arr[] = {2, 1, 3, 5, 4, 7, 6, 8, 9}, key = 5
 * Output: 3
 * Explanation: 5 is present at index 3
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - 1 <= arr[i] <= 10^6
 * - 1 <= key <= 10^6
 * 
 * Approach:
 * - Optimal: Modified Binary Search (O(log n) Time, O(1) Space)
 *   Since each element can be at most one position away from its correct position,
 *   we need to check arr[mid-1], arr[mid], and arr[mid+1] when comparing with target.
 *   Then we can eliminate half of the array based on comparisons.
 * 
 * - Method 2: Linear Search - O(n) Time, O(1) Space
 *   Traverse array and check each position and adjacent positions
 * 
 * Time: O(log n) - modified binary search (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

int searchAlmostSorted(vector<int>& arr, int target) {
    /*
    Approach:
    1. Do binary search.
    2. At mid, check:
       - arr[mid]
       - arr[mid - 1]
       - arr[mid + 1]
    3. If found → return index.
    4. Else:
       - If arr[mid] < target → left = mid + 2
       - Else → right = mid - 2

    Time: O(log n)
    Space: O(1)
    */

    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;

        if (mid - 1 >= left && arr[mid - 1] == target)
            return mid - 1;

        if (mid + 1 <= right && arr[mid + 1] == target)
            return mid + 1;

        if (arr[mid] < target) {
            left = mid + 2;
        } else {
            right = mid - 2;
        }
    }

    return -1;
}
