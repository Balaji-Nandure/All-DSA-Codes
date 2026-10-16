// Problem: Count Triplets with Sum Smaller than a Given Value
// Link (GFG): https://www.geeksforgeeks.org/problems/count-triplets-with-sum-smaller-than-x5549/1
// Article: https://www.geeksforgeeks.org/dsa/count-triplets-with-sum-smaller-than-a-given-value/
// Difficulty: Medium
// Topic: Searching, Two Pointers, Sorting, Combinatorial Counting

/*
Problem Statement:
Given an array `arr` of distinct integers of size N and a value `sum`.
Count the number of triplets (i, j, k) such that:
    arr[i] + arr[j] + arr[k] < sum
    with i < j < k.

Example 1:
Input: N = 4, sum = 2, arr = [-2, 0, 1, 3]
Output: 2
Explanation: Triplets are (-2, 0, 1) and (-2, 0, 3).
(-2 + 0 + 1 = -1 < 2), (-2 + 0 + 3 = 1 < 2).

Example 2:
Input: N = 5, sum = 12, arr = [5, 1, 3, 4, 7]
Output: 4
Explanation: Triplets are (1, 3, 4), (1, 3, 5), (1, 3, 7), (1, 4, 5).

Constraints:
- 3 <= N <= 10^3
- -10^5 <= arr[i], sum <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Triplet Sum equal to X (Arrays Problem 28):
//   * We checked exact equality `arr[i] + arr[j] + arr[k] == sum`, 
//     so whenever `sum` matched, we only counted that specific pair and moved both pointers.
// - In Count Triplets with Sum < sum:
//   * We have an INEQUALITY (`< sum`).
//   * In a sorted array, if `arr[i] + arr[left] + arr[right] < sum`:
//     Then replacing `arr[right]` with ANY element strictly to the left of `right` 
//     (i.e., any element from `left + 1` up to `right`) will yield an EVEN SMALLER SUM!
//   * This allows us to BATCH COUNT `(right - left)` valid triplets in a SINGLE O(1) STEP!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Sorting + Convergent Two Pointers Batch Counting (Optimal & Chosen):
//   - Step 1: Sort `arr` in ascending order: O(N log N).
//   - Step 2: Loop `i` from 0 to `n - 3`:
//       * `left = i + 1`, `right = n - 1`.
//       * While `left < right`:
//           - `currentSum = arr[i] + arr[left] + arr[right]`.
//           - If `currentSum < sum`:
//               All elements from `left + 1` to `right` paired with `i` and `left` 
//               will also have sum < sum.
//               Add `(right - left)` directly to count!
//               Advance `left++` to explore larger sums.
//           - Else (`currentSum >= sum`):
//               Sum is too large -> decrease `right--`.
//   - Complexity: O(N^2) time, O(1) auxiliary space!
//   - Why this approach: Reduces an O(N^3) combinatorial check to O(N^2) through sorted batch counting.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long countTriplets(long long arr[], int n, long long sum) {
        // Step 1: Sort the array
        sort(arr, arr + n);

        long long totalCount = 0;

        // Step 2: Fix the first element arr[i]
        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                long long currentSum = arr[i] + arr[left] + arr[right];

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Sorted Array Invariant: If arr[i] + arr[left] + arr[right] < sum,
                // then arr[i] + arr[left] + arr[k] < sum for ALL k such that left < k <= right.
                // We instantly batch-add (right - left) triplets in O(1)!
                if (currentSum < sum) {
                    totalCount += (right - left);
                    left++; // Increment left to try larger candidate triplets
                } else {
                    right--; // Sum is >= sum, decrement right to reduce the sum
                }
            }
        }

        return totalCount;
    }
};

int main() {
    Solution sol;
    long long arr1[] = {-2, 0, 1, 3};
    int n1 = 4;
    long long sum1 = 2;
    cout << "Count triplets with sum < " << sum1 << ": " 
         << sol.countTriplets(arr1, n1, sum1) << "\n";

    long long arr2[] = {5, 1, 3, 4, 7};
    int n2 = 5;
    long long sum2 = 12;
    cout << "Count triplets with sum < " << sum2 << ": " 
         << sol.countTriplets(arr2, n2, sum2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N^2).
  * Sorting array takes O(N log N).
  * Outer loop runs N times, inner two-pointer loop runs N times = O(N^2).
- Space Complexity: O(1) auxiliary space (in-place sort).

Key Takeaways:
- Inequality constraints on sorted arrays allow instant batch-counting of entire ranges
  `(right - left)` without testing each pair.
*/
