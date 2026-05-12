/*
Problem:
Remove all common characters from both strings
and concatenate remaining characters.

If no characters remain, return "-1".

Example:
s1 = "aacdb"
s2 = "gafd"

Common chars = a, d

Remaining:
s1 -> c b
s2 -> g f

Answer = "cbgf"

Approach:
1. Store frequency/presence of characters of s1.
2. Store frequency/presence of characters of s2.
3. Traverse s1:
      keep characters not present in s2
4. Traverse s2:
      keep characters not present in s1
5. If result empty return "-1"

Why this works?
- A character is common if it exists in both strings.
- We only append characters unique to their string.

Pattern:
Hashing / Frequency Array

Time Complexity: O(N + M)
Space Complexity: O(1)

GFG Link:
https://www.geeksforgeeks.org/problems/remove-common-characters-and-concatenate-1587115621/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    string concatenatedString(string s1, string s2) {

        // Presence arrays
        int freq1[26] = {0};
        int freq2[26] = {0};

        // Mark characters present in s1
        for(char ch : s1) {
            freq1[ch - 'a'] = 1;
        }

        // Mark characters present in s2
        for(char ch : s2) {
            freq2[ch - 'a'] = 1;
        }

        string ans = "";

        // Keep chars from s1 not present in s2
        for(char ch : s1) {

            if(freq2[ch - 'a'] == 0) {
                ans += ch;
            }
        }

        // Keep chars from s2 not present in s1
        for(char ch : s2) {

            if(freq1[ch - 'a'] == 0) {
                ans += ch;
            }
        }

        // If nothing remains
        if(ans.empty()) {
            return "-1";
        }

        return ans;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    REMOVE COMMON ELEMENTS
    + STRING CONCATENATION
    + ORDER PRESERVATION

Think immediately:
    FREQUENCY COUNTING + FILTERING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Common character = present in both strings
2. Uncommon character = present in exactly one string
3. Order preservation requires sequential processing
4. Fixed alphabet size enables O(1) space

-----------------------------------------------------

COMMON MISTAKES:

1. Removing duplicates incorrectly
2. Not preserving original order
3. Forgetting "-1" return case
4. Using wrong condition for common/uncommon

-----------------------------------------------------

SIMILAR PROBLEMS

- Remove common elements problems
- String filtering and concatenation
- Character set operations

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Remove common elements from two collections
- Concatenate remaining elements
- Preserve original order

Think:
Frequency Counting + Sequential Filtering

Algorithm:
1. Mark presence in both collections
2. Filter uncommon elements from each
3. Concatenate in original order
4. Handle empty result case

Key insight:
Common = present in both, Uncommon = present in exactly one

-----------------------------------------------------
*/
