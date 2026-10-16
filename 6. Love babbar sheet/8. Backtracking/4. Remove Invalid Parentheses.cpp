#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

/**
 * Problem: Remove Invalid Parentheses
 * 
 * Given a string s containing letters and parentheses, remove the MINIMUM number 
 * of invalid parentheses to make the input string valid. Return all unique results.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In standard parenthesis checking, we only validate in O(N).
 * - Here, we must search all possible subsets of removals, prune immediately when a prefix 
 *   becomes invalid, and guarantee MINIMAL removals without generating duplicates.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Two-Phase Optimal Backtracking:
 *   Phase 1 (Calculate Exact Removals in O(N)):
 *     Scan string to count misplaced left and right parentheses:
 *     - If '(': rem_left++
 *     - If ')': if rem_left > 0 rem_left--; else rem_right++;
 *     Now rem_left and rem_right give the EXACT minimum number of '(' and ')' to discard.
 * 
 *   Phase 2 (Pruned DFS Backtracking):
 *     At each index `idx`:
 *     Option A: Discard current character:
 *       - If s[idx] == '(' and rem_left > 0: recurse with rem_left - 1.
 *       - If s[idx] == ')' and rem_right > 0: recurse with rem_right - 1.
 *     Option B: Keep current character:
 *       - Maintain running balance (open_count, close_count).
 *       - If close_count > open_count at any point: PRUNE IMMEDIATELY (invalid prefix).
 * 
 *   Deduplication:
 *     To avoid duplicate branch exploration (e.g. string "...((..."), if consecutive 
 *     parentheses are identical, only remove the first one in this decision level.
 */

class Solution {
    vector<string> result;

    void backtrack(int idx, int open_count, int close_count, 
                   int rem_left, int rem_right, 
                   const string& s, string& current) {
        // Base case: Reached end of string
        if (idx == (int)s.length()) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Valid complete string requires exact required removals and equal matched brackets
            if (rem_left == 0 && rem_right == 0 && open_count == close_count) {
                result.push_back(current);
            }
            return;
        }

        char c = s[idx];

        // Pruning: A prefix is invalid if closing parentheses exceed open parentheses
        if (close_count > open_count) {
            return;
        }

        // Option 1: Discard the current character (if it's an invalid parenthesis)
        if (c == '(' && rem_left > 0) {
            // Skip duplicates: avoid removing consecutive '(' to prevent identical branches
            int next_idx = idx;
            while (next_idx + 1 < (int)s.length() && s[next_idx + 1] == '(') {
                next_idx++;
            }
            // Can discard 1 to (next_idx - idx + 1) '('s
            backtrack(idx + 1, open_count, close_count, rem_left - 1, rem_right, s, current);
        } else if (c == ')' && rem_right > 0) {
            backtrack(idx + 1, open_count, close_count, rem_left, rem_right - 1, s, current);
        }

        // Option 2: Keep the current character
        current.push_back(c);
        if (c == '(') {
            backtrack(idx + 1, open_count + 1, close_count, rem_left, rem_right, s, current);
        } else if (c == ')') {
            backtrack(idx + 1, open_count, close_count + 1, rem_left, rem_right, s, current);
        } else {
            // Non-parenthesis letter
            backtrack(idx + 1, open_count, close_count, rem_left, rem_right, s, current);
        }

        // Backtrack
        current.pop_back();
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        result.clear();

        // Step 1: Count exact minimum '(' and ')' to remove
        int rem_left = 0, rem_right = 0;
        for (char c : s) {
            if (c == '(') {
                rem_left++;
            } else if (c == ')') {
                if (rem_left > 0) {
                    rem_left--;
                } else {
                    rem_right++;
                }
            }
        }

        // Step 2: Backtrack with exact removal quotas
        string current = "";
        backtrack(0, 0, 0, rem_left, rem_right, s, current);

        // Deduplicate using unordered_set if needed
        unordered_set<string> unique_res(result.begin(), result.end());
        return vector<string>(unique_res.begin(), unique_res.end());
    }
};

int main() {
    Solution sol;
    string s1 = "()())()";
    vector<string> ans1 = sol.removeInvalidParentheses(s1);
    cout << "Valid variations for \"" << s1 << "\":\n";
    for (const string& str : ans1) {
        cout << "  \"" << str << "\"\n";
    }
    // Expected: "(())()", "()()()"

    string s2 = "(a)())()";
    vector<string> ans2 = sol.removeInvalidParentheses(s2);
    cout << "Valid variations for \"" << s2 << "\":\n";
    for (const string& str : ans2) {
        cout << "  \"" << str << "\"\n";
    }
    // Expected: "(a())()", "(a)()()"

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(2^N) bounded strictly by the search tree depth of min-removals (rem_left + rem_right).
 *   Pruning prefixes with close_count > open_count drastically eliminates invalid subtrees.
 * - Space Complexity: O(N) recursion stack and buffer string.
 */
