/*
Problem: Peak Element

GFG: https://www.geeksforgeeks.org/find-a-peak-in-a-given-array/

Description: You are given an array arr[] where no two adjacent elements are same, find the index of a peak element. An element is considered to be a peak if it is greater than its adjacent elements (if they exist).

If there are multiple peak elements, Return index of any one of them. The output will be "true" if the index returned by your function is correct; otherwise, it will be "false".

Note: Consider the element before the first element and the element after the last element to be negative infinity.

Examples:

Input: arr = [1, 2, 4, 5, 7, 8, 3]
Output: true
Explanation: arr[5] = 8 is a peak element because arr[4] < arr[5] > arr[6].
Input: arr = [10, 20, 15, 2, 23, 90, 80]
Output: true
Explanation: Element 20 at index 1 is a peak since 10 < 20 > 15. Index 5 (value 90) is also a peak, but returning any one peak index is valid.

Constraints:
1 ≤ arr.size() ≤ 106
-231 ≤ arr[i] ≤ 231 - 1

Approach:
Binary Search:
We use Binary Search.
If mid element is smaller than right neighbor,
then peak must be on right side.
Else peak is on left side or mid itself.

Why this works:
Because array always has at least one peak.
If slope is increasing → peak on right
If slope is decreasing → peak on left

Algorithm:
1. Initialize low = 0, high = n-1
2. While low < high:
   - mid = low + (high - low) / 2
   - If arr[mid] < arr[mid+1]: low = mid + 1
   - Else: high = mid
3. Return low (or high, they are equal)

Time Complexity: O(log n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int peakElement(int arr[], int n) {
        int low = 0;
        int high = n - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            // If mid is smaller than next element
            // then peak lies on right side
            if (arr[mid] < arr[mid + 1]) {
                low = mid + 1;
            }
            else {
                // Peak is on left side or at mid
                high = mid;
            }
        }

        // low == high → peak index
        return low;
    }
};
