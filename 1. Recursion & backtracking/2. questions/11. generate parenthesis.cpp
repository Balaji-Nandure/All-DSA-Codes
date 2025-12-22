/*
 * Problem: Generate Parentheses
 *
 * LeetCode 22: Generate Parentheses
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/generate-all-possible-parentheses/1
 *
 * Given an integer n, return all combinations of n pairs of balanced parentheses.
 *
 * Example: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 *
 * Approach: Use backtracking
 * - Add '(' if left parentheses available
 * - Add ')' if right < left (maintains balance)
 *
 * Time: O(4^n / sqrt(n)) - Catalan number
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Backtracking function to generate balanced parentheses
void backtrack(int n, int left, int right, string &curr, vector<string> &result) {
    // Base case: generated 2n characters (n pairs)
    if (curr.length() == 2 * n) {
        result.push_back(curr);
        return;
    }
    // Add '(' if we still have left parentheses available
    if (left < n) {
        curr.push_back('(');
        backtrack(n, left + 1, right, curr, result);
        curr.pop_back(); // Backtrack
    }
    // Add ')' if it won't invalidate (right < left ensures balance)
    if (right < left) {
        curr.push_back(')');
        backtrack(n, left, right + 1, curr, result);
        curr.pop_back(); // Backtrack
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
