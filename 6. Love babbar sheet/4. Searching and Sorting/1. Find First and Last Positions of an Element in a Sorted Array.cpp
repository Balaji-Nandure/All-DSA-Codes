// Problem: Find First and Last Positions of an Element in a Sorted Array
// Link (GFG): https://www.geeksforgeeks.org/problems/first-and-last-occurrences-of-x3116/1
// Article: https://www.geeksforgeeks.org/dsa/find-first-and-last-positions-of-an-element-in-a-sorted-array/
// Difficulty: Medium
// Topic: Searching, Binary Search, Boundary Conditions

/*
Problem Statement:
Given a sorted array `arr` with possibly duplicate elements, find the first and 
last occurrences of an element `x` in the given array.
If the number `x` is not found in the array, return `{-1, -1}`.

Example 1:
Input: arr = [1, 3, 5, 5, 5, 5, 67, 123, 125], x = 5
Output: [2, 5]
Explanation: First occurrence of 5 is at index 2, and last occurrence is at index 5.

Example 2:
Input: arr = [1, 3, 5, 5, 5, 5, 7, 123, 125], x = 7
Output: [6, 6]

Example 3:
Input: arr = [1, 2, 3], x = 4
Output: [-1, -1]

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i], x <= 10^9
- arr is sorted in non-decreasing order.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Standard Binary Search:
//   * The algorithm halts the instant `arr[mid] == x`, returning `mid`.
//   * However, `mid` could be ANY arbitrary duplicate of `x` (e.g. In [5, 5, 5, 5], 
//     standard binary search might land on index 1 or 2).
// - In First and Last Occurrence Search:
//   * Finding `arr[mid] == x` is NOT enough to terminate!
//   * For FIRST occurrence: Even after finding a match, a duplicate might exist 
//     further left, so we record `ans = mid` and force the search to continue in the 
//     LEFT half (`high = mid - 1`).
//   * For LAST occurrence: Record `ans = mid` and force the search to continue in the 
//     RIGHT half (`low = mid + 1`).

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Linear Scan
//   - Traverse from left to find first, from right to find last.
//   - Complexity: O(N) time. Suboptimal; violates O(log N) requirements for sorted data.
//
// Approach 2: Standard Binary Search + Linear Expansion
//   - Find `mid` where `arr[mid] == x`, then expand left and right linearly.
//   - Complexity: O(N) worst case (e.g. array of all 5s). Still fails logarithmic guarantee.
//
// Approach 3: Two Independent Binary Searches (Optimal & Chosen)
//   - Search 1 (`findFirst`):
//       * If `arr[mid] == x`: candidate found! Record `first = mid`, then continue left: `high = mid - 1`.
//       * If `arr[mid] < x`: `low = mid + 1`.
//       * If `arr[mid] > x`: `high = mid - 1`.
//   - Search 2 (`findLast`):
//       * If `arr[mid] == x`: candidate found! Record `last = mid`, then continue right: `low = mid + 1`.
//       * If `arr[mid] < x`: `low = mid + 1`.
//       * If `arr[mid] > x`: `high = mid - 1`.
//   - Complexity: O(log N) time, O(1) space.
//   - Why this approach: Guaranteed logarithmic upper bound regardless of duplicate distribution.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    int findFirst(const vector<int>& arr, int n, int x) {
        int low = 0, high = n - 1;
        int firstIdx = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == x) {
                firstIdx = mid;
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Continue searching strictly in the left half to locate any earlier occurrence!
                high = mid - 1;
            } else if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return firstIdx;
    }

    int findLast(const vector<int>& arr, int n, int x) {
        int low = 0, high = n - 1;
        int lastIdx = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == x) {
                lastIdx = mid;
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Continue searching strictly in the right half to locate any later occurrence!
                low = mid + 1;
            } else if (arr[mid] < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return lastIdx;
    }

public:
    vector<int> firstAndLast(vector<int>& arr, int n, int x) {
        int first = findFirst(arr, n, x);
        if (first == -1) {
            return {-1, -1}; // If not present at all, both are -1
        }
        int last = findLast(arr, n, x);
        return {first, last};
    }
};

int main() {
    Solution sol;
    vector<int> arr = {1, 3, 5, 5, 5, 5, 67, 123, 125};
    int x = 5;

    vector<int> res = sol.firstAndLast(arr, arr.size(), x);
    cout << "Target " << x << " appears from index " << res[0] << " to " << res[1] << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(log N) + O(log N) = O(log N), exactly two binary search passes.
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Modifying binary search to record `ans = mid` and persist in the direction of interest
  is the foundation of `lower_bound` and `upper_bound`.
*/
