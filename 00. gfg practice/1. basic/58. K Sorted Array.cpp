/*
 * Problem: K Sorted Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/k-sorted-array1610/1
 * 
 * Given an array of n distinct elements. Check whether the given array is a 
 * k-sorted array or not. A k-sorted array is an array where each element is 
 * at most k distance away from its target position in the sorted array.
 * Return "Yes" if the array is a k-sorted array else return "No".
 * 
 * Examples:
 * Input: n=6, arr[] = {3, 2, 1, 5, 6, 4}, k = 2
 * Output: Yes
 * Explanation: Every element is at most 2 distance away from its target 
 * position in the sorted array.
 * 
 * Input: n=7, arr[] = {13, 8, 10, 7, 15, 14, 12}, k = 1
 * Output: No
 * Explanation: Elements are more than 1 distance away from their sorted positions.
 * 
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 0 ≤ k ≤ n
 * 
 * Expected Time Complexity: O(nlogn)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Copy the array and sort it to get target positions
 * - Use hashmap to store sorted index of each element
 * - For each element in original array, check if distance from its 
 *   current position to sorted position is ≤ k
 * - If any element violates this condition, return "No"
 * - If all elements satisfy the condition, return "Yes"
 * 
 * Time: O(n log n) - sorting dominates
 * Space: O(n) - for sorted array and hashmap
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    string isKSortedArray(int arr[], int n, int k) {
        
        // Step 1: Copy array
        vector<int> sorted(arr, arr + n);
        
        // Step 2: Sort the copied array
        sort(sorted.begin(), sorted.end());
        
        // Step 3: Store sorted positions using hashmap
        unordered_map<int, int> pos;
        
        for(int i = 0; i < n; i++) {
            pos[sorted[i]] = i;
        }
        
        // Step 4: Check distance for each element
        for(int i = 0; i < n; i++) {
            int distance = abs(i - pos[arr[i]]);
            if(distance > k) {
                return "No";
            }
        }
        
        return "Yes";
    }
};