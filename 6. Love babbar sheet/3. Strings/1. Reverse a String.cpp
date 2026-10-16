// Problem: Reverse a String
// Link (GFG): https://www.geeksforgeeks.org/problems/reverse-a-string/1
// Article: https://www.geeksforgeeks.org/dsa/reverse-a-string/
// Difficulty: Basic / Easy
// Topic: String, Two Pointers, In-Place Reversal

/*
Problem Statement:
You are given a string s. You need to reverse the string.
The reversal should be done in-place or return the reversed string.

Example 1:
Input: s = "Geeks"
Output: "skeeG"

Example 2:
Input: s = "for"
Output: "rof"

Example 3:
Input: s = "a"
Output: "a"

Constraints:
- 1 <= s.length() <= 10^5
- s contains only lower and uppercase alphabetic characters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 1 (Reverse an Array):
//   * We reversed an array of arbitrary integer types `vector<int>`.
// - In Strings Problem 1 (Reverse a String):
//   * Strings in C++ (`std::string`) are contiguous, mutable character buffers terminated 
//     by `\0`.
//   * In Java/Python, strings are immutable (creating a new string is mandatory).
//   * In C++, we exploit in-place mutability by swapping characters at `left` and `right` 
//     pointers towards the center in O(1) auxiliary space!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Auxiliary String / Stack
//   - Push all characters into a stack or append backwards into a new string.
//   - Complexity: O(N) time, O(N) auxiliary space.
//   - Why Suboptimal: Unnecessary memory allocation.
//
// Approach 2: Two-Pointer Convergent Swap (Optimal & Chosen)
//   - Initialize `left = 0`, `right = s.length() - 1`.
//   - While `left < right`:
//       `swap(s[left], s[right]);`
//       `left++; right--;`
//   - Complexity: O(N) time, O(1) auxiliary space.
//   - Total Swaps: exactly N / 2.
//   - Why this approach: Maximum performance, minimal cache misses, zero dynamic allocations.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseString(string& s) {
        int left = 0;
        int right = (int)s.length() - 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Symmetric two-pointer convergence swaps mirrored characters until meeting at middle
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }

        return s;
    }
};

int main() {
    Solution sol;
    string s1 = "Geeks";
    cout << "Original: " << s1 << " -> Reversed: " << sol.reverseString(s1) << "\n";

    string s2 = "Hello World";
    cout << "Original: " << s2 << " -> Reversed: " << sol.reverseString(s2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N), exactly N / 2 swap operations where N is the length of string.
- Space Complexity: O(1) auxiliary space (in-place modification).

Key Takeaways:
- Two-pointer convergence is the foundational building block for string transformations,
  palindromes, and sliding windows.
*/
