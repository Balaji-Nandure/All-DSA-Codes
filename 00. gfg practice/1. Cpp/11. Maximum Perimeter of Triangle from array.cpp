/*
Question: Maximum Perimeter of Triangle from array
Given an array of positive integers, find the maximum perimeter of a triangle that can be formed using any three elements from the array. If no triangle can be formed, return -1.

For three sides to form a valid triangle, they must satisfy the triangle inequality:
- The sum of any two sides must be greater than the third side.

Approach:
1. Sort the array in descending order to get the largest elements first
2. Iterate through the array and check every triplet of consecutive elements
3. For a valid triangle with sides a, b, c (where a >= b >= c), we only need to check if b + c > a
   (since a >= b >= c, the other two conditions a + c > b and a + b > c are automatically satisfied)
4. Return the perimeter of the first valid triangle found (which will be maximum due to sorting)
5. If no valid triangle is found, return -1

Time Complexity: O(n log n) for sorting + O(n) for iteration = O(n log n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPerimeter(vector<int>& arr) {
        sort(arr.begin(), arr.end(), greater<int>());
        
        for (int i = 0; i < arr.size() - 2; i++) {
            if (arr[i + 1] + arr[i + 2] > arr[i]) {
                return arr[i] + arr[i + 1] + arr[i + 2];
            }
        }
        
        return -1;
    }
};
