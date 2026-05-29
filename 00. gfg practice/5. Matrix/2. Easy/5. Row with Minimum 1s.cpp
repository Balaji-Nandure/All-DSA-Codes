/*
GeeksforGeeks: Row with Minimum 1s
Difficulty: Easy

Problem:
Given a 2D binary matrix (1-based indexed) mat of dimensions nxm, determine the 
row that contains the minimum number of 1's.
Note: The matrix contains only 1's and 0's. Also, if two or more rows contain 
the minimum number of 1's, the answer is the lowest of those indices.

Example 1:
Input: 
mat = [[1, 1, 1, 1], 
       [1, 1, 0, 0], 
       [0, 0, 1, 1], 
       [1, 1, 1, 1]]
Output: 2
Explanation: 
- Row 1: 4 ones
- Row 2: 2 ones
- Row 3: 2 ones
- Row 4: 4 ones
Rows 2 and 3 contain the minimum number of 1's (2 each). Since row 2 is 
less than row 3, the answer is 2 (1-based indexing).

Example 2:
Input: 
mat = [[0, 0, 0], 
       [0, 0, 0], 
       [0, 0, 0]]
Output: 1
Explanation: All the rows contain the same number of 1's (0 each). Among them, 
index 1 is the smallest, so the answer is 1.

Core Idea:
Since the elements in each row are NOT sorted (they can be in any random order 
of 0s and 1s), we must count the 1s by checking every element in the matrix. 
We can simply iterate row by row, count the number of 1s in the current row, 
and keep track of the row that gave us the lowest count.
By only updating our answer strictly when `count < min1s` (and not `<=`), 
we automatically guarantee that if a later row ties for the minimum, we keep 
the earlier (smaller) 1-based index!

Approach:
1. Initialize `min1s = INT_MAX` and `ansRow = -1`.
2. Iterate through each row `i` from `0` to `n - 1`.
3. Initialize a `count = 0` for the current row.
4. Iterate through each element `j` from `0` to `m - 1` in the current row.
   a. If `mat[i][j] == 1`, increment `count`.
5. After the inner loop, check if `count < min1s`:
   a. If so, update `min1s = count` and `ansRow = i + 1` (1-based index).
6. Return `ansRow`.

Time Complexity : O(N * M) — We must visit every single element in the matrix to count the 1s.
Space Complexity: O(1) — No extra space is used.

GFG Link:
https://www.geeksforgeeks.org/problems/row-with-minimum-number-of-1s5430/1
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minRow(vector<vector<int>> &mat) {
        int n = mat.size();
        int m = mat[0].size();
        
        int min1s = INT_MAX;
        int ansRow = -1;
        
        for (int i = 0; i < n; i++) {
            int count = 0;
            
            // Count the 1s in the current row
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 1) {
                    count++;
                }
            }
            
            // Update only if we find a STRICTLY smaller count.
            // This guarantees we keep the lowest 1-based index on ties.
            if (count < min1s) {
                min1s = count;
                ansRow = i + 1; // 1-based indexing
            }
        }
        
        return ansRow;
    }
};

/*
Dry Run — Example 1:
mat = [[1, 1, 1, 1], 
       [1, 1, 0, 0], 
       [0, 0, 1, 1], 
       [1, 1, 1, 1]]

Initial: min1s = INT_MAX, ansRow = -1

i = 0 (Row 1):
  - count = 4
  - 4 < INT_MAX is true. 
  - min1s = 4, ansRow = 1

i = 1 (Row 2):
  - count = 2
  - 2 < 4 is true.
  - min1s = 2, ansRow = 2

i = 2 (Row 3):
  - count = 2
  - 2 < 2 is FALSE! (This is key, it ignores the tie and keeps ansRow = 2)

i = 3 (Row 4):
  - count = 4
  - 4 < 2 is FALSE.
  
Return ansRow = 2. ✓
*/
