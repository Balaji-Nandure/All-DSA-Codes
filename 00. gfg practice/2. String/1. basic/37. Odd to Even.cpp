/*
Problem: Odd to Even

GFG: https://www.geeksforgeeks.org/problems/odd-to-even0537/1

Description:
Given an odd number as a string, make the largest even number possible using
exactly one swap operation. If no such number is possible, return the input
string itself.

Examples:

Input: s = "4543"
Output: "4534"

Input: s = "1539"
Output: "1539"

Constraints:
1 <= |s| <= 10^5

Approach (Greedy Swap):
To get the largest even number after exactly one swap:
1) Prefer the leftmost even digit that is smaller than the last digit.
2) If such digit does not exist, use the rightmost even digit.

Key insight:
- A number is even only if the last digit is even
- Bringing a smaller even digit to the end can increase earlier positions
- Earliest position gain gives lexicographically larger number

Algorithm:
1. Let last = s[n - 1]
2. Scan all indices [0, n-2] for even digits
3. Track:
   - first even digit < last (take first such index and stop)
   - otherwise keep updating rightmost even index
4. Swap chosen index with last digit
5. If no even digit exists, return original string

Time Complexity: O(|s|)
Space Complexity: O(1)

Pattern: Greedy / One Swap / Last Digit Fix
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GREEDY SWAP APPROACH
=====================================================

TC: O(n)
SC: O(1)

GREEDY IDEA
- The final digit must be even.
- Best case is to improve an earlier position by moving a larger last digit left.
- So first try earliest even digit smaller than last digit.
- If not possible, use the rightmost even digit.

DRY RUN:
s = "4543"

Rightmost even digit before last position: index 2 -> '4'
Swap with last digit '3'
Result = "4534"
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    string makeEven(string s) {

        int n = s.size();
        int swapIndex = -1;
        char last = s[n - 1];

        for(int i = 0; i <= n - 2; i++) {

            if((s[i] - '0') % 2 == 0) {
                swapIndex = i;

                if(s[i] < last) {
                    break;
                }
            }
        }

        if(swapIndex == -1) {
            return s;
        }

        swap(s[swapIndex], s[n - 1]);
        return s;
    }
};


/*
-----------------------------------------------------

INTERVIEW INSIGHT

Whenever problem involves:
    MAKE NUMBER EVEN
    + EXACTLY ONE SWAP
    + LARGEST POSSIBLE RESULT

Think immediately:
    GREEDY EVEN-DIGIT SWAP

-----------------------------------------------------

KEY OBSERVATIONS:

1. The last digit decides parity.
2. If an even digit smaller than last exists, take the leftmost one.
3. Otherwise, take the rightmost even digit.
4. If no even digit exists, no valid swap can help.

-----------------------------------------------------

COMMON MISTAKES:

1. Always swapping with the rightmost even digit.
2. Forgetting that the input is already odd.
3. Doing more than one swap.

-----------------------------------------------------
*/
