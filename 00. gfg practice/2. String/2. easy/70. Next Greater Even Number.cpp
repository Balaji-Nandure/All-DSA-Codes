/*
Problem: Next Greater Even Number

Given a positive integer x (as a string). The task is to find the smallest even number e such that e > x and all digits in x and e are the same.
Note: If no possible number exists then return -1.

Constraints:
1 <= x.size() <= 10

--------------------------------------------------

Pattern:
Math / Combinatorics (Next Permutation)

--------------------------------------------------

Key Observation:
- We are looking for a rearrangement of the digits of `x` that forms a number strictly greater than `x`.
- Among all such rearrangements, we want the smallest one that is even.
- Since the string length is at most 10, the maximum number of permutations is 10! (3,628,800), and we only explore permutations lexicographically greater than the initial state.
- C++ provides `next_permutation`, which elegantly generates the next lexicographically greater permutation in-place, handling duplicate digits automatically.
- By repeatedly applying `next_permutation`, the first permutation we encounter that ends with an even digit is guaranteed to be the smallest greater even number.

--------------------------------------------------

Approach:
1. Use a `while` loop with `next_permutation(x.begin(), x.end())`.
2. This will naturally generate permutations of `x` in strictly increasing order.
3. For each generated permutation, check if the last character is an even digit (i.e. divisible by 2).
4. If it is, convert the string to a `long long` using `stoll()` and return it.
5. If the loop exhausts all permutations without finding a match, it means no greater even number can be formed. Return `-1`.

--------------------------------------------------

Time Complexity: O(N!) in the absolute worst case (which is bounded by 10! ~ 3.6 x 10^6 operations, running in just a few milliseconds in C++).
Space Complexity: O(1) as permutations are evaluated in-place.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/next-greater-even-number/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long getNextEven(string x) {
        // next_permutation modifies the string in-place to the next lexicographically greater permutation
        while (next_permutation(x.begin(), x.end())) {
            // Check if the number is even (last digit is divisible by 2)
            if ((x.back() - '0') % 2 == 0) {
                return stoll(x);
            }
        }
        
        // If we exhaust all permutations and find no even number
        return -1;
    }
};
