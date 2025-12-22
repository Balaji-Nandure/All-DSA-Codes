/*
 * Problem: Count Inversions in an Array
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/inversion-of-array/0
 *
 * Inversion: Two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j.
 * Count total number of inversions in the array.
 *
 * Time: O(n log n) - using merge sort approach
 * Space: O(n) - for temporary arrays
 */

class Solution {
private:
    // Merge function: merges arr[l..m] and arr[m+1..r] while counting inversions
    int merge(vector<int> &arr, int l, int m, int r) {
        int n1 = m - l + 1;    // Size of left subarray
        int n2 = r - m;        // Size of right subarray

        // Create temporary arrays
        vector<int> left(n1), right(n2);

        // Copy data to temporary arrays
        for (int i = 0; i < n1; ++i) 
            left[i] = arr[l + i];
        for (int i = 0; i < n2; ++i) 
            right[i] = arr[m + 1 + i];

        int inversions = 0;    // Count inversions in this merge
        int i = 0, j = 0, k = l; // Indices for left[], right[], and arr[]

        // Merge while counting inversions
        while (i < n1 && j < n2) {
            // If left[i] <= right[j], no inversion
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                // left[i] > right[j]: all remaining elements in left[] 
                // form inversions with right[j]
                arr[k++] = right[j++];
                inversions += (n1 - i); // Count all remaining in left[]
            }
        }

        // Copy remaining elements of left[]
        while (i < n1) 
            arr[k++] = left[i++];

        // Copy remaining elements of right[]
        while (j < n2) 
            arr[k++] = right[j++];

        return inversions; // Return inversions counted in this merge
    }

    // Merge Sort: recursively sort and count inversions
    int mergeSort(vector<int> &arr, int l, int r) {
        int inversions = 0;
        if (l < r) {
            // Find midpoint to divide array
            int m = l + (r - l) / 2;

            // Count inversions in left half
            inversions += mergeSort(arr, l, m);
            // Count inversions in right half
            inversions += mergeSort(arr, m + 1, r);
            // Count split inversions (between left and right halves)
            inversions += merge(arr, l, m, r);
        }
        return inversions;
    }

public:
    // Public method to return inversion count given array 'arr'
    int inversionCount(vector<int> &arr) {
        // Calls the recursive mergeSort; array is modified in-place.
        return mergeSort(arr, 0, static_cast<int>(arr.size()) - 1);
    }
};