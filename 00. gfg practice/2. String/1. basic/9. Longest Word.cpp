/*
Problem:
Given an array of strings,
return the longest string.

If multiple strings have same maximum length,
return the first occurring string.

Example:
Input:
["Apple", "Mango", "Orange", "Banana"]

Output:
"Orange"

Because:
Orange and Banana both have length 6,
but Orange appears first.

Approach:
1. Assume first string is longest.
2. Traverse array.
3. If current string length is greater,
   update answer.
4. Do NOT update for equal length,
   because we need first occurring string.

Why this works?
- We always keep track of the longest string seen so far.
- Ignoring equal lengths preserves first occurrence.

Pattern:
Linear Traversal

Time Complexity: O(N)
Space Complexity: O(1)

GFG Link:
https://www.geeksforgeeks.org/problems/longest-word-in-dictionary2256/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    string longest(vector<string>& arr) {

        // Assume first string is longest
        string ans = arr[0];

        // Traverse all strings
        for(int i = 1; i < arr.size(); i++) {

            // Update only if strictly longer
            if(arr[i].size() > ans.size()) {
                ans = arr[i];
            }
        }

        return ans;
    }
};

/*
Summary:
- Keep track of longest string
- Update only for strictly greater length
- Naturally keeps first occurring answer
*/
