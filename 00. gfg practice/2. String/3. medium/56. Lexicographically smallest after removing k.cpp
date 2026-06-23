/*
    Problem Name: Lexicographically smallest after removing k
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string s consisting of n lowercase characters. Return the lexicographically smallest string after removing exactly k characters from the string. But you have to correct the value of k, i.e., if the length of the string is a power of 2, reduce k by half, else multiply k by 2. You can remove any k characters.
    Note: If it is not possible to remove k (the value of k after correction) characters or if the resulting string is empty return "-1".

    Expected Complexities:
    Time Complexity: O(n), where n is the length of the string.
    Space Complexity: O(n) for the stack/string used to build the result.

    Love Babbar Style Approach:
    1. Correcting `k`: First, we determine if the length of the string `n` is a power of 2 using bitwise operations (`(n & (n - 1)) == 0`). If it is, we divide `k` by 2; otherwise, we multiply `k` by 2.
    2. Edge Cases: If the corrected `k` is greater than or equal to `n`, it means we must remove all characters or more than what's available. We simply return `"-1"`.
    3. Monotonic Stack: We iterate through the string and use a stack (or a string behaving as a stack) to build our answer. For each character `c`:
       - If the stack is not empty, the top of the stack is greater than `c`, and we still have characters to remove (`k > 0`), we pop the top element and decrement `k`. This ensures that we greedily place smaller characters earlier, creating a lexicographically smaller string.
       - Then, we push `c` to the stack.
    4. Post-processing: After checking all characters, if we still need to remove more characters (`k > 0`), we pop them from the end of our stack. Since the stack is monotonically non-decreasing at this point, removing the largest characters from the end is the optimal choice.
    5. Result: Return the final string built from the stack.

    Dry Run:
    Input: s = "fooland", k = 2
    - n = 7 (not a power of 2), so corrected k = 2 * 2 = 4.
    - Stack processing:
      - 'f': stack = "f", k=4
      - 'o': stack = "fo", k=4
      - 'o': stack = "foo", k=4
      - 'l': 'l' < 'o', pop 'o', k=3. 'l' < 'o', pop 'o', k=2. stack = "fl", k=2
      - 'a': 'a' < 'l', pop 'l', k=1. 'a' < 'f', pop 'f', k=0. stack = "a", k=0
      - 'n': stack = "an", k=0
      - 'd': stack = "and", k=0
    - Remaining k is 0, so no elements to pop from the end.
    Result: "and"
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
  private:
    bool isPowerOfTwo(int n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

  public:
    string lexicographicallySmallest(string s, int k) {
        int n = s.length();
        
        // Correcting the value of k
        if (isPowerOfTwo(n)) {
            k = k / 2;
        } else {
            k = k * 2;
        }
        
        // Edge cases
        if (k >= n) {
            return "-1";
        }
        
        // Monotonic stack using string
        string st = "";
        for (char c : s) {
            while (!st.empty() && st.back() > c && k > 0) {
                st.pop_back();
                k--;
            }
            st.push_back(c);
        }
        
        // If there are still characters to remove
        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }
        
        return st;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            int k;
            cin >> s >> k;
            Solution ob;
            cout << ob.lexicographicallySmallest(s, k) << "\n";
        }
    }
    return 0;
}
