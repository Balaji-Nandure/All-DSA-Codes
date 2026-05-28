/*
Problem: 1[0]1 Pattern Count

Given a string S, your task is to find the number of patterns of form 1[0]1 where [0] represents any number of zeroes (minimum requirement is one 0) there should not be any other character except 0 in the [0] sequence.

Example 1:
Input:
S = "100001abc101"
Output: 2
Explanation: The two patterns are "100001" and "101".

Example 2:
Input:
S = "1001ab010abc01001"
Output: 2
Explanation: The two patterns are "1001"(at start) and "1001"(at end).

Constraints:
1 <= Length of String <= 10^5

--------------------------------------------------

Pattern:
String Processing + Two Pointers

--------------------------------------------------

Key Observation:
- We are looking for sequences that strictly start with a '1', have one or more '0's, and strictly end with a '1'.
- A pattern ending in '1' can simultaneously serve as the starting '1' for the next pattern (e.g., "10101" contains two patterns).
- When we encounter a '1', we can scan forward to see if it is followed by exclusively '0's.
- If we pass at least one '0' and hit a '1', we found a valid pattern.
- Because a trailing '1' can also be a leading '1' for the next sequence, we should make sure our main loop resumes exactly at that trailing '1'.

--------------------------------------------------

Approach:
1. Initialize `count = 0` and iterate `i` through the string `S`.
2. When `S[i] == '1'`, initialize a second pointer `j = i + 1`.
3. Use a `while` loop to advance `j` as long as `j < n` and `S[j] == '0'`.
4. After the `while` loop, check if we actually moved past at least one '0' (meaning `j > i + 1`).
5. If we did, and `j < n` and `S[j] == '1'`, it means the sequence successfully terminated with a '1'. We increment our `count`.
6. Since we scanned characters up to `j`, we can safely update `i = j - 1` so that the next iteration of the outer `for` loop (which does `i++`) starts exactly at index `j`. This perfectly handles overlapping patterns like "10101" because we'll resume checking from the terminating '1'.
7. Return `count`.

--------------------------------------------------

Time Complexity: O(|S|) since the inner loop strictly advances `j` and the outer loop catches up to `j`, each character is visited at most twice.
Space Complexity: O(1) Auxiliary Space.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/101-pattern-count1341/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int patternCount(string S) {
        int count = 0;
        int n = S.length();
        
        for (int i = 0; i < n; i++) {
            // When we find a starting '1'
            if (S[i] == '1') {
                int j = i + 1;
                
                // Skip all consecutive '0's
                while (j < n && S[j] == '0') {
                    j++;
                }
                
                // If we skipped at least one '0' and ended up exactly on a '1'
                if (j > i + 1 && j < n && S[j] == '1') {
                    count++;
                }
                
                // Jump the outer loop pointer to j - 1. 
                // The `i++` of the outer loop will land it exactly on `j`.
                // This cleanly handles overlapping patterns like "10101"
                // because we'll resume exactly at the terminating '1'.
                // If it wasn't a '1', it still safely skips the '0's.
                i = j - 1;
            }
        }
        
        return count;
    }
};
