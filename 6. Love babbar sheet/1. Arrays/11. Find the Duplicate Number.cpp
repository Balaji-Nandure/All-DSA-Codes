// Problem: Find the Duplicate Number in an Array of N+1 Integers
// Link (LeetCode 287): https://leetcode.com/problems/find-the-duplicate-number/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/find-duplicates-in-an-array/1
// Article: https://www.geeksforgeeks.org/dsa/find-duplicates-in-on-time-and-constant-extra-space/
// Difficulty: Medium
// Topic: Array, Two Pointers, Linked List Cycle Detection, Floyd's Tortoise and Hare

/*
Problem Statement:
Given an array of integers `nums` containing `n + 1` integers where each integer is in the range `[1, n]` inclusive.
There is only one repeated number in `nums`, return this repeated number.

You must solve the problem:
1. WITHOUT modifying the array (read-only).
2. Using only O(1) constant extra space.
3. In less than O(N^2) time complexity (optimally O(N)).

Example 1:
Input: nums = [1, 3, 4, 2, 2]
Output: 2

Example 2:
Input: nums = [3, 1, 3, 4, 2]
Output: 3

Example 3:
Input: nums = [3, 3, 3, 3, 3]
Output: 3

Constraints:
- 1 <= n <= 10^5
- nums.length == n + 1
- 1 <= nums[i] <= n
- All integers in nums appear only once except for precisely one integer which appears two or more times.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Reverse): Mutated array in-place.
// - In Problem 6 (Union/Intersection): Handled duplicates using sorting or sets.
// - In Problem 11 (Duplicate Number):
//   * Array mutation is STRICTLY FORBIDDEN.
//   * Extra memory allocation (sets/hashmaps) is STRICTLY FORBIDDEN (must be O(1)).
//   * We reinterpret the array as a LINKED LIST where index `i` points to `nums[i]`.
//   * Because duplicate values have multiple incoming pointers, they form the ENTRY POINT OF A CYCLE!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Sorting (`std::sort`)
//   - Complexity: O(N log N) time, O(1) or O(N) space.
//   - Why Rejected: Mutates the array (violates constraint 1).
//
// Approach 2: Hash Set / Frequency Array
//   - Complexity: O(N) time, O(N) space.
//   - Why Rejected: Uses O(N) memory (violates constraint 2).
//
// Approach 3: Negative Index Marking (`nums[abs(x)] = -nums[abs(x)]`)
//   - Complexity: O(N) time, O(1) space.
//   - Why Rejected: Mutates array elements during traversal (violates constraint 1).
//
// Approach 4: Floyd's Cycle Detection (Tortoise and Hare) - OPTIMAL & CHOSEN
//   - Model the array as a functional graph / linked list: `node -> nums[node]`.
//   - Since values are in [1, n], index 0 is never pointed to by any node (it is the head).
//   - Phase 1: Slow moves by 1 step (`nums[slow]`), Fast moves by 2 steps (`nums[nums[fast]]`).
//              They must collide inside the cycle.
//   - Phase 2: Reset `slow = nums[0]`. Move both `slow` and `fast` by 1 step at a time.
//              They are guaranteed to meet at the entrance of the cycle (the duplicate number)!
//   - Complexity: Exactly O(N) time, O(1) space, 100% read-only!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Floyd's Tortoise & Hare (O(N) Time, O(1) Space, Read-Only)
    // -------------------------------------------------------------------------
    int findDuplicate(vector<int>& nums) {
        // Phase 1: Detect the intersection point inside the cycle
        int slow = nums[0];
        int fast = nums[0];

        do {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // slow moves 1 step forward: slow = nums[slow]
            // fast moves 2 steps forward: fast = nums[nums[fast]]
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Phase 2: Find the entrance to the cycle
        // Reset slow pointer back to the start (head)
        slow = nums[0];

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Move both pointers at identical speed of 1 step.
        // By Floyd's mathematical proof:
        // Distance from head to cycle entrance == Distance from collision point to entrance.
        // Therefore, when they meet, they meet exactly at the cycle entrance (duplicate value)!
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow; // The duplicate element
    }

    // -------------------------------------------------------------------------
    // Method 2: Binary Search on Value Range [1 ... n] (Alternative O(N log N))
    // Useful if interviewer asks for an alternative read-only O(1) space method
    // -------------------------------------------------------------------------
    int findDuplicateBinarySearch(const vector<int>& nums) {
        int low = 1, high = nums.size() - 1;
        int duplicate = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Count how many numbers in array are <= mid
            int count = 0;
            for (int x : nums) {
                if (x <= mid) count++;
            }

            // By Pigeonhole Principle: if count > mid, duplicate lies in [low ... mid]
            if (count > mid) {
                duplicate = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return duplicate;
    }
};

/*
Time Complexity:
- Method 1 (Floyd's Algorithm): O(N) — Slow pointer traverses at most 2 * N nodes before meeting.
- Method 2 (Binary Search): O(N * log N) — log N iterations, each doing a full array scan of size N.

Space Complexity: O(1) Auxiliary Space
- Pure two-pointer traversal with zero auxiliary buffers or recursion.

Key Insights:
1. Why Cycle Entrance is the Duplicate:
   - If two distinct indices `i` and `j` contain the same value `K` (`nums[i] == nums[j] == K`),
     both nodes `i` and `j` have directed edges pointing to node `K`.
   - Node `K` has an in-degree >= 2, making it the junction point where paths converge into a cycle!
2. Index 0 is Safe as Head:
   - Because values are strictly in range [1, n], no element can point to index 0 (`nums[i] != 0`).
   - Thus, index 0 is guaranteed to be outside the cycle, acting as the valid linked list head.
*/
