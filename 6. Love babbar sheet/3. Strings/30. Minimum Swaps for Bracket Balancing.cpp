// Problem: Minimum Swaps for Bracket Balancing
// Link (GFG): https://www.geeksforgeeks.org/problems/minimum-swaps-for-bracket-balancing2704/1
// Article: https://www.geeksforgeeks.org/dsa/minimum-swaps-bracket-balancing/
// Difficulty: Medium
// Topic: String, Greedy, Two Pointers / Balance Invariant

/*
Problem Statement:
You are given a string S of 2N characters consisting of N '[' and N ']'.
A string of brackets is balanced if brackets are properly nested.
In one operation, you can swap ANY TWO ADJACENT brackets.
Find the minimum number of ADJACENT swaps required to balance the string.

Example 1:
Input: S = "[]][]["
Output: 2
Explanation:
First swap S[2] and S[3] -> "[][]["
Second swap S[4] and S[5] -> "[][][]", which is balanced.
Total swaps = 2.

Example 2:
Input: S = "[[][]]"
Output: 0 (Already balanced)

Constraints:
- 1 <= S.length() <= 10^5
- Total count of '[' equals total count of ']' = N.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 21 (Count Bracket Reversals):
//   * The operation was REVERSING a bracket in-place (`{` -> `}`).
// - In Problem 30 (Adjacent Swaps for Balancing):
//   * Total counts of '[' and ']' are already equal!
//   * The operation is SWAPPING ADJACENT BRACKETS (`swap(S[i], S[i+1])`).
//   * Whenever the running balance `count` drops below 0 (more ']' than '['), 
//     there is an imbalance deficit.
//   * The next '[' encountered in the string MUST be shifted left across all currently 
//     unmatched ']' brackets! Moving across `k` brackets requires exactly `k` adjacent swaps.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Vector of '[' indices
//   - Pre-record indices of all '[' in a vector.
//   - Track imbalance and calculate distance to next available '['.
//   - Complexity: O(N) time, O(N) space.
//
// Approach 2: O(1) Space Invariant Balance Tracking (Optimal & Chosen)
//   - Maintain `balance = 0` (count of '[' minus count of ']') and `swaps = 0`.
//   - Traverse string character by character:
//       * If `S[i] == '['`:
//           - If `balance < 0`:
//               Current state is in deficit (there are `-balance` excess closing brackets).
//               This opening bracket must be shifted left past those `-balance` brackets!
//               Add `-balance` to `swaps`!
//           - Increment `balance++`.
//       * If `S[i] == ']'`:
//           - Decrement `balance--`.
//   - Return `swaps`.
//   - Complexity: O(N) single pass, O(1) auxiliary space!
//   - Why this approach: Avoids storing positions in arrays or simulating physical swaps.

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int minimumNumberOfSwaps(string S) {
        int balance = 0; // Tracks surplus/deficit of open brackets
        int swaps = 0;   // Accumulates total adjacent swaps required

        for (char ch : S) {
            if (ch == '[') {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // If balance is negative, there are |balance| unmatched ']' preceding this '['.
                // To resolve the invalidity, this '[' must swap across all those |balance| brackets.
                // Each step across a bracket costs 1 adjacent swap!
                if (balance < 0) {
                    swaps += (-balance);
                }
                balance++;
            } else {
                // Closing bracket encountered
                balance--;
            }
        }

        return swaps;
    }
};

int main() {
    Solution sol;
    string s1 = "[]][][";
    cout << "Min adjacent swaps for \"" << s1 << "\": " 
         << sol.minimumNumberOfSwaps(s1) << "\n";

    string s2 = "[[][]]";
    cout << "Min adjacent swaps for \"" << s2 << "\": " 
         << sol.minimumNumberOfSwaps(s2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), single pass over string S.
- Space Complexity: O(1) auxiliary space (no vector or stack needed).

Key Takeaways:
- Accumulated negative prefix deficits in balanced-component problems directly represent
  the exact distance displacement cost for adjacent transposition swaps.
*/
