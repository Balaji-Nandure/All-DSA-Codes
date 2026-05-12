/*
Problem: Capitalize First Letter of Words

GFG: https://www.geeksforgeeks.org/problems/capitalize-first-letter-of-each-word/1

Description:
Given a string s, convert the first letter of each word in the string to uppercase.

Examples:

Input: s = "gEEKs"
Output: "GEEKs"

Input: s = "i love programming"
Output: "I Love Programming"

Constraints:
1 <= s.length() <= 10^4
Consists of lowercase alphabets and spaces to separate words

Approach (String Traversal):
Key insight:
- Every word starts either at index 0 or after a space
- Capitalize first character of each word if it's lowercase
- Modify string in-place for efficiency

Algorithm:
1. Capitalize first character if it's lowercase
2. Traverse string from index 1 to end
3. For each character, check if previous character is space
4. If previous is space and current is lowercase, capitalize it
5. Return the modified string

Time Complexity: O(n)
Space Complexity: O(1) - in-place modification

Pattern: String Traversal / In-place Modification
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
CAPITALIZATION APPROACH
=====================================================

TC: O(n)
SC: O(1) - in-place modification

🔥 STRING TRAVERSAL APPROACH
- Identify word boundaries (spaces)
- Capitalize first character of each word
- Modify string in-place

🧠 KEY INSIGHT:
Word boundaries are easy to identify:
- First character (index 0)
- Character after a space

🎯 ALGORITHM:
1. Capitalize first character if lowercase
2. Traverse string from index 1
3. If previous char is space, capitalize current char
4. Return modified string

⚡ CAPITALIZATION LOGIC:
s = "i love programming"

Step 1: Capitalize first character
i -> I
s = "I love programming"

Step 2: Traverse remaining
Index 1: ' ' (space) -> skip
Index 2: 'l', previous is ' ' -> l -> L
s = "I Love programming"
Index 3: 'o', previous is 'L' -> skip
Index 4: 'v', previous is 'o' -> skip
Index 5: 'e', previous is 'v' -> skip
Index 6: ' ' (space) -> skip
Index 7: 'p', previous is ' ' -> p -> P
s = "I Love Programming"
Index 8+: remaining chars -> skip

Final: "I Love Programming"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1) - in-place modification

    string capitalizeFirst(string s) {

        // Capitalize first character if lowercase
        if(s[0] >= 'a' && s[0] <= 'z') {
            s[0] = s[0] - 'a' + 'A';
        }

        // Traverse remaining string
        for(int i = 1; i < s.size(); i++) {

            // New word starts after space
            if(s[i - 1] == ' ' &&
               s[i] >= 'a' &&
               s[i] <= 'z') {

                s[i] = s[i] - 'a' + 'A';
            }
        }

        return s;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    WORD PROCESSING
    + CAPITALIZATION
    + STRING TRANSFORMATION

Think immediately:
    STRING TRAVERSAL

-----------------------------------------------------

KEY OBSERVATIONS:

1. Word boundaries are at spaces
2. First character is always a word start
3. Only need to check previous character
4. In-place modification is efficient

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling empty string
2. Capitalizing non-alphabetic characters
3. Not checking previous character properly
4. Using extra space unnecessarily

-----------------------------------------------------

SIMILAR PROBLEMS

- Word case conversion
- String formatting tasks
- Text processing problems

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Process words in string
- Capitalize/transform first letters
- Need word boundary detection

Think:
String Traversal with Boundary Detection

Algorithm:
1. Handle first character separately
2. Traverse string looking for boundaries
3. Apply transformation at word starts
4. Return modified string

Key insight:
Word boundaries are identified by spaces or string start

-----------------------------------------------------
*/
