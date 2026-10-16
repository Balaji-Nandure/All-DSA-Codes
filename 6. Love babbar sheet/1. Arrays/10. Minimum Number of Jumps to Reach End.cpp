// Problem: Minimum Number of Jumps to Reach End (Jump Game II)
// Link (LeetCode 45): https://leetcode.com/problems/jump-game-ii/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1
// Article: https://www.geeksforgeeks.org/dsa/minimum-number-jumps-reach-endset-2on-solution/
// Difficulty: Medium
// Topic: Array, Dynamic Programming, Greedy, BFS

/*
Problem Statement:
Given an array `arr[]` of non-negative integers of length `n`, each element represents your maximum jump 
length at that position.
Your goal is to reach the last index in the minimum number of jumps. 
Return the minimum number of jumps to reach the end, or -1 if the end cannot be reached.

Example 1:
Input: arr = [1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9]
Output: 3
Explanation:
- 1st jump from 1st element to 2nd element with value 3.
- 2nd jump from 2nd element to 5th element with value 9.
- 3rd jump from 5th element to the end.

Example 2:
Input: arr = [1, 4, 3, 2, 6, 7]
Output: 2

Example 3 (Unreachable):
Input: arr = [0, 10, 20]
Output: -1
Explanation: Cannot move anywhere from index 0.

Constraints:
- 1 <= arr.size() <= 10^5
- 0 <= arr[i] <= 10^5
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 8 (Kadane): Subarrays were contiguous sequences of size 1, 2, 3...
// - In Problem 10 (Minimum Jumps):
//   * Transitions are NON-CONTIGUOUS jumps: from index `i`, we can land on ANY index in `[i + 1 ... i + arr[i]]`.
//   * This is equivalent to finding the shortest path in an unweighted Directed Acyclic Graph (DAG)
//     where edges represent valid jump ranges!
//   * Instead of a full BFS queue, we can maintain the BFS frontier using only two pointers (`currEnd`, `maxReach`)!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Dynamic Programming (DP)
//   - Let dp[i] = min jumps to reach index i.
//   - dp[j] = min(dp[j], dp[i] + 1) for all j in [i+1 ... i+arr[i]].
//   - Complexity: O(N^2) time, O(N) space.
//   - Why Suboptimal: O(N^2) leads to Time Limit Exceeded for N = 10^5.
//
// Approach 2: Greedy Level-Order Traversal (Implicit BFS) - OPTIMAL & CHOSEN
//   - Maintain 3 variables:
//     * `jumps`: Number of jumps taken so far.
//     * `currEnd`: The furthest index reachable using the current number of jumps (current BFS level boundary).
//     * `maxReach`: The furthest index reachable in the NEXT jump among all indices explored in current level.
//   - Loop through indices `i` from `0` to `n - 2`:
//     * Update `maxReach = max(maxReach, i + arr[i])`.
//     * When `i == currEnd`: We have reached the boundary of our current jump!
//       We MUST make a jump: `jumps++`, `currEnd = maxReach`.
//       If `currEnd <= i`: We are stuck at a 0 with no forward progress -> return -1!
//   - Complexity: Exactly O(N) time in a single pass, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();

        // Base cases
        if (n <= 1) return 0;       // Already at the destination
        if (arr[0] == 0) return -1; // Cannot make any jump from the start

        int jumps = 0;
        int currEnd = 0;   // Furthest reach of current jump
        int maxReach = 0;  // Furthest reach possible for next jump

        // Traverse up to n - 2 (we do not need to jump from the last index)
        for (int i = 0; i < n - 1; i++) {
            // Update the maximum reach possible from any visited index
            maxReach = max(maxReach, i + arr[i]);

            // Early exit optimization: if we can already reach or exceed the destination
            if (maxReach >= n - 1) {
                return jumps + 1;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // When we reach currEnd, our current jump has been fully exhausted.
            // We MUST commit to taking another jump!
            if (i == currEnd) {
                jumps++;
                currEnd = maxReach;

                // If currEnd has not advanced beyond current index i,
                // it means all explored positions led to 0s -> stuck!
                if (currEnd <= i) {
                    return -1;
                }
            }
        }

        return (currEnd >= n - 1) ? jumps : -1;
    }
};

/*
Time Complexity: O(N)
- Exactly one linear pass from index 0 to n - 2. Constant operations per element: O(N).

Space Complexity: O(1) Auxiliary Space
- Uses only 3 integer tracking variables (`jumps`, `currEnd`, `maxReach`).

Key Insights:
1. Implicit BFS Window:
   - Range `[previousEnd + 1 ... currEnd]` represents all nodes at distance `jumps` from index 0.
   - We scan this window, determine the maximum reach for the next level, and jump when reaching the window boundary.
2. Why Loop Ends at `n - 2`:
   - If we looped up to `n - 1`, landing on the destination index would trigger an unnecessary additional jump
     whenever `currEnd == n - 1`!
*/
