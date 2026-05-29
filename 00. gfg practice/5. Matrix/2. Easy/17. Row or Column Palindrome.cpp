/*
GeeksforGeeks: Row or Column Palindrome
Difficulty: Easy

Problem:
Given a matrix arr[][] of size n x n, find a row or column that forms a palindrome.
Return the index of the row or column followed by 'r' or 'c' respectively.
If multiple palindromes exist, then prioritize rows over columns.
If multiple rows or columns are palindromic, return the one with the smallest index.
If no palindrome exists, return "-1".

Example 1:
Input: 
arr[][] = [[1, 0, 0], 
           [0, 1, 0],
           [1, 1, 0]]
Output: 1 r
Explanation: 
Row 0: 1 0 0 (not palindrome)
Row 1: 0 1 0 (palindrome!). Return "1 r".

Example 2:
Input: 
arr[][] = [[1, 0],
           [1, 0]]
Output: 0 c
Explanation: 
Row 0: 1 0 (no)
Row 1: 1 0 (no)
Col 0: 1 1 (palindrome!). Return "0 c".

Core Idea:
A sequence is a palindrome if it reads the same forwards and backwards. We can 
check this by comparing the first element with the last, the second with the 
second-to-last, and so on up to the middle.

Because the problem specifically asks us to:
1. Prioritize rows over columns
2. Prioritize smaller indices over larger ones

We can simply structure our loops to match these exact priorities!
First, we will loop through all the rows starting from index 0. If we find any row 
that is a palindrome, we instantly return its index and don't even bother checking 
the rest of the matrix. 

If we finish checking all the rows and none of them were palindromes, we then 
loop through all the columns starting from index 0. If we find a palindromic 
column, we return it.

If both loops finish and we found absolutely nothing, we just return "-1".

Approach:
1. Loop `i` from 0 to `n - 1` (Checking rows):
   - Assume it is a palindrome (`isPal = true`).
   - Loop `j` from 0 to `n / 2`: 
     - If `arr[i][j] != arr[i][n - 1 - j]`, set `isPal = false` and `break`.
   - If `isPal` is still true, return `to_string(i) + " r"`.
2. Loop `j` from 0 to `n - 1` (Checking columns):
   - Assume it is a palindrome (`isPal = true`).
   - Loop `i` from 0 to `n / 2`:
     - If `arr[i][j] != arr[n - 1 - i][j]`, set `isPal = false` and `break`.
   - If `isPal` is still true, return `to_string(j) + " c"`.
3. If neither loop returned anything, return `"-1"`.

Time Complexity : O(N^2) — We check at most N rows and N columns, each taking O(N) comparisons.
Space Complexity: O(1) — No extra space is required (except for returning the small string).

GFG Link:
https://www.geeksforgeeks.org/problems/row-or-column-palindrome1430/1
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string palindrome(vector<vector<int>>& arr) {
        int n = arr.size();
        
        // 1. Check all rows first (prioritize rows, and smallest index first)
        for (int i = 0; i < n; i++) {
            bool isPal = true;
            
            // Compare elements from the outside moving towards the center
            for (int j = 0; j < n / 2; j++) {
                if (arr[i][j] != arr[i][n - 1 - j]) {
                    isPal = false;
                    break; // Mismatch found, not a palindrome
                }
            }
            
            if (isPal) {
                return to_string(i) + " r";
            }
        }
        
        // 2. Check all columns (only if no row was a palindrome)
        for (int j = 0; j < n; j++) {
            bool isPal = true;
            
            // Compare elements from the top/bottom moving towards the center
            for (int i = 0; i < n / 2; i++) {
                if (arr[i][j] != arr[n - 1 - i][j]) {
                    isPal = false;
                    break; // Mismatch found, not a palindrome
                }
            }
            
            if (isPal) {
                return to_string(j) + " c";
            }
        }
        
        // 3. No palindrome found anywhere
        return "-1";
    }
};

/*
Dry Run — Example 1:
arr[][] = [[1, 0, 0], 
           [0, 1, 0],
           [1, 1, 0]]
n = 3

Row 0 (i=0):
  - j=0: arr[0][0] (1) vs arr[0][2] (0). Mismatch! isPal = false, break.

Row 1 (i=1):
  - j=0: arr[1][0] (0) vs arr[1][2] (0). Match!
  - Loop finishes. isPal = true.
  - Return "1 r".

Output: "1 r" ✓
*/
