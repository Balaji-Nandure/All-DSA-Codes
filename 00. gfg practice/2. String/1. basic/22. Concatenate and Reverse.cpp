/*
Problem: Concatenate and Reverse

GFG: https://www.geeksforgeeks.org/problems/concatenate-and-reverse/1

Description:
Given two strings s1 and s2 as input, concatenate two strings and then reverse the joined string.

Examples:

Input: s1 = "Geeks", s2 = "forGeeks"
Output: "skeeGrofskeeG" 
Explanation: Concatenating s1 and s2 to get "GeeksforGeeks" then reversing it to "skeeGrofskeeG".

Input: s1 = "Practice", s2 = "Geeks"
Output: "skeeGecitcarP"
Explanation: Concatenating s1 and s2 to get "PracticeGeeks" then reversing it to "skeeGecitcarP".

Constraints:
1 ≤ |s1| ≤ 10^3
1 ≤ |s2| ≤ 10^3

Approach (String Concatenation + Reversal):
Key insight:
- First concatenate the two strings: s1 + s2
- Then reverse the concatenated string
- Use built-in string operations for efficiency

Algorithm:
1. Concatenate s1 and s2 using + operator
2. Reverse the concatenated string using reverse() function
3. Return the reversed string

Time Complexity: O(n + m) where n = |s1|, m = |s2|
Space Complexity: O(n + m) for the concatenated and reversed string

Pattern: String Manipulation / Concatenation + Reversal
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
CONCATENATE AND REVERSE APPROACH
=====================================================

TC: O(n + m)
SC: O(n + m) for result string

🔥 STRING CONCATENATION + REVERSAL
- Concatenate two strings
- Reverse the concatenated result
- Use built-in operations for efficiency

🧠 KEY INSIGHT:
Two-step process:
1. Join strings: s1 + s2
2. Reverse the joined string

🎯 ALGORITHM:
1. Concatenate s1 and s2
2. Reverse the concatenated string
3. Return the result

⚡ CONCATENATION AND REVERSAL LOGIC:
s1 = "Geeks", s2 = "forGeeks"

Step 1: Concatenate
concatenated = s1 + s2 = "GeeksforGeeks"

Step 2: Reverse
"GeeksforGeeks" -> "skeeGrofskeeG"

Final: "skeeGrofskeeG"

s1 = "Practice", s2 = "Geeks"

Step 1: Concatenate
concatenated = s1 + s2 = "PracticeGeeks"

Step 2: Reverse
"PracticeGeeks" -> "skeeGecitcarP"

Final: "skeeGecitcarP"
*/

class Solution {
public:

    // TC: O(n + m)
    // SC: O(n + m) for result string

    string conRevstr(string s1, string s2) {

        // Step 1: Concatenate the two strings
        string concatenated = s1 + s2;

        // Step 2: Reverse the concatenated string
        reverse(concatenated.begin(), concatenated.end());

        // Step 3: Return the result
        return concatenated;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    STRING CONCATENATION
    + STRING REVERSAL
    + TWO-STEP TRANSFORMATION

Think immediately:
    CONCATENATE THEN REVERSE

-----------------------------------------------------

KEY OBSERVATIONS:

1. Two separate operations: concat + reverse
2. Order matters: concatenate first, then reverse
3. Built-in functions are efficient
4. Simple string manipulation problem

-----------------------------------------------------

COMMON MISTAKES:

1. Reversing individual strings instead of concatenated
2. Wrong order of operations
3. Not handling empty strings
4. Using manual reversal when built-in exists

-----------------------------------------------------

SIMILAR PROBLEMS

- String transformation problems
- Multi-step string operations
- Concatenation and modification

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Multiple string operations in sequence
- Concatenation followed by transformation
- Two-step string processing

Think:
Sequential String Operations

Algorithm:
1. Perform first operation (concatenation)
2. Perform second operation (reversal)
3. Return final result

Key insight:
Order of operations matters in string transformations

-----------------------------------------------------
*/
