// Problem: Find Minimum or Pivot Element in a Rotated Sorted Array
// Link (GFG): https://www.geeksforgeeks.org/problems/minimum-element-in-a-sorted-and-rotated-array3611/1
// Article: https://www.geeksforgeeks.org/dsa/find-minimum-element-in-a-sorted-and-rotated-array/
// Difficulty: Easy / Medium
// Topic: Searching, Binary Search, Rotated Array Invariant

/*
Problem Statement:
A sorted array `arr` of size n with distinct elements has been cyclically rotated 
at some unknown pivot point. Find the minimum element in the array in O(log N) time.
(The minimum element also identifies the exact pivot inflection point where the rotation occurred).

Example 1:
Input: arr = [5, 6, 1, 2, 3, 4]
Output: 1
Explanation: 1 is the minimum element (rotation pivot).

Example 2:
Input: arr = [3, 1, 2]
Output: 1

Example 3:
Input: arr = [4, 5, 6, 7, 0, 1, 2]
Output: 0

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^6
- All elements are distinct.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 3 (Search in Rotated Sorted Array):
//   * A known target `key` was provided; we checked which half was sorted and if key was inside.
// - In Problem 21 (Find Minimum / Pivot Element):
//   * NO target value is given!
//   * The minimum element is the SOLE element in the array that is strictly smaller 
//     than its predecessor (`arr[i] < arr[i-1]`).
//   * We compare `arr[mid]` directly against `arr[high]`!
//     If `arr[mid] > arr[high]`, the cliff/minimum is GUARANTEED to be in the right half!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Binary Search Comparing with Upper Boundary (Optimal & Chosen):
//   - Range: `low = 0`, `high = n - 1`.
//   - While `low < high`:
//       * `mid = low + (high - low) / 2`.
//       * Case 1: `arr[mid] > arr[high]`:
//           - Because the array was originally ascending, having `arr[mid] > arr[high]` 
//             proves that the rotation wrap-around (cliff) happened to the RIGHT of `mid`!
//           - The minimum element CANNOT be in `[low .. mid]`!
//           - Discard left half: `low = mid + 1`.
//       * Case 2: `arr[mid] <= arr[high]`:
//           - The subarray `[mid .. high]` is sorted, so the minimum is either `arr[mid]` 
//             itself or somewhere to its left!
//           - We cannot discard `mid`, so: `high = mid`.
//   - When `low == high`: `arr[low]` is the minimum element!
//   - Complexity: O(log N) time, O(1) auxiliary space.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& arr) {
        int low = 0;
        int high = (int)arr.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Comparing mid with the right boundary high:
            // If arr[mid] > arr[high], the rotation cliff must lie strictly in the right half (mid + 1 to high).
            // If arr[mid] <= arr[high], the minimum is in the left half including mid itself (high = mid).
            if (arr[mid] > arr[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        // When low == high, pointer has converged to the inflection point (minimum element)
        return arr[low];
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {5, 6, 1, 2, 3, 4};
    cout << "Minimum in arr1: " << sol.findMin(arr1) << "\n";

    vector<int> arr2 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Minimum in arr2: " << sol.findMin(arr2) << "\n";

    vector<int> arr3 = {1, 2, 3, 4, 5}; // Already sorted, 0 rotations
    cout << "Minimum in arr3 (unrotated): " << sol.findMin(arr3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(log N). Binary search halves the candidate range at each iteration.
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Comparing `arr[mid]` with `arr[high]` rather than `arr[low]` is the key to handling
  both rotated arrays and already-sorted unrotated arrays uniformly.
*/
