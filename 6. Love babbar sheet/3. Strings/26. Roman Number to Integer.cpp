// Problem: Converting Roman Numerals to Decimal (Roman Number to Integer)
// Link (GFG): https://www.geeksforgeeks.org/problems/roman-number-to-integer3201/1
// Article: https://www.geeksforgeeks.org/dsa/roman-number-to-integer/
// Difficulty: Easy
// Topic: String, Math, Hash Map / Lookup Table

/*
Problem Statement:
Given a string in Roman numeral format `s`, your task is to convert it to an integer.

Roman Numeral Values:
  'I' = 1
  'V' = 5
  'X' = 10
  'L' = 50
  'C' = 100
  'D' = 500
  'M' = 1000

Subtractive Rule:
- When a smaller value symbol appears BEFORE a larger value symbol, it is SUBTRACTED.
  * IV = 4, IX = 9
  * XL = 40, XC = 90
  * CD = 400, CM = 900
- In all other cases, values are ADDED.

Example 1:
Input: s = "V"
Output: 5

Example 2:
Input: s = "III"
Output: 3

Example 3:
Input: s = "MCMIV"
Output: 1904
Explanation: M (1000) + CM (900) + IV (4) = 1904.

Constraints:
- 1 <= s.length() <= 15
- s contains only valid Roman numeral characters: ('I', 'V', 'X', 'L', 'C', 'D', 'M').
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Standard Base-10 Strings (like "1904"):
//   * Every digit's positional weight is strictly determined by its power of 10 (`digit * 10^k`).
// - In Roman Numeral Decoding:
//   * The sign (addition vs subtraction) depends on the RELATIVE VALUE of the NEXT adjacent character!
//   * A 1-step lookahead `val(s[i]) < val(s[i + 1])` decides whether `val(s[i])` is added or subtracted.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Single-Pass Left-to-Right Scan with 1-Step Lookahead (Optimal & Chosen):
//   - Maintain integer `total = 0`.
//   - For `i = 0` to `n - 1`:
//       * If `i + 1 < n` and `value(s[i]) < value(s[i + 1])`:
//           `total -= value(s[i]);` (Subtractive rule)
//       * Else:
//           `total += value(s[i]);` (Additive rule)
//   - Direct switch or lookup table converts Roman char to integer in O(1).
//   - Complexity: O(N) time, O(1) space.
//   - Why this approach: Eliminates string slicing or look-behind buffers.

#include <iostream>
#include <string>

using namespace std;

class Solution {
private:
    int charValue(char ch) {
        switch (ch) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }

public:
    int romanToDecimal(string& s) {
        int n = s.length();
        int total = 0;

        for (int i = 0; i < n; ++i) {
            int currentVal = charValue(s[i]);

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 1-Step Lookahead: If current character is strictly smaller than the next,
            // it represents a subtractive prefix (e.g. 'I' before 'V' is -1 + 5 = 4).
            // Otherwise, it is a standard additive numeral.
            if (i + 1 < n && currentVal < charValue(s[i + 1])) {
                total -= currentVal;
            } else {
                total += currentVal;
            }
        }

        return total;
    }
};

int main() {
    Solution sol;
    string s1 = "V";
    cout << s1 << " -> " << sol.romanToDecimal(s1) << "\n";

    string s2 = "MCMIV";
    cout << s2 << " -> " << sol.romanToDecimal(s2) << "\n";

    string s3 = "MMMDCCCLXXXVIII"; // 3888
    cout << s3 << " -> " << sol.romanToDecimal(s3) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) where N is length of string (at most 15 chars).
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Lookahead comparison (`current < next`) is the universal pattern for parsing 
  subtractive notations.
*/
