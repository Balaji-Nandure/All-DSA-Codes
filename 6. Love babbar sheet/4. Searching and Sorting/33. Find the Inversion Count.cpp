/**
 * ============================================================================
 * Problem: Count Inversions in an Array
 * Category: Searching and Sorting / Divide and Conquer
 * 
 * Problem Statement:
 * Given an array of integers arr[]. Find the Inversion Count of the array.
 * 
 * Inversion Count: For an array, inversion count indicates how far (or close)
 * the array is from being sorted. If the array is already sorted, the inversion 
 * count is 0. If an array is sorted in the reverse order, the inversion count 
 * is maximum: N * (N - 1) / 2.
 * Formally, two elements arr[i] and arr[j] form an inversion if:
 *   arr[i] > arr[j] and i < j.
 * 
 * Constraints:
 * 1 <= N <= 5 * 10^5
 * 1 <= arr[i] <= 10^18
 * Result can reach up to 5*10^5 * (5*10^5 - 1) / 2 ≈ 1.25 * 10^11 (requires long long).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Dual-purpose Divide and Conquer:
 *    - In standard Merge Sort, we divide to conquer and sort elements.
 *    - Here, the sorting process itself naturally exposes how many elements from
 *      the left half are larger than elements in the right half.
 * 2. O(1) Batch Counting via Subarray Sortedness:
 *    - If arr[left] > arr[right], and the left subarray [left...mid] is ALREADY SORTED,
 *      then every subsequent element from left to mid is also strictly greater than arr[right].
 *    - This single comparison counts (mid - left + 1) inversions in O(1) time,
 *      avoiding quadratic element-by-element verification.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Brute Force O(N^2):
 *    - Nested loops checking every pair (i, j). For N = 5 * 10^5, N^2 = 2.5 * 10^11
 *      operations, which causes severe Time Limit Exceeded.
 * 2. Enhanced Merge Sort O(N log N):
 *    - Base Case: Subarrays of size 1 have 0 inversions.
 *    - Divide: Split array into left [low...mid] and right [mid+1...high].
 *    - Conquer: Recursively count inversions in left half and right half.
 *    - Combine (Merge): Count split inversions while merging two sorted halves.
 *      When arr[left] > arr[right], add `(mid - left + 1)` to the count.
 *    - Total Time: Exactly O(N log N).
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    /**
     * Merges two sorted subarrays arr[low...mid] and arr[mid+1...high]
     * and counts the cross-inversions between them.
     */
    long long mergeAndCount(vector<long long>& arr, vector<long long>& temp, int low, int mid, int high) {
        int i = low;      // Pointer for left subarray [low...mid]
        int j = mid + 1;  // Pointer for right subarray [mid+1...high]
        int k = low;      // Pointer for merged temp array
        long long invCount = 0;

        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Since subarray arr[low...mid] is sorted, if arr[i] > arr[j],
                // all remaining elements from index i to mid are ALSO greater than arr[j].
                // This single check batch-counts (mid - i + 1) inversions in O(1) time!
                invCount += (mid - i + 1);
                temp[k++] = arr[j++];
            }
        }

        // Copy remaining elements of left subarray, if any
        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        // Copy remaining elements of right subarray, if any
        while (j <= high) {
            temp[k++] = arr[j++];
        }

        // Copy merged elements back to original array
        for (i = low; i <= high; ++i) {
            arr[i] = temp[i];
        }

        return invCount;
    }

    /**
     * Recursive helper to perform merge sort and accumulate inversion count.
     */
    long long mergeSortAndCount(vector<long long>& arr, vector<long long>& temp, int low, int high) {
        long long invCount = 0;
        if (low < high) {
            int mid = low + (high - low) / 2;

            // Inversions in left half
            invCount += mergeSortAndCount(arr, temp, low, mid);

            // Inversions in right half
            invCount += mergeSortAndCount(arr, temp, mid + 1, high);

            // Cross inversions between left and right halves
            invCount += mergeAndCount(arr, temp, low, mid, high);
        }
        return invCount;
    }

public:
    /**
     * Returns the total inversion count of the array.
     * @param arr Input array of integers.
     * @return Total number of inversions.
     */
    long long inversionCount(vector<long long>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        vector<long long> temp(n);
        return mergeSortAndCount(arr, temp, 0, n - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: arr = {2, 4, 1, 3, 5}
    // Inversions: (2, 1), (4, 1), (4, 3) -> Total = 3
    vector<long long> arr1 = {2, 4, 1, 3, 5};
    cout << "Test 1: Inversion Count = " << solver.inversionCount(arr1) << " (Expected: 3)\n";

    // Test Case 2: Reverse sorted array {5, 4, 3, 2, 1}
    // Inversions: 5 * 4 / 2 = 10
    vector<long long> arr2 = {5, 4, 3, 2, 1};
    cout << "Test 2: Inversion Count = " << solver.inversionCount(arr2) << " (Expected: 10)\n";

    // Test Case 3: Already sorted array {1, 2, 3, 4, 5}
    // Inversions: 0
    vector<long long> arr3 = {1, 2, 3, 4, 5};
    cout << "Test 3: Inversion Count = " << solver.inversionCount(arr3) << " (Expected: 0)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - At each level of recursion, merging takes O(N) time.
 *   - There are log2(N) levels in the recursion tree.
 *   - Total Time Complexity: O(N log N) in all cases (best, worst, average).
 *   - For N = 5 * 10^5, ~9.5 * 10^6 operations, executing in under 0.1 seconds.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(N) for the temporary merge buffer.
 *   - Recursion stack: O(log N).
 *   - Total Space Complexity: O(N).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Sorting does not destroy the ability to count earlier relative order if done
 *    hierarchically in divide-and-conquer.
 * 2. Inversion counts easily exceed 2^31 - 1; always use `long long`.
 */
