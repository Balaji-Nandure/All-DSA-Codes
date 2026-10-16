// Problem: Find Common Elements in Three Sorted Arrays
// Link (Article): https://www.geeksforgeeks.org/dsa/find-common-elements-three-sorted-arrays/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/common-elements1132/1
// Difficulty: Easy
// Topic: Array, Three Pointers, Intersection

/*
Problem Statement:
Given three sorted arrays `arr1[]`, `arr2[]`, and `arr3[]`, find all elements that are common 
in all three arrays. 
Each common element should appear ONLY ONCE in the output (no duplicates), even if it appears 
multiple times in the original arrays.

Example 1:
Input: 
arr1 = [1, 5, 10, 20, 40, 80]
arr2 = [6, 7, 20, 80, 100]
arr3 = [3, 4, 15, 20, 30, 70, 80, 120]
Output: [20, 80]
Explanation: 20 and 80 are the only elements common to all three arrays.

Example 2:
Input:
arr1 = [1, 1, 1]
arr2 = [1, 1]
arr3 = [1]
Output: [1]

Constraints:
- 1 <= arr1.size(), arr2.size(), arr3.size() <= 10^5
- -10^5 <= arr1[i], arr2[i], arr3[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 6: We intersected TWO sorted arrays using 2 pointers.
// - In Problem 19:
//   * We are intersecting THREE sorted arrays simultaneously.
//   * Instead of 2 pointers, we manage 3 synchronized pointers (`i`, `j`, `k`).
//   * A single element must match in all 3 arrays before it can be added.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Hash Set
//   - Insert arr1 into set1, intersect with arr2 into set2, intersect with arr3: O(N1 + N2 + N3) space.
//   - Why Suboptimal: Allocates heap memory for sets when the arrays are ALREADY SORTED!
//
// Approach 2: Three Pointers (Synchronized Linear March) - OPTIMAL & CHOSEN
//   - Let pointers `i = 0`, `j = 0`, `k = 0`.
//   - While `i < n1 && j < n2 && k < n3`:
//     * Case 1: `arr1[i] == arr2[j] && arr2[j] == arr3[k]`
//       All three match! Add to result (avoiding duplicates). Advance all three pointers: `i++, j++, k++`.
//     * Case 2: `arr1[i] < arr2[j]` -> `arr1[i]` is strictly smaller, advance `i++`.
//     * Case 3: `arr2[j] < arr3[k]` -> `arr2[j]` is strictly smaller, advance `j++`.
//     * Case 4: Otherwise, `arr3[k]` is the smallest, advance `k++`.
//   - Complexity: Exactly O(N1 + N2 + N3) time, O(1) auxiliary space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> commonElements(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        int n1 = arr1.size(), n2 = arr2.size(), n3 = arr3.size();
        int i = 0, j = 0, k = 0;
        vector<int> result;

        while (i < n1 && j < n2 && k < n3) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If all three elements are equal, we found a common element!
            if (arr1[i] == arr2[j] && arr2[j] == arr3[k]) {
                // Ensure no duplicate insertion into result
                if (result.empty() || result.back() != arr1[i]) {
                    result.push_back(arr1[i]);
                }
                i++;
                j++;
                k++;
            }
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Advance ONLY the pointer pointing to the strictly smallest value among the three.
            // Since arrays are sorted ascending, a smaller value can NEVER match the larger values!
            else if (arr1[i] < arr2[j]) {
                i++;
            }
            else if (arr2[j] < arr3[k]) {
                j++;
            }
            else {
                k++;
            }
        }

        return result;
    }
};

/*
Time Complexity: O(N1 + N2 + N3)
- In every iteration of the while loop, at least one of the three pointers (`i`, `j`, `k`) advances.
- The loop terminates as soon as any one array is exhausted.
- Total iterations bounded by (N1 + N2 + N3): Linear time O(N1 + N2 + N3).

Space Complexity: O(1) Auxiliary Space
- Ignoring the output container, only three scalar index pointers are used.

Key Insights:
1. Greedily Advancing the Minimum:
   - If `arr1[i] < arr2[j]`, `arr1[i]` is too small to match `arr2[j]` or anything larger.
   - It is impossible for `arr1[i]` to be part of any 3-way match, so incrementing `i` is 100% safe.
2. In-place Deduplication:
   - `result.empty() || result.back() != arr1[i]` ensures output uniqueness without an expensive `std::set`.
*/
