// Problem: Maximum Sum Such that No Two Elements are Adjacent (Stickler Thief / House Robber)
// Link (GFG): https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1
// Article: https://www.geeksforgeeks.org/dsa/maximum-sum-such-that-no-two-elements-are-adjacent/
// Difficulty: Medium
// Topic: Dynamic Programming, State Machine, O(1) Space DP

/*
Problem Statement:
Stickler the thief wants to loot money from a society having N houses in a single row.
A thief cannot loot two adjacent houses because the security alarms will be triggered.
Find the maximum amount of money Stickler can loot such that no two chosen houses are adjacent.

Example 1:
Input: arr = [6, 5, 5, 7, 4]
Output: 15
Explanation: Loot houses 0, 2, and 4 (indices): 6 + 5 + 4 = 15.

Example 2:
Input: arr = [1, 5, 3]
Output: 5
Explanation: Loot house 1: sum = 5.

Example 3:
Input: arr = [5, 5, 10, 100, 10, 5]
Output: 110
Explanation: 5 + 100 + 5 = 110.

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^4
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Kadane's Algorithm (Arrays Problem 8):
//   * Elements HAD TO BE strictly contiguous.
// - In Maximum Sum without Adjacent Elements:
//   * Elements CANNOT be contiguous!
//   * Picking element `arr[i]` strictly FORBIDS picking `arr[i-1]`.
//   * This 2-state decision ("Pick" vs "Don't Pick") creates a classic Markov state machine 
//     that can be solved in O(N) time with only two scalar tracking variables!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// 2-State Dynamic Programming with O(1) Space (Optimal & Chosen):
//   - At any house `i`, there are two mutually exclusive states:
//       1. `incl`: Maximum sum if house `i` is ROBBED.
//          Because adjacent house `i-1` cannot be robbed, `incl = prev_excl + arr[i]`.
//       2. `excl`: Maximum sum if house `i` is NOT ROBBED.
//          Since house `i` is skipped, we take the best of previous include or exclude:
//          `excl = max(prev_incl, prev_excl)`.
//   - Complexity: Strict O(N) single pass, O(1) auxiliary space!
//   - Why this approach: Outperforms array-based DP (`vector<int> dp(n)`) by eliminating 
//     cache misses and zero heap allocations.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int FindMaxSum(vector<int>& arr, int n) {
        if (n == 0) return 0;
        if (n == 1) return arr[0];

        int incl = arr[0]; // Best sum including the first element
        int excl = 0;      // Best sum excluding the first element

        for (int i = 1; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // State 1: To include arr[i], we MUST exclude arr[i-1] (previous excl)
            int new_incl = excl + arr[i];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // State 2: To exclude arr[i], we take the maximum possible sum up to arr[i-1]
            int new_excl = max(incl, excl);

            incl = new_incl;
            excl = new_excl;
        }

        return max(incl, excl);
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {6, 5, 5, 7, 4};
    cout << "Max loot in arr1: " << sol.FindMaxSum(arr1, arr1.size()) << "\n";

    vector<int> arr2 = {5, 5, 10, 100, 10, 5};
    cout << "Max loot in arr2: " << sol.FindMaxSum(arr2, arr2.size()) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), single pass over the array of size N.
- Space Complexity: O(1) auxiliary space (using only two integer state variables).

Key Takeaways:
- Non-adjacent sequence maximization is the prototype for state-machine dynamic programming 
  (House Robber series, Buy/Sell Stock with Cooldown).
*/
