// Problem: Count Inversions in an Array
// Link (Article): https://www.geeksforgeeks.org/dsa/inversion-count-in-array-using-merge-sort/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1
// Difficulty: Medium / Hard
// Topic: Array, Divide and Conquer, Merge Sort, Inversion Count

/*
Problem Statement:
Given an array of integers `arr[]`. Find the Inversion Count in the array.
Two elements `arr[i]` and `arr[j]` form an inversion if:
    `arr[i] > arr[j]`  AND  `i < j`

Inversion Count indicates how far (or close) the array is from being sorted:
- If array is already sorted, Inversion Count = 0.
- If array is sorted in reverse order, Inversion Count is maximum = n * (n - 1) / 2.

Example 1:
Input: arr = [2, 4, 1, 3, 5]
Output: 3
Explanation: The 3 inversions are (2, 1), (4, 1), (4, 3).

Example 2:
Input: arr = [2, 3, 4, 5, 6]
Output: 0
Explanation: Array is already sorted.

Example 3:
Input: arr = [10, 10, 10]
Output: 0
Explanation: Elements are equal, not strictly greater.

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 6 & 12: We merged sorted arrays to achieve in-place sorted order.
// - In Problem 16:
//   * We do not just sort; we COUNT CROSS-BOUNDARY PAIRS satisfying a condition (`i < j` & `arr[i] > arr[j]`).
//   * The Divide and Conquer structure of Merge Sort naturally groups pairs into:
//     1. Inversions entirely in the left half
//     2. Inversions entirely in the right half
//     3. Split inversions (one element in left half, one in right half)

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Brute Force (Nested Loops)
//   - Compare every pair (i, j) with i < j: O(N^2).
//   - Why NOT: N <= 10^5, so N^2 = 10^10 operations => massive TLE.
//
// Approach 2: Modified Merge Sort (Divide & Conquer) - OPTIMAL & CHOSEN
//   - Split array into two halves until single elements.
//   - During `merge(arr, low, mid, high)`:
//     * Both subarrays `arr[low ... mid]` and `arr[mid + 1 ... high]` are INDIVIDUALLY SORTED.
//     * When comparing `arr[i]` from left and `arr[j]` from right:
//       If `arr[i] > arr[j]`:
//       Since `arr[low ... mid]` is sorted, EVERY element from `i` to `mid` is >= arr[i] > arr[j]!
//       Therefore, `arr[j]` forms an inversion with ALL `(mid - i + 1)` remaining elements in the left half!
//       We add `(mid - i + 1)` to our total in O(1) time without looping!
//   - Complexity: Exactly O(N log N) time, O(N) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    long long merge(vector<long long>& arr, vector<long long>& temp, int low, int mid, int high) {
        int i = low;     // Starting index for left subarray
        int j = mid + 1; // Starting index for right subarray
        int k = low;     // Starting index for merged subarray in temp
        long long invCount = 0;

        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                // arr[i] > arr[j]
                temp[k++] = arr[j++];

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Because the left subarray [low ... mid] is sorted:
                // arr[i] <= arr[i+1] <= ... <= arr[mid].
                // Since arr[i] > arr[j], ALL remaining elements from index i to mid
                // are GUARANTEED to be strictly greater than arr[j]!
                // This counts (mid - i + 1) inversions in O(1) time without checking them individually!
                invCount += (mid - i + 1);
            }
        }

        // Copy remaining elements of left subarray
        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        // Copy remaining elements of right subarray
        while (j <= high) {
            temp[k++] = arr[j++];
        }

        // Copy sorted elements back into original array
        for (int idx = low; idx <= high; idx++) {
            arr[idx] = temp[idx];
        }

        return invCount;
    }

    long long mergeSort(vector<long long>& arr, vector<long long>& temp, int low, int high) {
        long long invCount = 0;
        if (low < high) {
            int mid = low + (high - low) / 2;

            // Inversions in left half
            invCount += mergeSort(arr, temp, low, mid);

            // Inversions in right half
            invCount += mergeSort(arr, temp, mid + 1, high);

            // Cross-inversions between left and right halves
            invCount += merge(arr, temp, low, mid, high);
        }
        return invCount;
    }

public:
    long long inversionCount(vector<long long>& arr) {
        int n = arr.size();
        vector<long long> temp(n);
        return mergeSort(arr, temp, 0, n - 1);
    }
};

/*
Time Complexity: O(N log N)
- Standard Merge Sort recurrence: T(N) = 2T(N / 2) + O(N) = O(N log N).
- At each merge level, inversions are counted in O(1) per comparison.

Space Complexity: O(N) Auxiliary Space
- Temporary array `temp` of size N allocated once and shared across all recursive merge calls.

Key Insights:
1. Why (mid - i + 1) Counts Everything:
   - Example: Left = [4, 6, 8], Right = [3, 5, 7].
   - Comparing 4 with 3: since 4 > 3, not only 4 is > 3, but 6 and 8 are also > 3!
   - Total added immediately = (2 - 0 + 1) = 3 inversions for element 3.
2. 64-bit Count Requirement:
   - Maximum inversions = N * (N - 1) / 2. For N = 10^5, this is ~ 5 * 10^9, which overflows 32-bit `int`.
   - `long long` must be used for `invCount`.
*/
