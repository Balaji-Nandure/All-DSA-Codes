/*
    Problem Name: Decode the String
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 394

    Problem Statement:
    Given an encoded string `s`, decode it by expanding the pattern `k[substring]`,
    where the substring inside the brackets is repeated `k` times.
    `k` is guaranteed to be a positive integer, and the string contains only lowercase
    English alphabets, digits, and square brackets `[` and `]`.
    Return the final decoded string.

    Note: The length of the output string will never exceed 10^5.

    Examples:
    Input: s = "3[b2[ca]]"
    Output: "bcacabcacabcaca"
    Explanation:
    - Inner substring "2[ca]" expands to "caca".
    - String becomes "3[bcaca]".
    - "3[bcaca]" expands to "bcacabcacabcaca".

    Input: s = "3[ab]"
    Output: "ababab"
    Explanation: "ab" repeated 3 times gives "ababab".

    Input: s = "2[abc]3[cd]ef"
    Output: "abcabccdcdcdef"

    Constraints:
    1 <= |s| <= 10^5
    1 <= k <= 100

    Expected Complexities:
    Time Complexity: O(Length of output string)
    Space Complexity: O(Length of output string) (stack space)

    Approach 1: Two Stacks (Count Stack & String Stack) (Optimal O(Output Length) Time - Striver & Love Babbar)
    Approach 2: Recursive DFS (System Call Stack) (Optimal O(Output Length) Time)

    INTUITION & STRATEGY:
    1. Nested brackets indicate nested subproblems, which naturally suggest using a Stack.
    2. We maintain:
       - `countStack`: stores the multiplier `k`.
       - `stringStack`: stores the string accumulated before entering the current bracket `[`.
       - `currentStr`: the current substring being formed.
       - `k`: the running number being parsed (handles multi-digit integers like "10[a]").
    3. Traversal rules for character `ch`:
       - If `isdigit(ch)`: update running multiplier: `k = k * 10 + (ch - '0')`.
       - If `ch == '['`:
         * Push `k` onto `countStack`.
         * Push `currentStr` onto `stringStack`.
         * Reset `k = 0` and `currentStr = ""`.
       - If `ch == ']'`:
         * Pop the count `repeatCount = countStack.top()`.
         * Pop the prefix `prevStr = stringStack.top()`.
         * Repeat `currentStr` `repeatCount` times.
         * New `currentStr = prevStr + repeated_string`.
       - If `isalpha(ch)`:
         * Append directly: `currentStr += ch`.
    4. At the end of the string, `currentStr` contains the complete decoded result.

    DRY RUN:
    Example: s = "3[b2[ca]]"
    - '3': k = 3
    - '[': countStack = [3], stringStack = [""], k = 0, currentStr = ""
    - 'b': currentStr = "b"
    - '2': k = 2
    - '[': countStack = [3, 2], stringStack = ["", "b"], k = 0, currentStr = ""
    - 'c': currentStr = "c"
    - 'a': currentStr = "ca"
    - ']': count = 2, prev = "b" -> repeated = "caca" -> currentStr = "b" + "caca" = "bcaca"
    - ']': count = 3, prev = "" -> repeated = "bcacabcacabcaca" -> currentStr = "" + "bcacabcacabcaca"
    - Result: "bcacabcacabcaca".
*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// ============================================================================
// Approach: Two Stacks (Optimal O(Output Length) Time, O(Output Length) Space)
// ============================================================================
// class SolutionTwoStacks {
// public:
//     string decodedString(string &s) {
//         stack<int> countStack;
//         stack<string> stringStack;

//         string currentStr = "";
//         int k = 0;

//         for (char ch : s) {
//             // Case 1: Digit (build multi-digit k)
//             if (isdigit(ch)) {
//                 k = k * 10 + (ch - '0');
//             }
//             // Case 2: Opening bracket '[' (push current context and reset)
//             else if (ch == '[') {
//                 countStack.push(k);
//                 stringStack.push(currentStr);

//                 k = 0;
//                 currentStr = "";
//             }
//             // Case 3: Closing bracket ']' (pop context, repeat currentStr, and prepend prevStr)
//             else if (ch == ']') {
//                 int repeatCount = countStack.top();
//                 countStack.pop();

//                 string prevStr = stringStack.top();
//                 stringStack.pop();

//                 string expanded = "";
//                 while (repeatCount--) {
//                     expanded += currentStr;
//                 }

//                 currentStr = prevStr + expanded;
//             }
//             // Case 4: Alphabet character (append to currentStr)
//             else {
//                 currentStr += ch;
//             }
//         }

//         return currentStr;
//     }
// };

// ============================================================================
// Approach 2: Recursive DFS (Optimal O(Output Length) Time, Call Stack Space)
// ============================================================================
class SolutionRecursion {
private:
    string decodeHelper(const string &s, int &i) {
        string result = "";
        int k = 0;

        while (i < s.length()) {
            char ch = s[i];

            // Case 1: Digit (accumulate multiplier k)
            if (isdigit(ch)) {
                k = k * 10 + (ch - '0');
                i++;
            }
            // Case 2: Opening bracket '[' (recurse for inner substring)
            else if (ch == '[') {
                i++; // Skip '['
                string innerDecoded = decodeHelper(s, i);

                // Repeat the inner substring k times
                while (k > 0) {
                    result += innerDecoded;
                    k--;
                }
            }
            // Case 3: Closing bracket ']' (finish current recursive level)
            else if (ch == ']') {
                i++; // Skip ']'
                return result;
            }
            // Case 4: Alphabet character
            else {
                result += ch;
                i++;
            }
        }

        return result;
    }

public:
    string decodedString(string &s) {
        int i = 0;
        return decodeHelper(s, i);
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    string decodedString(string &s) {
        SolutionTwoStacks solver;
        return solver.decodedString(s);
    }

    // Overload for by-value parameter
    string decodedString(string s) {
        return decodedString(s);
    }

    // LeetCode alias
    string decodeString(string s) {
        return decodedString(s);
    }
};
