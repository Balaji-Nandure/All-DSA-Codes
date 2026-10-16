// Problem: Search in a Rotated Sorted Array
// Link (GFG): https://www.geeksforgeeks.org/problems/search-in-a-rotated-array0959/1
// Article: https://www.geeksforgeeks.org/dsa/search-an-element-in-a-sorted-and-pivoted-array/
// Difficulty: Medium
// Topic: Searching, Binary Search, Rotated Array Invariant

/*
Problem Statement:
Given a sorted and rotated array `A` of distinct elements which was originally sorted 
in ascending order and then cyclically rotated at some unknown pivot point.
Given a target `key`, find the index of `key` in `A`.
If `key` is not present, return -1.

Example 1:
Input: A = [5, 6, 7, 8, 9, 10, 1, 2, 3], key = 10
Output: 5
Explanation: 10 is found at index 5.

Example 2:
Input: A = [3, 5, 1, 2], key = 6
Output: -1
Explanation: 6 is not in the array.

Example 3:
Input: A = [4, 5, 6, 7, 0, 1, 2], key = 0
Output: 4

Constraints:
- 1 <= A.size() <= 10^5
- 0 <= A[i] <= 10^9
- All elements in A are distinct.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Standard Binary Search:
//   * The ENTIRE array is monotonic, so comparing `arr[mid]` with `key` immediately 
//     discards either `[low..mid-1]` or `[mid+1..high]`.
// - In Rotated Sorted Array:
//   * The array is split into TWO sorted segments separated by a rotation cliff.
//   * However, the fundamental invariant remains:
//     AT LEAST ONE OF THE TWO HALVES (left or right) IS ALWAYS STRICTLY SORTED!
//   * We identify WHICH half is sorted, check if `key` falls inside that sorted range's 
//     clear boundaries, and prune the other half deterministically!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Single-Pass Modified Binary Search (Optimal & Chosen):
//   - Set `low = 0`, `high = n - 1`.
//   - Compute `mid = low + (high - low) / 2`.
//   - If `arr[mid] == key`: Return `mid`.
//   - Check which half is sorted:
//       * Case 1: Left half `[low .. mid]` is sorted (`arr[low] <= arr[mid]`):
//           - If `arr[low] <= key && key < arr[mid]`:
//               Target lies strictly in the left half -> `high = mid - 1`.
//           - Else:
//               Target must be in the right half -> `low = mid + 1`.
//
//       * Case 2: Right half `[mid .. high]` is sorted (`arr[mid] <= arr[high]`):
//           - If `arr[mid] < key && key <= arr[high]`:
//               Target lies strictly in the right half -> `low = mid + 1`.
//           - Else:
//               Target must be in the left half -> `high = mid - 1`.
//   - Complexity: O(log N) time, O(1) space.
//   - Why this approach: Achieves search in a single binary pass without two separate 
//     pivot-finding passes.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& arr, int key) {
        int low = 0;
        int high = (int)arr.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == key) {
                return mid; // Target found
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Invariant: At least one half must be sorted.
            // Check if LEFT half [low .. mid] is sorted:
            if (arr[low] <= arr[mid]) {
                // If key falls strictly inside the sorted left half's boundary range:
                if (key >= arr[low] && key < arr[mid]) {
                    high = mid - 1; // Narrow search to left half
                } else {
                    low = mid + 1;  // Narrow search to right half
                }
            } 
            // Otherwise, RIGHT half [mid .. high] MUST be sorted:
            else {
                // If key falls strictly inside the sorted right half's boundary range:
                if (key > arr[mid] && key <= arr[high]) {
                    low = mid + 1;  // Narrow search to right half
                } else {
                    high = mid - 1; // Narrow search to left half
                }
            }
        }

        return -1; // Target not found
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {5, 6, 7, 8, 9, 10, 1, 2, 3};
    int key1 = 10;
    cout << "Search " << key1 << " in arr1: index " << sol.search(arr1, key1) << "\n";

    vector<int> arr2 = {4, 5, 6, 7, 0, 1, 2};
    int key2 = 0;
    cout << "Search " << key2 << " in arr2: index " << sol.search(arr2, key2) << "\n";

    int key3 = 99;
    cout << "Search " << key3 << " in arr2: index " << sol.search(arr2, key3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(log N), binary search halves the search space at each iteration.
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Identifying which half is sorted and testing if the target is within its range 
  is the master template for all rotated array binary search problems.
*/
