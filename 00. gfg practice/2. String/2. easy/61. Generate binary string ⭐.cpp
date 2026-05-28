/*
Problem: Generate binary string

Given a string containing of 0, 1 and ? - a wildcard character, generate all distinct binary strings that can be formed by replacing each wildcard character by either 0 or 1.
Note : Strings should be printed in lexicographically increasing order.

Constraints:
1 <= length of string <= 30
Note: Number of '?' in any string does not exceed 15.

--------------------------------------------------

Pattern:
Recursion / Backtracking

--------------------------------------------------

Key Observation:
- At every wildcard character '?', we have two choices: replace it with '0' or replace it with '1'.
- To maintain a lexicographically increasing order, we should always explore the '0' choice before the '1' choice.
- Since the number of wildcards is at most 15, the maximum number of generated strings is 2^15 = 32768, which easily fits within time and space limits.

--------------------------------------------------

Approach:
1. Create a helper recursive function `solve(string& s, int idx, vector<string>& ans)`.
2. Base case: If `idx` reaches the length of the string, it means we have processed all characters. We push the current string `s` into the `ans` array and return.
3. If the character at `idx` is '?', we have two possibilities:
    a. Change it to '0' and call `solve(s, idx + 1, ans)`.
    b. Change it to '1' and call `solve(s, idx + 1, ans)`.
    c. Backtrack by changing it back to '?' so we don't affect other recursive calls.
4. If the character is not '?', we simply move to the next character: `solve(s, idx + 1, ans)`.
5. Return the `ans` array from the main function.

--------------------------------------------------

Time Complexity: O(2^k * N) where k is the number of wildcards and N is the string length. There are 2^k leaf nodes in the recursion tree, and storing a string of length N takes O(N) time.
Space Complexity: O(2^k * N) to store the resulting strings, plus O(N) for the recursive call stack space.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/generate-binary-string3642/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    void solve(string& s, int idx, vector<string>& ans) {
        if (idx == s.length()) {
            ans.push_back(s);
            return;
        }
        
        if (s[idx] == '?') {
            s[idx] = '0';
            solve(s, idx + 1, ans);
            
            s[idx] = '1';
            solve(s, idx + 1, ans);
            
            s[idx] = '?'; // backtrack
        } else {
            solve(s, idx + 1, ans);
        }
    }

public:
    vector<string> generate_binary_string(string s) {
        vector<string> ans;
        solve(s, 0, ans);
        return ans;
    }
};
