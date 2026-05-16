/*
Problem: Delete alternate characters

GFG: https://www.geeksforgeeks.org/problems/delete-alternate-characters/1

Description:
Given a string s as input. Delete the characters at odd indices of the string. 
Return the final string after deletion of characters at odd indices.

Examples:

Input: s = "Geeks"
Output: "Ges" 
Explanation: Deleted "e" at index 1 and "k" at index 3.

Input: s = "GeeksforGeeks"
Output: "GesoGes"
Explanation: Deleted e, k, f, r, e, k at index 1, 3, 5, 7, 9, 11.

Constraints:
1 <= s.size() <= 1000

Approach (String Traversal):
Key insight:
- Keep characters at even indices (0, 2, 4, ...)
- Delete characters at odd indices (1, 3, 5, ...)
- Build result string with only even index characters

Algorithm:
1. Initialize empty result string
2. Traverse string with index i from 0 to end
3. If i is even (i % 2 == 0), add character to result
4. Skip characters at odd indices
5. Return the result string

Time Complexity: O(n)
Space Complexity: O(n/2) ≈ O(n) for result string

Pattern: String Filtering / Index-based Selection
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
ALTERNATE CHARACTER DELETION APPROACH
=====================================================

TC: O(n)
SC: O(n/2) ≈ O(n) for result string

🔥 INDEX-BASED FILTERING
- Keep characters at even indices
- Skip characters at odd indices
- Build result string with filtered characters

🧠 KEY INSIGHT:
Index pattern recognition:
- Even indices: 0, 2, 4, 6, ...
- Odd indices: 1, 3, 5, 7, ...
- Keep only even index characters

🎯 ALGORITHM:
1. Initialize empty result string
2. Traverse string with index
3. Add character if index is even
4. Skip if index is odd
5. Return filtered string

⚡ DELETION LOGIC:
s = "GeeksforGeeks"

Indices: 0 1 2 3 4 5 6 7 8 9 10 11 12
Chars:  G e e k s f o r G e e  k  s

Step 1: Initialize result = ""

Step 2: Traverse and filter
Index 0: even -> keep 'G' -> result = "G"
Index 1: odd -> skip 'e'
Index 2: even -> keep 'e' -> result = "Ge"
Index 3: odd -> skip 'k'
Index 4: even -> keep 's' -> result = "Ges"
Index 5: odd -> skip 'f'
Index 6: even -> keep 'o' -> result = "Geso"
Index 7: odd -> skip 'r'
Index 8: even -> keep 'G' -> result = "GesoG"
Index 9: odd -> skip 'e'
Index 10: even -> keep 'e' -> result = "GesoGe"
Index 11: odd -> skip 'k'
Index 12: even -> keep 's' -> result = "GesoGes"

Final: "GesoGes"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(n/2) ≈ O(n) for result string

    string delAlternate(string s) {

        string result = "";

        // Jump by 2 to directly access even indices
        for(int i = 0; i < s.length(); i += 2) {
            result += s[i];
        }

        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    CHARACTER DELETION
    + INDEX-BASED FILTERING
    + ALTERNATE PATTERN

Think immediately:
    INDEX-BASED STRING FILTERING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Even indices start from 0
2. Odd indices start from 1
3. Pattern is regular and predictable
4. Simple filtering problem

-----------------------------------------------------

COMMON MISTAKES:

1. Starting counting from 1 instead of 0
2. Using wrong modulo condition
3. Not handling empty string
4. Complex logic for simple filtering

-----------------------------------------------------

SIMILAR PROBLEMS

- Keep alternate characters
- Index-based string operations
- String filtering problems

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Filter characters based on position
- Need index-based selection
- Alternate pattern operations

Think:
Index-based String Filtering

Algorithm:
1. Traverse string with index
2. Apply condition on index
3. Keep or skip based on condition
4. Build result string

Key insight:
Index parity determines character selection

-----------------------------------------------------
*/
