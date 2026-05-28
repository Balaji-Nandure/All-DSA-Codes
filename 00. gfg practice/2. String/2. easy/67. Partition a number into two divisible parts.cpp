/*
Problem: Partition a number into two divisible parts

Given a number (as string) and two integers a and b, divide the string in two non-empty parts such that the first part is divisible by a and the second part is divisible by b. In case multiple answers exist, return the string such that the first non-empty part has minimum length.

Constraints:
1 <= |S| <= 10^6
1 <= a, b <= 10^6

--------------------------------------------------

Pattern:
String Processing + Modular Arithmetic + Precomputation

--------------------------------------------------

Key Observation:
- We need to split the string `S` at some index `i` such that the prefix `S[0..i]` is divisible by `a`, and the suffix `S[i+1..n-1]` is divisible by `b`.
- Since the string can be very long (up to 10^6), we cannot convert the substrings to integers directly. We must use modular arithmetic.
- We can precalculate the modulo `b` for all possible suffixes in O(N) time by iterating from right to left and keeping track of the power of 10 modulo `b`.
- Once we have the suffix remainders, we can iterate from left to right, maintaining the prefix modulo `a`.
- At each index `i`, we check if the prefix modulo `a` is 0 and the suffix modulo `b` at `i+1` is 0.
- The first index `i` that satisfies this condition gives the partition with the minimum length for the first part.

--------------------------------------------------

Approach:
1. Let `n` be the length of string `S`.
2. Initialize an array `suf` of size `n` to store the modulo `b` for suffixes.
3. Compute `suf` from right to left:
   - `suf[n-1] = (S[n-1] - '0') % b`
   - Keep a `power` variable initialized to `10 % b`.
   - For `i` from `n-2` down to 1:
       `suf[i] = ((S[i] - '0') * power + suf[i+1]) % b`
       `power = (power * 10) % b`
4. Iterate `i` from 0 to `n-2` to check partitions:
   - Maintain a running `pref` modulo `a`: `pref = (pref * 10 + (S[i] - '0')) % a`
   - If `pref == 0` and `suf[i+1] == 0`:
       Return `S.substr(0, i+1) + " " + S.substr(i+1)`.
5. If the loop completes without returning, return "-1".

--------------------------------------------------

Time Complexity: O(N) as we make two linear passes over the string (one for suffix remainders, one for prefix remainders). String slicing at the end takes O(N) as well.
Space Complexity: O(N) for the `suf` array and the returned string.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/partition-a-number-into-two-divisible-parts3605/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string stringPartition(string S, int a, int b) {
        int n = S.length();
        if (n < 2) return "-1";
        
        vector<int> suf(n, 0);
        long long power = 10 % b;
        
        suf[n-1] = (S[n-1] - '0') % b;
        
        for (int i = n - 2; i >= 1; --i) {
            suf[i] = ((S[i] - '0') * power + suf[i+1]) % b;
            power = (power * 10) % b;
        }
        
        long long pref = 0;
        for (int i = 0; i < n - 1; ++i) {
            pref = (pref * 10 + (S[i] - '0')) % a;
            
            if (pref == 0 && suf[i+1] == 0) {
                return S.substr(0, i + 1) + " " + S.substr(i + 1);
            }
        }
        
        return "-1";
    }
};
