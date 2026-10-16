// Problem: Factorial of a Large Number
// Link (Article): https://www.geeksforgeeks.org/dsa/factorial-large-number/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/factorials-of-large-numbers2508/1
// Difficulty: Medium
// Topic: Array, Big Integer Arithmetic, Mathematics

/*
Problem Statement:
Given an integer `N`, calculate the factorial `N! = 1 * 2 * 3 * ... * N`.
Since the result can be extraordinarily large (e.g., 1000! has 2568 decimal digits), 
it cannot fit in standard 64-bit primitive data types (`long long` overflows around 20!).
Return the digits of the factorial in order as a vector of integers.

Example 1:
Input: N = 5
Output: [1, 2, 0]
Explanation: 5! = 120.

Example 2:
Input: N = 10
Output: [3, 6, 2, 8, 8, 0, 0]
Explanation: 10! = 3628800.

Constraints:
- 1 <= N <= 1000
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - Previous problems processed numbers within standard 32-bit or 64-bit primitive types.
// - In Problem 22:
//   * The value exceeds hardware registers (Arbitrary Precision Arithmetic).
//   * We use the ARRAY ITSELF AS A BIG-INTEGER NUMERICAL REGISTER, where each index
//     represents a single decimal digit (base 10).

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Elementary School Multiplication on an Array:
//   1. Represent the number 1 as `digits = [1]`, with index 0 storing the Least Significant Digit (LSD).
//   2. For each multiplier `x` from 2 to N:
//      - Initialize `carry = 0`.
//      - Traverse all existing digits in `digits`:
//        * `prod = digits[i] * x + carry`
//        * `digits[i] = prod % 10`
//        * `carry = prod / 10`
//      - While `carry > 0`:
//        * Append `carry % 10` to `digits`.
//        * `carry /= 10`.
//   3. Since digits are stored in reverse order (LSD at index 0), reverse the vector at the end!
//   - Complexity: O(N * digits) ≈ O(N^2) time, O(digits) space.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> factorial(int N) {
        // digits[0] stores the least significant digit (LSD)
        vector<int> digits;
        digits.push_back(1); // 0! = 1 and 1! = 1

        for (int x = 2; x <= N; x++) {
            int carry = 0;

            // Multiply each digit by x and propagate carry
            for (int i = 0; i < (int)digits.size(); i++) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Standard grade-school multiplication digit-by-digit:
                // Multiply current digit by x, add the incoming carry,
                // store remainder modulo 10 in the slot, and send the quotient forward as carry!
                long long prod = 1LL * digits[i] * x + carry;
                digits[i] = prod % 10;
                carry = prod / 10;
            }

            // Append remaining carry digits to the most significant end
            while (carry > 0) {
                digits.push_back(carry % 10);
                carry /= 10;
            }
        }

        // Reverse to return digits from Most Significant Digit (MSD) to Least Significant Digit (LSD)
        reverse(digits.begin(), digits.end());
        return digits;
    }
};

/*
Time Complexity: O(N * D)
- N = input number (up to 1000).
- D = number of digits in N! (for N = 1000, D ≈ 2568 by Stirling's approximation).
- Inner loop runs D times for each of the N multiplications: O(1000 * 2568) ≈ 2.5 * 10^6 operations.
- Runs in under 10 milliseconds!

Space Complexity: O(D) Auxiliary Space
- Vector stores exactly D digits (at most ~2600 integers for N = 1000).

Key Insights:
1. Least Significant Digit at Index 0:
   - Storing the LSD at `digits[0]` allows us to push new carry digits to `digits.back()` in O(1) time.
   - Reversing once at the very end is significantly faster than inserting at `digits[0]` (which is O(D) per shift).
*/
