/*
Problem: Largest number in one swap

GFG: https://www.geeksforgeeks.org/problems/largest-number-in-one-swap1520/1

Description:
Given a numeric string s,
find the lexicographically largest string
possible using at most one swap.

Examples:

Input: s = "768"
Output: "867"

Explanation:
Swap '7' and '8'

--------------------------------------------------

Input: s = "333"
Output: "333"

Explanation:
All digits same,
no better swap possible.

Constraints:
1 ≤ s.size() ≤ 10^5
'0' ≤ s[i] ≤ '9'

Approach:
- Store last occurrence of every digit
- Traverse string from left to right
- For current digit:
    try to find larger digit from 9 → current+1
- If larger digit exists later:
    swap once and return

Why?
- Leftmost bigger improvement gives
  maximum lexicographical result.

Dry Run:
s = "768"

Last positions:
7 -> 0
6 -> 1
8 -> 2

i=0 -> '7'

Try larger digits:
8 exists at index 2 ✅

Swap:
"768" -> "867"

Return answer ✅

--------------------------------------------------

Dry Run:
s = "333"

No larger digit exists later

Return original string ✅

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    string largestSwap(string &s) {

        int n = s.size();

        vector<int> last(10, -1);

        // Store last occurrence
        for(int i = 0; i < n; i++) {
            last[s[i] - '0'] = i;
        }

        for(int i = 0; i < n; i++) {

            int cur = s[i] - '0';

            // Try bigger digits
            for(int d = 9; d > cur; d--) {

                // Bigger digit exists later
                if(last[d] > i) {

                    swap(s[i], s[last[d]]);

                    return s;
                }
            }
        }

        return s;
    }
};