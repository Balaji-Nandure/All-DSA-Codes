/*
Problem: Reverse Using Stack

GFG: https://www.geeksforgeeks.org/problems/reverse-a-string-using-stack/1

Description:
Given a string s, reverse it using a stack.

Examples:

Input: s = "GeeksforGeeks"  Output: "skeeGrofskeeG"
Input: s = "Geek"           Output: "keeG"

Constraints:
1 ≤ s.length() ≤ 100

Approach (Stack):
- Push all chars onto stack
- Pop all chars back into string (LIFO gives reverse)

Dry Run: s = "Geek"
  Push: G, e, e, k  → Stack top: k
  Pop:  k, e, e, G  → "keeG" ✅

Time Complexity: O(n)
Space Complexity: O(n) — stack stores all chars
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(n)
    string reverse(string& s) {

        stack<char> st;

        for(char ch : s) st.push(ch);

        for(int i = 0; i < s.size(); i++) {
            s[i] = st.top();
            st.pop();
        }

        return s;
    }
};
