/*
    Problem Name: Count subsequences of type a^i, b^j, c^k
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string S, the task is to count number of subsequences of the form a^i b^j c^k, where i >= 1, j >=1 and k >= 1.
    Note: 
    1. Two subsequences are considered different if the set of array indexes picked for the 2 subsequences are different.
    2. For large test cases, the output value will be too large, return the answer MODULO 10^9+7.

    Expected Complexities:
    Time Complexity: O(N), where N is the length of the string S.
    Space Complexity: O(1).

    Love Babbar Style Approach:
    1. Initialization: We use three variables `a`, `b`, and `c` initialized to 0. 
       - `a` represents the count of subsequences of the form `a^i`.
       - `b` represents the count of subsequences of the form `a^i b^j`.
       - `c` represents the count of subsequences of the form `a^i b^j c^k`.
    2. Traversal: Iterate through each character `ch` of the string `S`.
       - If `ch == 'a'`: The new 'a' can either be appended to existing `a^i` subsequences (giving `a` new ones), act as a single 'a' starting a new subsequence (`1`), or we can ignore it (keeping the existing `a` subsequences). So, new `a = (2 * a + 1) % MOD`.
       - If `ch == 'b'`: The new 'b' can be appended to existing `a^i b^j` subsequences (`b`), appended to existing `a^i` subsequences to form new `a^i b^j` (`a`), or we ignore it. So, new `b = (2 * b + a) % MOD`.
       - If `ch == 'c'`: The new 'c' can be appended to existing `a^i b^j c^k` subsequences (`c`), appended to existing `a^i b^j` subsequences to form new `a^i b^j c^k` (`b`), or we ignore it. So, new `c = (2 * c + b) % MOD`.
    3. Result: Return the final value of `c`, which holds the count of valid `a^i b^j c^k` subsequences.

    Dry Run:
    Input: S = "abbc"
    Initialization: a = 0, b = 0, c = 0, MOD = 1e9+7
    Iteration:
    - ch = 'a': a = 2 * 0 + 1 = 1.
    - ch = 'b': b = 2 * 0 + 1 = 1.
    - ch = 'b': b = 2 * 1 + 1 = 3.
    - ch = 'c': c = 2 * 0 + 3 = 3.
    End of loop.
    Result: Return c = 3.
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
  public:
    int fun(string &s) {
        long long a = 0;
        long long b = 0;
        long long c = 0;
        long long MOD = 1e9 + 7;
        
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == 'a') {
                a = (2 * a + 1) % MOD;
            } else if (s[i] == 'b') {
                b = (2 * b + a) % MOD;
            } else if (s[i] == 'c') {
                c = (2 * c + b) % MOD;
            }
        }
        
        return c;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            Solution ob;
            cout << ob.fun(s) << "\n";
        }
    }
    return 0;
}
