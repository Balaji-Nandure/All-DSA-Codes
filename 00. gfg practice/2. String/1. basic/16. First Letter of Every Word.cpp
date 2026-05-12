/*
Problem: First Letter of Every Word

GFG: https://www.geeksforgeeks.org/problems/first-letter-of-every-word/1

Description:
Given a string s, the task is to create a string with the first letter of every word in the string. 
The string s contains lower case English alphabets and its words have a single space between them.

Examples:

Input: s = "geeks for geeks"
Output: "gfg"
Explanation: 
First word starts at index 0, take 'g' 
After first space, next word starts with 'f'
After second space, next word starts with 'g'

Input: s = "bad is good"
Output: "big"

Constraints:
1 ≤ |s| ≤ 10^5

Approach (String Traversal):
Key insight:
- First character is always the first letter of first word
- Every word starts after a space
- Extract first letter of each word and build result string

Algorithm:
1. Add first character to result (first word's first letter)
2. Traverse string from index 1 to end
3. When encountering a space, take the next character (if exists)
4. Add that character to result string
5. Return the result

Time Complexity: O(n)
Space Complexity: O(k) where k is number of words

Pattern: String Traversal / Character Extraction
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
FIRST LETTER EXTRACTION APPROACH
=====================================================

TC: O(n)
SC: O(k) where k = number of words

🔥 STRING TRAVERSAL APPROACH
- Identify word boundaries (spaces)
- Extract first character after each space
- Build result string with first letters

🧠 KEY INSIGHT:
Word boundaries are easy to identify:
- First character (index 0)
- Character after a space

🎯 ALGORITHM:
1. Add first character to result
2. Traverse string looking for spaces
3. Take character after each space
4. Build result string
5. Return result

⚡ EXTRACTION LOGIC:
s = "geeks for geeks"

Step 1: Add first character
result = "g"

Step 2: Traverse string
Index 0: 'g' -> already added
Index 1: 'e' -> skip
Index 2: 'e' -> skip
Index 3: 'k' -> skip
Index 4: 's' -> skip
Index 5: ' ' (space) -> take next char 'f'
result = "gf"
Index 6: 'f' -> skip (already taken)
Index 7: 'o' -> skip
Index 8: 'r' -> skip
Index 9: ' ' (space) -> take next char 'g'
result = "gfg"
Index 10: 'g' -> skip (already taken)

Final: "gfg"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(k) where k = number of words

    string firstLetter(string s) {

        string result = "";

        // Add first character (first word's first letter)
        if(s.length() > 0) {
            result += s[0];
        }

        // Traverse remaining string
        for(int i = 1; i < s.length(); i++) {

            // If current character is space and next character exists
            if(s[i - 1] == ' ' && i < s.length()) {
                result += s[i];
            }
        }

        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    WORD BOUNDARY DETECTION
    + CHARACTER EXTRACTION
    + STRING COMPRESSION

Think immediately:
    STRING TRAVERSAL

-----------------------------------------------------

KEY OBSERVATIONS:

1. Word boundaries are at spaces
2. First character is always included
3. Need to handle single-word strings
4. Result length equals number of words

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling empty string
2. Missing the first character
3. Going out of bounds after last space
4. Including spaces in result

-----------------------------------------------------

SIMILAR PROBLEMS

- Word abbreviation
- String compression
- Acronym generation

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Extract specific characters from words
- Need word boundary detection
- Build compressed string

Think:
String Traversal with Boundary Detection

Algorithm:
1. Handle first character separately
2. Traverse looking for boundaries
3. Extract target characters
4. Build result string

Key insight:
Word boundaries are identified by spaces or string start

-----------------------------------------------------
*/
