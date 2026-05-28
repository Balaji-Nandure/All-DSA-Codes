/*
Problem: Meta Strings

Given two strings s1 and s2 consisting of lowercase english alphabets, check whether these strings are meta strings or not.

Note: Meta strings are the strings which can be made equal by exactly one swap in any of the strings. Equal string are not considered here as Meta strings.

Example 1:
Input: s1 = "geeks", s2 = "keegs"
Output: true
Explanation: We can swap the 0th and 3rd character of s2 to make it equal to s1.

Example 2:
Input: s1 = "geeks", s2 = "geeks"
Output: false
Explanation: Equal strings are not considered Meta strings.

Example 3:
Input: s1 = "a", s2 = "b"
Output: false
Explanation: Since there is only character, we cannot do any swap.

Constraints:
1 <= |s1|, |s2| <= 10^5

--------------------------------------------------

Pattern:
String Processing + Counting Mismatches

--------------------------------------------------

Key Observation:
- For two strings to be made equal by exactly ONE swap:
  1. They must be of the exact same length.
  2. They cannot already be completely identical (as per the problem statement constraints).
  3. They must differ at EXACTLY TWO indices.
  4. If they differ at indices `i` and `j`, then `s1[i]` must equal `s2[j]` and `s1[j]` must equal `s2[i]`.
- We can iterate through the strings simultaneously and simply count the number of positional mismatches.
- We only need to keep track of the first two mismatched indices. If we encounter a third mismatch, we can immediately return false because one swap can only fix at most two characters.

--------------------------------------------------

Approach:
1. Check if `s1.length() != s2.length()`. If so, return `false`.
2. Check if `s1 == s2`. If they are already identical, return `false`.
3. Initialize `first = -1` and `second = -1` to store the indices of mismatches, and `mismatchCount = 0`.
4. Loop through the string from index `0` to `n-1`:
   - If `s1[i] != s2[i]`:
     - Increment `mismatchCount`.
     - If `mismatchCount == 1`, set `first = i`.
     - If `mismatchCount == 2`, set `second = i`.
     - If `mismatchCount > 2`, immediately return `false`.
5. Finally, return `true` if all conditions are perfectly met: `mismatchCount == 2` AND `s1[first] == s2[second]` AND `s1[second] == s2[first]`.

--------------------------------------------------

Time Complexity: O(N) where N is the length of the strings. We traverse the strings at most once.
Space Complexity: O(1) Auxiliary Space.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/meta-strings5713/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool checkMeta(string s1, string s2) {
        // Condition 1: Must be of equal length
        if (s1.length() != s2.length()) {
            return false;
        }
        
        // Condition 2: Equal strings are not considered Meta strings
        if (s1 == s2) {
            return false;
        }
        
        int first = -1;
        int second = -1;
        int mismatchCount = 0;
        
        for (int i = 0; i < s1.length(); i++) {
            if (s1[i] != s2[i]) {
                mismatchCount++;
                
                if (mismatchCount == 1) {
                    first = i;
                } else if (mismatchCount == 2) {
                    second = i;
                } else {
                    // More than 2 mismatches means it's impossible to fix with just one swap
                    return false;
                }
            }
        }
        
        // Condition 3 & 4: Exactly 2 mismatches, and they can be resolved by swapping
        return (mismatchCount == 2 && s1[first] == s2[second] && s1[second] == s2[first]);
    }
};
