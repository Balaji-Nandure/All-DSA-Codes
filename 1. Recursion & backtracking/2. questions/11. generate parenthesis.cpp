/*
 * Problem: Generate Parentheses
 *
 * LeetCode 22: Generate Parentheses
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/generate-all-possible-parentheses/1
 *
 * Given an integer n, return all combinations of n pairs of balanced parentheses.
For example: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Approach:
- Use recursion & backtracking.
- At each step, we can:
    - Add '(' if we still have left parentheses available.
    - Add ')' if it will not invalidate the sequence (i.e., right < left used).

Function signature:
vector<string> generateParenthesis(int n)
*/

#include <bits/stdc++.h>
using namespace std;

// Helper backtracking function
void backtrack(int n, int left, int right, string &curr, vector<string> &result) {
    // Base case: all parentheses used
    if (curr.length() == 2 * n) {
        result.push_back(curr);
        return;
    }
    // Add '(' if available
    if (left < n) {
        curr.push_back('(');
        backtrack(n, left + 1, right, curr, result);
        curr.pop_back();
    }
    // Add ')' if it won't invalidate the string
    if (right < left) {
        curr.push_back(')');
        backtrack(n, left, right + 1, curr, result);
        curr.pop_back();
    }
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    string curr = "";
    backtrack(n, 0, 0, curr, result);
    return result;
}

int main() {
    int n = 5;
    vector<string> ans = generateParenthesis(n);
    cout << "All combinations of balanced parentheses for n = " << n << ":" << endl;
    for (auto &s : ans) {
        cout << s << endl;
    }
    return 0;
}
