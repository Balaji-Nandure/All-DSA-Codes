// Problem: Merge Two Sorted Arrays with O(1) Extra Space (Gap Method)
// Link (GFG): https://www.geeksforgeeks.org/problems/merge-two-sorted-arrays-1587115620/1
// Article: https://www.geeksforgeeks.org/dsa/merge-two-sorted-arrays-o1-extra-space/
// Difficulty: Hard
// Topic: Sorting, Shell Sort Gap Algorithm, In-Place Reorganization

/*
Problem Statement:
Given two sorted arrays `arr1[]` and `arr2[]` of sizes `n` and `m` in non-decreasing order.
Merge them in sorted order WITHOUT using any extra space.
Modify `arr1` so that it contains the first `n` elements in sorted order, 
and `arr2` so that it contains the last `m` elements in sorted order.

Example 1:
Input: 
n = 4, arr1 = [1, 3, 5, 7]
m = 5, arr2 = [0, 2, 6, 8, 9]
Output: 
arr1 = [0, 1, 2, 3]
arr2 = [5, 6, 7, 8, 9]

Example 2:
Input:
n = 2, arr1 = [10, 12]
m = 3, arr2 = [5, 18, 20]
Output: 
arr1 = [5, 10]
arr2 = [12, 18, 20]

Constraints:
- 1 <= n, m <= 10^5
- 0 <= arr1[i], arr2[i] <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Standard Merge Sort:
//   * Merging two sorted arrays is trivial in O(N + M) time using an auxiliary buffer of size N + M.
// - In In-Place Merge:
//   * Auxiliary arrays are STRICTLY FORBIDDEN (O(1) extra space).
//   * Naively inserting elements into `arr1` causes O(N * M) shifting cascades.
//   * Donald Shell's Gap Method (from Shell Sort) solves this in O((N + M) log(N + M)) 
//     by treating both arrays as a single continuous conceptual array and performing 
//     diminishing-stride pairwise comparisons!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Shell Sort Diminishing Gap Method (Optimal & Chosen):
//   - Initial gap: `gap = ceil((n + m) / 2.0) = (n + m + 1) / 2`.
//   - While `gap > 0`:
//       * Pointers `i = 0`, `j = gap`.
//       * While `j < n + m`:
//           - Case 1: Both `i` and `j` in `arr1` (`j < n`):
//               If `arr1[i] > arr1[j]`: `swap(arr1[i], arr1[j])`.
//           - Case 2: `i` in `arr1`, `j` in `arr2` (`i < n && j >= n`):
//               If `arr1[i] > arr2[j - n]`: `swap(arr1[i], arr2[j - n])`.
//           - Case 3: Both `i` and `j` in `arr2` (`i >= n`):
//               If `arr2[i - n] > arr2[j - n]`: `swap(arr2[i - n], arr2[j - n])`.
//           - Advance `i++; j++;`
//       * Reduce gap: `gap = (gap <= 1) ? 0 : (gap + 1) / 2`.
//   - Complexity: O((N + M) * log(N + M)) time, O(1) auxiliary space!
//   - Why this approach: Eliminates shifting elements and strictly abides by O(1) memory.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void merge(long long arr1[], long long arr2[], int n, int m) {
        int totalLen = n + m;
        // Initial gap calculation: ceil(totalLen / 2)
        int gap = (totalLen + 1) / 2;

        while (gap > 0) {
            int i = 0;
            int j = gap;

            while (j < totalLen) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Unified gap comparison across the array boundary:
                // Maps continuous virtual index j into arr1 (if j < n) or arr2 (if j >= n)

                // Case 1: Both elements in arr1
                if (j < n) {
                    if (arr1[i] > arr1[j]) {
                        swap(arr1[i], arr1[j]);
                    }
                }
                // Case 2: Left element in arr1, Right element in arr2
                else if (i < n && j >= n) {
                    if (arr1[i] > arr2[j - n]) {
                        swap(arr1[i], arr2[j - n]);
                    }
                }
                // Case 3: Both elements in arr2
                else {
                    if (arr2[i - n] > arr2[j - n]) {
                        swap(arr2[i - n], arr2[j - n]);
                    }
                }

                i++;
                j++;
            }

            // Diminish gap by half; when gap reaches 1, next is 0 (terminates)
            if (gap <= 1) {
                gap = 0;
            } else {
                gap = (gap + 1) / 2;
            }
        }
    }
};

int main() {
    Solution sol;
    long long arr1[] = {1, 3, 5, 7};
    long long arr2[] = {0, 2, 6, 8, 9};
    int n = 4, m = 5;

    sol.merge(arr1, arr2, n, m);

    cout << "arr1: ";
    for (int i = 0; i < n; ++i) cout << arr1[i] << " ";
    cout << "\narr2: ";
    for (int i = 0; i < m; ++i) cout << arr2[i] << " ";
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O((N + M) * log(N + M)).
  * The outer loop halves the gap log(N + M) times.
  * In each outer iteration, the inner loop touches (N + M) elements.
- Space Complexity: O(1) auxiliary space (strict in-place swaps).

Key Takeaways:
- Shell Sort's diminishing stride algorithm guarantees that when gap drops to 1,
  the array is almost completely sorted, requiring only localized swaps.
*/
