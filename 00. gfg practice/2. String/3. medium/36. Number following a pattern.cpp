#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Number following a pattern (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/number-following-a-pattern5456/1
 *
 * Problem Statement:
 *   Given a pattern string S consisting only of characters 'I' (increase) and 'D' (decrease),
 *   construct the smallest numeric string using digits 1-9 (no repetitions) such that the
 *   relative ordering of adjacent digits follows the pattern.
 *   'I' means the next digit must be greater than the current digit, and 'D' means the next
 *   digit must be smaller.
 *
 * Approach (Greedy + Stack):
 *   - The smallest possible number can be built by using the smallest available digits in
 *     increasing order (1, 2, 3, ...).
 *   - While scanning the pattern, push the index+1 onto a stack. Whenever we encounter an
 *     'I' (or after processing the whole pattern), we pop all elements from the stack and
 *     append them to the result. This ensures that sequences of 'D's get reversed, producing
 *     the minimal lexicographic order.
 *   - After the loop, push the last number (pattern length + 1) and flush the stack.
 *
 * Complexity:
 *   - Time:   O(N) where N = S.length()   (single pass + stack operations)
 *   - Space:  O(N) for the auxiliary stack and result string.
 *
 * Example:
 *   Pattern: "IIDDD"
 *   Steps:
 *     i=0 push 1, pattern[0]='I' -> pop -> result "1"
 *     i=1 push 2, pattern[1]='I' -> pop -> result "12"
 *     i=2 push 3, pattern[2]='D' (no pop)
 *     i=3 push 4, pattern[3]='D'
 *     i=4 push 5, pattern[4]='D'
 *   After loop push 6 and pop all -> result "126543"
 */

class Solution {
public:
    string printMinNumberForPattern(string S) {
        int n = S.size();
        vector<int> st;               // auxiliary stack
        string result;
        for (int i = 0; i <= n; ++i) {
            // push current position (i+1) onto stack
            st.push_back(i + 1);
            // if end of pattern or current char is 'I', flush stack
            if (i == n || S[i] == 'I') {
                while (!st.empty()) {
                    result += to_string(st.back());
                    st.pop_back();
                }
            }
        }
        return result;
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    vector<pair<string, string>> tests = {
        {"D", "21"},
        {"IIDDD", "126543"},
        {"IDID", "132546"}
    };
    for (auto &tc : tests) {
        cout << "Pattern: " << tc.first << " -> " << sol.printMinNumberForPattern(tc.first) << " (expected " << tc.second << ")\n";
    }
    return 0;
}
