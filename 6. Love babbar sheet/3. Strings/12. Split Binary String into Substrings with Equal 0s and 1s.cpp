// Problem: Split the Binary String into Substrings with Equal 0s and 1s
// Link (GFG): https://www.geeksforgeeks.org/problems/split-the-binary-string-into-substrings-with-equal-number-of-0s-and-1s/1
// Article: https://www.geeksforgeeks.org/dsa/split-the-binary-string-into-substrings-with-equal-number-of-0s-and-1s/
// Difficulty: Easy / Medium
// Topic: String, Greedy, Prefix Counting

/*
Problem Statement:
Given a binary string str of length N. The task is to find the maximum count of 
consecutive substrings into which str can be split such that each substring contains 
an equal number of 0s and 1s.
If it is impossible to split the entire string such that all pieces have equal 0s and 1s, return -1.

Example 1:
Input: str = "0100110101"
Output: 4
Explanation: The 4 valid substrings are "01", "0011", "01", "01".

Example 2:
Input: str = "0111100010"
Output: 3
Explanation: The 3 valid substrings are "01", "111000", "10".

Example 3:
Input: str = "0000"
Output: -1
Explanation: Total count of 0s is 4, count of 1s is 0. Impossible to achieve equal counts.

Constraints:
- 1 <= N <= 10^5
- str consists only of '0' and '1'
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 21 (Subarray with 0 Sum):
//   * We found whether AT LEAST ONE zero-sum sub-segment exists using a prefix sum hash set.
// - In Strings Problem 12 (Maximum Balanced Binary Splits):
//   * We must partition the ENTIRE string contiguously into the MAXIMUM possible number 
//     of balanced sub-blocks.
//   * The key greedy property: Making a cut at the EARLIEST moment `count0 == count1` 
//     is always globally optimal because any larger balanced block containing a smaller 
//     balanced prefix can simply be split into two valid balanced blocks!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Greedy Prefix Balance Counter (Optimal & Chosen)
//   - Maintain two counters: `count0 = 0`, `count1 = 0`, and split counter `ans = 0`.
//   - Iterate through string from left to right:
//       * If `str[i] == '0'`: `count0++`.
//       * If `str[i] == '1'`: `count1++`.
//       * If `count0 == count1`: We have reached a point where the prefix has equal 0s and 1s.
//         Increment `ans++`. (Greedily commit this cut immediately!).
//   - After traversing the entire string:
//       * If `count0 != count1`: The string as a whole does not have equal numbers of 0s and 1s, 
//         meaning the trailing fragment cannot be balanced! Return `-1`.
//       * Else: Return `ans`.
//   - Complexity: O(N) single pass, O(1) auxiliary space!
//   - Why this approach: It is mathematically impossible to achieve a higher count than 
//     cutting at every zero-crossing of the balance counter.

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int maxSubStr(string str) {
        int count0 = 0;
        int count1 = 0;
        int maxSplits = 0;

        for (char ch : str) {
            if (ch == '0') {
                count0++;
            } else if (ch == '1') {
                count1++;
            }

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The instant count0 == count1, we have found the smallest independent balanced block.
            // Cutting greedily here guarantees the maximum possible total count of splits!
            if (count0 == count1) {
                maxSplits++;
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If total 0s and total 1s at the end of the entire string are unequal,
        // the remaining suffix can never be balanced, making the entire partition invalid!
        if (count0 != count1) {
            return -1;
        }

        return maxSplits;
    }
};

int main() {
    Solution sol;
    string s1 = "0100110101";
    cout << "Max splits for \"" << s1 << "\": " << sol.maxSubStr(s1) << "\n";

    string s2 = "0111100010";
    cout << "Max splits for \"" << s2 << "\": " << sol.maxSubStr(s2) << "\n";

    string s3 = "0000";
    cout << "Max splits for \"" << s3 << "\": " << sol.maxSubStr(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), single linear scan through the string of length N.
- Space Complexity: O(1) auxiliary space (only a couple of integer counters).

Key Takeaways:
- Local greedy choices (cutting at every equal zero-crossing) lead to global optimum 
  in prefix-balance partitioning.
*/
