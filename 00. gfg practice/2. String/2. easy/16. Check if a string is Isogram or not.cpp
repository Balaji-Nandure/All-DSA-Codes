/*
Problem: Check if a string is Isogram or not

GFG: https://www.geeksforgeeks.org/problems/check-if-a-string-is-isogram-or-not-1587115620/1

Description:
Given a string s of lowercase alphabets,
check whether it is an Isogram or not.

An Isogram is a string in which
no character appears more than once.

Examples:

Input: s = "machine"
Output: true

Explanation:
All characters appear exactly once.

--------------------------------------------------

Input: s = "geeks"
Output: false

Explanation:
'e' appears more than once.

--------------------------------------------------

Input: s = "abc"
Output: true

Constraints:
1 ≤ s.size() ≤ 10^3

Approach (Frequency Array):
- Create frequency array of size 26
- Traverse string:
    if character already appeared → return false
    else mark it visited
- If traversal completes:
    string is an isogram

Dry Run: s = "machine"

  m -> not visited
  a -> not visited
  c -> not visited
  h -> not visited
  i -> not visited
  n -> not visited
  e -> not visited

  No duplicates found → true ✅

--------------------------------------------------

Dry Run: s = "geeks"

  g -> not visited
  e -> not visited
  e -> already visited ❌

  Return false

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    bool isIsogram(string s) {

        bool visited[26] = {false};

        for(char ch : s) {

            int idx = ch - 'a';

            // Character already present
            if(visited[idx]) {
                return false;
            }

            visited[idx] = true;
        }

        return true;
    }
};