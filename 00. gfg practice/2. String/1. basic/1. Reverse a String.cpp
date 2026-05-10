/*
Problem: Reverse a String

GFG: https://www.geeksforgeeks.org/problems/reverse-a-string/1

Description:
You are given a string s, and your task is to reverse the string.

Examples:

Input: s = "Geeks"
Output: "skeeG"

Input: s = "for"
Output: "rof"

Input: s = "a"
Output: "a"

Constraints:
1 <= s.size() <= 10^6
s contains only alphabetic characters (both uppercase and lowercase).

Approach (Two Pointers):
This is a basic string manipulation problem where we need to reverse the characters.

Key insight:
- Use two pointers: one at start, one at end
- Swap characters while moving pointers towards center
- Stop when pointers meet or cross

Algorithm:
1. Initialize left = 0, right = n-1
2. While left < right:
   - Swap s[left] and s[right]
   - left++, right--
3. Return the reversed string

Time Complexity: O(n)
Space Complexity: O(1) if modifying in-place, O(n) if creating new string

Pattern: Two Pointers / String Manipulation
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
TWO POINTERS STRING REVERSAL
=====================================================

TC: O(n)
SC: O(1) in-place, O(n) new string

🔥 TWO POINTERS APPROACH
- Use left pointer at start, right pointer at end
- Swap characters while moving towards center
- Most efficient way to reverse string

🧠 KEY INSIGHT:
String reversal is symmetric:
- First character becomes last
- Second character becomes second last
- Continue until middle is reached

🎯 ALGORITHM:
1. Initialize left = 0, right = n-1
2. While left < right:
   - Swap s[left] and s[right]
   - left++, right--
3. Return reversed string

⚡ POINTER MOVEMENT:
"hello"
left=0, right=4: swap 'h' and 'o'
left=1, right=3: swap 'e' and 'l'
left=2, right=2: stop (crossed)
Result: "olleh"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1) in-place modification

    string reverseString(string s) {

        int left = 0;

        int right = s.length() - 1;

        while(left < right) {

            // Swap characters
            swap(s[left], s[right]);

            left++;

            right--;
        }

        return s;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    STRING REVERSAL
    + CHARACTER MANIPULATION
    + IN-PLACE MODIFICATION

Think immediately:
    TWO POINTERS APPROACH

-----------------------------------------------------

KEY OBSERVATIONS:

1. String reversal is symmetric operation
2. Two pointers approach is most efficient
3. Can modify in-place for O(1) space
4. Built-in reverse function also works

-----------------------------------------------------

COMMON MISTAKES:

1. Going beyond middle (left >= right)
2. Not handling single character strings
3. Creating unnecessary copies
4. Using extra space when not needed

-----------------------------------------------------

SIMILAR PROBLEMS

- String reversal problems
- Palindrome checking
- Two-pointer string manipulation

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Need to reverse string/array
- In-place modification preferred
- Symmetric operations required

Think:
Two Pointers

Algorithm:
1. left = 0, right = n-1
2. While left < right:
   - Swap elements
   - left++, right--
3. Return result

Key insight:
Work from both ends towards center

-----------------------------------------------------
*/
