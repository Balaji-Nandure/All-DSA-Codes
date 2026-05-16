/*
Problem: Remove characters from alphanumeric string

GFG: https://www.geeksforgeeks.org/problems/remove-characters-from-alphanumeric-string0648/1

Description:
Given a string s, remove all characters except the numeric characters from an
alphanumeric string.

Examples:

Input: s = "AA1d23cBB4"
Output: "1234"
Explanation: Remove all characters other than numbers.

Input: s = "a1b2c3"
Output: "123"
Explanation: Remove all characters other than numbers.

Constraints:
1 <= |s| <= 10^5

Approach (Character Filtering):
Traverse the string and keep only digit characters.

Key insight:
- A character is a digit if it lies between '0' and '9'
- Build the answer string by appending only digits

Algorithm:
1. Initialize empty result string
2. For each character ch in s:
   - If '0' <= ch <= '9', append it to result
3. Return result

Time Complexity: O(|s|)
Space Complexity: O(|s|)

Pattern: String Filtering / Digit Check
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
DIGIT FILTERING APPROACH
=====================================================

TC: O(n)
SC: O(n)

DIGIT FILTERING
- Scan the string once
- Append only numeric characters

KEY INSIGHT:
We do not need parsing or number conversion.
Just keep characters that are digits.

DRY RUN:
s = "AA1d23cBB4"
Keep: 1, 2, 3, 4
Result: "1234"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(n)

    string removeCharacters(string s) {

        string ans = "";

        for(char ch : s) {

            if(ch >= '0' && ch <= '9') {
                ans.push_back(ch);
            }
        }

        return ans;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    EXTRACTING DIGITS FROM STRING
    + FILTERING CHARACTERS
    + PRESERVING ORDER

Think immediately:
    SINGLE PASS FILTERING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Digits are contiguous in ASCII ('0'..'9').
2. We keep relative order by scanning left to right.
3. No need for regex or conversion to integers.

-----------------------------------------------------

COMMON MISTAKES:

1. Trying to convert the whole string to a number.
2. Losing order by sorting digits accidentally.
3. Using extra data structures when a string append is enough.

-----------------------------------------------------
*/
