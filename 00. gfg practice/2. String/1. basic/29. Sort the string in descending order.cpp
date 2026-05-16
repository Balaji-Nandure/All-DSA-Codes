/*
Problem: Sort the string in descending order

GFG: https://www.geeksforgeeks.org/problems/sort-the-string-in-descending-order3542/1

Description:
Given a string s containing only lowercase alphabets, sort it in
lexicographically-descending order.

Examples:

Input: s = "geeks"
Output: "skgee"
Explanation: "skgee" is the lexicographically descending order.

Input: s = "for"
Output: "rof"
Explanation: "rof" is in lexicographically-descending order.

Constraints:
1 <= |s| <= 10^5
s contains only lowercase alphabets.

Approach (Frequency Counting):
Since the string contains only lowercase alphabets, there are only 26 possible
characters. Count the frequency of each character, then rebuild the string from
'z' to 'a'.

Key insight:
- Sorting normally takes O(n log n)
- But lowercase alphabets are limited to 26 characters
- Frequency counting allows us to build descending order in O(n)

Algorithm:
1. Create a frequency array of size 26
2. Traverse the string and count every character
3. Traverse characters from 'z' to 'a'
4. Add each character frequency times to the answer
5. Return the answer string

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: Frequency Counting / String Sorting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
FREQUENCY COUNTING APPROACH
=====================================================

TC: O(n)
SC: O(1)

FREQUENCY COUNTING
- Count how many times each lowercase character appears
- Rebuild the string from largest character to smallest character
- This gives descending lexicographical order

KEY INSIGHT:
Only 26 lowercase letters are possible.
So, instead of comparing characters again and again, store their counts.

ALGORITHM:
1. Initialize freq[26] with 0
2. For each character ch in s:
   - freq[ch - 'a']++
3. For i from 25 down to 0:
   - Add char('a' + i) freq[i] times
4. Return the final string

DRY RUN:
s = "geeks"

Frequency:
e -> 2
g -> 1
k -> 1
s -> 1

Traverse from z to a:
s, k, g, e, e

Result = "skgee"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    string ReverseSort(string s) {

        vector<int> freq(26, 0);

        for(char ch : s) {

            freq[ch - 'a']++;
        }

        string ans = "";

        for(int i = 25; i >= 0; i--) {

            while(freq[i] > 0) {

                ans.push_back(char('a' + i));

                freq[i]--;
            }
        }

        return ans;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    SORTING LOWERCASE STRING
    + LIMITED CHARACTER SET
    + LEXICOGRAPHICAL ORDER

Think immediately:
    FREQUENCY COUNTING

-----------------------------------------------------

KEY OBSERVATIONS:

1. The string contains only lowercase alphabets.
2. There are only 26 possible characters.
3. Descending order means start from 'z' and move towards 'a'.
4. Frequency counting avoids O(n log n) sorting.

-----------------------------------------------------

COMMON MISTAKES:

1. Sorting in ascending order by mistake.
2. Forgetting repeated characters.
3. Using extra space based on n unnecessarily.
4. Writing a comparator when counting is simpler.

-----------------------------------------------------

SIMILAR PROBLEMS

- Sort a string in ascending order
- Count frequency of characters
- Rearrange string based on character order
- Sort characters with limited alphabet

-----------------------------------------------------

REUSABLE PATTERN:

Whenever:
- Input characters belong to a small fixed range
- Need sorted output
- Character frequencies matter

Think:
Frequency Counting

Algorithm:
1. Count all character frequencies
2. Traverse the character range in required order
3. Append each character according to its count
4. Return the rebuilt string

-----------------------------------------------------
*/
