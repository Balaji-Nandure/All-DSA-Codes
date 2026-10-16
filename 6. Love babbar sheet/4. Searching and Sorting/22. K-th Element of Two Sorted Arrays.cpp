// Problem: K-th Element of Two Sorted Arrays
// Link (GFG): https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1
// Article: https://www.geeksforgeeks.org/dsa/k-th-element-two-sorted-arrays/
// Difficulty: Medium / Hard
// Topic: Searching, Binary Search, Partition Cut, Divide and Conquer

/*
Problem Statement:
Given two sorted arrays arr1 and arr2 of sizes n and m respectively, and an element k. 
Find the element that would be at the k-th position of the final combined sorted array (1-based index).
Solve it in O(log(min(n, m))) time.

Example 1:
Input:
n = 5, m = 4, k = 5
arr1 = [2, 3, 6, 7, 9]
arr2 = [1, 4, 8, 10]
Output: 6
Explanation: Combined sorted array: [1, 2, 3, 4, 6, 7, 8, 9, 10]. 
5th element is 6.

Example 2:
Input:
n = 4, m = 6, k = 7
arr1 = [100, 112, 256, 349, 770]
arr2 = [72, 86, 113, 119, 265, 445, 892]
Output: 256

Constraints:
- 1 <= n, m <= 10^6
- 1 <= arr1[i], arr2[i] <= 10^9
- 1 <= k <= n + m
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 36 (Median of Two Sorted Arrays):
//   * Partition cut split the combined arrays into two EQUAL halves `cut1 + cut2 = (n + m + 1) / 2`.
// - In K-th Element of Two Sorted Arrays:
//   * We want ANY arbitrary rank `k` (not necessarily the middle rank).
//   * Partition invariant: `cut1 + cut2 = k`.
//   * Critical boundary guard: `cut1` cannot be arbitrarily chosen between 0 and n!
//     If `k > m`, `cut1` MUST take at least `k - m` elements (since arr2 has only m elements).
//     Similarly, `cut1` cannot exceed `min(n, k)`.
//     Hence, `low = max(0, k - m)` and `high = min(n, k)`!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Binary Search on Partition Cut (Optimal & Chosen):
//   - Ensure `arr1` is the smaller array (if `n > m`, swap arrays) so binary search runs in O(log(min(n, m))).
//   - Search space for `cut1`: `low = max(0, k - m)`, `high = min(n, k)`.
//   - In each step:
//       * `cut1 = low + (high - low) / 2`.
//       * `cut2 = k - cut1`.
//       * `l1 = (cut1 == 0) ? INT_MIN : arr1[cut1 - 1]`.
//       * `r1 = (cut1 == n) ? INT_MAX : arr1[cut1]`.
//       * `l2 = (cut2 == 0) ? INT_MIN : arr2[cut2 - 1]`.
//       * `r2 = (cut2 == m) ? INT_MAX : arr2[cut2]`.
//       * If `l1 <= r2 && l2 <= r1`:
//           Valid partition! The k elements in the combined left side are strictly <= all right side elements.
//           The k-th element is `max(l1, l2)`!
//       * Else if `l1 > r2`: `cut1` is too large, search left: `high = cut1 - 1`.
//       * Else: `cut1` is too small, search right: `low = cut1 + 1`.
//   - Complexity: O(log(min(n, m))) time, O(1) space.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int kthElement(vector<int>& arr1, vector<int>& arr2, int n, int m, int k) {
        // Ensure binary search is performed on the smaller array
        if (n > m) {
            return kthElement(arr2, arr1, m, n, k);
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Precise boundary initialization:
        // low cannot be 0 if k > m (arr2 cannot supply all k elements).
        // high cannot exceed k (cannot pick more than k elements from arr1).
        int low = max(0, k - m);
        int high = min(n, k);

        while (low <= high) {
            int cut1 = low + (high - low) / 2;
            int cut2 = k - cut1;

            int l1 = (cut1 == 0) ? INT_MIN : arr1[cut1 - 1];
            int r1 = (cut1 == n) ? INT_MAX : arr1[cut1];

            int l2 = (cut2 == 0) ? INT_MIN : arr2[cut2 - 1];
            int r2 = (cut2 == m) ? INT_MAX : arr2[cut2];

            // Valid partition condition
            if (l1 <= r2 && l2 <= r1) {
                return max(l1, l2); // The k-th element is the maximum of the left partition
            } else if (l1 > r2) {
                high = cut1 - 1; // Take fewer elements from arr1
            } else {
                low = cut1 + 1;  // Take more elements from arr1
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {2, 3, 6, 7, 9};
    vector<int> arr2 = {1, 4, 8, 10};
    int k = 5;

    cout << "5th element in combined sorted arrays: " 
         << sol.kthElement(arr1, arr2, arr1.size(), arr2.size(), k) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(log(min(N, M))). For N = 10^6 and M = 10^6, at most 20 iterations!
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- The partition cut technique is the definitive generalized solution for finding 
  any arbitrary rank-k element across two sorted arrays in logarithmic time.
*/
