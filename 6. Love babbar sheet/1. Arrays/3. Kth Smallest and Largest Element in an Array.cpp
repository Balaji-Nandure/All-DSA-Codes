// Problem: Find the "Kth" Max and Min Element of an Array
// Link (GFG Kth Smallest): https://www.geeksforgeeks.org/problems/kth-smallest-element5635/1
// Link (LeetCode 215 Kth Largest): https://leetcode.com/problems/kth-largest-element-in-an-array/
// Difficulty: Medium
// Topic: Array, Heap (Priority Queue), Divide and Conquer, QuickSelect

/*
Problem Statement:
Given an array `arr[]` of size `n` and a positive integer `k`, find the:
1. `k`-th smallest element in the array.
2. `k`-th largest element in the array.

Example 1:
Input: arr = [7, 10, 4, 3, 20, 15], k = 3
Output: 
- 3rd smallest = 7  (Sorted: [3, 4, 7, 10, 15, 20])
- 3rd largest = 10  (Sorted descending: [20, 15, 10, 7, 4, 3])

Example 2:
Input: arr = [2, 3, 1, 20, 15], k = 4
Output: 
- 4th smallest = 15
- 4th largest = 2

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^5
- 1 <= k <= arr.size()
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Reverse Array): In-place structural rearrangement using Two Pointers.
// - In Problem 2 (Min & Max Element): Found the absolute 1st extremum (k = 1) in O(N) time with 1.5N comparisons.
// - In Problem 3 (Kth Element):
//   * We are NOT looking for the absolute extremes (k = 1), but an arbitrary k-th ranked element (1 <= k <= N).
//   * A simple min/max variable cannot remember the previous (k - 1) rejected elements.
//   * We must choose a data structure (Heap) or partition algorithm (QuickSelect) that maintains partial order.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Full Sorting (`std::sort`)
//   - Sort the array in O(N log N). Return arr[k - 1] or arr[n - k].
//   - Why Suboptimal: We sort all N elements even if k is very small (e.g., k = 2). Wastes O(N log N).
//
// Approach 2: Max-Heap of size K (for Kth Smallest) / Min-Heap of size K (for Kth Largest) - HEAP METHOD
//   - Maintain a heap of strictly size K.
//   - For Kth Smallest: Use `max_heap` of size K.
//     * Push elements. If size > k, pop the maximum!
//     * At the end, heap contains the K smallest elements, and `top()` is the Kth smallest.
//   - Time Complexity: O(N log K).
//   - Space Complexity: O(K).
//   - Why Great: Exceptional when N is huge (streaming data) and K is small.
//
// Approach 3: QuickSelect (Hoare's Selection Algorithm) - THEORETICALLY OPTIMAL
//   - Partition like QuickSort around a random pivot.
//   - If pivot index == k - 1, we found the element!
//   - If pivot index > k - 1, recurse ONLY on the left partition.
//   - If pivot index < k - 1, recurse ONLY on the right partition.
//   - Time Complexity: O(N) on Average, O(N^2) worst case (mitigated with randomized pivot).
//   - Space Complexity: O(1) auxiliary space (tail-call optimized iterative loop).
//   - Why this: Expected linear time O(N) without the O(K) memory overhead of a heap.

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper: Lomuto Partition with Random Pivot for QuickSelect
    int partition(vector<int>& arr, int low, int high) {
        // Random pivot selection prevents O(N^2) worst case on sorted arrays
        int randomIdx = low + rand() % (high - low + 1);
        swap(arr[randomIdx], arr[high]);

        int pivot = arr[high];
        int i = low;

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[high]);
        return i; // Final resting index of pivot
    }

public:
    // -------------------------------------------------------------------------
    // Method 1: QuickSelect Algorithm (Expected O(N) Time, O(1) Extra Space)
    // -------------------------------------------------------------------------
    int kthSmallestQuickSelect(vector<int>& arr, int k) {
        int low = 0, high = arr.size() - 1;
        int targetIdx = k - 1; // 0-based index of k-th smallest

        while (low <= high) {
            int pIdx = partition(arr, low, high);

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Unlike QuickSort which recurses on BOTH left and right sides (N log N),
            // QuickSelect discards an entire half and recurses into ONLY ONE side!
            // Recurrence: T(N) = T(N / 2) + O(N) ==> O(N + N/2 + N/4 + ...) = O(2N) = O(N)!
            if (pIdx == targetIdx) {
                return arr[pIdx]; // Element found!
            } else if (pIdx > targetIdx) {
                high = pIdx - 1; // Target lies in the left partition
            } else {
                low = pIdx + 1;  // Target lies in the right partition
            }
        }
        return -1;
    }

    // -------------------------------------------------------------------------
    // Method 2: Max-Heap Method for K-th Smallest (O(N log K) Time, O(K) Space)
    // -------------------------------------------------------------------------
    int kthSmallestHeap(const vector<int>& arr, int k) {
        // Max-heap to store the k smallest elements seen so far
        priority_queue<int> maxH;

        for (int x : arr) {
            maxH.push(x);
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // By popping whenever size > k, we evict the largest elements among the subset,
            // strictly preserving only the 'k' smallest elements in the heap!
            if ((int)maxH.size() > k) {
                maxH.pop();
            }
        }
        // Top of max-heap is the largest among the k smallest => Kth smallest!
        return maxH.top();
    }

    // -------------------------------------------------------------------------
    // Method 3: Min-Heap Method for K-th Largest (LeetCode 215)
    // -------------------------------------------------------------------------
    int findKthLargest(const vector<int>& arr, int k) {
        // Min-heap to store the k largest elements seen so far
        priority_queue<int, vector<int>, greater<int>> minH;

        for (int x : arr) {
            minH.push(x);
            // Evict the smallest among the subset to keep only the k largest
            if ((int)minH.size() > k) {
                minH.pop();
            }
        }
        // Top of min-heap is the smallest among the k largest => Kth largest!
        return minH.top();
    }
};

/*
Time Complexity:
1. QuickSelect:
   - Average Case: O(N) — each step halves the search space (N + N/2 + N/4 + ... ≈ 2N).
   - Worst Case: O(N^2) — extremely rare due to randomized pivot selection.
2. Heap Method:
   - O(N * log K) — inserting N elements into a heap of size K takes log K per element.
   - When K << N (e.g., K = 5, N = 10^6), O(N log K) is effectively linear and faster than sorting.

Space Complexity:
- QuickSelect: O(1) Auxiliary Space (implemented iteratively without recursion stack).
- Heap Method: O(K) Auxiliary Space for storing K elements in priority queue.

Key Insights:
1. Inverse Heap Rule:
   - To find K-th SMALLEST: use a MAX-heap of size K.
   - To find K-th LARGEST:  use a MIN-heap of size K.
2. QuickSelect vs. QuickSort:
   - QuickSort solves T(N) = 2T(N/2) + O(N) = O(N log N).
   - QuickSelect solves T(N) = T(N/2) + O(N) = O(N) via geometric series summation!
*/
