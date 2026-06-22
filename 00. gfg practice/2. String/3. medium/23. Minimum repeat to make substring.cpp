/*
GeeksforGeeks: Minimum repeat to make substring
Difficulty: Medium

Problem:
Given two strings s1 and s2, return the minimum number of times s1 has to be repeated such that s2 is a substring of it.
If s2 can never be a substring of any repetition of s1, return -1.

Note: Both strings contain only lowercase letters.

Examples:
Input: s1 = "ww", s2 = "www"
Output: 2
Explanation: Repeating s1 two times ("wwww"), s2 ("www") is a substring of it.

Input: s1 = "abac", s2 = "cabaca" 
Output: 3 
Explanation: Repeating s1 three times ("abacabacabac"), s2 ("cabaca") is a substring of it. 
             s2 is not a substring of s1 when it is repeated less than 3 times.

Input: s1 = "ab", s2 = "cab"
Output: -1

Constraints:
1 <= s1.size(), s2.size() <= 10^5

Core Idea:
- To match a substring s2 of length L2, the repeated version of s1 must be at least of length L2.
- The minimum number of repetitions to achieve a length of at least L2 is k = ceil(L2 / L1).
- Because s2 can start anywhere inside the first copy of s1 (from index 0 up to L1 - 1), it can spill over into the next repetition.
- Thus, the starting index of s2 must be within the first copy of s1.
- Therefore, we only need to check:
  1. If s2 is a substring of s1 repeated k times (returns k).
  2. If s2 is a substring of s1 repeated k + 1 times (returns k + 1).
- If s2 is not found in either, it is mathematically impossible for s2 to be a substring, so we return -1.

Approach:
1. Start with `temp = s1` and `count = 1`.
2. While `temp.length() < s2.length()`, append `s1` to `temp` and increment `count`.
3. Check if `s2` is in `temp` using `temp.find(s2) != string::npos`. If yes, return `count`.
4. Check if `s2` is in `temp + s1`. If yes, return `count + 1`.
5. If not found in either, return -1.

Time Complexity: O(L1 + L2) — Constructing the repeated string and running substring search takes linear time.
Space Complexity: O(L1 + L2) — To store the repeated string of length at most O(L1 + L2).

GFG Link: https://www.geeksforgeeks.org/problems/minimum-number-of-times-a-string-has-to-be-repeated-such-that-another-string-is-substring-of-it/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int minRepeats(string s1, string s2) {
        string temp = s1;
        int count = 1;
        
        // Step 1: Repeat s1 until its length is at least the length of s2
        while (temp.length() < s2.length()) {
            temp += s1;
            count++;
        }
        
        // Step 2: Check if s2 is a substring of the current repeated string (k times)
        if (temp.find(s2) != string::npos) {
            return count;
        }
        
        // Step 3: Check if s2 is a substring after repeating one more time (k + 1 times)
        if ((temp + s1).find(s2) != string::npos) {
            return count + 1;
        }
        
        // Step 4: If still not found, s2 can never be a substring
        return -1;
    }
};

// Solution 2: Using comparison with -1
// Works because string::npos is internally defined as -1 (promoted to size_t max)
class Solution2 {
public:
    int minRepeats(string s1, string s2) {
        string temp = s1;
        int count = 1;
        
        while (temp.length() < s2.length()) {
            temp += s1;
            count++;
        }
        
        // Comparing with -1 works correctly since string::npos wraps to -1 as size_t
        if (temp.find(s2) != -1) {
            return count;
        }
        
        if ((temp + s1).find(s2) != -1) {
            return count + 1;
        }
        
        return -1;
    }
};

/*
Dry Run — Example:
s1 = "abac", s2 = "cabaca"
L1 = 4, L2 = 6

1. Initialization:
   - temp = "abac"
   - count = 1

2. Loop:
   - temp.length() (4) < s2.length() (6) is true:
     - temp = temp + s1 = "abacabac"
     - count = 2
   - temp.length() (8) < s2.length() (6) is false. Loop terminates.

3. First substring check:
   - Does "abacabac" contain "cabaca"?
   - Indices:
     "a  b  a  c  a  b  a  c"
      0  1  2  3  4  5  6  7
     - Substring "cabac" is present at index 3, but "cabaca" requires 'a' at index 8, which is missing.
   - Result: Not found.

4. Second substring check (with one more repetition):
   - temp + s1 = "abacabac" + "abac" = "abacabacabac"
   - Does "abacabacabac" contain "cabaca"?
   - Indices:
     "a  b  a  c  a  b  a  c  a  b  a  c"
      0  1  2  3  4  5  6  7  8  9  10 11
                     ^  ^  ^  ^  ^  ^
                     c  a  b  a  c  a
   - Yes! Found starting at index 3.
   - Return count + 1 = 2 + 1 = 3.

Output: 3
*/
