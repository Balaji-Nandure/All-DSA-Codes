/**
 * Problem: Length of the Longest Valid Substring (Longest Valid Parentheses)
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Balanced Parenthesis problem", we only returned a boolean flag for the entire string.
 * - Here, the entire string may be invalid (e.g. `)()())`), but contains contiguous substrings that are valid.
 * - We must determine the MAXIMUM LENGTH of such contiguous valid substrings in O(N) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Approach 1: Stack of Indices (Standard Stack approach):
 *   - Push sentinel index `-1` onto the stack as the base before any valid match.
 *   - For each character at index `i`:
 *     - If `s[i] == '('`: Push `i`.
 *     - If `s[i] == ')'`: Pop the top.
 *       - If stack becomes empty: Current `)` had no matching `(`, so push `i` as the new base!
 *       - If stack is not empty: Valid substring extends from `st.top()` to `i`, length = `i - st.top()`.
 * - Approach 2: Two-Pass Counter (O(1) Extra Space):
 *   - Scan left-to-right counting `open` and `close`. Reset when `close > open`.
 *   - Scan right-to-left counting `open` and `close`. Reset when `open > close`.
 * 
 * TIME COMPLEXITY:
 * - O(N): Single pass over string of length N.
 * 
 * SPACE COMPLEXITY:
 * - Approach 1: O(N) auxiliary space.
 * - Approach 2: O(1) space.
 */

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

// Approach 1: Stack of indices (O(N) space)
int findMaxLenStack(const std::string& s) {
    std::stack<int> st;
    st.push(-1); // Sentinel base index
    int maxLen = 0;

    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If stack is empty, this ')' is unmatched and sets a new baseline anchor.
            // Otherwise, distance from current index to the new stack top is the valid length.
            if (st.empty()) {
                st.push(i);
            } else {
                maxLen = std::max(maxLen, i - st.top());
            }
        }
    }

    return maxLen;
}

// Approach 2: Two Counters (O(1) extra space)
int findMaxLenTwoCounters(const std::string& s) {
    int open = 0, close = 0, maxLen = 0;
    int n = s.length();

    // Left to Right scan
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') open++;
        else close++;

        if (open == close) {
            maxLen = std::max(maxLen, 2 * close);
        } else if (close > open) {
            open = close = 0;
        }
    }

    // Right to Left scan
    open = close = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '(') open++;
        else close++;

        if (open == close) {
            maxLen = std::max(maxLen, 2 * open);
        } else if (open > close) {
            open = close = 0;
        }
    }

    return maxLen;
}

int main() {
    std::string s1 = "((()";
    std::string s2 = ")()())";

    std::cout << "Max len for " << s1 << ": " << findMaxLenStack(s1) << "\n"; // 2
    std::cout << "Max len for " << s2 << ": " << findMaxLenStack(s2) << "\n"; // 4
    std::cout << "Max len (O(1) space) for " << s2 << ": " << findMaxLenTwoCounters(s2) << "\n"; // 4

    return 0;
}
