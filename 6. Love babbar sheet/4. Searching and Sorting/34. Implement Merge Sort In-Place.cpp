/**
 * ============================================================================
 * Problem: Implement In-Place Merge Sort (O(1) Auxiliary Space)
 * Category: Searching and Sorting
 * 
 * Problem Statement:
 * Standard Merge Sort requires O(N) auxiliary memory to temporarily hold elements
 * during the merge phase. Implement Merge Sort such that it operates strictly 
 * IN-PLACE with O(1) auxiliary space (excluding O(log N) recursive call stack frames).
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * -10^9 <= arr[i] <= 10^9
 * Must NOT allocate any vector/array of size proportional to N.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Standard Merge Sort vs In-Place Merge:
 *    - Standard Merge Sort (Problem 33) uses a temporary buffer `temp[N]`.
 *      It achieves optimal O(N log N) time but consumes O(N) memory.
 *    - In-place merging cannot overwrite values that haven't been copied yet.
 * 2. Two Distinct In-Place Paradigms:
 *    - Paradigm A: Shifting / Insertion Method:
 *      When arr[j] < arr[i], right-shift elements [i ... j - 1] by 1 position.
 *      Time per merge: O(len^2). Overall Time: O(N^2). Space: O(1).
 *    - Paradigm B: Shell's Diminishing Gap Method:
 *      Treats the adjacent sorted subarrays arr[low...mid] and arr[mid+1...high]
 *      as a unified range of length L = high - low + 1.
 *      Applies gap = ceil(L / 2), comparing and swapping across gap until gap becomes 0.
 *      Time per merge: O(L log L). Overall Time: O(N log^2 N). Space: O(1).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Gap Method (Recommended & Optimal O(N log^2 N) In-Place):
 *    - Calculate initial gap = ceil(length / 2).
 *    - While gap > 0:
 *        Iterate pointer i from low to (high - gap).
 *        If arr[i] > arr[i + gap], swap(arr[i], arr[i + gap]).
 *        Update gap = nextGap(gap).
 *    - Recurrence relation: T(N) = 2*T(N/2) + O(N log N).
 *    - By Master Theorem: T(N) = O(N log^2 N), which easily handles N = 10^5!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    /**
     * Calculates the next gap using ceiling division: ceil(gap / 2).
     */
    int nextGap(int gap) {
        if (gap <= 1) return 0;
        return (gap / 2) + (gap % 2);
    }

    /**
     * Method 1: Gap Method In-Place Merge
     * Merges arr[low...mid] and arr[mid+1...high] in-place in O(L log L) time, O(1) space.
     */
    void inPlaceMergeGap(vector<int>& arr, int low, int mid, int high) {
        int len = high - low + 1;
        int gap = nextGap(len);

        while (gap > 0) {
            int i = low;
            while (i + gap <= high) {
                int j = i + gap;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // By comparing and conditionally swapping elements separated by 'gap',
                // we sort the entire combined range without requiring any auxiliary merge buffer!
                if (arr[i] > arr[j]) {
                    swap(arr[i], arr[j]);
                }
                i++;
            }
            gap = nextGap(gap);
        }
    }

    /**
     * Method 2: Shifting In-Place Merge (Linear Scan with Shifting)
     * Merges in-place in O(L^2) time, O(1) space.
     */
    void inPlaceMergeShift(vector<int>& arr, int low, int mid, int high) {
        int i = low;
        int j = mid + 1;

        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) {
                i++;
            } else {
                int val = arr[j];
                int index = j;

                // Shift all elements between i and j-1 right by 1
                while (index != i) {
                    arr[index] = arr[index - 1];
                    index--;
                }
                arr[i] = val;

                // Update pointers since all elements shifted
                i++;
                mid++;
                j++;
            }
        }
    }

public:
    /**
     * Divide and conquer in-place merge sort using the O(N log^2 N) Gap method.
     */
    void inPlaceMergeSort(vector<int>& arr, int low, int high) {
        if (low >= high) return;

        int mid = low + (high - low) / 2;

        // Recursively sort left and right halves
        inPlaceMergeSort(arr, low, mid);
        inPlaceMergeSort(arr, mid + 1, high);

        // Merge two sorted halves in-place
        inPlaceMergeGap(arr, low, mid, high);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Arbitrary unsorted vector
    vector<int> arr1 = {12, 11, 13, 5, 6, 7};
    cout << "Test 1 Original: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n";

    solver.inPlaceMergeSort(arr1, 0, arr1.size() - 1);

    cout << "Test 1 Sorted:   ";
    for (int x : arr1) cout << x << " ";
    cout << "\n";

    // Test Case 2: Array with duplicates and negatives
    vector<int> arr2 = {4, -1, 7, 3, -1, 9, 0, 2};
    solver.inPlaceMergeSort(arr2, 0, arr2.size() - 1);

    cout << "Test 2 Sorted:   ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Gap Method Merge:
 *   - Merge Step Time: O(L log L) for subarray of length L.
 *   - Overall Time Complexity:
 *       T(N) = 2 * T(N/2) + O(N log N) = O(N log^2 N).
 *   - For N = 10^5, N log^2 N ≈ 10^5 * (17)^2 ≈ 2.8 * 10^7 operations (runs in ~0.15s).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly. No auxiliary vectors allocated.
 *   - Call Stack Space: O(log N) for recursion tree depth.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The Gap Method provides a bridge between Shell Sort and Merge Sort.
 * 2. It circumvents the memory overhead of classic Merge Sort while avoiding
 *    the O(N^2) degradation of naive shifting.
 */
