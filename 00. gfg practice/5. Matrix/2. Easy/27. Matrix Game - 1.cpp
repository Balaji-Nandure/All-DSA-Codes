/*
GeeksforGeeks: Matrix Game - 1
Difficulty: Easy

Problem:
Given N and a N*N matrix containing 0’s and 1’s. Group all the row numbers (starting index 0) which are having 1’s at same position.

Example 1:
Input:
N = 4
matrix = [0 0 1 0
          0 1 0 0
          0 0 1 0
          0 0 0 0]
Output: 0 1
Explanation:
In the above test case, 1st and 3rd row have the 1's at same column, i.e., 2 (starting index from 0) so group first and third row. And print the index of first row, i.e., 0 (starting index from 0).
For second row, as it is the only row with same indexing of 1's so print it's index, i.e., 1.
For forth row, 1 is not present in this row so didn't print anything.

Example 2:
Input:
N = 1
matrix = [0]
Output: -1
Explanation:
There is no row containing 1.

Your task:
You don't need to read input or print anything. Your task is to complete the function groupRows(), which takes the matrix and an integer N as input parameters and returns a list of row numbers after grouping. If there is no row containing 1, return -1.

Core Idea:
Since we need to group rows that have 1's at the exact same positions, the pattern of 0's and 1's for these rows must be identical. 
We can represent each row as a string (e.g., "0010"). We also need to ignore rows that do not contain any 1's (i.e., consisting entirely of 0's).
By using a HashSet (unordered_set in C++), we can keep track of the row patterns we have already encountered. For each row:
- We form its pattern string and check if it has at least one '1'.
- If it contains a '1' and its pattern is not yet in our HashSet, it is the first row of a new group. We add its index to our result array and insert the pattern into the HashSet.
- If it contains a '1' but the pattern is already in the HashSet, it belongs to an existing group, so we skip it.

Approach:
1. Initialize an `unordered_set<string> seen` to keep track of unique row patterns.
2. Initialize a `vector<int> ans` to store the first row index of each group.
3. Loop through each row `i` from 0 to N-1:
   a. Create a string `s` to represent the pattern of the row.
   b. Keep a boolean `has_one` to track if the row contains at least one '1'.
   c. Iterate through each column `j`, appending the character '0' or '1' to `s` and updating `has_one`.
   d. If `has_one` is true and `s` is not found in `seen`:
      - Insert `s` into `seen`.
      - Add `i` to `ans`.
4. If `ans` is empty (meaning no row had a '1'), return `{-1}`.
5. Return `ans`.

Time Complexity : O(N^2) — We iterate through all elements of the N*N matrix exactly once. Generating the string takes O(N) for each row, resulting in O(N^2) overall.
Space Complexity: O(N^2) — In the worst case (where all rows have unique patterns and at least one 1), the unordered_set will store N strings of length N, taking up O(N^2) space.

GFG Link:
https://practice.geeksforgeeks.org/problems/matrix-game-1/1
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> groupRows(vector<vector<int>>& matrix, int n) {
        unordered_set<string> seen;
        vector<int> ans;
        
        for (int i = 0; i < n; i++) {
            string s = "";
            bool has_one = false;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    has_one = true;
                }
                s += (matrix[i][j] == 1 ? '1' : '0');
            }
            
            // If the row has at least one '1' and its pattern hasn't been seen yet
            if (has_one) {
                if (seen.find(s) == seen.end()) {
                    seen.insert(s);
                    ans.push_back(i);
                }
            }
        }
        
        // If no row contains a 1
        if (ans.empty()) {
            return {-1};
        }
        
        return ans;
    }
};

/*
Dry Run — Example 1:
Input:
N = 4
matrix = [
  [0, 0, 1, 0],
  [0, 1, 0, 0],
  [0, 0, 1, 0],
  [0, 0, 0, 0]
]

Iteration details:
- Row i = 0: pattern s = "0010", has_one = true. `seen` is empty, so insert "0010", add 0 to ans. ans = [0].
- Row i = 1: pattern s = "0100", has_one = true. "0100" not in `seen`, so insert "0100", add 1 to ans. ans = [0, 1].
- Row i = 2: pattern s = "0010", has_one = true. "0010" is already in `seen`. Skip.
- Row i = 3: pattern s = "0000", has_one = false. Skip.

Result:
ans = [0, 1]
Returns [0, 1]

Matches expected output perfectly! ✓
*/
