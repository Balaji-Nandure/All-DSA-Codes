/*
Problem: String with numbers at its end

GFG: https://www.geeksforgeeks.org/problems/string-with-numbers-at-its-end/1

Description:
Given string s that is appended with a number at last. The task is to check whether 
length of string excluding that number is equal to that number.

Examples:

Input: s = "geeks5"
Output: 1
Explanation: Length of geeks is 5 and last number is also 5.

Input: s = "geek5"
Output: 0
Explanation: Length of geek is 4 and last number is 5.

Constraints:
1 <= |s| <= 10^5

Approach (String Parsing and Comparison):
Key insight:
- Extract the trailing number from the string
- Calculate length of string without the number
- Compare the length with the extracted number

Algorithm:
1. Find where the trailing number starts (last non-digit character)
2. Extract the number part from that position
3. Convert number string to integer
4. Calculate string length without the number
5. Compare length with the number
6. Return 1 if equal, 0 if not equal

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: String Parsing / Number Extraction
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
STRING PARSING AND COMPARISON APPROACH
=====================================================

TC: O(n)
SC: O(1)

🔥 TRAILING NUMBER EXTRACTION
- Find where number starts
- Extract number part
- Compare with string length

🧠 KEY INSIGHT:
Number extraction process:
- Find last non-digit character
- Everything after that is the number
- Convert to integer for comparison

🎯 ALGORITHM:
1. Find start of trailing number
2. Extract number part
3. Convert to integer
4. Calculate string length without number
5. Compare and return result

⚡ PARSING LOGIC:
s = "geeks5"

Step 1: Find start of trailing number
Traverse from end:
s[4] = '5' -> digit
s[3] = 's' -> not digit
Number starts at index 4

Step 2: Extract number
numberStr = "5"
number = 5

Step 3: Calculate string length without number
stringLength = 4 (indices 0-3: "geeks")

Step 4: Compare
stringLength (4) == number (5) -> false

Result: 0

s = "geeks5"

Step 1: Find start of trailing number
Traverse from end:
s[5] = '5' -> digit
s[4] = 's' -> not digit
Number starts at index 5

Step 2: Extract number
numberStr = "5"
number = 5

Step 3: Calculate string length without number
stringLength = 5 (indices 0-4: "geeks")

Step 4: Compare
stringLength (5) == number (5) -> true

Result: 1
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int isSame(string s) {

        int n = s.size();

        int i = n - 1;

        int num = 0;
        int place = 1;

        // Extract number from end
        while(i >= 0 && isdigit(s[i])) {

            num = (s[i] - '0') * place + num;

            place *= 10;

            i--;
        }

        // Length of string part
        int len = i + 1;

        // Compare
        return (len == num);
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    TRAILING NUMBER EXTRACTION
    + STRING PARSING
    + LENGTH COMPARISON

Think immediately:
    STRING PARSING FROM END

-----------------------------------------------------

KEY OBSERVATIONS:

1. Number is always at the end
2. Need to find boundary between letters and digits
3. Extract number part and convert to integer
4. Compare with string length

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling multiple digit numbers
2. Wrong boundary detection
3. Not converting string to number
4. Off-by-one errors in length calculation

-----------------------------------------------------

SIMILAR PROBLEMS

- String parsing problems
- Number extraction from strings
- Length comparison tasks

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Extract trailing numbers from strings
- Parse mixed alphanumeric strings
- Compare string properties with extracted values

Think:
String Parsing with Boundary Detection

Algorithm:
1. Find boundary between character types
2. Extract relevant parts
3. Convert and compare
4. Return boolean result

Key insight:
Parse from end to find number boundaries

-----------------------------------------------------
*/
