/*
 * Problem: Count Inversions in an Array
 *
 * Inversion Count: For an array, inversion count indicates how far (or close)
 * the array is from being sorted. If array is already sorted then the
 * inversion count is 0. If array is sorted in reverse order that inversion
 * count is the maximum. Formally, two elements a[i] and a[j] form an inversion 
 * if a[i] > a[j] and i < j.
 */

class Solution {
private:
    // Merge function for merge sort; merges arr[l..m] and arr[m+1..r]
    // while counting inversions.
    int merge(vector<int> &arr, int l, int m, int r) {
        int n1 = m - l + 1;    // Size of left subarray
        int n2 = r - m;        // Size of right subarray

        // Create temporary arrays
        vector<int> left(n1), right(n2);

        // Copy data to temporary arrays left[] and right[]
        for (int i = 0; i < n1; ++i) 
            left[i] = arr[l + i];
        for (int i = 0; i < n2; ++i) 
            right[i] = arr[m + 1 + i];

        int inversions = 0;    // Number of inversions found in this merge step
        int i = 0, j = 0, k = l; // i - index for left[], j - index for right[], k - index for arr[]

        // Merge the two subarrays back into arr[l..r]
        while (i < n1 && j < n2) {
            // If current element of left[] is <= right[], no inversion
            if (left[i] <= right[j]) {
                arr[k++] = left[i++];
            } else {
                // left[i] > right[j] means all the remaining elements in left[]
                // will form an inversion with right[j]
                arr[k++] = right[j++];
                inversions += (n1 - i); // Number of remaining elements in left[]
            }
        }

        // Copy any remaining elements of left[], if any
        while (i < n1) 
            arr[k++] = left[i++];

        // Copy any remaining elements of right[], if any
        while (j < n2) 
            arr[k++] = right[j++];

        // Return number of inversions counted in this merge step
        return inversions;
    }

    // Recursive mergeSort function that sorts the subarray arr[l..r]
    // and returns the inversion count
    int mergeSort(vector<int> &arr, int l, int r) {
        int inversions = 0;
        if (l < r) {
            // Find the midpoint to divide the array into two halves
            int m = l + (r - l) / 2;

            // Count inversions in left half
            inversions += mergeSort(arr, l, m);
            // Count inversions in right half
            inversions += mergeSort(arr, m + 1, r);
            // Count split inversions during merge
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