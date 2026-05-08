/*
Problem: Sum of Subarrays

GFG:
https://www.geeksforgeeks.org/problems/sum-of-subarrays2229/1

----------------------------------------------------

Example:

arr = [1,2,3]

Subarrays:
[1]       -> 1
[2]       -> 2
[3]       -> 3
[1,2]     -> 3
[2,3]     -> 5
[1,2,3]   -> 6

Total = 20

----------------------------------------------------

Main Observation:

Instead of generating all subarrays,
focus on contribution of each element.

Question:
How many subarrays contain arr[i] ?

----------------------------------------------------

Contribution Formula:

For index i:

Choices for starting point:
(i + 1)

Choices for ending point:
(n - i)

So total subarrays containing arr[i]:

(i + 1) * (n - i)

Contribution:

arr[i] * (i + 1) * (n - i)

----------------------------------------------------

Example:

arr = [1,2,3]

For 2:
index = 1

Start choices:
[1,2], [2]
=> 2 choices

End choices:
[2], [2,3]
=> 2 choices

Total:
2 * 2 = 4 subarrays

Contribution:
2 * 4 = 8

----------------------------------------------------

Pattern:
Contribution Technique

----------------------------------------------------

Approach 1:
Brute Force Generate All Subarrays

----------------------------------------------------

Time Complexity:
O(n^2)

Space Complexity:
O(1)

----------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class BruteForceSolution {
public:

    // TC: O(n^2)
    // SC: O(1)

    long long subarraySum(vector<int>& arr) {

        int n = arr.size();

        long long total = 0;

        // Generate all subarrays
        for(int i = 0; i < n; i++) {

            long long sum = 0;

            for(int j = i; j < n; j++) {

                sum += arr[j];

                total += sum;
            }
        }

        return total;
    }
};

/*
----------------------------------------------------

Approach 2:
Contribution Technique

Every element contributes independently.

Contribution of arr[i]:

arr[i] * (i+1) * (n-i)

----------------------------------------------------

Time Complexity:
O(n)

Space Complexity:
O(1)

----------------------------------------------------
*/

class ContributionSolution {
public:

    // TC: O(n)
    // SC: O(1)

    long long subarraySum(vector<int>& arr) {

        int n = arr.size();

        long long total = 0;

        for(int i = 0; i < n; i++) {

            long long contribution =
            1LL * arr[i] * (i + 1) * (n - i);

            total += contribution;
        }

        return total;
    }
};

/*
----------------------------------------------------

Best / Online Judge Solution

Using Contribution Technique

----------------------------------------------------
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    long long subarraySum(vector<int>& arr) {

        int n = arr.size();

        long long total = 0;

        for(int i = 0; i < n; i++) {

            total +=
            1LL * arr[i] * (i + 1) * (n - i);
        }

        return total;
    }
};

/*
----------------------------------------------------

Dry Run:

arr = [1,2,3]

For 1:
Contribution:
1 * 1 * 3 = 3

For 2:
Contribution:
2 * 2 * 2 = 8

For 3:
Contribution:
3 * 3 * 1 = 9

Total:
3 + 8 + 9 = 20

----------------------------------------------------

Why Formula Works?

For every element:
- choose any start before/equal i
- choose any end after/equal i

So:
start choices = i+1
end choices = n-i

Total subarrays containing arr[i]:

(i+1)*(n-i)

----------------------------------------------------

Common Mistakes:

1. Forgetting contribution logic
2. Integer overflow
3. Using int instead of long long
4. Confusing:
(n-i-1)
with:
(n-i)

----------------------------------------------------

Reusable Pattern:

Whenever question asks:
- Sum over ALL subarrays
- Total contribution

Think:
Contribution Technique

Element Contribution:
value × frequency of appearance

----------------------------------------------------
*/


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    SUM OVER ALL SUBARRAYS

Think immediately:
    CONTRIBUTION TECHNIQUE

-----------------------------------------------------

KEY OBSERVATIONS:

1. Each element contributes independently
2. Find frequency of each element in all subarrays
3. Multiply value by frequency and sum

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting contribution logic
2. Integer overflow (use long long)
3. Using int instead of long long
4. Confusing (n-i-1) with (n-i)

-----------------------------------------------------

SIMILAR PROBLEMS

- Sum of all subarrays
- Subarray sum problems
- Contribution technique applications

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Sum over all subarrays
- Total contribution needed

Think:
Contribution Technique

Formula:
Element Contribution = value × frequency of appearance

For subarrays:
frequency = (i+1) × (n-i)

-----------------------------------------------------
*/
