/*
Problem: Shuffle Integers

GFG:
https://www.geeksforgeeks.org/problems/shuffle-integers2401/1

Description:
Given an array arr of n elements in the following format {a1, a2, a3, a4, ... , an/2, b1, b2, b3, b4, ... , bn/2}, the task is shuffle the array to {a1, b1, a2, b2, a3, b3, ... , an/2, bn/2} without using extra space. Note that n is even.

Examples:

Input: n = 4, arr = {1, 2, 9, 15}
Output: 1 9 2 15
Explanation: a1=1, a2=2, b1=9, b2=15. So the final array will be: a1, b1, a2, b2 = {1,9,2,15}.

Input: n = 6 arr = {1, 2, 3, 4, 5, 6} 
Output: 1 4 2 5 3 6

Constraints:
1 ≤ n ≤ 10^5
1 ≤ arr[i] ≤ 10^3

Approach (In-Place Encoding):
This is an array rearrangement problem that requires in-place solution.

Key insight:
- Since values are small (≤ 1000), we can encode both old and new values in same position
- Use encoding: arr[i] = old + new * BASE
- Later extract new values using division

Algorithm:
1. Calculate BASE = max_value + 1 = 1001
2. For each i from 0 to n/2-1:
   - Encode a[i] at position 2*i
   - Encode b[i] at position 2*i+1
3. Decode all values by dividing by BASE

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: In-Place Encoding / Array Rearrangement
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
IN-PLACE ENCODING TECHNIQUE
=====================================================

TC: O(n)
SC: O(1)

🔥 ENCODING APPROACH
- Store both old and new values in same position
- Use BASE = max_value + 1
- Extract new values later using division

🧠 KEY INSIGHT:
Since 1 ≤ arr[i] ≤ 1000, we can safely use BASE = 1001
Encoding: old + new * BASE
Decoding: new = arr[i] / BASE

🎯 ALGORITHM:
1. Calculate BASE = 1001
2. Encode shuffled values in-place
3. Decode final values

⚡ ENCODING FORMULA:
arr[i] = arr[i] + (arr[source] % BASE) * BASE
This preserves old value and stores new value
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    void shuffleArray(long long arr[], int n) {

        long long BASE = 1001;

        int mid = n / 2;

        int idx = 0;

        // Encode shuffled values
        for(int i = 0; i < mid; i++) {

            // Put a[i] at even position
            arr[idx] += (arr[i] % BASE) * BASE;
            idx++;

            // Put b[i] at odd position
            arr[idx] += (arr[mid + i] % BASE) * BASE;
            idx++;
        }

        // Decode final values
        for(int i = 0; i < n; i++) {

            arr[i] /= BASE;
        }
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    REARRANGE ARRAY + NO EXTRA SPACE
    + SMALL VALUE CONSTRAINTS

Think immediately:
    IN-PLACE ENCODING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Values are bounded (≤ 1000)
2. Need in-place rearrangement
3. Can encode multiple values in same position

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting modulo while reading old value
2. Using small BASE causing overflow
3. Overwriting values before using them
4. Wrong index calculations

-----------------------------------------------------

SIMILAR PROBLEMS

- Rearrange array in-place
- Encode-decode techniques
- Array manipulation without extra space

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Rearrange array
- No extra space allowed
- Small value constraints

Think:
Encoding Technique

Store: old + new * BASE
Recover: new = arr[i] / BASE

-----------------------------------------------------
*/
