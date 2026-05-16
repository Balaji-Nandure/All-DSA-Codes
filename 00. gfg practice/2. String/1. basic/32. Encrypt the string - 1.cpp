/*
Problem: Encrypt the string - 1

GFG: https://www.geeksforgeeks.org/problems/encrypt-the-string-1/1

Description:
Every substring of identical letters is replaced by a single instance of that
letter followed by the number of occurrences of that letter. The resulting
string is then reversed.

Examples:

Input: s = "aabc"
Output: "1c1b2a"
Explanation:
Step 1: a2b1c1
Step 2: 1c1b2a

Input: s = "aaaaa"
Output: "5a"
Explanation:
Step 1: a5
Step 2: 5a

Constraints:
1 <= |s| <= 1000

Approach (Run Length Encoding):
Traverse the string and count consecutive equal characters. Append the
character and its count to a temporary string, then reverse that string.

Key insight:
- Equal adjacent characters form one group
- Each group becomes character + count
- Final answer is the reverse of the encoded string

Algorithm:
1. Traverse the string with a counter for consecutive equal characters
2. For each group, append character and its count to an encoded string
3. Reverse the encoded string
4. Return the reversed string

Time Complexity: O(|s|)
Space Complexity: O(|s|)

Pattern: String Compression / Run Length Encoding
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
RUN LENGTH ENCODING APPROACH
=====================================================

TC: O(n)
SC: O(n)

RUN LENGTH ENCODING
- Group consecutive equal characters
- Store each group as character + count
- Reverse the final encoded string

KEY INSIGHT:
We do not need to compress the entire string first and then reverse in place.
Building the encoded result directly is simple and clear.

DRY RUN:
s = "aabc"

Groups:
a -> 2
b -> 1
c -> 1

Encoded = "a2b1c1"
Reversed = "1c1b2a"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(n)

    string encryptString(string s) {

        string encoded = "";
        int n = s.size();

        for(int i = 0; i < n; ) {

            char current = s[i];
            int count = 0;

            while(i < n && s[i] == current) {
                count++;
                i++;
            }

            encoded.push_back(current);
            encoded += to_string(count);
        }

        reverse(encoded.begin(), encoded.end());
        return encoded;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    CONSECUTIVE CHARACTER GROUPS
    + COUNTING RUNS
    + STRING ENCODING

Think immediately:
    RUN LENGTH ENCODING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Only adjacent identical letters are grouped together.
2. Each group becomes one character plus its frequency.
3. The final result is the reverse of the encoded form.

-----------------------------------------------------

COMMON MISTAKES:

1. Counting all equal letters globally instead of consecutive runs.
2. Forgetting to reverse the encoded string.
3. Missing the last run.
4. Using integer concatenation incorrectly instead of converting count to string.

-----------------------------------------------------
*/
