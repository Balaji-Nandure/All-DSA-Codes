/*
Problem: Sum of 2 Primes

GFG: https://www.geeksforgeeks.org/problems/sum-of-prime4751/1

Description:
Given a number n, determine whether it can be expressed as a + b, where both a and b are prime numbers. If such a pair exists, return the pair (a, b) such that a ≤ b. If multiple pairs are possible, return the pair with the smallest value of a. If no such pair exists, return [-1, -1].

Examples:

Input: n = 10
Output: [3 7]
Explanation: There are two possibilities 3, 7 & 5, 5 are both prime & their sum is 10, but we'll pick 3, 7 as 3 < 5.

Input: n = 3
Output: [-1 -1]
Explanation: There are no solutions to the number 3.

Constraints:
2 ≤ n ≤ 10^6

Approach (Sieve of Eratosthenes):
This is a prime number problem that requires efficient prime checking.

Key insight:
- Need to find two primes whose sum equals n
- For each a, check if both a and (n-a) are prime
- Use Sieve to precompute all primes up to n for O(1) prime checking
- Only need to check till n/2 to avoid duplicate pairs

Algorithm:
1. Build Sieve of Eratosthenes to mark all primes up to n
2. For a from 2 to n/2:
   - Check if a is prime
   - Check if (n-a) is prime
   - If both prime, return {a, n-a}
3. If no pair found, return {-1, -1}

Time Complexity: O(n log log n)
Space Complexity: O(n)

Pattern: Prime Numbers + Sieve of Eratosthenes
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
SIEVE OF ERATOSTHENES
=====================================================

TC: O(n log log n)
SC: O(n)

🔥 SIEVE APPROACH
- Precompute all primes up to n
- O(1) prime checking after preprocessing
- Optimal for multiple prime queries

🧠 KEY INSIGHT:
Instead of checking primality repeatedly,
precompute all primes using Sieve.

Sieve Algorithm:
- Initially mark all numbers as prime
- For each prime p, mark multiples as non-prime
- Start from p*p (smaller multiples already handled)

🎯 ALGORITHM:
1. Build sieve up to n
2. Check a from 2 to n/2
3. Return first valid prime pair

⚡ OPTIMIZATION:
Only check till n/2 because:
- a <= b requirement
- After n/2, pairs start repeating
- Example: 3+7 and 7+3 are same pair
*/

class Solution {
public:

    // TC: O(n log log n)
    // SC: O(n)

    vector<int> getPrimes(int n) {

        vector<bool> prime(n + 1, true);

        prime[0] = false;
        prime[1] = false;

        // Build sieve
        for(int i = 2; i * i <= n; i++) {

            if(prime[i]) {

                for(int j = i * i; j <= n; j += i) {

                    prime[j] = false;
                }
            }
        }

        // Find smallest valid pair
        for(int a = 2; a <= n / 2; a++) {

            int b = n - a;

            if(prime[a] && prime[b]) {

                return {a, b};
            }
        }

        return {-1, -1};
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    MULTIPLE PRIME CHECKS

Think immediately:
    SIEVE OF ERATOSTHENES

-----------------------------------------------------

KEY OBSERVATIONS:

1. Need efficient prime checking for multiple queries
2. Sieve provides O(1) prime lookup after O(n) preprocessing
3. Only need to check till n/2 to avoid duplicates

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting 0 and 1 are NOT prime
2. Checking till n unnecessarily (use n/2)
3. Wrong sieve implementation (start from i*i)
4. Not handling edge cases properly

-----------------------------------------------------

SIMILAR PROBLEMS

- Goldbach's Conjecture
- Prime Number problems
- Sieve applications
- Prime pair finding

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Multiple prime checks
- Range up to 10^6 or more

Think:
Sieve of Eratosthenes

Steps:
1. Build sieve
2. O(1) prime lookup
3. Solve main problem

-----------------------------------------------------
*/
