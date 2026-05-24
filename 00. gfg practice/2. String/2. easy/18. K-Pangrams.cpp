/*
Problem: K-Pangrams

GFG: https://www.geeksforgeeks.org/problems/k-pangrams0909/1

Description:
Given a string str and an integer k,
check whether the string can be converted into
a pangram using at most k operations.

A Pangram:
- Contains all 26 lowercase English alphabets
  at least once.

One operation:
- Replace an existing alphabetic character
  with any lowercase alphabet.

Spaces are ignored.

Examples:

Input:
str = "the quick brown fox jumps over the lazy dog"
k = 0

Output:
true

Explanation:
Already contains all 26 letters.

--------------------------------------------------

Input:
str = "aaaaaaaaaaaaaaaaaaaaaaaaaa"
k = 25

Output:
true

Explanation:
Keep one 'a' and convert remaining 25 chars
into missing 25 alphabets.

--------------------------------------------------

Input:
str = "a b c d e f g h i j k l m"
k = 20

Output:
false

Explanation:
Only 13 alphabetic characters exist.
Even after replacements,
cannot make all 26 alphabets appear.

Constraints:
1 ≤ str.size() ≤ 10^5
0 ≤ k ≤ 50

Approach:
- Ignore spaces
- Count total alphabetic characters
- If total letters < 26:
    impossible → return false

- Count distinct characters present
- Missing characters:
    missing = 26 - distinctCount

- To make pangram:
    we need to create all missing characters
    using replacements

- If missing <= k:
    return true
  else:
    return false

Dry Run:
str = "aaaaaaaaaaaaaaaaaaaaaaaaaa"
k = 25

Distinct chars = {a}
distinctCount = 1

Missing chars = 26 - 1 = 25

k = 25

25 <= 25 ✅
Return true

--------------------------------------------------

Dry Run:
str = "a b c d e f g h i j k l m"

Total letters = 13

13 < 26 ❌

Impossible to create pangram
Return false

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    bool kPangram(string str, int k) {

        bool present[26] = {false};

        int totalLetters = 0;
        int distinctCount = 0;

        for(char ch : str) {

            // Ignore spaces
            if(ch == ' ') continue;

            totalLetters++;

            int idx = ch - 'a';

            if(!present[idx]) {

                present[idx] = true;
                distinctCount++;
            }
        }

        // Not enough letters to form pangram
        if(totalLetters < 26) {
            return false;
        }

        int missingChars = 26 - distinctCount;

        return (missingChars <= k);
    }
};