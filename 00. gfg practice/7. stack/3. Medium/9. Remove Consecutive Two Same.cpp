/*
    Problem Name: Remove Consecutive Two Same
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 1047 (Remove All Adjacent Duplicates In String)

    Problem Statement:
    Given a string `s`, repeatedly remove all adjacent duplicate character pairs until no such pairs remain.
    Return the resulting string, or "-1" if the string becomes empty.

    Examples:
    Input: s = "aaabbaaccd"
    Output: "ad"
    Explanation:
    - Remove the first "aa" -> "abbaaccd"
    - Remove "bb" -> "aaaccd"
    - The remaining 'a' and following "aa" forms "aaa", removing adjacent "aa" leaves "accd"
    - Remove "cc" -> "ad"
    Final remaining string is "ad".

    Input: s = "aaaa"
    Output: "-1"
    Explanation:
    - First "aa" removed -> "aa"
    - Next "aa" removed -> ""
    Since the resulting string becomes empty, return "-1".

    Constraints:
    1 <= s.size() <= 10^5
    s consists of lowercase English letters.

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N) (stack space / result string)

    Approach 1: Using std::stack<char> (Optimal O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Using std::string as a Stack (Optimal O(N) Time, O(1) Auxiliary Space)

    INTUITION & STRATEGY:
    1. Whenever two adjacent characters match, they destroy each other.
    2. Destroying a pair can cause previously non-adjacent characters to become adjacent,
       which may also form duplicate pairs.
    3. A Stack (Last-In, First-Out) naturally simulates this process:
       - For each character `ch` in string `s`:
         * If the stack is not empty and `stack.top() == ch`:
           - We found an adjacent matching pair!
           - Pop the top character (both characters are deleted).
         * Otherwise:
           - Push `ch` onto the stack.
    4. At the end:
       - If the stack is empty, return "-1".
       - Otherwise, reconstruct the string from the stack.
    5. Optimization (Approach 2):
       - Use a `std::string` directly as a stack using `push_back()` and `pop_back()`.
       - Avoids reversing or extra conversion at the end.

    DRY RUN:
    Example: s = "aaabbaaccd"
    - 'a': st = "a"
    - 'a': matches top 'a' -> pop -> st = ""
    - 'a': st = "a"
    - 'b': st = "ab"
    - 'b': matches top 'b' -> pop -> st = "a"
    - 'a': matches top 'a' -> pop -> st = ""
    - 'a': st = "a"
    - 'c': st = "ac"
    - 'c': matches top 'c' -> pop -> st = "a"
    - 'd': st = "ad"
    - Result: "ad" (not empty, so return "ad").
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// ============================================================================
// Approach 1: Using std::stack<char> (Optimal O(N) Time, O(N) Space)
// ============================================================================
class SolutionStack {
public:
    string removePair(string s) {
        stack<char> st;

        for (char ch : s) {
            // If top matches current character, pop the duplicate pair
            if (!st.empty() && st.top() == ch) {
                st.pop();
            } else {
                st.push(ch);
            }
        }

        // If all characters were removed, return "-1"
        if (st.empty()) {
            return "-1";
        }

        // Reconstruct string from stack
        string result = "";
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        reverse(result.begin(), result.end());

        return result;
    }
};

// ============================================================================
// Approach 2: Using std::string directly as a Stack (O(N) Time, O(1) Aux Space)
// ============================================================================
class SolutionStringStack {
public:
    string removePair(string s) {
        string res = "";

        for (char ch : s) {
            // If last character matches current, remove the pair
            if (!res.empty() && res.back() == ch) {
                res.pop_back();
            } else {
                res.push_back(ch);
            }
        }

        // If string becomes empty, return "-1"
        return res.empty() ? "-1" : res;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    string removePair(string s) {
        SolutionStringStack solver;
        return solver.removePair(s);
    }
};
