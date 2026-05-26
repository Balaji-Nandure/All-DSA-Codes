/*
Problem: Special array reversal

Given a string S, containing special characters and all the alphabets, reverse the string without affecting the positions of the special characters.

Example 1:
Input: S = "A&B"
Output: "B&A"
Explanation: As we ignore '&' and then reverse, so answer is "B&A".

Example 2:
Input: S = "A&x#"
Output: "x&A#"
Explanation: We swap only A and x.

Constraints:
1 <= |S| <= 10^5

--------------------------------------------------

Pattern:
String Processing + Two Pointer Approach

--------------------------------------------------

Key Observation:
- We want to reverse only the alphabets, leaving the positions of special characters intact.
- Using a two-pointer approach, we can scan the string from both ends.
- If a character at the left pointer is not an alphabet, we skip it (increment left pointer).
- If a character at the right pointer is not an alphabet, we skip it (decrement right pointer).
- If both are alphabets, we swap them and move both pointers inward.

--------------------------------------------------

Time Complexity: O(n)
Space Complexity: O(1) (in-place modification)

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/special-array-reversal2328/1
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    string reverse(string str) {
        int i = 0;
        int j = str.length() - 1;
        
        while (i < j) {
            // Skip non-alphabet characters at the left pointer
            if (!isalpha(str[i])) {
                i++;
            }
            // Skip non-alphabet characters at the right pointer
            else if (!isalpha(str[j])) {
                j--;
            }
            // Swap alphabets
            else {
                swap(str[i], str[j]);
                i++;
                j--;
            }
        }
        
        return str;
    }
};
