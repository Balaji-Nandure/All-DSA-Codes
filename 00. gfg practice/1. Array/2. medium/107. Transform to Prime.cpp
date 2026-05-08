/*
Problem: Transform to Prime

GFG:
https://www.geeksforgeeks.org/problems/transform-to-prime3356/1

----------------------------------------------------

Example:

arr = [2,4,6,8,12]

Sum = 32

Next prime after 32:
37

Needed number:
37 - 32 = 5

Answer = 5

----------------------------------------------------

Intuition:

1. Find total array sum
2. Check if sum is prime
3. If not:
   keep increasing number
   until we find a prime

Answer:
prime - sum

----------------------------------------------------

Pattern:
Prime Checking

----------------------------------------------------

/*
----------------------------------------------------

Approach 3:
Using Sieve

Since:
sum <= 10^6

We can precompute primes.

----------------------------------------------------

Time Complexity:
O(MAX log log MAX)

Space Complexity:
O(MAX)

----------------------------------------------------
*/

class SieveSolution {
public:

    // TC: O(MAX log log MAX)
    // SC: O(MAX)

    int minNumber(int arr[], int N) {

        int sum = 0;

        for(int i = 0; i < N; i++) {

            sum += arr[i];
        }

        int LIMIT = 2000000;

        vector<bool> prime(LIMIT + 1, true);

        prime[0] = false;
        prime[1] = false;

        // Build sieve
        for(int i = 2; i * i <= LIMIT; i++) {

            if(prime[i]) {

                for(int j = i * i; j <= LIMIT; j += i) {

                    prime[j] = false;
                }
            }
        }

        int candidate = sum;

        while(!prime[candidate]) {

            candidate++;
        }

        return candidate - sum;
    }
};

/*
----------------------------------------------------

Best / Online Judge Solution

Using Optimized Prime Checking

Reason:
No need to build huge sieve.
Next prime distance is usually small.

----------------------------------------------------
*/

class Solution {
public:

    bool isPrime(int n) {

        if(n < 2)
            return false;

        if(n == 2)
            return true;

        if(n % 2 == 0)
            return false;

        for(int i = 3; i * i <= n; i += 2) {

            if(n % i == 0)
                return false;
        }

        return true;
    }

    // TC: Very Fast Practically
    // SC: O(1)

    int minNumber(int arr[], int N) {

        int sum = 0;

        for(int i = 0; i < N; i++) {

            sum += arr[i];
        }

        int candidate = sum;

        // Find nearest prime >= sum
        while(!isPrime(candidate)) {

            candidate++;
        }

        return candidate - sum;
    }
};

/*
----------------------------------------------------

Dry Run:

arr = [2,4,6,8,12]

sum = 32

32 not prime
33 not prime
34 not prime
35 not prime
36 not prime
37 prime

Answer:
37 - 32 = 5

----------------------------------------------------

Common Mistakes:

1. Forgetting sum itself may already be prime
2. Treating 1 as prime
3. Checking all divisors till n
4. Forgetting even optimization

----------------------------------------------------

Why check till sqrt(n) ?

If n has divisor greater than sqrt(n),
another divisor must exist smaller than sqrt(n).

So checking beyond sqrt is unnecessary.

----------------------------------------------------

Reusable Pattern:

Whenever:
- Repeated prime checking
- Constraints around 10^6

Think:
1. sqrt(n) prime check
2. Sieve (if many queries)

----------------------------------------------------
*/


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    FINDING NEAREST PRIME

Think immediately:
    OPTIMIZED PRIME CHECKING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Next prime distance is usually small
2. No need for large sieve for single query
3. Optimized prime check is sufficient

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting sum may already be prime
2. Treating 1 as prime
3. Not optimizing prime check
4. Checking divisors beyond sqrt(n)

-----------------------------------------------------

SIMILAR PROBLEMS

- Nearest prime number
- Prime checking problems
- Number theory applications

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Need to find nearest prime
- Single prime query

Think:
Optimized Prime Check

Optimizations:
- Handle 2 separately
- Skip even numbers
- Check till sqrt(n)

-----------------------------------------------------
*/
