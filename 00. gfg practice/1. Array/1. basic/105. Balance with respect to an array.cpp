/*
Problem: Balance with respect to an array

GFG: https://www.geeksforgeeks.org/problems/balance-with-respect-to-an-array/1

Description: Find whether a given number x is balanced with respect to a given array arr. Sort array first in non-decreasing order. Check if absolute difference between floor of x and x is equal to absolute difference between ceil of x and x.
Note: The ceiling of x is smallest element in array greater than or equal to x, and floor of x is greatest element smaller than or equal to x.

Examples:

Input: arr[] = [1, 2, 8, 10, 10, 12, 19], x = 5 
Output: true
Explanation: Here 2 is floor value and 8 is ceil value and (5 - 2) = (8 - 5).
Input: arr[] = [1, 2, 5, 7, 8, 11, 12, 15], x = 9
Output: false
Explanation: Here 8 is floor value and 11 is ceil value and (9 - 8) != (11 - 9).

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ arr[i], x≤ 106

Approach:
1. Sort the array
2. Use binary search to find floor and ceil of x
3. Check if 2*x == floor + ceil (equivalent to |x-floor| == |ceil-x|)
4. Return true if balanced, else false

Why it works:
- Sorting allows binary search for O(log n) floor/ceil finding
- Binary search efficiently finds the closest elements around x
- If x is exactly in middle of floor and ceil, it's balanced
- The condition |x-floor| == |ceil-x| simplifies to 2*x == floor + ceil

Time Complexity: O(n log n) for sorting + O(log n) for search = O(n log n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isBalanced(vector<int>& arr, int x) {
        sort(arr.begin(), arr.end());
        int n = arr.size();

        int floorVal = -1, ceilVal = -1;

        // Binary search for floor and ceil
        int low = 0, high = n - 1;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (arr[mid] == x) {
                floorVal = ceilVal = arr[mid];
                break;
            }
            else if (arr[mid] < x) {
                floorVal = arr[mid];
                low = mid + 1;
            }
            else {
                ceilVal = arr[mid];
                high = mid - 1;
            }
        }

        if (floorVal == -1 || ceilVal == -1) return false;

        return (2 * x == floorVal + ceilVal);
    }
};
