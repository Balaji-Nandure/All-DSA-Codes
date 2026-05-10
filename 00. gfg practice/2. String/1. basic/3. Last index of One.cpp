/*
Problem: Last index of One

GFG: https://www.geeksforgeeks.org/problems/last-index-of-one/1

Description:
Given a string s consisting of only '0's and '1's, find the last index of the '1' present.

Note: If '1' is not present, return "-1"

Examples:

Input: s = 00001
Output: 4
Explanation: Last index of 1 in given string is 4.

Input: s = 0
Output: -1
Explanation: Since, 1 is not present, so output is -1.

Constraints:
1 <= |s| <= 10^6
s = {0,1}

Expected Time Complexity: O(n)
Expected Auxillary Space: O(1)

Approach (Reverse Traversal):
This is a simple search problem where we need to find the last occurrence of '1'.

Key insight:
- Traverse string from right to left (reverse order)
- Return first index where '1' is found
- If no '1' found, return -1

Algorithm:
1. Start from the last index (n-1) and go backwards
2. For each index i:
   - If s[i] == '1', return i
3. If loop completes, return -1 (no '1' found)

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: Reverse Traversal / Linear Search
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
REVERSE TRAVERSAL SEARCH
=====================================================

TC: O(n)
SC: O(1)

🔥 REVERSE SEARCH APPROACH
- Traverse string from right to left
- Find first occurrence of '1'
- Most efficient for last occurrence

🧠 KEY INSIGHT:
To find last occurrence:
- Start from the end
- Move backwards until '1' found
- First '1' encountered is the last one

🎯 ALGORITHM:
1. Start from index n-1 (last character)
2. While i >= 0:
   - If s[i] == '1', return i
   - i--
3. Return -1 if no '1' found

⚡ REVERSE LOGIC:
s = "00001"
i=4: s[4]='1' → return 4

s = "00000"
i=4: s[4]='0'
i=3: s[3]='0'
i=2: s[2]='0'
i=1: s[1]='0'
i=0: s[0]='0'
i=-1: loop ends → return -1
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int lastIndex(string s) {

        int n = s.length();

        // Traverse from right to left
        for(int i = n - 1; i >= 0; i--) {

            if(s[i] == '1') {

                return i;
            }
        }

        // No '1' found
        return -1;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    LAST OCCURRENCE
    + SPECIFIC CHARACTER SEARCH
    + STRING TRAVERSAL

Think immediately:
    REVERSE LINEAR SEARCH

-----------------------------------------------------

KEY OBSERVATIONS:

1. Reverse traversal finds last occurrence efficiently
2. O(n) time is optimal (must check each char in worst case)
3. O(1) space (no extra data structures needed)
4. Simple and straightforward solution

-----------------------------------------------------

COMMON MISTAKES:

1. Traversing from left to right (finds first occurrence)
2. Not handling empty string edge case
3. Returning wrong index (off-by-one errors)
4. Using extra space unnecessarily

-----------------------------------------------------

SIMILAR PROBLEMS

- Last occurrence problems
- Character search in strings
- Linear search variations

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Find last occurrence of element
- Search in string/array
- Need reverse traversal

Think:
Reverse Linear Search

Algorithm:
1. Start from end (n-1)
2. Move backwards (i--)
3. Return index when target found
4. Return -1 if not found

Key insight:
Reverse traversal = last occurrence

-----------------------------------------------------
*/
