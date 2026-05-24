/*
Problem: Remaining String

GFG: https://www.geeksforgeeks.org/problems/remaining-string3515/1

Description:
Given a string s, a character ch, and an integer count,
return the substring remaining after the character ch
has appeared count number of times.

If:
- ch does not appear count times
- OR remaining substring becomes empty

Return "".

Note:
Uppercase and lowercase are treated differently.

Examples:

Input:
s = "Thisisdemostring"
ch = 'i'
count = 3

Output:
"ng"

Explanation:
Occurrences of 'i':
1st -> index 2
2nd -> index 4
3rd -> index 13

Remaining substring after index 13:
"ng"

--------------------------------------------------

Input:
s = "Thisisdemostri"
ch = 'i'
count = 3

Output:
""

Explanation:
3rd occurrence is at last index,
so remaining substring is empty.

--------------------------------------------------

Input:
s = "abcd"
ch = 'x'
count = 2

Output:
""

Explanation:
'x' does not appear 2 times.

Constraints:
1 ≤ s.length() ≤ 10^5
1 ≤ count ≤ s.length()

Approach (Single Traversal):
- Traverse the string
- Count occurrences of ch
- When count-th occurrence is found:
    return substring after that index
- If substring is empty OR count-th occurrence not found:
    return ""

Dry Run:
s = "Thisisdemostring"
ch = 'i'
count = 3

i=0 -> 'T'
i=2 -> 'i' -> occurrence=1
i=4 -> 'i' -> occurrence=2
...
i=13 -> 'i' -> occurrence=3

Return s.substr(14)
= "ng" ✅

Time Complexity: O(n)
Space Complexity: O(1) extra
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1) extra
    string printString(string s, char ch, int count) {

        int occurrence = 0;

        for(int i = 0; i < s.size(); i++) {

            // Found target character
            if(s[i] == ch) {

                occurrence++;

                // count-th occurrence found
                if(occurrence == count) {

                    // If no remaining substring
                    if(i == s.size() - 1) return "";

                    // Return remaining substring
                    return s.substr(i + 1);
                }
            }
        }

        // count-th occurrence not found
        return "";
    }
};