/*
 * Problem: Stable Sort and Position
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/stable-sort-and-position/0
 * 
 * Given an array arr[] of integers that may contain duplicate elements, and an index k (0-based).
 * The task is to find the final position of the element at index k after stable sort is applied.
 * 
 * Stable sort: Elements with equal values maintain their relative order from the original array.
 * 
 * Examples:
 * Input: arr[] = [3, 4, 3, 5, 2, 3, 4, 3, 1, 5], k = 5
 * Output: 4
 * Explanation: Element at index 5 is 3. After stable sort: [1, 2, 3, 3, 3, 3, 4, 4, 5, 5].
 *              The 3 at index 5 ends up at position 4 (0-indexed).
 * 
 * Input: arr[] = [3, 4, 3, 5, 2, 3, 4, 3, 1, 5], k = 2
 * Output: 3
 * Explanation: Element at index 2 is 3. After stable sort, it ends up at position 3.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - In a stable sort, the final position of arr[k] depends on:
 *   1. Count of elements with value strictly less than arr[k] (all come before arr[k])
 *   2. Count of elements with value equal to arr[k] and index < k (same value, but came before in original order)
 * - Final position = (count of elements < arr[k]) + (count of elements == arr[k] with index < k)
 * - Single pass through the array to compute both counts
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getIndex(vector<int>& arr, int k) {
        int n = arr.size();
        int val = arr[k];
        
        int lessCount = 0;
        int equalBeforeCount = 0;
        
        for (int i = 0; i < n; i++) {
            if (arr[i] < val) {
                lessCount++;
            } else if (arr[i] == val && i < k) {
                equalBeforeCount++;
            }
        }
        
        return lessCount + equalBeforeCount;
    }
};
