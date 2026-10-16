// Problem: Find a Pair with a Given Difference
// Link (GFG): https://www.geeksforgeeks.org/problems/find-pair-given-difference1559/1
// Article: https://www.geeksforgeeks.org/dsa/find-a-pair-with-the-given-difference/
// Difficulty: Easy / Medium
// Topic: Searching, Two Pointers, Hash Set, Sorting

/*
Problem Statement:
Given an array `arr[]` of size n and an integer x. Return 1 (or true) if there exists 
a pair of elements in the array whose absolute difference is x, i.e.:
    |arr[i] - arr[j]| = x   and   i != j.
Otherwise return -1 (or false).

Example 1:
Input: n = 6, x = 78, arr = [5, 20, 3, 2, 5, 80]
Output: 1
Explanation: Pair (2, 80) has difference 80 - 2 = 78.

Example 2:
Input: n = 5, x = 45, arr = [90, 70, 20, 80, 50]
Output: -1
Explanation: No pair has difference 45.

Example 3 (Zero Difference):
Input: n = 4, x = 0, arr = [1, 2, 3, 1]
Output: 1 (Pair (1, 1) has difference 0 at distinct indices 0 and 3).

Constraints:
- 1 <= n <= 10^5
- 0 <= x <= 10^5
- 1 <= arr[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Two Sum (Arrays Problem 18 - Count Pairs with Given Sum):
//   * Two pointers move CONVERGENTLY from opposite ends towards the center (`left -> <- right`).
//   * When `sum < target`, `left++`; when `sum > target`, `right--`.
// - In Pair with Given Difference (`arr[j] - arr[i] = x`):
//   * Convergent two pointers FAIL because increasing both or decreasing both can increase difference!
//   * Instead, Two Pointers must move in the SAME DIRECTION (parallel pursuit: `i = 0`, `j = 1`).
//   * Critical pitfall when `x = 0`: We must enforce `i != j` so an element cannot pair with itself!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Hash Set
//   - Maintain an `unordered_set<int> seen`.
//   - For each element `v`:
//       * If `seen.count(v + x) || seen.count(v - x)`: Return 1.
//       * `seen.insert(v)`.
//   - Complexity: O(N) time, O(N) space.
//
// Approach 2: Sorting + Parallel Two Pointers (Optimal for O(1) Space)
//   - Sort `arr`: O(N log N).
//   - Initialize `i = 0`, `j = 1`.
//   - While `i < n && j < n`:
//       * If `i != j && arr[j] - arr[i] == x`: Return 1!
//       * If `arr[j] - arr[i] < x`: Difference is too small -> widen it by `j++`.
//       * If `arr[j] - arr[i] > x`: Difference is too large -> shrink it by `i++`.
//       * If `i == j`: Advance `j++` (distinct elements constraint).
//   - Complexity: O(N log N) time, O(1) auxiliary space!
//   - Why this approach: Avoids hash collision overhead and uses zero dynamic heap memory.

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // Approach 2: Sorting + Parallel Two Pointers (O(1) Auxiliary Space)
    bool findPairTwoPointers(vector<int>& arr, int size, int x) {
        sort(arr.begin(), arr.end());

        int i = 0;
        int j = 1;

        while (i < size && j < size) {
            int diff = arr[j] - arr[i];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Must enforce i != j to prevent pairing an element with itself when x == 0!
            if (i != j && diff == x) {
                return true;
            } else if (diff < x) {
                j++; // Need a larger difference, expand right pointer
            } else {
                i++; // Need a smaller difference, shrink left pointer
            }

            // If left catches up with right, advance right pointer forward
            if (i == j) {
                j++;
            }
        }

        return false;
    }

    // Approach 1: Hash Set (O(N) Time, O(N) Space)
    bool findPairHashSet(const vector<int>& arr, int size, int x) {
        unordered_set<int> seen;

        for (int val : arr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Searching for complement: |val - other| = x means other is either (val + x) or (val - x)
            if (seen.find(val + x) != seen.end() || seen.find(val - x) != seen.end()) {
                return true;
            }
            seen.insert(val);
        }

        return false;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {5, 20, 3, 2, 5, 80};
    int x1 = 78;
    cout << "Pair with diff " << x1 << " in arr1? " 
         << (sol.findPairTwoPointers(arr1, arr1.size(), x1) ? "Yes" : "No") << "\n";

    vector<int> arr2 = {90, 70, 20, 80, 50};
    int x2 = 45;
    cout << "Pair with diff " << x2 << " in arr2? " 
         << (sol.findPairTwoPointers(arr2, arr2.size(), x2) ? "Yes" : "No") << "\n";

    vector<int> arr3 = {1, 2, 3, 1};
    int x3 = 0;
    cout << "Pair with diff " << x3 << " in arr3 (x=0 test)? " 
         << (sol.findPairTwoPointers(arr3, arr3.size(), x3) ? "Yes" : "No") << "\n";

    return 0;
}

/*
Complexity Analysis:
- Sorting + Two Pointers:
  * Time Complexity: O(N log N) for sorting + O(N) for parallel two-pointer march.
  * Space Complexity: O(1) auxiliary space.
- Hash Set:
  * Time Complexity: O(N) average time.
  * Space Complexity: O(N) auxiliary space.

Key Takeaways:
- Two Sum uses convergent pointers (`left -> <- right`), whereas Difference Search 
  requires parallel pursuit pointers (`i -> j ->`) to preserve monotonicity.
*/
