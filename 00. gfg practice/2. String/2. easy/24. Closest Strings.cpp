/*
Problem: Closest Strings

GFG: https://www.geeksforgeeks.org/problems/closest-strings0611/1

Description:
Given an array of strings and two words,
find minimum distance between their indices.

There can be multiple occurrences
of both words.

Examples:

Input:
S = {"the", "quick", "brown", "fox", "quick"}
word1 = "the"
word2 = "fox"

Output:
3

Explanation:
Indices:
"the" -> 0
"fox" -> 3

Distance = |0 - 3| = 3

--------------------------------------------------

Input:
S = {"geeks", "for", "geeks", "contribute", "practice"}

word1 = "geeks"
word2 = "practice"

Output:
2

Explanation:
Closest occurrence:
index 2 and index 4

Distance = 2

Constraints:
Sum of lengths of words ≤ 10^5

Approach:
- Traverse array once
- Store latest index of:
    word1 -> i1
    word2 -> i2

- Whenever both indices exist:
    update minimum distance

Why?
Closest pair can be formed using
latest occurrences only.

Dry Run:

S = {"the", "quick", "brown", "fox", "quick"}

word1 = "the"
word2 = "fox"

i=0 -> "the"
i1 = 0

i=3 -> "fox"
i2 = 3

Distance = |0 - 3| = 3

Answer = 3 ✅

--------------------------------------------------

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    int shortestDistance(vector<string> &s,
                         string word1,
                         string word2) {

        int i1 = -1;
        int i2 = -1;

        int ans = INT_MAX;

        for(int i = 0; i < s.size(); i++) {

            if(s[i] == word1) {
                i1 = i;
            }

            if(s[i] == word2) {
                i2 = i;
            }

            // Both words found
            if(i1 != -1 && i2 != -1) {

                ans = min(ans, abs(i1 - i2));
            }
        }

        return ans;
    }
};