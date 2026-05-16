/*
Problem: Count of camel case characters

GFG: https://www.geeksforgeeks.org/problems/count-of-camel-case-characters5903/1

Description:
Given a string. Count number of Camel Case characters in it.

Examples:

Input: S = "ckjkUUYII"
Output: 5
Explanation: Camel Case characters present: U, U, Y, I and I.

Input: S = "abcd"
Output: 0
Explanation: No Camel Case character present.

Constraints:
1 <= |S| <= 10^5

Approach (Character Traversal):
Key insight:
- Camel Case characters are uppercase English letters (A-Z)
- Simply count characters that fall in uppercase range
- Linear scan through the string

Algorithm:
1. Initialize count to 0
2. Traverse string character by character
3. For each character, check if it's between 'A' and 'Z'
4. If yes, increment count
5. Return count

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: Character Traversal / Counting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
CAMEL CASE COUNTING APPROACH
=====================================================

TC: O(n)
SC: O(1)

🔥 UPPERCASE CHARACTER COUNTING
- Traverse string
- Count uppercase letters (A-Z)
- Simple character range checking

🧠 KEY INSIGHT:
Camel Case definition:
- Uppercase English letters only
- Range: 'A' to 'Z'
- All other characters are ignored

🎯 ALGORITHM:
1. Initialize counter
2. Traverse string
3. Check character range
4. Count uppercase letters
5. Return total count

⚡ COUNTING LOGIC:
S = "ckjkUUYII"

Step 1: Initialize count = 0

Step 2: Traverse and count
c -> lowercase -> skip
k -> lowercase -> skip
j -> lowercase -> skip
k -> lowercase -> skip
U -> uppercase -> count = 1
U -> uppercase -> count = 2
Y -> uppercase -> count = 3
I -> uppercase -> count = 4
I -> uppercase -> count = 5

Final: 5

S = "abcd"

Step 1: Initialize count = 0

Step 2: Traverse and count
a -> lowercase -> skip
b -> lowercase -> skip
c -> lowercase -> skip
d -> lowercase -> skip

Final: 0
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int countCamelCase(string S) {

        int count = 0;

        // Traverse string
        for(char ch : S) {

            // Uppercase character
            if(ch >= 'A' && ch <= 'Z') {

                count++;
            }
        }

        return count;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    CHARACTER COUNTING
    + UPPERCASE DETECTION
    + RANGE CHECKING

Think immediately:
    CHARACTER TRAVERSAL WITH RANGE CHECK

-----------------------------------------------------

KEY OBSERVATIONS:

1. Camel Case = uppercase letters only
2. Simple range check: 'A' to 'Z'
3. Linear scan is sufficient
4. No complex logic needed

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling edge cases (empty string)
2. Using wrong character range
3. Counting non-alphabetic characters
4. Complex logic for simple counting

-----------------------------------------------------

SIMILAR PROBLEMS

- Character type counting
- Uppercase/lowercase statistics
- String analysis problems

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Count specific character types
- Need range-based character checking
- Simple string analysis

Think:
Character Traversal with Range Checking

Algorithm:
1. Define character range criteria
2. Traverse string
3. Check each character against criteria
4. Count matching characters
5. Return total count

Key insight:
Simple range checking enables efficient character counting

-----------------------------------------------------
*/
