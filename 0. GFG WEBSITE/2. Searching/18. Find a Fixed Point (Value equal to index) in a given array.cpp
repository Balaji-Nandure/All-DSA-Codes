/*
 * Problem: Find a Fixed Point (Value equal to index) in a given array
 *
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-a-fixed-point-in-a-given-array/
 *
 * A Fixed Point in an array is an index i such that arr[i] == i.
 * 
 * Given a sorted array of distinct integers, return any fixed point
 * (any (i) such that arr[i] == i), or -1 if there is no fixed point.
 * 
 * Examples:
 * Input: arr[] = {-10, -5, 0, 3, 7}
 * Output: 3  // arr[3] == 3
 * 
 * Input: arr[] = {0, 2, 5, 8, 17}
 * Output: 0  // arr[0] == 0
 *
 * Input: arr[] = {-10, -5, 3, 4, 7, 9}
 * Output: -1 // No Fixed Point
 * 
 * Constraints:
 * - Array is sorted in increasing order, all values distinct
 * 
 * Approach:
 * Binary Search (O(log n) time, O(1) space)
 * At each step:
 * - if arr[mid] == mid: found fixed point
 * - if arr[mid] < mid: search right half
 * - if arr[mid] > mid: search left half
 */

#include <bits/stdc++.h>
using namespace std;

// Binary Search approach
int fixedPoint(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == mid) {
            return mid;
        }
        else if (arr[mid] < mid) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}


// Linear Search approach (for completeness, O(n) time)
int fixedPointLinear(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == i)
            return i;
    }
    return -1;
}
