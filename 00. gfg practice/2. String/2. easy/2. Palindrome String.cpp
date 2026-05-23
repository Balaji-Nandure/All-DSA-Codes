/*
Problem: Palindrome String

GFG: https://www.geeksforgeeks.org/problems/palindrome-string0817/1

Description:
Given a string s, determine if it is a palindrome.
A palindrome reads the same forwards and backwards.

Examples:

Input: s = "abba"   Output: true
Input: s = "abc"    Output: false

Constraints:
1 ≤ s.size() ≤ 10^6
s contains only lowercase english letters (a-z).

Approach (Two Pointers):
- left pointer at start, right pointer at end
- Compare characters moving inward
- If any mismatch → not palindrome

Dry Run: s = "abba"
  left=0, right=3 → 'a'=='a' ✅
  left=1, right=2 → 'b'=='b' ✅
  left=2, right=1 → crossed → stop → true ✅

Dry Run: s = "abc"
  left=0, right=2 → 'a'!='c' ❌ → false

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(1)
    bool isPalindrome(string& s) {

        int left = 0, right = s.size() - 1;

        while(left < right) {

            if(s[left] != s[right]) return false;

            left++;
            right--;
        }

        return true;
    }
};
