/*
Problem: Prime String

Provided a String of length N, your task is to find out whether or not the given string is a prime string. A prime string is a string in which the sum of the ASCII value of all the characters is prime.

Constraints:
1 <= |S| <= 10^6

--------------------------------------------------

Pattern:
Math / Prime Checking

--------------------------------------------------

Key Observation:
- We need to calculate the sum of ASCII values of all characters in the string.
- The maximum possible sum is 10^6 * 122 (ASCII of 'z') = ~1.22 * 10^8, which comfortably fits in a standard 32-bit integer.
- Once we have the sum, we can use a standard O(sqrt(sum)) primality test to check if the sum is a prime number.

--------------------------------------------------

Approach:
1. Initialize a variable `sum` to 0.
2. Iterate through each character `c` in the string `s` and add its ASCII value to `sum`.
3. Check if `sum` is prime:
    a. If `sum <= 1`, return false.
    b. If `sum == 2` or `sum == 3`, return true.
    c. If `sum` is divisible by 2 or 3, return false.
    d. Iterate `i` from 5 up to `sqrt(sum)` in steps of 6 (checking `i` and `i + 2`).
    e. If `sum` is divisible by any, return false.
    f. Otherwise, return true.

--------------------------------------------------

Time Complexity: O(|S| + sqrt(Sum)), which is effectively O(|S|) because |S| dominates.
Space Complexity: O(1) as we only use a few integer variables.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/prime-string/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isPrimeString(int N, string S) {
        long long sum = 0;
        for (char c : S) {
            sum += c;
        }
        
        if (sum <= 1) return false;
        if (sum == 2 || sum == 3) return true;
        if (sum % 2 == 0 || sum % 3 == 0) return false;
        
        for (int i = 5; i * i <= sum; i += 6) {
            if (sum % i == 0 || sum % (i + 2) == 0) {
                return false;
            }
        }
        
        return true;
    }
};
