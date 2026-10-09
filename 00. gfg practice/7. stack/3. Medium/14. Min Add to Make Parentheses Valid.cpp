/*
    Problem Name: Min Add to Make Parentheses Valid
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 921

    Problem Statement:
    You are given a string `s` consisting only of the characters '(' and ')'.
    Your task is to determine the minimum number of parentheses (either '(' or ')')
    that must be inserted at any positions to make the string `s` a valid parentheses string.

    A parentheses string is considered valid if:
    1. Every opening parenthesis '(' has a corresponding closing parenthesis ')'.
    2. Every closing parenthesis ')' has a corresponding opening parenthesis '('.
    3. Parentheses are properly nested.

    Examples:
    Input: s = "(()("
    Output: 2
    Explanation: There are two unmatched '(' at the end, so we need to add two ')' to make the string valid.

    Input: s = ")))"
    Output: 3
    Explanation: Three '(' need to be added at the start to make the string valid.

    Input: s = ")()()"
    Output: 1
    Explanation: The very first ')' is unmatched, so we need to add one '(' at the beginning.

    Constraints:
    1 <= s.size() <= 10^5
    s[i] in { '(', ')' }

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) (Counter approach) / O(N) (Stack approach)

    Approach 1: Using Explicit Stack (O(N) Time, O(N) Space)
    Approach 2: Balance Counter (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. A valid pair is formed when a '(' is followed later by a matching ')'.
    2. An unmatched ')' occurs when a ')' appears with no preceding unmatched '(' available.
       Each such unmatched ')' requires adding a '(' to balance it (count as `ans++`).
    3. An unmatched '(' occurs when a '(' is left open without any succeeding ')'.
       Each such unmatched '(' requires adding a ')' to balance it (tracked by `balance`).
    4. By maintaining:
       - `balance`: number of currently open '(' waiting for a ')'.
       - `ans`: number of ')' that could not be matched with any open '('.
       - For each character `c` in `s`:
         * If `c == '('`: increment `balance++`.
         * If `c == ')'`:
           - If `balance > 0`: it matches an open '(', so decrement `balance--`.
           - Else: it is an unmatched ')', so increment `ans++`.
    5. Total parentheses to add = `ans + balance`.

    DRY RUN:
    Example: s = "(()("
    - c = '(': balance = 1, ans = 0
    - c = '(': balance = 2, ans = 0
    - c = ')': balance > 0 -> balance = 1, ans = 0
    - c = '(': balance = 2, ans = 0
    - Result = ans + balance = 0 + 2 = 2.

    Example: s = ")()()"
    - c = ')': balance == 0 -> ans = 1, balance = 0
    - c = '(': balance = 1, ans = 1
    - c = ')': balance > 0 -> balance = 0, ans = 1
    - c = '(': balance = 1, ans = 1
    - c = ')': balance > 0 -> balance = 0, ans = 1
    - Result = ans + balance = 1 + 0 = 1.
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

// ============================================================================
// Approach 1: Using Stack (O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    int minParentheses(string& s) {
        stack<char> st;

        for (char c : s) {
            if (c == '(') {
                st.push(c);
            } else {
                if (!st.empty() && st.top() == '(') {
                    st.pop();
                } else {
                    st.push(c);
                }
            }
        }

        return st.size();
    }
};

// ============================================================================
// Approach 2: Balance Counter (Optimal O(N) Time, O(1) Auxiliary Space)
// ============================================================================
class SolutionOptimal {
public:
    int minParentheses(string& s) {
        int balance = 0;
        int ans = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            } else {
                if (balance > 0) {
                    balance--;
                } else {
                    ans++;
                }
            }
        }

        return ans + balance;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int minParentheses(string& s) {
        SolutionOptimal solver;
        return solver.minParentheses(s);
    }

    // Overload for by-value passing
    int minParentheses(string s) {
        return minParentheses(s);
    }

    // LeetCode alias
    int minAddToMakeValid(string s) {
        return minParentheses(s);
    }
};
