/*
Problem: Check if it is possible to convert one string into another with given constraints

Given two strings S and T, which contains three characters i.e 'A', 'B' and '#' only. Check whether it is possible to convert the first string into another string by performing following operations on string first.
1- A can move towards Left only
2- B can move towards Right only
3- Neither A nor B should cross each other

Example 1:
Input:
S=#A#B#B#   
T=A###B#B
Output: 1

Example 2:
Input:
S=#A#B# 
T=#B#A#
Output: 0

Constraints:
1 <= M, N <= 100000

--------------------------------------------------

Pattern:
String Processing + Two Pointers

--------------------------------------------------

Key Observation:
- We want to move 'A's to the left and 'B's to the right across empty spaces '#'.
- The relative ordering of the 'A's and 'B's must remain EXACTLY the same in both strings because they are not allowed to cross each other.
- Thus, if we ignore all '#' characters, the remaining sequence of 'A's and 'B's must be identical in both strings.
- *Why is simply removing '#' and checking S == T not enough?*
  Because it only verifies that the order is the same and they don't cross, but it DOES NOT verify movement direction constraints.
  For example, if S = "#A#" and T = "##A", removing '#' gives "A" == "A" (True).
  But in reality, 'A' in S is at index 1 and in T is at index 2, meaning 'A' moved RIGHT, which is invalid!
- Since 'A' can only move left, the index of an 'A' in the starting string `S` must be >= the index of the corresponding 'A' in the target string `T`.
- Since 'B' can only move right, the index of a 'B' in `S` must be <= the index of the corresponding 'B' in `T`.
- We can use two pointers `i` and `j` to scan `S` and `T` simultaneously, skipping `#` characters, and checking these conditions on the fly.

--------------------------------------------------

Approach:
1. If lengths `M` and `N` are different, return 0.
2. Initialize two pointers `i = 0` (for `S`) and `j = 0` (for `T`).
3. Loop while `i < M` or `j < N`:
   - Advance `i` until `S[i]` is not `#` or `i == M`.
   - Advance `j` until `T[j]` is not `#` or `j == N`.
   - If both `i` and `j` reach the end (`M` and `N` respectively), return 1.
   - If only one pointer reaches the end, it means the sequences of 'A' and 'B' have different lengths or counts. Return 0.
   - If `S[i] != T[j]`, the relative ordering is different. Return 0.
   - If `S[i] == 'A'` and `i < j`, 'A' would need to move right to reach `j`, which is invalid. Return 0.
   - If `S[i] == 'B'` and `i > j`, 'B' would need to move left to reach `j`, which is invalid. Return 0.
   - Increment `i` and `j` and continue the loop.
4. If the loop completes successfully, return 1.

--------------------------------------------------

Time Complexity: O(M + N) since each pointer traverses its respective string exactly once.
Space Complexity: O(1) Auxiliary Space.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/check-if-it-is-possible-to-convert-one-string-into-another-with-given-constraints4116/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int isItPossible(string S, string T, int M, int N) {
        // If lengths are different, conversion is impossible
        if (M != N) {
            return 0;
        }
        
        int i = 0, j = 0;
        
        // Use Two Pointers to compare the characters
        while (i < M || j < N) {
            // Skip all '#' characters in S
            while (i < M && S[i] == '#') {
                i++;
            }
            
            // Skip all '#' characters in T
            while (j < N && T[j] == '#') {
                j++;
            }
            
            // If both pointers reached the end, conversion is perfectly valid
            if (i == M && j == N) {
                return 1;
            }
            
            // If only one pointer reached the end, counts don't match
            if (i == M || j == N) {
                return 0;
            }
            
            // The characters must match (relative ordering must be identical)
            if (S[i] != T[j]) {
                return 0;
            }
            
            // 'A' can only move left, so index in S must be >= index in T
            if (S[i] == 'A' && i < j) {
                return 0;
            }
            
            // 'B' can only move right, so index in S must be <= index in T
            if (S[i] == 'B' && i > j) {
                return 0;
            }
            
            // Move to the next characters
            i++;
            j++;
        }
        
        return 1;
    }
};
