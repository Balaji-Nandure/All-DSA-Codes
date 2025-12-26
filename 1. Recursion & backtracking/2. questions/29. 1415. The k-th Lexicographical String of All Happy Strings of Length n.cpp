/*
 * Problem: The k-th Lexicographical String of All Happy Strings of Length n
 * 
 * LeetCode 1415: The k-th Lexicographical String of All Happy Strings of Length n
 * 
 * A happy string is a string that:
 * - Consists only of the letters 'a', 'b', and 'c'
 * - Does not contain any of the substrings "aaa", "bbb", or "ccc"
 * 
 * Given two integers n and k, return the k-th lexicographically smallest happy string
 * of length n. If there are fewer than k happy strings of length n, return an empty string "".
 * 
 * Example 1:
 * Input: n = 1, k = 3
 * Output: "c"
 * Explanation: The list ["a", "b", "c"] contains 3 happy strings of length 1.
 *              The 3rd string is "c".
 * 
 * Example 2:
 * Input: n = 1, k = 4
 * Output: ""
 * Explanation: There are only 3 happy strings of length 1.
 * 
 * Example 3:
 * Input: n = 3, k = 9
 * Output: "cab"
 * Explanation: There are 12 happy strings of length 3:
 *              ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]
 *              The 9th string is "cab".
 * 
 * Constraints:
 * - 1 <= n <= 10
 * - 1 <= k <= 100
 * 
 * Approach:
 * - Use backtracking to generate happy strings in lexicographical order
 * - Keep a counter to track which string we're on
 * - When we reach the k-th string, return it immediately
 * - Prune branches that can't lead to valid happy strings
 * - Try characters in order: 'a', 'b', 'c' to maintain lexicographical order
 * 
 * Time: O(3^n) worst case, but pruned significantly
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    /*
        TRICK:
        - Happy strings are formed using characters {a, b, c}
        - Adjacent characters must be different
        - Total strings are small, so we can generate them in lexicographical order
        - Instead of storing all strings, stop as soon as we reach the k-th one

        APPROACH:
        - Use backtracking to build the string character by character
        - Always try characters in lexicographical order: a -> b -> c
        - Skip a character if it is same as the previous character
        - Maintain a local counter passed by reference
        - When counter == k, store answer and stop recursion
    */

    void backtrack(
        int n,
        int k,
        string &current,
        int &count,
        string &result
    ) {
        // If we already found the k-th string, stop further recursion
        if (!result.empty()) {
            return;
        }

        // If a valid happy string of length n is formed
        if (current.size() == n) {
            count++;

            // If this is the k-th string, store result
            if (count == k) {
                result = current;
            }
            return;
        }

        // Try characters in lexicographical order
        for (char ch = 'a'; ch <= 'c'; ch++) {

            // Adjacent characters must not be the same
            if (!current.empty() && current.back() == ch) {
                continue;
            }

            // Choose
            current.push_back(ch);

            // Explore
            backtrack(n, k, current, count, result);

            // Un-choose (backtrack)
            current.pop_back();
        }
    }

    string getHappyString(int n, int k) {
        string current = "";
        string result = "";
        int count = 0;

        backtrack(n, k, current, count, result);

        return result;
    }
};

int main() {
    Solution sol;
    int n, k;
    cin >> n >> k;
    cout << sol.getHappyString(n, k) << endl;
    return 0;
}