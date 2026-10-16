/**
 * ============================================================================
 * Problem: 3-Way QuickSort (Partitioning and Sorting with Many Repeated Entries)
 * Category: Searching and Sorting
 * 
 * Problem Statement:
 * Standard QuickSort (using Lomuto or Hoare partitioning) suffers devastating
 * performance degradation to O(N^2) time when the input array contains many 
 * duplicate or repeated entries (in the extreme case of an array with all 
 * identical elements, standard Lomuto quicksort takes O(N^2) time!).
 * 
 * Implement 3-Way QuickSort (Dutch National Flag Partitioning) which partitions
 * the array into three distinct contiguous segments around a pivot value V:
 *   1. Elements strictly less than V:    arr[low ... lt - 1]
 *   2. Elements equal to V:              arr[lt ... gt]
 *   3. Elements strictly greater than V: arr[gt + 1 ... high]
 * 
 * And recursively sorts ONLY the first and third segments.
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * -10^9 <= arr[i] <= 10^9
 * Must run in O(N) when all elements are identical, and O(N log N) in general.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. 2-Way vs 3-Way Partitioning:
 *    - 2-Way QuickSort divides elements into [<= pivot] and [> pivot].
 *      Duplicate pivot values get shoved into one side or oscillate, causing
 *      highly unbalanced recursive splits (N - 1 vs 0), leading to O(N^2) stack depth.
 *    - 3-Way QuickSort bundles ALL instances of the pivot together in the middle
 *      [lt...gt] in a single pass.
 * 2. Skipping the Middle Partition:
 *    - Because all elements equal to the pivot are placed in their final sorted positions,
 *      subsequent recursive calls completely bypass [lt...gt].
 *    - If an array has K unique elements, 3-Way QuickSort completes in O(N log K) time!
 *    - If all elements are equal (K = 1), it terminates in exactly O(N) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Dutch National Flag Partitioning:
 *    - Choose pivot = arr[low].
 *    - Initialize: `lt = low`, `gt = high`, `i = low + 1`.
 *    - Invariant:
 *        arr[low ... lt - 1] < pivot
 *        arr[lt ... i - 1] == pivot
 *        arr[i ... gt] = unprocessed
 *        arr[gt + 1 ... high] > pivot
 *    - While i <= gt:
 *        - If arr[i] < pivot: swap(arr[lt], arr[i]), lt++, i++.
 *        - If arr[i] > pivot: swap(arr[i], arr[gt]), gt-- (do NOT increment i, re-examine new arr[i]).
 *        - If arr[i] == pivot: i++.
 * 2. Recursive calls:
 *    - quickSort3Way(arr, low, lt - 1)
 *    - quickSort3Way(arr, gt + 1, high)
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Solution {
private:
    /**
     * Performs 3-way Dutch National Flag partitioning on arr[low...high].
     * Outputs the boundaries [lt, gt] where arr[lt...gt] == pivot.
     */
    pair<int, int> partition3Way(vector<int>& arr, int low, int high) {
        // Randomized pivot selection to prevent worst-case on pre-sorted inputs
        int randomPivotIdx = low + rand() % (high - low + 1);
        swap(arr[low], arr[randomPivotIdx]);

        int pivot = arr[low];
        int lt = low;       // arr[low...lt-1] will contain elements < pivot
        int gt = high;      // arr[gt+1...high] will contain elements > pivot
        int i = low + 1;    // Current element being inspected

        while (i <= gt) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Three-way branching guarantees that equal elements are clustered in [lt...gt]
            // in a single pass, completely eliminating them from further recursive subproblems.
            if (arr[i] < pivot) {
                swap(arr[lt], arr[i]);
                lt++;
                i++;
            } else if (arr[i] > pivot) {
                swap(arr[i], arr[gt]);
                gt--; // Note: i is NOT incremented, as arr[i] after swap must still be inspected
            } else {
                i++;  // arr[i] == pivot, simply expand the middle equal partition
            }
        }

        return {lt, gt};
    }

public:
    /**
     * Recursively sorts arr[low...high] using 3-Way QuickSort.
     */
    void quickSort3Way(vector<int>& arr, int low, int high) {
        if (low >= high) return;

        // Partition into: < pivot, == pivot, > pivot
        pair<int, int> boundaries = partition3Way(arr, low, high);
        int lt = boundaries.first;
        int gt = boundaries.second;

        // Recursively sort ONLY the strictly smaller and strictly larger segments
        quickSort3Way(arr, low, lt - 1);
        quickSort3Way(arr, gt + 1, high);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Array with massive duplicate frequencies
    vector<int> arr1 = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
    cout << "Test 1 Original: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n";

    solver.quickSort3Way(arr1, 0, arr1.size() - 1);

    cout << "Test 1 Sorted:   ";
    for (int x : arr1) cout << x << " ";
    cout << "\n";

    // Test Case 2: All identical elements (Degrades standard quicksort to O(N^2), but O(N) here!)
    vector<int> arr2 = {5, 5, 5, 5, 5, 5, 5};
    solver.quickSort3Way(arr2, 0, arr2.size() - 1);

    cout << "Test 2 (All Identical): ";
    for (int x : arr2) cout << x << " ";
    cout << "\n";

    // Test Case 3: Already sorted array
    vector<int> arr3 = {1, 2, 3, 4, 5, 6, 7};
    solver.quickSort3Way(arr3, 0, arr3.size() - 1);

    cout << "Test 3 (Pre-sorted):    ";
    for (int x : arr3) cout << x << " ";
    cout << "\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - All elements identical: Exactly O(N) time (a single partition puts all
 *     elements in the equal partition, both recursive calls are empty!).
 *   - K unique elements: O(N log K) time.
 *   - Distinct elements (worst/average case): O(N log N) time with randomized pivot.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) in-place swaps.
 *   - Recursion stack: O(log N) average depth.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. 3-Way QuickSort (Bentley-McIlroy / Sedgewick) is the standard partitioning
 *    used in modern industrial implementations (like Java's `Arrays.sort()` for primitives)
 *    because real-world data is heavily dominated by repeated values.
 */
