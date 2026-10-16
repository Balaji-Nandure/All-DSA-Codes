// Problem: Find Next Greater Number with Same Set of Digits (Next Permutation of Digits)
// Link (GFG): https://www.geeksforgeeks.org/problems/next-permutation5226/1
// Article: https://www.geeksforgeeks.org/dsa/find-next-greater-number-set-digits/
// Difficulty: Medium / Hard
// Topic: String, Math, Next Permutation, Greedy Two Pointers

/*
Problem Statement:
Given a number represented as a digit string `s` (or integer array), find the smallest 
number greater than `s` that can be created using the exact same set of digits.
If the number has its digits in strictly descending order (e.g. "4321"), no greater number 
can be formed using the same digits. In that case, return "-1" (or circular wrap to smallest 
depending on problem specification).

Example 1:
Input: s = "218765"
Output: "251678"
Explanation:
Digits "8765" are descending. The dip is at '1' (index 1).
The next larger digit to the right of '1' is '5'.
Swap '1' and '5' -> "258761".
Reverse suffix "8761" -> "251678".

Example 2:
Input: s = "1234"
Output: "1243"

Example 3:
Input: s = "4321"
Output: "-1" (no greater permutation possible)

Constraints:
- 1 <= s.length() <= 10^5
- s consists only of numeric digits '0'-'9'.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 11 (Print All Permutations):
//   * We generated ALL N! permutations recursively.
// - In Problem 15 (Next Greater Number):
//   * We only want the IMMEDIATE NEXT permutation in lexicographical order.
//   * Narayana Pandita's 14th-century algorithm achieves this in a single in-place scan 
//     in O(N) time without generating or exploring unwanted permutations!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Narayana Pandita's 3-Step Algorithm (Optimal & Chosen):
//   Step 1: Find the rightmost dip (first decreasing element from right to left):
//     - Scan backwards from `n - 2` down to 0 to find the largest index `i` such that:
//       `s[i] < s[i + 1]`.
//     - If no such `i` exists, the entire sequence is descending (already maximal) -> return "-1".
//
//   Step 2: Find the successor to swap:
//     - Scan backwards from `n - 1` down to `i + 1` to find the smallest digit greater than `s[i]`:
//       First `j` such that `s[j] > s[i]`.
//     - Swap `s[i]` with `s[j]`.
//
//   Step 3: Minimize the suffix:
//     - The suffix `s[i + 1 .. n - 1]` is currently in descending order.
//     - To make the resulting number as small as possible (the immediate next greater), 
//       reverse the suffix so it becomes ascending!
//   - Complexity: O(N) time, O(1) auxiliary space.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string nextGreaterNumber(string s) {
        int n = s.length();
        if (n <= 1) return "-1";

        // Step 1: Find the largest index i such that s[i] < s[i + 1]
        int i = n - 2;
        while (i >= 0 && s[i] >= s[i + 1]) {
            i--;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If no index i exists (i == -1), the digits are monotonically non-increasing.
        // It is impossible to form any strictly greater number using the same digits!
        if (i < 0) {
            return "-1";
        }

        // Step 2: Find index j > i such that s[j] > s[i] (smallest digit greater than s[i] to the right)
        int j = n - 1;
        while (s[j] <= s[i]) {
            j--;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Swap the dip with its immediate ceiling digit to increase the prefix by the minimal possible amount
        swap(s[i], s[j]);

        // Step 3: Reverse the suffix starting from i + 1 to make it strictly ascending (minimal)
        reverse(s.begin() + i + 1, s.end());

        return s;
    }
};

int main() {
    Solution sol;
    string s1 = "218765";
    cout << "Next greater of \"" << s1 << "\": " << sol.nextGreaterNumber(s1) << "\n";

    string s2 = "1234";
    cout << "Next greater of \"" << s2 << "\": " << sol.nextGreaterNumber(s2) << "\n";

    string s3 = "4321";
    cout << "Next greater of \"" << s3 << "\": " << sol.nextGreaterNumber(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N).
  * Step 1 takes at most N comparisons.
  * Step 2 takes at most N comparisons.
  * Step 3 reverses at most N elements = N/2 swaps.
  * Total time is strictly linear O(N).
- Space Complexity: O(1) auxiliary space (in-place modification).

Key Takeaways:
- Dip -> Successor Swap -> Suffix Reverse is the universal linear formula for finding 
  the next permutation of any sequence.
*/
