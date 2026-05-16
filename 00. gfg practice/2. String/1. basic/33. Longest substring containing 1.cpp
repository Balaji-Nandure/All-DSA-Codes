/*
Problem: Longest substring containing '1'

GFG: https://www.geeksforgeeks.org/problems/longest-substring-containing-1/1

Description:
Given a binary string, return the length of the longest contiguous substring
containing only '1'.

Examples:

Input: 110
Output: 2

Input: 11101110
Output: 3

Constraints:
1 <= T <= 100
1 <= |string length| <= 10^4

Approach (Single Pass Counting):
Traverse the string once while maintaining the current streak of '1's and the
maximum streak seen so far.

Key insight:
- Extend the current count when the character is '1'
- Reset the current count when the character is '0'
- Track the maximum after each reset and at the end

Algorithm:
1. Initialize current = 0 and best = 0
2. Traverse each character in the string
3. If character is '1', increment current
4. If character is '0', update best and reset current
5. After traversal, update best one last time
6. Return best

Time Complexity: O(|s|)
Space Complexity: O(1)

Pattern: Single Pass / Streak Counting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
STREAK COUNTING APPROACH
=====================================================

TC: O(n)
SC: O(1)

STREAK COUNTING
- Count consecutive '1's as you scan
- Reset count when a '0' appears
- Keep the maximum streak seen so far

KEY INSIGHT:
Only contiguous 1s matter. A zero breaks the substring.

DRY RUN:
s = "11101110"

current = 0, best = 0
1 -> current = 1
1 -> current = 2
1 -> current = 3
0 -> best = 3, current = 0
1 -> current = 1
1 -> current = 2
1 -> current = 3
0 -> best = 3, current = 0

Result = 3
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    int maxlength(string s) {

        int current = 0;
        int best = 0;

        for(char ch : s) {

            if(ch == '1') {
                current++;
            } else {
                best = max(best, current);
                current = 0;
            }
        }

        best = max(best, current);
        return best;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    LONGEST CONTIGUOUS RUN
    + BINARY STRING
    + ONLY ONE CHARACTER TYPE MATTERS

Think immediately:
    STREAK COUNTING

-----------------------------------------------------

KEY OBSERVATIONS:

1. A zero breaks the streak of ones.
2. We only need the current streak and the best streak.
3. One pass is enough.

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting to check the last streak after the loop.
2. Resetting the best count instead of the current count.
3. Using nested loops when a single pass works.

-----------------------------------------------------
*/
