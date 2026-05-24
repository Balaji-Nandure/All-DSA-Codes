/*
Problem: Naive Pattern Search

GFG: https://www.geeksforgeeks.org/problems/naive-pattern-search-1587115620/1

Description:
Given:
- text string S
- pattern string P

Check whether pattern exists
inside the text or not.

Return:
- true  -> if pattern found
- false -> otherwise

Examples:

Input:
S = "aabaacaadaabaaabaa"
P = "aaba"

Output:
true

Explanation:
Pattern exists starting at index 0.

--------------------------------------------------

Input:
S = "aabaacaadaabaaabaa"
P = "ccda"

Output:
false

Explanation:
Pattern does not exist.

Constraints:
1 ≤ |S|, |P| ≤ 10^3

Approach (Naive Search):
- Try every possible starting index
- Match pattern character by character
- If complete pattern matches:
    return true

Why called Naive?
- Brute force comparison
- No preprocessing

Dry Run:
S = "abcdef"
P = "cde"

Start at i=0:
a != c ❌

Start at i=1:
b != c ❌

Start at i=2:
c == c
d == d
e == e ✅

Pattern found → true

--------------------------------------------------

Time Complexity: O(n * m)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n * m)  SC: O(1)
    bool search(string pat, string txt) {

        int n = txt.size();
        int m = pat.size();

        // Try every starting index
        for(int i = 0; i <= n - m; i++) {

            int j = 0;

            // Match pattern
            while(j < m && txt[i + j] == pat[j]) {
                j++;
            }

            // Full pattern matched
            if(j == m) {
                return true;
            }
        }

        return false;
    }
};