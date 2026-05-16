/*
Problem: Alternate Merge two strings

GFG: https://www.geeksforgeeks.org/problems/alternate-merge-two-strings/1

Description:
Given two strings s1 and s2, merge them alternatively i.e. the first character of s1 then the first character of s2 and so on till the strings end.

Note: Add the whole string if other string is empty.

Examples:

Input: s1 = "Hello", s2 = "Bye"
Output: "HBeylelo"
Explanation: The characters of both the given strings are arranged alternatlively.

Input: s1 = "abc", s2 = "def"
Output: "adbecf"
Explanation: The characters of both the given strings are arranged alternatlively.

Constraints:
1 <= |s1|, |s2| <= 10^3

Approach (Two Pointers / Simulation):
Key insight:
- Use two pointers to traverse both strings simultaneously
- Add characters alternately from both strings
- When one string finishes, append remaining characters of the other

Algorithm:
1. Initialize two pointers i and j to 0
2. While both strings have characters:
   - Add s1[i] to result, increment i
   - Add s2[j] to result, increment j
3. Append remaining characters from s1 (if any)
4. Append remaining characters from s2 (if any)
5. Return the merged string

Time Complexity: O(n + m) where n = |s1|, m = |s2|
Space Complexity: O(n + m) for the result string

Pattern: Two Pointers / String Simulation
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
ALTERNATE MERGE APPROACH
=====================================================

TC: O(n + m)
SC: O(n + m) for result string

🔥 TWO POINTERS SIMULATION
- Use two pointers for both strings
- Add characters alternately
- Handle remaining characters separately

🧠 KEY INSIGHT:
Alternate merging pattern:
- Take one character from s1
- Take one character from s2
- Repeat until one string ends
- Append remaining characters

🎯 ALGORITHM:
1. Initialize two pointers
2. Alternate merge while both strings exist
3. Append remaining characters
4. Return merged string

⚡ MERGE LOGIC:
s1 = "Hello", s2 = "Bye"

Step 1: Initialize pointers
i = 0, j = 0, result = ""

Step 2: Alternate merge
Iteration 1:
result += s1[0] = 'H' -> result = "H"
result += s2[0] = 'B' -> result = "HB"
i = 1, j = 1

Iteration 2:
result += s1[1] = 'e' -> result = "HBe"
result += s2[1] = 'y' -> result = "HBe y"
i = 2, j = 2

Iteration 3:
result += s1[2] = 'l' -> result = "HBe yl"
result += s2[2] = 'e' -> result = "HBe yle"
i = 3, j = 3

Step 3: s2 finished, append remaining s1
result += s1[3] = 'l' -> result = "HBe ylel"
result += s1[4] = 'o' -> result = "HBe ylelo"

Final: "HBeylelo"
*/

class Solution {
public:

    // TC: O(n + m)
    // SC: O(n + m) for result string

    string merge(string s1, string s2) {

        int i = 0;
        int j = 0;

        string ans = "";

        // Alternate merge while both strings have characters
        while(i < s1.size() && j < s2.size()) {

            ans += s1[i];
            ans += s2[j];

            i++;
            j++;
        }

        // Append remaining characters of s1
        while(i < s1.size()) {

            ans += s1[i];
            i++;
        }

        // Append remaining characters of s2
        while(j < s2.size()) {

            ans += s2[j];
            j++;
        }

        return ans;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    STRING MERGING
    + ALTERNATE PATTERN
    + TWO STRING PROCESSING

Think immediately:
    TWO POINTERS SIMULATION

-----------------------------------------------------

KEY OBSERVATIONS:

1. Need two pointers for both strings
2. Alternate pattern is fixed (s1 then s2)
3. Handle different length strings
4. Simple simulation problem

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling empty strings
2. Wrong order of characters
3. Forgetting remaining characters
4. Using complex logic for simple simulation

-----------------------------------------------------

SIMILAR PROBLEMS

- String interleaving
- Merge patterns
- Two string operations

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Merge two strings in specific pattern
- Need alternate processing
- Handle different length inputs

Think:
Two Pointers Simulation

Algorithm:
1. Initialize two pointers
2. Process according to pattern
3. Handle remaining characters
4. Return merged result

Key insight:
Alternate processing with boundary handling

-----------------------------------------------------
*/
