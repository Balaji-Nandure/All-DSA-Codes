/*
Problem: Arya's Long String

Arya has a string, s, of uppercase English letters. She writes down the string s on a paper k times. She wants to calculate the occurence of a specific letter c in the first n characters of the final string.

Constraints:
1 <= |s| <= 10^5
1 <= k <= 10^5
1 <= n <= |s|*k

--------------------------------------------------

Pattern:
Math / Modular Arithmetic

--------------------------------------------------

Key Observation:
- The string `s` is repeated `k` times. We need to find the number of times `c` appears in the first `n` characters of this repeated string.
- Let `L` be the length of string `s`.
- The first `n` characters consist of `n / L` full repetitions of the string `s`, followed by a remainder of `n % L` characters from the beginning of `s`.
- We can count the occurrences of `c` in a single string `s`, and multiply it by `n / L`.
- Then, we add the occurrences of `c` in the first `n % L` characters of `s`.

--------------------------------------------------

Approach:
1. Find the length of the string `s`, let it be `L`.
2. Initialize two counters: `count_in_s` for the number of times `c` appears in the entire string `s`, and `count_in_rem` for the number of times `c` appears in the first `n % L` characters of `s`.
3. Iterate through the string `s` from `i = 0` to `L - 1`:
    a. If `s[i] == c`, increment `count_in_s`.
    b. Additionally, if `i < n % L`, increment `count_in_rem`.
4. The total occurrences of `c` will be `(n / L) * count_in_s + count_in_rem`.
5. Return the total occurrences.

--------------------------------------------------

Time Complexity: O(|s|) as we only need to iterate through the string `s` once.
Space Complexity: O(1) since we only use a few variables for counting.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/arya-s-long-string5840/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int fun(string s, int k, int n, char c) {
        int len = s.length();
        int cnt = 0;
        int remCnt = 0;
        int rem = n % len;
        
        for (int i = 0; i < len; ++i) {
            if (s[i] == c) {
                cnt++;
                if (i < rem) {
                    remCnt++;
                }
            }
        }
        
        return cnt * (n / len) + remCnt;
    }
};
