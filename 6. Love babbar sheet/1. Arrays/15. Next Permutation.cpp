// Problem: Next Permutation
// Link (LeetCode 31): https://leetcode.com/problems/next-permutation/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/next-permutation5226/1
// Article: https://www.geeksforgeeks.org/cpp/lexicographically-next-permutation-in-cpp/
// Difficulty: Medium
// Topic: Array, Two Pointers, Combinatorics, In-place Reversal

/*
Problem Statement:
A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
The next permutation of an array of integers is the next lexicographically greater permutation.
If no such arrangement is possible (i.e., the array is in descending order), the array must be 
rearranged to the lowest possible order (i.e., sorted in ascending order).

The replacement must be in-place and use only constant extra memory O(1).

Example 1:
Input: nums = [1, 2, 3]
Output: [1, 3, 2]

Example 2:
Input: nums = [3, 2, 1]
Output: [1, 2, 3]

Example 3:
Input: nums = [1, 1, 5]
Output: [1, 5, 1]

Example 4:
Input: nums = [2, 1, 5, 4, 3, 0, 0]
Output: [2, 3, 0, 0, 1, 4, 5]

Constraints:
- 1 <= nums.length <= 10^5
- 0 <= nums[i] <= 100
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - Previous array problems worked with sums, intervals, or simple elements.
// - In Problem 15:
//   * We are navigating the LEXICOGRAPHICAL ORDER of permutations.
//   * A suffix that is descending (e.g., [5, 4, 3, 0]) is already at its MAXIMUM possible permutation.
//   * To make the SMALLEST possible increase, we must alter the prefix as far to the right as possible!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Algorithm (Narayana Pandita's Algorithm - Single Pass O(N)):
//   Step 1 (Find Breakpoint / Dip from Right):
//     - Scan from right to left to find the first index `i` where `nums[i] < nums[i + 1]`.
//     - The suffix `nums[i + 1 ... n - 1]` is in strictly descending order.
//   Step 2 (Edge Case - Entire Array Descending):
//     - If no such `i` exists (i == -1), the array is at its absolute maximum (e.g., [3, 2, 1]).
//     - Reverse the entire array to return the smallest permutation [1, 2, 3].
//   Step 3 (Find Next Larger Element from Right):
//     - Scan from right to left to find the smallest number in the suffix that is greater than `nums[i]`.
//     - That is: find largest index `j` such that `nums[j] > nums[i]`.
//   Step 4 (Swap):
//     - Swap `nums[i]` and `nums[j]`.
//   Step 5 (Reverse Suffix):
//     - The suffix `nums[i + 1 ... n - 1]` is still in descending order.
//     - Reverse it to make it ASCENDING (lexicographically smallest possible tail)!
//   Complexity: Exactly O(N) time in 1 pass, O(1) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;

        // Step 1: Find the first dip from the right
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // While scanning backwards, if nums[i] >= nums[i+1], that suffix is descending (maximized).
        // The first index i where nums[i] < nums[i+1] is where we CAN make a minimal increase!
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // Step 2 & 3: If a valid dip was found, swap with the next greater element in the suffix
        if (i >= 0) {
            int j = n - 1;
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Search from the right for the first element strictly greater than nums[i].
            // Because the suffix is descending, the first one encountered from the right
            // is the SMALLEST element greater than nums[i]!
            while (nums[j] <= nums[i]) {
                j--;
            }
            // Swap to promote the next larger digit into position i
            swap(nums[i], nums[j]);
        }

        // Step 4: Reverse the suffix starting from i + 1 to the end
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // After the swap, the suffix is STILL in descending order.
        // Reversing it converts it into ascending order, ensuring the suffix is minimized!
        reverse(nums.begin() + i + 1, nums.end());
    }
};

/*
Time Complexity: O(N)
- Finding the dip index `i`: at most O(N) steps.
- Finding the swap index `j`: at most O(N) steps.
- Reversing the suffix: at most O(N / 2) swaps.
- Overall Time Complexity: O(N) linear time.

Space Complexity: O(1) Auxiliary Space
- Pure in-place swaps and pointer shifts. Zero auxiliary space.

Key Insights:
1. Why the Suffix is still Descending after Swap:
   - `nums[j]` was chosen as the smallest element in the suffix greater than `nums[i]`.
   - Swapping `nums[i]` and `nums[j]` maintains the monotonic decreasing property of the suffix.
   - Because it is already sorted in reverse, a simple `reverse()` sorts it ascending in O(N/2) without an O(N log N) sort!
2. Standard Library Equivalent:
   - This exact algorithm powers C++ STL `std::next_permutation(nums.begin(), nums.end())`.
*/
