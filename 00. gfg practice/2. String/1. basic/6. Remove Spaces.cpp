/*
Problem: Remove Spaces

GFG: https://www.geeksforgeeks.org/problems/remove-spaces/1

Description:
Given a string s, remove all the spaces from the string and return the modified string.

Examples:

Input: s = "g eeks for ge eks"
Output: "geeksforgeeks"
Explanation: All space characters are removed from the given string while preserving the order of the remaining characters, resulting in the final string "geeksforgeeks".

Input: s = "abc d "
Output: "abcd"
Explanation: All space characters are removed from the given string while preserving the order of the remaining characters, resulting in the final string "abcd".

Constraints:
1 ≤ |s| ≤ 10^5

Approach (Two Pointers / String Filtering):
This is a basic string filtering problem where we need to remove all space characters.

Key insight:
- Iterate through the string and collect only non-space characters
- Build result string by skipping spaces
- Preserve order of remaining characters

Algorithm:
1. Initialize empty result string
2. For each character in input string:
   - If character is not space (' '), add to result
3. Return the result string

Time Complexity: O(n)
Space Complexity: O(n) for result string

Pattern: String Filtering / Character Removal
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
STRING FILTERING APPROACH
=====================================================

TC: O(n)
SC: O(n) for result string

🔥 FILTERING APPROACH
- Iterate through string character by character
- Skip space characters, keep others
- Build result string in one pass

🧠 KEY INSIGHT:
String filtering is straightforward:
- Check each character individually
- Include only non-space characters
- Maintain original order automatically

🎯 ALGORITHM:
1. Initialize empty result string
2. For each character in s:
   - If char != ' ', append to result
3. Return result string

⚡ FILTERING LOGIC:
s = "g eeks for ge eks"
i=0: 'g' → result="g"
i=1: ' ' → skip
i=2: 'e' → result="ge"
i=3: 'e' → result="gee"
...
Final: "geeksforgeeks"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(n)

    string removeSpaces(string s) {

        string result = "";

        // Filter out space characters
        for(char c : s) {

            if(c != ' ') {

                result.push_back(c);
            }
        }

        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    CHARACTER REMOVAL
    + STRING FILTERING
    + SPACE HANDLING

Think immediately:
    STRING FILTERING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Simple linear scan is sufficient
2. Only need to check for space character
3. Order is preserved by sequential processing
4. Can use string builder for efficiency

-----------------------------------------------------

COMMON MISTAKES:

1. Using erase-remove idiom incorrectly
2. Not handling leading/trailing spaces
3. Creating unnecessary intermediate strings
4. Using wrong space character ('\t' vs ' ')

-----------------------------------------------------

SIMILAR PROBLEMS

- Remove specific characters
- String filtering problems
- Character elimination tasks

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Remove specific characters from string
- Filter string based on conditions
- Preserve order of remaining elements

Think:
String Filtering

Algorithm:
1. Initialize empty result
2. For each character:
   - If character meets condition, keep it
   - Else, skip it
3. Return filtered string

Key insight:
Linear scan + conditional inclusion

-----------------------------------------------------
*/
