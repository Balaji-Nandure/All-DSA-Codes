// Problem: Find a Fixed Point (Value Equal to Index) in a Given Array
// Link (GFG): https://www.geeksforgeeks.org/problems/value-equal-to-index-value1330/1
// Article: https://www.geeksforgeeks.org/dsa/find-a-fixed-point-in-a-given-array/
// Difficulty: Basic / Easy
// Topic: Searching, Binary Search, Linear Scan, Monotonicity

/*
Problem Statement:
Given an array of n integers. Find all elements whose value is equal to its 1-based index 
(i.e., arr[i] == i + 1 for 0-based array indexing).
Return all such values in sorted order. If no such value exists, return an empty list.

Also, examine the famous interview variant:
"If the array is SORTED and contains DISTINCT integers, find a fixed point (arr[i] == i) in O(log N) time."

Example 1:
Input: arr = [15, 2, 45, 12, 7]
Output: [2]
Explanation: Only arr[1] = 2 matches its 1-based index (index 2).

Example 2:
Input: arr = [1]
Output: [1]

Example 3 (Sorted Distinct Variant):
Input: arr = [-10, -5, 0, 3, 7]
Output: 3 (arr[3] == 3)

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (First and Last Occurrence):
//   * We searched for a constant target value `x`.
// - In Problem 2 (Fixed Point / Value equal to Index):
//   * The target value is DYNAMIC: It changes with the index itself (`target = i`)!
//   * If the array has distinct sorted integers, the function `f(i) = arr[i] - i` 
//     is STRICTLY MONOTONICALLY INCREASING (`arr[i+1] - (i+1) >= arr[i] - i`).
//   * This allows us to apply Binary Search on `arr[mid] vs mid` in O(log N)!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Variant 1: General Array (GFG Practice Problem - Can have duplicates / unsorted)
//   - Traverse array once: If `arr[i] == i + 1`, collect `arr[i]`.
//   - Complexity: O(N) time, O(1) auxiliary space.
//
// Variant 2: Sorted Distinct Array (Classic FAANG Question)
//   - `low = 0`, `high = n - 1`.
//   - `mid = low + (high - low) / 2`.
//   - If `arr[mid] == mid`: Fixed point found! Return `mid`.
//   - If `arr[mid] > mid`: Since elements are distinct and sorted, every element to the right
//     of `mid` satisfies `arr[j] > j`. A fixed point CANNOT exist on the right! Search LEFT: `high = mid - 1`.
//   - If `arr[mid] < mid`: Search RIGHT: `low = mid + 1`.
//   - Complexity: O(log N) time, O(1) space.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // General GFG version: 1-based indexing, multiple answers possible
    vector<int> valueEqualToIndex(vector<int>& arr) {
        vector<int> result;
        int n = arr.size();

        for (int i = 0; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 1-based index comparison: arr[i] must equal (i + 1)
            if (arr[i] == i + 1) {
                result.push_back(arr[i]);
            }
        }

        return result;
    }

    // Classic Interview Variant: Sorted array of DISTINCT elements (O(log N))
    int binarySearchFixedPoint(const vector<int>& arr) {
        int low = 0;
        int high = (int)arr.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == mid) {
                return mid; // Fixed point located!
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Monotonic property: Since all elements are distinct and sorted,
            // if arr[mid] > mid, then arr[mid + k] >= arr[mid] + k > mid + k.
            // Hence, NO element to the right can ever equal its index! Search left!
            if (arr[mid] > mid) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return -1; // No fixed point exists
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {15, 2, 45, 12, 7};
    vector<int> res1 = sol.valueEqualToIndex(arr1);
    cout << "Fixed points in arr1 (1-based): ";
    for (int x : res1) cout << x << " ";
    cout << "\n";

    vector<int> arr2 = {-10, -5, 0, 3, 7};
    cout << "Fixed point in sorted distinct arr2 (0-based binary search): " 
         << sol.binarySearchFixedPoint(arr2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- General Case (All matches):
  * Time Complexity: O(N), single linear pass.
  * Space Complexity: O(1) auxiliary space.
- Sorted Distinct Case (Single fixed point):
  * Time Complexity: O(log N) logarithmic binary search.
  * Space Complexity: O(1) auxiliary space.

Key Takeaways:
- When `arr` is sorted and distinct, `f(i) = arr[i] - i` is monotonically non-decreasing,
  which transforms fixed point search into binary zero-finding.
*/
