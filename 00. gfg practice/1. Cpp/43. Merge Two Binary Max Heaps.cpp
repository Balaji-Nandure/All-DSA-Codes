/*
 * Problem: Merge Two Binary Max Heaps
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/merge-two-binary-max-heap0144/1
 * 
 * Given two binary max heaps represented as arrays a[] and b[].
 * Both arrays individually satisfy max-heap property.
 * Merge them into a single valid max heap and return it.
 * 
 * Example:
 * Input:
 * a = {10, 5, 6, 2}
 * b = {12, 7, 9}
 * Output:
 * One possible max heap: {12, 10, 9, 2, 5, 7, 6}
 * 
 * Constraints:
 * 1 ≤ a.size(), b.size() ≤ 10^5
 * 1 ≤ a[i], b[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(n + m)
 * Expected Auxiliary Space: O(n + m)
 * 
 * Approach:
 * - Combine both arrays into a single vector of size (n + m)
 * - The merged array won't be a heap, so build max heap using heapify
 * - Start from last non-leaf node (size/2 - 1) and heapify towards root
 * - This bottom-up approach efficiently builds the heap in O(n + m) time
 * - Heapify function maintains max-heap property by comparing with children
 * 
 * Time: O(n + m) - linear time for merging and heap building
 * Space: O(n + m) - storing merged array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    // Function to heapify subtree rooted at index i
    // TC for one call: O(log n)
    void heapify(vector<int> &arr, int size, int i) {
        int largest = i;              // Assume current index is largest
        int left = 2 * i + 1;         // Left child index
        int right = 2 * i + 2;        // Right child index
        
        // If left child exists and is greater
        if (left < size && arr[left] > arr[largest])
            largest = left;
        
        // If right child exists and is greater
        if (right < size && arr[right] > arr[largest])
            largest = right;
        
        // If largest changed, swap and recurse
        if (largest != i) {
            swap(arr[i], arr[largest]);
            
            // Recursively heapify affected subtree
            heapify(arr, size, largest);
        }
    }
    
    
    vector<int> mergeHeaps(vector<int> &a, vector<int> &b, int n, int m) {
        
        // Step 1: Create merged vector
        vector<int> merged;
        
        // Reserve space (important optimization)
        merged.reserve(n + m);
        
        // Step 2: Insert all elements
        for (int i = 0; i < n; i++)
            merged.push_back(a[i]);
        
        for (int i = 0; i < m; i++)
            merged.push_back(b[i]);
        
        int size = n + m;
        
        // Step 3: Build max heap using bottom-up heapify
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(merged, size, i);
        }
        
        return merged;
    }
};
