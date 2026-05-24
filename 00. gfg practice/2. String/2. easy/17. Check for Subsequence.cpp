/*
Problem: Check for Subsequence

GFG: https://www.geeksforgeeks.org/problems/check-for-subsequence4930/1

Description:
Given two strings s1 and s2,
check whether s1 is a subsequence of s2 or not.

A subsequence can be formed by deleting some characters
without changing the relative order of remaining characters.

Examples:

Input:
s1 = "AXY"
s2 = "YADXCP"

Output:
false

Explanation:
'Y' appears before 'A' in s2,
so order is not maintained.

--------------------------------------------------

Input:
s1 = "gksrek"
s2 = "geeksforgeeks"

Output:
true

Explanation:
Characters of s1 appear in s2
in the same relative order.

--------------------------------------------------

Input:
s1 = "abc"
s2 = "ahbgdc"

Output:
true

Constraints:
1 ≤ s1.size(), s2.size() ≤ 10^6

Approach (Two Pointers):
- Keep pointer i for s1
- Traverse s2 using pointer j
- If s1[i] == s2[j]:
    move i forward
- Always move j forward
- If i reaches end of s1:
    all characters matched in order

Dry Run:
s1 = "gksrek"
s2 = "geeksforgeeks"

  i=0 -> 'g'
  s2: g ✅ -> i=1

  i=1 -> 'k'
  s2: e,e,k ✅ -> i=2

  i=2 -> 's'
  s2: s ✅ -> i=3

  Continue similarly...

  All chars matched → true ✅

--------------------------------------------------

Dry Run:
s1 = "AXY"
s2 = "YADXCP"

  Need A -> found
  Need X -> found
  Need Y -> not found after X

  Return false ❌

Time Complexity: O(n + m)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n + m)  SC: O(1)
    bool isSubSequence(string A, string B) {

        int i = 0; // pointer for A
        int j = 0; // pointer for B

        while(i < A.size() && j < B.size()) {

            // Character matched
            if(A[i] == B[j]) {
                i++;
            }

            j++;
        }

        // All characters of A matched
        return (i == A.size());
    }
};