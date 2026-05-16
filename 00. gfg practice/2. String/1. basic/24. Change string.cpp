/*
Problem: Change string

GFG: https://www.geeksforgeeks.org/problems/change-the-string3541/1

Description:
Given a string s, task is to change complete string to uppercase or lowercase depending on the case of the first character.

Examples:

Input: s = "abCD"
Output: "abcd"
Explanation: The first letter (a) is lowercase. Hence, complete string is made lowercase.

Input: s = "Abcd"
Output: "ABCD"
Explanation: The first letter (A) is uppercase. Hence, complete string is made uppercase.

Constraints:
1 <= |s| <= 10^4

Approach (Case-based String Transformation):
Key insight:
- Check the case of the first character
- If first character is lowercase, convert entire string to lowercase
- If first character is uppercase, convert entire string to uppercase
- Decision depends entirely on the first character

Algorithm:
1. Check if first character is lowercase (a-z) or uppercase (A-Z)
2. If first character is lowercase:
   - Convert all uppercase characters to lowercase
3. Else (first character is uppercase):
   - Convert all lowercase characters to uppercase
4. Return the modified string

Time Complexity: O(n)
Space Complexity: O(1) - in-place modification

Pattern: Character Manipulation / Case Conversion
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
CASE-BASED STRING TRANSFORMATION APPROACH
=====================================================

TC: O(n)
SC: O(1) - in-place modification

🔥 FIRST CHARACTER DECISION
- Check case of first character
- Convert entire string accordingly
- In-place character case conversion

🧠 KEY INSIGHT:
Decision rule:
- First character lowercase → entire string lowercase
- First character uppercase → entire string uppercase

🎯 ALGORITHM:
1. Check first character case
2. Convert entire string based on decision
3. Return modified string

⚡ CASE CONVERSION LOGIC:
s = "abCD"

Step 1: Check first character
s[0] = 'a' (lowercase)

Step 2: Convert entire string to lowercase
a -> a (already lowercase)
b -> b (already lowercase)
C -> c (C - 'A' + 'a' = 'c')
D -> d (D - 'A' + 'a' = 'd')

Result: "abcd"

s = "Abcd"

Step 1: Check first character
s[0] = 'A' (uppercase)

Step 2: Convert entire string to uppercase
A -> A (already uppercase)
b -> B (b - 'a' + 'A' = 'B')
c -> C (c - 'a' + 'A' = 'C')
d -> D (d - 'a' + 'A' = 'D')

Result: "ABCD"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1) - in-place modification

    string modify(string s) {

        // First character is lowercase
        if(s[0] >= 'a' && s[0] <= 'z') {

            // Convert entire string to lowercase
            for(int i = 0; i < s.size(); i++) {

                if(s[i] >= 'A' && s[i] <= 'Z') {

                    s[i] = s[i] - 'A' + 'a';
                }
            }
        }

        // First character is uppercase
        else {

            // Convert entire string to uppercase
            for(int i = 0; i < s.size(); i++) {

                if(s[i] >= 'a' && s[i] <= 'z') {

                    s[i] = s[i] - 'a' + 'A';
                }
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
    + FIRST CHARACTER DECISION
    + STRING TRANSFORMATION

Think immediately:
    FIRST CHARACTER-BASED CONVERSION

-----------------------------------------------------

KEY OBSERVATIONS:

1. Decision depends only on first character
2. Need to convert entire string uniformly
3. Character case conversion is straightforward
4. In-place modification is efficient

-----------------------------------------------------

COMMON MISTAKES:

1. Not checking first character correctly
2. Using built-in functions incorrectly
3. Not handling empty string
4. Converting only part of the string

-----------------------------------------------------

SIMILAR PROBLEMS

- String case conversion
- Character transformation
- First character-based operations

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Transform entire string based on single character
- Need uniform case conversion
- First character determines operation

Think:
First Character-based String Transformation

Algorithm:
1. Check first character property
2. Apply transformation to entire string
3. Return modified string

Key insight:
Single character decision determines entire transformation

-----------------------------------------------------
*/
