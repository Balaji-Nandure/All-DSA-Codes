/*
Problem: Generate Grey Code Sequences

Given a number N, your task is to complete the function which generates all n-bit grey code sequences, a grey code sequence is a sequence such that successive patterns in it differ by one bit.

Constraints:
1 <= N <= 16

--------------------------------------------------

Pattern:
Math / Bit Manipulation

--------------------------------------------------

Key Observation:
- A well-known bit manipulation trick generates the `i`-th number in a Grey Code sequence directly: `G(i) = i ^ (i >> 1)`.
- We need to generate this sequence for all numbers from `0` to `2^N - 1`.
- For each generated number, we convert it into its binary string representation of length exactly `N`.

--------------------------------------------------

Approach:
1. Initialize an empty vector of strings `ans`.
2. Calculate the total number of codes, which is `2^N` (can be elegantly written as `1 << N`).
3. Loop `i` from `0` to `(1 << N) - 1`:
    a. Calculate the Grey Code integer value for `i` using `val = i ^ (i >> 1)`.
    b. Construct a binary string `s` of length `N` corresponding to `val`.
    c. We can build this string by checking each bit from `N - 1` down to `0`. If the `j`-th bit of `val` is set, append '1', else append '0'.
    d. Push the generated string `s` into `ans`.
4. Return `ans`.

--------------------------------------------------

Time Complexity: O(N * 2^N) as there are 2^N codes to generate, and creating a string of length N for each code takes O(N) time.
Space Complexity: O(1) auxiliary space (excluding the output array which intrinsically requires O(N * 2^N) to store the result).

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/generate-grey-code-sequences/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generateCode(int N) {
        vector<string> ans;
        int total = 1 << N;
        
        for (int i = 0; i < total; ++i) {
            int val = i ^ (i >> 1);
            string s = "";
            
            // Build the string of length N bit by bit
            for (int j = N - 1; j >= 0; --j) {
                if ((val >> j) & 1) {
                    s += "1";
                } else {
                    s += "0";
                }
            }
            
            ans.push_back(s);
        }
        
        return ans;
    }
};
