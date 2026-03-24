/*
Problem: Maximum Product Subarray

GFG: https://www.geeksforgeeks.org/maximum-product-subarray/

Description: Given an array arr[] that contains positive and negative integers (may contain 0 as well). Find the maximum product that we can get in a subarray of arr[].

Note: It is guaranteed that the answer fits in a 32-bit integer.

Examples:

Input: arr[] = [-2, 6, -3, -10, 0, 2]
Output: 180
Explanation: The subarray with maximum product is [6, -3, -10] with product = 6 * (-3) * (-10) = 180.
Input: arr[] = [-1, -3, -10, 0, 6]
Output: 30
Explanation: The subarray with maximum product is [-3, -10] with product = (-3) * (-10) = 30.
Input: arr[] = [2, 3, 4] 
Output: 24 
Explanation: For an array with all positive elements, the result is product of all elements.

Constraints:
1 ≤ arr.size() ≤ 106
-100 ≤ arr[i] ≤ 100

Approach:
Track Maximum and Minimum Products:
We track two values:
1. maxEndingHere → maximum product till current index
2. minEndingHere → minimum product till current index

Why min?
Because negative * negative = positive → can become max.

If current number is negative → swap max and min.

Algorithm:
1. Initialize maxEnding = minEnding = result = arr[0]
2. For each element from index 1:
   - If arr[i] < 0: swap(maxEnding, minEnding)
   - maxEnding = max(arr[i], maxEnding * arr[i])
   - minEnding = min(arr[i], minEnding * arr[i])
   - result = max(result, maxEnding)
3. Return result

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProductSubarray(int arr[], int n) {
        int maxEnding = arr[0];
        int minEnding = arr[0];
        int result = arr[0];

        for (int i = 1; i < n; i++) {
            // If negative number → swap
            if (arr[i] < 0) {
                int temp = maxEnding;
                maxEnding = minEnding;
                minEnding = temp;
            }

            // Either start new subarray or extend
            maxEnding = max(arr[i], maxEnding * arr[i]);
            minEnding = min(arr[i], minEnding * arr[i]);

            // Update result
            result = max(result, maxEnding);
        }

        return result;
    }
};
