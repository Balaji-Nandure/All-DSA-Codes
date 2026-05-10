/*
Problem: Not a Subset Sum

GFG: https://www.geeksforgeeks.org/problems/smallest-positive-number-and-subset3631/1

Description:
Given a array arr[] of positive integers, find the smallest positive integer such that it cannot be represented as the sum of elements of any subset of the given array set.

Examples:

Input: arr[] = [3, 1, 2]
Output: 7
Explanation: 7 is the smallest positive number for which no subset is there with sum 7.

Input: arr[] = [3, 10, 9, 6, 20, 28]
Output: 1
Explanation: 1 is the smallest positive number for which no subset is there with sum 1.

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^3

Approach (Greedy Range Expansion):
This is a classic greedy problem where we maintain a reachable range of constructible sums.

Key insight:
- Maintain 'reachable' as the smallest value that cannot be constructed yet
- Initially reachable = 1 (only sum 0 is possible)
- For each sorted number:
  - If number > reachable, gap appears at reachable
  - Else, extend reachable range: reachable += number

Algorithm:
1. Sort array in ascending order
2. Initialize reachable = 1
3. For each number in sorted array:
   - If number > reachable: return reachable (gap found)
   - Else: reachable += number (extend range)
4. Return reachable (all sums up to reachable-1 possible)

Time Complexity: O(n log n)
Space Complexity: O(1)

Pattern: Greedy + Range Extension
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GREEDY RANGE EXPANSION
=====================================================

TC: O(n log n)
SC: O(1)

🔥 GREEDY APPROACH
- Sort array to process smallest numbers first
- Maintain reachable range of constructible sums
- Extend range when possible, detect gaps

🧠 KEY INSIGHT:
'reachable' means smallest value NOT constructible yet
If we can make [1...reachable-1] and next number <= reachable
Then we can extend to [1...reachable+number-1]

🎯 ALGORITHM:
1. Sort array ascending
2. Initialize reachable = 1
3. For each number:
   - If number > reachable: gap found
   - Else: reachable += number
4. Return reachable

⚡ RANGE EXTENSION LOGIC:
Current range: [1...reachable-1]
If num <= reachable:
New range: [1...reachable+num-1]
If num > reachable:
Gap at reachable
*/

class Solution {
public:

    // TC: O(n log n)
    // SC: O(1)

    long long smallestpositive(vector<int> arr) {

        sort(arr.begin(), arr.end());

        /*
        reachable means:
        smallest value NOT possible yet
        */

        long long reachable = 1;

        for(int num : arr) {

            /*
            Gap found
            We cannot create reachable
            */
            if(num > reachable) {

                return reachable;
            }

            /*
            Extend reachable range
            Earlier: [1 ... reachable-1]
            After adding num: [1 ... reachable+num-1]
            */
            reachable += num;
        }

        return reachable;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    SMALLEST MISSING CONSTRUCTIBLE VALUE
    + SUBSET SUMS
    + POSITIVE INTEGERS

Think immediately:
    GREEDY REACHABLE RANGE EXPANSION

-----------------------------------------------------

KEY OBSERVATIONS:

1. Sort enables processing smallest numbers first
2. 'reachable' tracks smallest unconstructible value
3. If num > reachable, gap appears
4. If num <= reachable, range extends continuously

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting to sort array first
2. Using int instead of long long (overflow)
3. Misunderstanding reachable meaning
4. Thinking reachable itself is achievable (it's not)

-----------------------------------------------------

SIMILAR PROBLEMS

- Smallest missing constructible value
- Subset sum range problems
- Greedy range extension

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Find smallest missing constructible value
- Subset sums with positive integers
- Range extension problems

Think:
Greedy Reachable Range

Algorithm:
1. Sort array
2. Initialize reachable = 1
3. For each num:
   - If num > reachable: return reachable
   - Else: reachable += num
4. Return reachable

Key insight:
reachable = smallest value NOT constructible yet

-----------------------------------------------------
*/
