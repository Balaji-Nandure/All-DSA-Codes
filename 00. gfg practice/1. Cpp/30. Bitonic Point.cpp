/*
 * Problem: Bitonic Point
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/bitonic-point/0
 * 
 * Given an array of integers arr[] that is first strictly increasing and then 
 * maybe strictly decreasing, find the bitonic point, that is, the maximum element 
 * in the array. Bitonic Point is a point before which elements are 
 * strictly increasing and after which elements are strictly decreasing.
 * 
 * Note: It is guaranteed that the array contains exactly one bitonic point.
 * 
 * Examples:
 * Input: arr[] = [1, 2, 4, 5, 7, 8, 3]
 * Output: 8
 * Explanation: Elements before 8 are strictly increasing [1, 2, 4, 5, 7] 
 *              and elements after 8 are strictly decreasing [3].
 * 
 * Input: arr[] = [10, 20, 30, 40, 50]
 * Output: 50
 * Explanation: Elements before 50 are strictly increasing [10, 20, 30 40] 
 *              and there are no elements after 50.
 * 
 * Input: arr[] = [120, 100, 80, 20, 0]
 * Output: 120
 * Explanation: There are no elements before 120 and elements after 120 
 *              are strictly decreasing [100, 80, 20, 0].
 * 
 * Constraints:
 * 3 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use binary search to find the bitonic point efficiently
 * - The bitonic point is where the array transitions from increasing to decreasing
 * - Use two pointers (low, high) and check slope at each step
 * - If arr[mid] < arr[mid+1]: still in increasing slope, peak on right side
 * - Else: in decreasing slope, peak is at mid or left side
 * - Continue until low == high, then arr[low] is the bitonic point
 * 
 * Time: O(log n) - binary search for the peak
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findBitonicPoint(vector<int>& arr) {
        int n = arr.size();
        
        int low = 0;
        int high = n - 1;
        
        while (low < high) {
            int mid = low + (high - low) / 2;
            
            // If mid element is smaller than next element,
            // we are in increasing slope.
            // So peak lies on right side.
            if (arr[mid] < arr[mid + 1]) {
                low = mid + 1;
            }
            // Else we are in decreasing slope,
            // so peak is at mid or left side.
            else {
                high = mid;
            }
        }
        
        // low == high → peak index
        return arr[low];
    }
};
