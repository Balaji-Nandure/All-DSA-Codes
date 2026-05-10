/*
Problem: First Occurrence

GFG: https://www.geeksforgeeks.org/problems/first-occurrence-of-a-word-in-a-string/1

Description:
Given two strings txt and pat, return the 0-based index of the first occurrence of the substring pat in txt. If pat is not found, return -1.
Note: You are not allowed to use the inbuilt function.

Examples:

Input: txt = "GeeksForGeeks", pat = "Fr"
Output: -1
Explanation: "Fr" is not present in the string "GeeksForGeeks" as substring.

Input: txt = "GeeksForGeeks", pat = "For"
Output: 5
Explanation: "For" is present as substring in "GeeksForGeeks" from index 5 (0 based indexing).

Input: txt = "GeeksForGeeks", pat = "gr"
Output: -1
Explanation: "gr" is not present in the string "GeeksForGeeks" as substring.

Constraints:
1 ≤ txt.size(), pat.size() ≤ 1000

Approach (Naive String Matching):
This is a basic substring search problem where we need to find first occurrence without using built-in functions.

Key insight:
- Check each possible starting position in txt
- Compare characters of pat with txt starting from that position
- Return first index where complete match is found

Algorithm:
1. For each starting index i in txt:
   - Check if pat can fit starting from i
   - Compare all characters of pat with txt[i...i+m-1]
   - If all match, return i
2. If no match found, return -1

Time Complexity: O(n*m) where n = txt.length(), m = pat.length()
Space Complexity: O(1)

Pattern: String Matching / Brute Force
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
NAIVE STRING MATCHING
=====================================================

TC: O(n*m)
SC: O(1)

🔥 BRUTE FORCE APPROACH
- Check each possible starting position
- Compare characters one by one
- Return first match found

🧠 KEY INSIGHT:
For pat to match at position i:
- txt[i] must equal pat[0]
- txt[i+1] must equal pat[1]
- Continue for all characters

🎯 ALGORITHM:
1. For each start position i in txt:
   - Check bounds: i + m <= n
   - Compare all characters
   - Return i if complete match
2. Return -1 if no match

⚡ MATCHING LOGIC:
txt = "GeeksForGeeks"
pat = "For"

i=0: "Gee" != "For"
i=1: "eek" != "For"
...
i=5: "For" == "For" -> return 5
*/

class Solution {
public:

    // TC: O(n*m)
    // SC: O(1)

    int findFirstOccurrence(string txt, string pat) {

        int n = txt.length();

        int m = pat.length();

        // Check each possible starting position
        for(int i = 0; i <= n - m; i++) {

            bool match = true;

            // Compare all characters
            for(int j = 0; j < m; j++) {

                if(txt[i + j] != pat[j]) {

                    match = false;

                    break;
                }
            }

            // Complete match found
            if(match) {

                return i;
            }
        }

        // No match found
        return -1;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    SUBSTRING SEARCH
    + PATTERN MATCHING
    + NO BUILT-IN FUNCTIONS

Think immediately:
    NAIVE STRING MATCHING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Need to check all possible starting positions
2. Character-by-character comparison required
3. Return first occurrence (not all occurrences)
4. Handle boundary conditions properly

-----------------------------------------------------

COMMON MISTAKES:

1. Not checking bounds (i + m <= n)
2. Using built-in find function (not allowed)
3. Returning wrong index (off-by-one errors)
4. Not handling empty pattern edge case

-----------------------------------------------------

SIMILAR PROBLEMS

- Substring search problems
- Pattern matching algorithms
- String comparison tasks

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Find substring in string
- No built-in functions allowed
- Need first occurrence only

Think:
Naive String Matching

Algorithm:
1. For each start position i:
   - Check if pat fits at i
   - Compare all characters
   - Return i if match
2. Return -1

Key insight:
Systematic check of all possible positions

-----------------------------------------------------
*/
