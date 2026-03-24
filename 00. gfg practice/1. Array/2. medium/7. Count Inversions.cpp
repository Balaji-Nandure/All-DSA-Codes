/*
Problem: Count Inversions in Array

GFG: https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1

Description: Given an array of integers arr[]. You have to find the Inversion Count of the array.
Note: Inversion count is the number of pairs of elements (i, j) such that i < j and arr[i] > arr[j].

Examples:

Input: arr[] = [2, 4, 1, 3, 5]
Output: 3
Explanation: The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
Input: arr[] = [2, 3, 4, 5, 6]
Output: 0
Explanation: As the sequence is already sorted so there is no inversion count.
Input: arr[] = [10, 10, 10]
Output: 0
Explanation: As all the elements of array are same, so there is no inversion count.

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ arr[i] ≤ 104

Approach:
Merge Sort Based Algorithm:
During merge process, count inversions when left[i] > right[j]

Algorithm:
1. Use modified merge sort
2. During merge:
   - If left[i] <= right[j]: no inversion
   - If left[i] > right[j]: inversions += (mid - left + 1)
3. Recursively sort and count

Why it works:
- When left[i] > right[j], all elements from left[i] to left[mid] are > right[j]
- This gives (mid - left + 1) inversions at once
- Merge sort ensures O(n log n) time

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long merge(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp;
        int left = low;
        int right = mid + 1;
        long long inv = 0;

        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left]);
                left++;
            } else {
                temp.push_back(arr[right]);
                inv += (mid - left + 1); // main step
                right++;
            }
        }

        while (left <= mid) {
            temp.push_back(arr[left]);
            left++;
        }

        while (right <= high) {
            temp.push_back(arr[right]);
            right++;
        }

        for (int i = low; i <= high; i++) {
            arr[i] = temp[i - low];
        }

        return inv;
    }

    long long mergeSort(vector<int>& arr, int low, int high) {
        long long inv = 0;
        if (low < high) {
            int mid = (low + high) / 2;
            inv += mergeSort(arr, low, mid);
            inv += mergeSort(arr, mid + 1, high);
            inv += merge(arr, low, mid, high);
        }
        return inv;
    }

    long long inversionCount(vector<int> &arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};


