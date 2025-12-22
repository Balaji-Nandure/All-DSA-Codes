/*
 * Problem: Quick Sort
 *
 * Divide and conquer sorting algorithm using partitioning.
 * Choose a pivot, partition array around pivot, recursively sort partitions.
 *
 * Time: O(n log n) average, O(n²) worst case
 * Space: O(log n) - recursion stack depth
 */

#include <bits/stdc++.h>
using namespace std;

// Partition function using Lomuto's partition scheme
// Partition1: Initialize i = low - 1
int partition1(vector<int>& arr, int low, int high) {
    // Choose any element as pivot (here: last element)
    int pivot = arr[high];
    int i = low - 1; // Index for smaller elements (right boundary)

    // Traverse from low to high-1 (pivot is at high)
    for (int j = low; j <= high - 1; ++j) {
        // If current element is smaller than pivot
        // For descending order: use arr[j] > pivot
        if (arr[j] < pivot) {
            ++i; // Increment index of smaller elements
            swap(arr[i], arr[j]);
        }
    }
    // Place pivot in correct position (after all smaller elements)
    swap(arr[i + 1], arr[high]);
    return i + 1; // Return pivot index
}

// Partition: Initialize i = low (preferred approach)
int partition(vector<int>& arr, int low, int high) {
    // Choose pivot (last element)
    int pivot = arr[high];
    int i = low; // Index for smaller elements

    // Traverse and partition
    for (int j = low; j <= high - 1; j++) {
        // If element is smaller than pivot, swap with element at i
        // For descending order: use arr[j] > pivot
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++; // Move boundary of smaller elements
        }
    }
    // Place pivot in its correct position
    swap(arr[i], arr[high]);
    return i; // Return pivot index
}

// Partition2: Choose middle element as pivot (variation)
int partition2(vector<int>& arr, int low, int high) {
    // Choose middle element as pivot (better for avoiding worst case)
    int mid = low + (high - low) / 2;
    int pivot = arr[mid];

    // Move pivot to end so partition logic works unchanged
    swap(arr[mid], arr[high]);

    int i = low;
    for (int j = low; j <= high - 1; j++) {
        // Partition around pivot
        // For descending order: use arr[j] > pivot
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    // Place pivot in correct position
    swap(arr[i], arr[high]);
    return i;
}


// Quick Sort: Divide and conquer using partitioning
void quickSort(vector<int>& arr, int low, int high) {
    // Base case: single element or empty subarray is sorted
    if (low >= high) return;
    
    // Partition: place pivot at correct position
    // After partition, pivot is at index pi and in correct position
    int pi = partition(arr, low, high);
    
    // Recursively sort left part (elements < pivot)
    quickSort(arr, low, pi - 1);
    
    // Recursively sort right part (elements > pivot)
    quickSort(arr, pi + 1, high);
}

int main() {
    vector<int> arr = {5, 4, 3, 7,12, 11, 13, 14, 9, 6, 2, 1, 16, 17, 10, 15 , 18, 19, 20};
    int n = arr.size();
    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    return 0;
}
