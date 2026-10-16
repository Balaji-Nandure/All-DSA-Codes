// Problem: Check whether a String is Palindrome or not
// Link (GFG): https://www.geeksforgeeks.org/problems/palindrome-string0817/1
// Article: https://www.geeksforgeeks.org/c/c-program-check-given-string-palindrome/
// Difficulty: Basic / Easy
// Topic: String, Two Pointers, Palindrome

/*
Problem Statement:
You are given a string s. Your task is to determine if the string is a palindrome.
A string is considered a palindrome if it reads the same backward as forward.
Return true (or 1) if it is a palindrome, else false (or 0).

Example 1:
Input: s = "abba"
Output: true
Explanation: "abba" reads the same forward and backward.

Example 2:
Input: s = "abc"
Output: false
Explanation: "abc" reversed is "cba", which is not equal to "abc".

Example 3:
Input: s = "a"
Output: true

Constraints:
- 1 <= s.length() <= 10^5
- s contains lowercase English alphabets.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1 (Reverse a String):
//   * We actively modified / mutated the string by swapping characters.
// - In Problem 2 (Check Palindrome):
//   * Read-only predicate check.
//   * The key efficiency win is EARLY EXIT: the moment any mirrored pair mismatches 
//     (`s[left] != s[right]`), we immediately return `false` without checking the rest of the string!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Reverse and Compare
//   - Create `string rev = s; reverse(rev.begin(), rev.end()); return rev == s;`
//   - Complexity: O(N) time, O(N) auxiliary space.
//   - Why Suboptimal: Allocates a duplicate string buffer and always reverses the full string 
//     even if the very first and last characters mismatch!
//
// Approach 2: Two-Pointer Symmetrical Scan (Optimal & Chosen)
//   - Set `left = 0`, `right = s.length() - 1`.
//   - While `left < right`:
//       If `s[left] != s[right]`: return false immediately.
//       `left++; right--;`
//   - Return true if pointers meet/cross.
//   - Complexity: O(N) worst case (O(1) best case on early mismatch), O(1) auxiliary space.
//   - Why this approach: Zero extra memory and optimal average-case runtime due to short-circuiting.

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(const string& s) {
        int left = 0;
        int right = (int)s.length() - 1;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Short-circuiting verification: The instant mirrored indices disagree,
        // we prune further checks, achieving O(1) best-case time.
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }
};

int main() {
    Solution sol;
    string s1 = "abba";
    cout << s1 << " is palindrome? " << (sol.isPalindrome(s1) ? "Yes" : "No") << "\n";

    string s2 = "geeks";
    cout << s2 << " is palindrome? " << (sol.isPalindrome(s2) ? "Yes" : "No") << "\n";

    string s3 = "racecar";
    cout << s3 << " is palindrome? " << (sol.isPalindrome(s3) ? "Yes" : "No") << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) worst case (when string is palindrome), O(1) best case (when first and last characters differ).
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Palindrome checks are symmetric invariants: testing from outside-in allows instant early termination.
*/
