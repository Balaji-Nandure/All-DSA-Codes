/*
GeeksforGeeks: Column with Max 0s
Difficulty: Easy

Problem:
You are given a matrix mat[][] of size n x n consisting only of 0s and 1s. 
Your task is to find the index of the column that contains the maximum number of 0s.
- If more than one column has the same maximum number of 0s, return the index 
  of the leftmost such column.
- If no column contains any 0 (i.e., all elements in the matrix are 1), return -1.

Example 1:
Input: 
mat[][] = [[0, 0, 0],
           [1, 0, 1],
           [0, 1, 1]]
Output: 0
Explanation: 
- Column 0: 2 zeros (at rows 0, 2)
- Column 1: 2 zeros (at rows 0, 1)
- Column 2: 1 zero (at row 0)
Columns 0 and 1 contain the same number of 0s; however, column 0 appears first, 
so the answer is 0.

Example 2:
Input: 
mat[][] = [[1, 1, 1],
           [1, 1, 1],
           [1, 1, 1]]
Output: -1
Explanation: Since no column contains any 0s, the answer is -1.

Core Idea:
Since the elements in each column are not sorted, we have to iterate through 
the entire matrix to count the number of 0s in each column.
We can loop over the columns in the outer loop, and loop over the rows in the 
inner loop to count the 0s column-by-column. 
To guarantee we return the *leftmost* column in the event of a tie, we only 
update our answer when we find a column with a STRICTLY greater count of 0s.
To easily handle the case where no zeros exist at all, we can initialize our 
max count variable to 0 and our answer column to -1.

Approach:
1. Initialize `max0s = 0` and `ansCol = -1`.
2. Iterate `j` from `0` to `n - 1` (Column loop).
3. Inside, initialize `count = 0`.
4. Iterate `i` from `0` to `n - 1` (Row loop).
   - If `mat[i][j] == 0`, increment `count`.
5. After counting the 0s for column `j`, check if `count > max0s`.
   - If true, update `max0s = count` and `ansCol = j`.
6. Return `ansCol`.

Time Complexity : O(N^2) — We must visit every single element in the N x N matrix.
Space Complexity: O(1) — No extra space is used.

GFG Link:
https://www.geeksforgeeks.org/problems/column-with-maximum-number-of-0s0003/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int columnWithMaxZeros(vector<vector<int>>& mat) {
        int n = mat.size();
        
        int max0s = 0;
        int ansCol = -1;
        
        // Loop over each column
        for (int j = 0; j < n; j++) {
            int count = 0;
            
            // Loop over each row to check the current column's elements
            for (int i = 0; i < n; i++) {
                if (mat[i][j] == 0) {
                    count++;
                }
            }
            
            // Update only if we find a STRICTLY greater count of 0s.
            // This guarantees we keep the leftmost (lowest) index on ties.
            if (count > max0s) {
                max0s = count;
                ansCol = j;
            }
        }
        
        return ansCol;
    }
};

/*
Dry Run — Example 1:
mat[][] = [[0, 0, 0],
           [1, 0, 1],
           [0, 1, 1]]
n = 3

Initial: max0s = 0, ansCol = -1

j = 0 (Column 0):
  - i=0: mat[0][0]=0 -> count=1
  - i=1: mat[1][0]=1 -> count=1
  - i=2: mat[2][0]=0 -> count=2
  - count (2) > max0s (0). 
  - max0s = 2, ansCol = 0

j = 1 (Column 1):
  - i=0: mat[0][1]=0 -> count=1
  - i=1: mat[1][1]=0 -> count=2
  - i=2: mat[2][1]=1 -> count=2
  - count (2) > max0s (2) is FALSE! (Maintains ansCol = 0)

j = 2 (Column 2):
  - i=0: mat[0][2]=0 -> count=1
  - i=1: mat[1][2]=1 -> count=1
  - i=2: mat[2][2]=1 -> count=1
  - count (1) > max0s (2) is FALSE.

Return ansCol = 0. ✓
*/
