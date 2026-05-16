/*
Problem: Keypad typing

GFG: https://www.geeksforgeeks.org/problems/keypad-typing/1

Description:
You are given a string s of lowercase alphabet characters. Find its matching decimal representation as on the shown keypad.

Examples:

Input: s = "geeksforgeeks"
Output: "4335736743357"
Explanation: Each character in the string "geeksforgeeks" is converted to its corresponding digit based on the keypad, and the digits are concatenated in order.

Input: s = "geeksquiz"
Output: "433577849"
Explanation: Each character in the string "geeksquiz" is converted to its corresponding digit based on the keypad, and the digits are concatenated in order.

Constraints:
1 ≤ s.size() ≤ 100

Approach (Direct Mapping):
Key insight:
- Create a mapping from each character to its keypad digit
- Standard phone keypad layout:
  2: abc, 3: def, 4: ghi, 5: jkl, 6: mno, 7: pqrs, 8: tuv, 9: wxyz
- Convert each character to its corresponding digit
- Concatenate all digits to form result

Algorithm:
1. Create a mapping array/dictionary for character to digit conversion
2. Initialize empty result string
3. For each character in input string:
   - Find its corresponding digit from mapping
   - Append digit to result
4. Return the result string

Time Complexity: O(n)
Space Complexity: O(n) for result string

Pattern: Character Mapping / String Transformation
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
KEYPAD MAPPING APPROACH
=====================================================

TC: O(n)
SC: O(n) for result string

🔥 DIRECT CHARACTER TO DIGIT MAPPING
- Create mapping based on phone keypad
- Convert each character to corresponding digit
- Concatenate digits to form result

🧠 KEY INSIGHT:
Phone keypad layout:
2: abc    3: def
4: ghi    5: jkl
6: mno    7: pqrs
8: tuv    9: wxyz

Mapping rule:
- a,b,c -> 2
- d,e,f -> 3
- g,h,i -> 4
- j,k,l -> 5
- m,n,o -> 6
- p,q,r,s -> 7
- t,u,v -> 8
- w,x,y,z -> 9

🎯 ALGORITHM:
1. Create character to digit mapping
2. Traverse input string
3. Convert each character to digit
4. Build result string
5. Return result

⚡ MAPPING LOGIC:
s = "geeksforgeeks"

Step 1: Initialize result = ""

Step 2: Convert each character
g -> 4
e -> 3
e -> 3
k -> 5
s -> 7
f -> 3
o -> 6
r -> 7
g -> 4
e -> 3
e -> 3
k -> 5
s -> 7

Step 3: Build result
"4" + "3" + "3" + "5" + "7" + "3" + "6" + "7" + "4" + "3" + "3" + "5" + "7"
= "4335736743357"

Final: "4335736743357"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(n) for result string

    string getNumber(string s) {

        // Create character to digit mapping
        unordered_map<char, char> keypad = {
            {'a', '2'}, {'b', '2'}, {'c', '2'},
            {'d', '3'}, {'e', '3'}, {'f', '3'},
            {'g', '4'}, {'h', '4'}, {'i', '4'},
            {'j', '5'}, {'k', '5'}, {'l', '5'},
            {'m', '6'}, {'n', '6'}, {'o', '6'},
            {'p', '7'}, {'q', '7'}, {'r', '7'}, {'s', '7'},
            {'t', '8'}, {'u', '8'}, {'v', '8'},
            {'w', '9'}, {'x', '9'}, {'y', '9'}, {'z', '9'}
        };

        string result = "";

        // Convert each character to corresponding digit
        for(char ch : s) {
            result += keypad[ch];
        }

        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    CHARACTER TO DIGIT/SYMBOL CONVERSION
    + FIXED MAPPING
    + STRING TRANSFORMATION

Think immediately:
    DIRECT MAPPING APPROACH

-----------------------------------------------------

KEY OBSERVATIONS:

1. Phone keypad has fixed mapping
2. Each character maps to exactly one digit
3. Need to handle all 26 lowercase letters
4. Result is concatenation of digits

-----------------------------------------------------

COMMON MISTAKES:

1. Wrong keypad mapping
2. Missing characters in mapping
3. Using inefficient string concatenation
4. Not handling edge cases

-----------------------------------------------------

SIMILAR PROBLEMS

- Character encoding/decoding
- String transformation with mapping
- Symbol conversion problems

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Convert characters using fixed mapping
- Need character to symbol transformation
- String encoding/decoding

Think:
Direct Character Mapping

Algorithm:
1. Create character to symbol mapping
2. Traverse input string
3. Convert each character using mapping
4. Build result string
5. Return transformed string

Key insight:
Fixed mapping enables O(1) character conversion

-----------------------------------------------------
*/
