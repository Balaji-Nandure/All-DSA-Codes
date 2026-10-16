// Problem: Sort an Array of 0s, 1s and 2s (Dutch National Flag Problem)
// Link (LeetCode 75): https://leetcode.com/problems/sort-colors/
// Link (GFG): https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s4231/1
// Difficulty: Medium
// Topic: Array, Two Pointers, Dutch National Flag Algorithm, In-place Sorting

/*
Problem Statement:
Given an array `nums` with `n` objects colored red, white, or blue, sort them in-place so that 
objects of the same color are adjacent, with the colors in the order red, white, and blue.
We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function, and in one-pass with O(1) extra space.

Example 1:
Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Example 2:
Input: nums = [2,0,1]
Output: [0,1,2]

Constraints:
- n == nums.length
- 1 <= n <= 10^5 (or 300 on LeetCode)
- nums[i] is either 0, 1, or 2.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Reverse Array): Used 2 pointers at the extremes (left & right) to reverse.
// - In Problem 2 (Min & Max): Pairwise comparisons to find 2 values without modifying the array.
// - In Problem 3 (Kth Element): QuickSelect partitioned around 1 pivot value into 2 partitions (<= and >).
// - In Problem 4 (Sort 0s, 1s, 2s):
//   * We need a 3-WAY PARTITION (3 distinct buckets: 0s, 1s, 2s).
//   * A single pivot or standard two pointers is insufficient.
//   * We use the 3-pointer Dutch National Flag (DNF) invariant to categorize in a SINGLE pass!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Full Sorting (`std::sort`)
//   - Complexity: O(N log N) time, O(1) space.
//   - Why NOT: Fails the problem constraint of sorting without library sort, and wastes N log N time.
//
// Approach 2: Counting Sort (2-Pass Approach)
//   - Count frequencies of 0, 1, and 2 in pass 1.
//   - Overwrite array with count0 zeros, count1 ones, count2 twos in pass 2.
//   - Complexity: O(2N) time, O(1) space.
//   - Why Suboptimal: Requires 2 full traversals of the array. Interviewers explicitly ask for a 1-pass solution.
//
// Approach 3: Dutch National Flag (DNF) Algorithm (1-Pass, 3 Pointers) - OPTIMAL & CHOSEN
//   - Devised by Edsger Dijkstra.
//   - Divides the array into 4 virtual regions using 3 pointers (`low`, `mid`, `high`):
//     1. [0 ... low - 1]     : All 0s (Extreme Left)
//     2. [low ... mid - 1]   : All 1s (Middle)
//     3. [mid ... high]      : Unexplored elements (Shrinking active window)
//     4. [high + 1 ... n - 1]: All 2s (Extreme Right)
//   - Loop invariant: While `mid <= high`, examine `nums[mid]`:
//     * If `nums[mid] == 0`: swap with `nums[low]`, low++, mid++
//     * If `nums[mid] == 1`: mid++ (already in middle bucket)
//     * If `nums[mid] == 2`: swap with `nums[high]`, high-- (do NOT increment mid!)
//   - Complexity: Exactly O(N) time in 1 pass, O(1) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Dutch National Flag Algorithm (Optimal 1-Pass, O(1) Space)
    // -------------------------------------------------------------------------
    void sortColors(vector<int>& nums) {
        int low = 0;
        int mid = 0;
        int high = nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // When nums[mid] is 0, we swap it with nums[low].
                // Since the region [low ... mid - 1] ONLY contains 1s, the element swapped
                // into index `mid` is GUARANTEED to be a 1!
                // Hence, it is completely safe to advance BOTH low and mid!
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            }
            else if (nums[mid] == 1) {
                // 1 belongs in the middle region [low ... mid - 1], simply advance mid
                mid++;
            }
            else { // nums[mid] == 2
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // We swap nums[mid] with nums[high] and decrement high.
                // BUT WE DO NOT INCREMENT `mid`!
                // Why? Because the element brought from nums[high] was UNEXPLORED.
                // It could be a 0, 1, or 2! We MUST re-examine nums[mid] in the next iteration.
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }

    // -------------------------------------------------------------------------
    // Method 2: Counting Sort (2-Pass Approach for comparison)
    // -------------------------------------------------------------------------
    void sortColorsCounting(vector<int>& nums) {
        int c0 = 0, c1 = 0, c2 = 0;
        for (int x : nums) {
            if (x == 0) c0++;
            else if (x == 1) c1++;
            else c2++;
        }

        int idx = 0;
        while (c0--) nums[idx++] = 0;
        while (c1--) nums[idx++] = 1;
        while (c2--) nums[idx++] = 2;
    }
};

/*
Time Complexity: O(N)
- Dutch National Flag: In every iteration, either `mid` increases by 1 or `high` decreases by 1.
- Total iterations bounded strictly by N. Exactly 1 pass: O(N).

Space Complexity: O(1) Auxiliary Space
- Pure in-place pointer manipulation. Zero extra heap or stack memory allocated.

Key Insights:
1. The Asymmetry between Swapping with `low` vs `high`:
   - `swap(nums[low], nums[mid])`: Increment both `low++` and `mid++` (swapped element is known to be 1).
   - `swap(nums[mid], nums[high])`: Decrement only `high--` (`mid` stays put to evaluate the unknown incoming element).
   - Forgetting to keep `mid` unchanged when swapping with `high` is the #1 bug in this problem!
2. Broad Application:
   - This 3-way partitioning is the foundation of 3-Way QuickSort (Bentley-McIlroy algorithm),
     which prevents O(N^2) degradation on arrays with high duplicate density.
*/
