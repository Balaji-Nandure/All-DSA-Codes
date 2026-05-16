/*
Problem: Remove all characters other than alphabets

GFG: https://www.geeksforgeeks.org/problems/remove-all-characters-other-than-alphabets/1

Description:
Given a string S, remove all the characters other than the alphabets.
Return "-1" if no alphabets remain.

Examples:

Input: S = "$Gee*k;s..fo, r'Ge^eks?"
Output: "GeeksforGeeks"
Explanation: Removed characters other than alphabets.

Input: S = "{{{}}> *& ^%*)"
Output: "-1"
Explanation: There are no alphabets.

Constraints:
1 <= |S| <= 10^5

Approach (Character Filtering):
This is a simple string filtering problem.

Key insight:
- We only need to keep alphabet characters
- All digits, spaces, and special characters should be skipped
- If the final string becomes empty, return "-1"

Algorithm:
1. Create an empty answer string
2. Traverse every character of S
3. If the character is an alphabet, add it to answer
4. After traversal, if answer is empty, return "-1"
5. Otherwise, return answer

Time Complexity: O(|S|)
Space Complexity: O(|S|)

Pattern: String Filtering / Character Checking
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
CHARACTER FILTERING APPROACH
=====================================================

TC: O(n)
SC: O(n)

CHARACTER FILTERING
- Traverse the string from left to right
- Keep only alphabet characters
- Ignore all non-alphabet characters

KEY INSIGHT:
The relative order of alphabets must remain the same.
So, we build a new string by appending only valid characters.

ALGORITHM:
1. Initialize ans = ""
2. For each character ch in S:
   - If ch is between 'a' and 'z' or between 'A' and 'Z',
     append it to ans
3. If ans is empty, return "-1"
4. Return ans

DRY RUN:
S = "$Gee*k;s..fo, r'Ge^eks?"

Keep: G e e k s f o r G e e k s
Skip: $, *, ;, ., ., ,, space, ', ^, ?

Result = "GeeksforGeeks"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(n)

    string removeSpecialCharacter(string S) {

        string ans = "";

        for(char ch : S) {

            if((ch >= 'a' && ch <= 'z') ||
               (ch >= 'A' && ch <= 'Z')) {

                ans.push_back(ch);
            }
        }

        if(ans.empty()) {

            return "-1";
        }

        return ans;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    REMOVING SPECIAL CHARACTERS
    + KEEPING ONLY ALPHABETS
    + PRESERVING ORIGINAL ORDER

Think immediately:
    CHARACTER FILTERING

-----------------------------------------------------

KEY OBSERVATIONS:

1. We do not need sorting or hashing.
2. We only need one pass over the string.
3. The order of remaining alphabets should not change.
4. Empty result must be handled by returning "-1".

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting to return "-1" when no alphabets exist.
2. Removing lowercase alphabets accidentally.
3. Removing uppercase alphabets accidentally.
4. Printing the answer instead of returning it.

-----------------------------------------------------

SIMILAR PROBLEMS

- Remove spaces from a string
- Remove digits from a string
- Keep only numeric characters
- Filter characters based on conditions

-----------------------------------------------------

REUSABLE PATTERN:

Whenever:
- Some characters need to be removed
- Some characters need to be kept
- Original order must be maintained

Think:
Filtering with a result string

Algorithm:
1. Create an empty result string
2. Traverse all characters
3. Append only characters that satisfy the condition
4. Handle empty result if required
5. Return the result

-----------------------------------------------------
*/
