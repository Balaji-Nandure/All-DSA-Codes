/*
Problem: Parenthesis Checker

GFG: https://www.geeksforgeeks.org/problems/parenthesis-checker2744/1

Description:
Given a string s composed of '(', ')', '{', '}', '[', ']',
check if the expression is balanced.

Examples:

Input: s = "[{()}]"    Output: true
Input: s = "[()()]{}"  Output: true
Input: s = "([]"       Output: false
Input: s = "([{]})"    Output: false

Constraints:
1 ≤ s.size() ≤ 10^6

Approach (Stack):
- Opening bracket → push onto stack
- Closing bracket → pop top & check match
- Stack LIFO naturally handles nesting

Dry Run: s = "[{()}]"
  '[' → push         Stack: [ '[' ]
  '{' → push         Stack: [ '[', '{' ]
  '(' → push         Stack: [ '[', '{', '(' ]
  ')' → top='(' ✅   Stack: [ '[', '{' ]
  '}' → top='{' ✅   Stack: [ '[' ]
  ']' → top='[' ✅   Stack: [ ]
  Stack empty → true ✅

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(n)  SC: O(n)
    bool isBalanced(string& s) {

        stack<char> st;

        for(char ch : s) {

            if(ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            }
            else {
                if(st.empty()) return false;

                char top = st.top();
                st.pop();

                if(ch == ')' && top != '(') return false;
                if(ch == '}' && top != '{') return false;
                if(ch == ']' && top != '[') return false;
            }
        }

        return st.empty();
    }
};
