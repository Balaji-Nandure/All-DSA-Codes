/*
Problem: Convert String to LowerCase

GFG: https://www.geeksforgeeks.org/problems/capital-city/1

Description:
Given a string s. The task is to convert string characters to lowercase.

Examples:

Input: s = "ABCddE"
Output: "abcdde"
Explanation: A, B, C and E are converted to a, b, c and e thus all uppercase characters of the string converted to lowercase letter.

Input: s = "LMNOppQQ"
Output: "lmnoppqq"
Explanation: L, M, N, O, and Q are converted to l, m, n, o and q thus all uppercase characters of the string converted to lowercase letter.

Constraints:
1 ≤ s.size() ≤ 10^6

Approach (ASCII Conversion):
This is a basic string manipulation problem where we need to convert all characters to lowercase.

Key insight:
- Uppercase letters have ASCII values 65-90 ('A' to 'Z')
- Lowercase letters have ASCII values 97-122 ('a' to 'z')
- Difference between uppercase and lowercase is 32
- Convert: lowercase = uppercase + 32

Algorithm:
1. Iterate through each character in the string
2. If character is uppercase (65-90):
   - Convert to lowercase by adding 32
3. Return the modified string

Time Complexity: O(n)
Space Complexity: O(1) if modifying in-place

Pattern: ASCII Manipulation / Character Conversion
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
ASCII CHARACTER CONVERSION
=====================================================

TC: O(n)
SC: O(1) in-place

🔥 ASCII CONVERSION APPROACH
- Use ASCII values to identify uppercase letters
- Convert by adding 32 (difference between cases)
- Most efficient character-by-character approach

🧠 KEY INSIGHT:
ASCII character codes:
- 'A' to 'Z': 65 to 90
- 'a' to 'z': 97 to 122
- Conversion: lowercase = uppercase + 32

🎯 ALGORITHM:
1. For each character in string:
   - If char is uppercase (65-90)
   - Convert to lowercase: char += 32
2. Return modified string

⚡ CONVERSION LOGIC:
'A' (65) + 32 = 'a' (97)
'B' (66) + 32 = 'b' (98)
'Z' (90) + 32 = 'z' (122)

Already lowercase: no change needed
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1) in-place modification

    string toLower(string s) {

        for(int i = 0; i < s.length(); i++) {

            // Check if character is uppercase
            if(s[i] >= 'A' && s[i] <= 'Z') {

                // Convert to lowercase
                s[i] = s[i] + 32;
            }
        }

        return s;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    CASE CONVERSION
    + CHARACTER MANIPULATION
    + ASCII OPERATIONS

Think immediately:
    ASCII CHARACTER CONVERSION

-----------------------------------------------------

KEY OBSERVATIONS:

1. Uppercase: 'A' to 'Z' (65-90)
2. Lowercase: 'a' to 'z' (97-122)
3. Fixed difference of 32 between cases
4. Can use built-in tolower() function too

-----------------------------------------------------

COMMON MISTAKES:

1. Using wrong ASCII difference (not 32)
2. Converting already lowercase characters
3. Not handling non-alphabetic characters
4. Using built-in functions when not allowed

-----------------------------------------------------

SIMILAR PROBLEMS

- Case conversion problems
- Character manipulation tasks
- ASCII-based string operations

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Convert between character cases
- ASCII-based character operations
- String character manipulation

Think:
ASCII Conversion

Algorithm:
1. For each character:
   - Check if uppercase ('A' <= char <= 'Z')
   - Convert: char += 32
2. Return modified string

Key insight:
Uppercase to lowercase: add 32

-----------------------------------------------------
*/
