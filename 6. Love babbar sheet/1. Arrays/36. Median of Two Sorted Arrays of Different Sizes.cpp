// Problem: Median of Two Sorted Arrays of Different Sizes
// Link (LeetCode 4): https://leetcode.com/problems/median-of-two-sorted-arrays/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/median-of-2-sorted-arrays-of-different-sizes/1
// Article: https://www.geeksforgeeks.org/dsa/median-of-two-sorted-arrays-of-different-sizes/
// Difficulty: Hard
// Topic: Array, Binary Search, Divide and Conquer

/*
Problem Statement:
Given two sorted arrays `nums1` of size `m` and `nums2` of size `n`. 
Find the median of the two sorted arrays after merging them into one sorted stream.
The overall run time complexity MUST be O(log(min(m, n))).

Example 1:
Input: nums1 = [1, 3], nums2 = [2]
Output: 2.00000
Explanation: Merged array = [1, 2, 3] and median is 2.

Example 2:
Input: nums1 = [1, 2], nums2 = [3, 4]
Output: 2.50000
Explanation: Merged array = [1, 2, 3, 4] and median is (2 + 3) / 2 = 2.5.

Example 3:
Input: nums1 = [0, 0], nums2 = [0, 0]
Output: 0.00000

Constraints:
- nums1.length == m, nums2.length == n
- 0 <= m, n <= 1000 (up to 10^5 on GFG)
- 1 <= m + n <= 2000 (up to 2 * 10^5)
- -10^6 <= nums1[i], nums2[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 35: Both arrays had identical length N (cut2 was simply n - cut1).
// - In Problem 36:
//   * Array lengths `m` and `n` can be vastly different (e.g., m = 2, n = 10000).
//   * Total length `m + n` can be either ODD or EVEN.
//   * Performing binary search on the larger array would take O(log(max(m, n))) and lead to 
//     negative indices for cut2!
//   * We must ALWAYS binary search on the SMALLER array!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Binary Search on Partition Cuts (THE OPTIMAL LEETCODE HARD SOLUTION)
//   - Step 1: Ensure `nums1` is the smaller array:
//     `if (m > n) return findMedianSortedArrays(nums2, nums1);`
//   - Step 2: Binary search on the cut of `nums1` in range `[0 ... m]`:
//     * Let `cut1 = (low + high) / 2`.
//     * Let `cut2 = (m + n + 1) / 2 - cut1`.
//       (The `+ 1` ensures the left half has exactly 1 extra element when total length is odd!).
//   - Step 3: Extract the 4 boundary elements around the cuts:
//     * `l1`: element left of cut1 in nums1  (INT_MIN if cut1 == 0)
//     * `r1`: element right of cut1 in nums1 (INT_MAX if cut1 == m)
//     * `l2`: element left of cut2 in nums2  (INT_MIN if cut2 == 0)
//     * `r2`: element right of cut2 in nums2 (INT_MAX if cut2 == n)
//   - Step 4: Validate the cut:
//     * If `l1 <= r2 && l2 <= r1`: Valid partition!
//       - If total length is ODD:  `median = max(l1, l2)`
//       - If total length is EVEN: `median = (max(l1, l2) + min(r1, r2)) / 2.0`
//     * If `l1 > r2`: `cut1` took too many elements from `nums1` -> `high = cut1 - 1`.
//     * If `l2 > r1`: `cut1` took too few elements from `nums1` -> `low = cut1 + 1`.
//   - Complexity: Exactly O(log(min(m, n))) time, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Always binary search on the smaller array!
        // 1. Optimizes time to O(log(min(m, n))).
        // 2. Guarantees cut2 is always >= 0 and <= n, completely eliminating out-of-bounds errors!
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int low = 0, high = m;

        while (low <= high) {
            int cut1 = low + (high - low) / 2;
            // The '+ 1' ensures the left partition contains the median element when (m + n) is odd
            int cut2 = (m + n + 1) / 2 - cut1;

            // Boundary values around the cuts
            int l1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
            int l2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
            int r1 = (cut1 == m) ? INT_MAX : nums1[cut1];
            int r2 = (cut2 == n) ? INT_MAX : nums2[cut2];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Valid partition check:
            // Since nums1 and nums2 are individually sorted, l1 <= r1 and l2 <= r2 are already true.
            // We only need to check the cross-conditions: l1 <= r2 and l2 <= r1!
            if (l1 <= r2 && l2 <= r1) {
                // If total number of elements is odd, max of the left partition is the median
                if ((m + n) % 2 == 1) {
                    return max(l1, l2);
                }
                // If total number of elements is even, average of max(left) and min(right)
                return (max(l1, l2) + min(r1, r2)) / 2.0;
            }
            else if (l1 > r2) {
                // l1 is too large, shift cut1 leftwards
                high = cut1 - 1;
            }
            else {
                // l2 > r1, meaning cut1 is too small, shift cut1 rightwards
                low = cut1 + 1;
            }
        }

        return 0.0;
    }
};

/*
Time Complexity: O(log(min(M, N)))
- Binary search operates exclusively on the array with smaller length.
- Search space is bounded by [0 ... min(M, N)].
- In each step, search space is halved: strictly O(log(min(M, N))).
- Example: If M = 10^5 and N = 10, binary search takes at most log2(10) ≈ 4 iterations!

Space Complexity: O(1) Auxiliary Space
- Uses only scalar pointers and cut boundary variables. Zero auxiliary allocations.

Key Insights:
1. Why (M + N + 1) / 2 Works for Both Odd and Even:
   - For even length (e.g. 10): (10 + 1) / 2 = 5 elements in left partition, 5 in right.
   - For odd length (e.g. 11):  (11 + 1) / 2 = 6 elements in left partition, 5 in right.
   - The extra element always resides in the left partition, meaning the odd median is simply `max(l1, l2)`.
2. INT_MIN and INT_MAX Sentinels:
   - Using sentinels handles edge cases where all elements of one array lie entirely on one side of the median.
*/
