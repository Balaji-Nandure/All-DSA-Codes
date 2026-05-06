/*
Problem: Sort by Absolute Difference

GFG: https://www.geeksforgeeks.org/problems/sort-by-absolute-difference-1587115621/1

Description:
You are given a number x and array arr[]. Your task is to rearrange the elements of array according to the absolute difference with x, i.e., an element having minimum difference comes first, and so on.
Note: If two or more elements are at equal distances arrange them in the same sequence as in the given array.

Examples:

Input: x = 7, arr[] = [10, 5, 3, 9, 2]
Output: [5, 9, 10, 3, 2]
Explanation: Sorting the numbers according to the absolute difference with 7, we have array elements as 5, 9, 10, 3, 2.

Input: x = 6, arr[] = [1, 2, 3, 4, 5]
Output: [5, 4, 3, 2, 1]
Explanation: Sorting the numbers according to the absolute difference with 6, we have array elements as 5, 4, 3, 2, 1.

Constraints:
1 ≤ x ≤ 10^5
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^5

Approach (Stable Sorting + Custom Comparator):
Since problem requires preserving original order for equal absolute differences, we need stable sorting.

Key insight:
- Normal sort() is not guaranteed to be stable
- stable_sort() preserves order of equal elements
- Use custom comparator based on abs(element - x)

Algorithm:
stable_sort(arr.begin(), arr.end(), 
    [&](int a, int b) {
        return abs(a - x) < abs(b - x);
    }
);

Why it works:
- stable_sort maintains original order for equal keys
- Custom comparator sorts by absolute difference from x
- Meets problem requirements exactly

Time Complexity: O(n log n)
Space Complexity: O(n) // stable_sort internal
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rearrange(vector<int> &arr, int x) {
        
        stable_sort(arr.begin(), arr.end(),
        
            [&](int a, int b) {
                return abs(a - x) < abs(b - x);
            }
        );
    }
};
