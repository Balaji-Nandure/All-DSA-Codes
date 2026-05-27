/*
Problem: Type it!

Geek is extremely punctual but today even he is not feeling like doing his homework assignment. He must start doing it immediately in order to meet the deadline. For the assignment, Geek needs to type a string s.
To reduce his workload, he has decided to perform one of the following two operations till he gets the string:

1. Append a character at the end of the string.
2. Append the string formed thus far to the end of the string. (This can not be done more than once.)

Help Geek find the minimum operations required to type the given string.

Example 1:
Input:
s = abcabca
Output: 5
Explanation: a -> ab -> abc -> abcabc -> abcabca

Example 2:
Input:
s = abcdefgh
Output: 8
Explanation: a -> ab -> abc -> abcd -> abcde -> abcdef -> abcdefg -> abcdefgh

Constraints:
1 <= N <= 10^3

--------------------------------------------------

Pattern:
String Processing + Greedy

--------------------------------------------------

Key Observation:
- We can use the "double the string" operation AT MOST ONCE.
- If we double a prefix of length `k`, we save exactly `k - 1` manual typing operations.
- To minimize the total operations, we need to maximize our savings. Thus, we want to find the largest prefix of length `k` that can be doubled.
- A prefix of length `k` can be doubled if and only if the substring from index `0` to `k-1` exactly matches the substring from index `k` to `2k-1`.
- Because we want the maximum `k`, we can just iterate `k` from `1` to `N/2` and track the largest `k` that satisfies the condition.
- The total operations will then be `N - k + 1` (where `N` is the total length, and `1` is the cost of the doubling operation).
- If no such prefix exists, we just append all characters one by one, taking `N` operations.

--------------------------------------------------

Approach:
1. Initialize `maxK = 0`.
2. Iterate `k` from 1 up to `N/2` (inclusive).
3. For each `k`, compare the first `k` characters with the next `k` characters.
4. If they match, update `maxK = k`.
5. If a valid `maxK` is found, return `N - maxK + 1`. Otherwise, return `N`.

--------------------------------------------------

Time Complexity: O(N^2) (In the worst case, string comparison takes O(K), leading to O(N^2) overall. This passes within the 10^3 constraint.)
Space Complexity: O(1) Auxiliary Space

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/type-it/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int minOperation(string s) {
        int n = s.length();
        int maxK = 0;
        
        // Find the largest k where the prefix of length k exactly matches
        // the substring of length k immediately following it.
        for (int k = 1; k * 2 <= n; k++) {
            bool match = true;
            for (int i = 0; i < k; i++) {
                if (s[i] != s[k + i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                maxK = k;
            }
        }
        
        // If we found a valid prefix to double
        if (maxK > 0) {
            return n - maxK + 1;
        }
        
        // If no duplication is possible, type all characters one by one
        return n;
    }
};
