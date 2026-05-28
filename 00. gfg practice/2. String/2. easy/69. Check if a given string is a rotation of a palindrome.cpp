/*
Problem: Check if a given string is a rotation of a palindrome

Given a string s, check if it can be rotated to form a palindrome.

Constraints:
1 <= s.length() <= 10^4

--------------------------------------------------

Pattern:
String Processing + Palindrome Checking

--------------------------------------------------

Key Observation:
- A string `s` of length `N` has exactly `N` possible rotations.
- Instead of manually creating `N` rotated strings, we can concatenate the string with itself (`doubled = s + s`).
- Any substring of length `N` within this `doubled` string represents one unique rotation of the original string.
- By checking if any of these `N` substrings is a palindrome, we can determine if a rotated palindrome is possible.

--------------------------------------------------

Approach:
1. Let `N` be the length of the string `s`.
2. Create a new string `doubled = s + s`.
3. Loop `i` from `0` to `N - 1`:
    a. Check if the substring starting at `i` and ending at `i + N - 1` is a palindrome. We can do this efficiently using a two-pointer approach directly on the `doubled` string without creating substrings.
    b. If it is a palindrome, immediately return 1.
4. If the loop completes and no palindromic rotation is found, return 0.

--------------------------------------------------

Time Complexity: O(N^2) as there are N rotations to check, and each palindrome check takes O(N) time.
Space Complexity: O(N) to store the concatenated string `doubled` which takes 2*N space.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/check-if-a-given-string-is-a-rotation-of-a-palindrome/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
    bool isPalindrome(const string& str, int start, int end) {
        while (start < end) {
            if (str[start] != str[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    }

public:
    int isRotatedPalindrome(string s) {
        int n = s.length();
        string doubled = s + s;
        
        for (int i = 0; i < n; ++i) {
            if (isPalindrome(doubled, i, i + n - 1)) {
                return 1;
            }
        }
        
        return 0;
    }
};
