/*
GeeksforGeeks: Trace Path
Difficulty: Easy

Problem:
There is a rectangular path for a Train to travel consisting of n rows and m columns. 
The train will start from one of the grid's cells and it will be given a command 
in the form of string s consisting of characters L, R, D, U. 
Find if it is possible to travel the train inside the grid only.

Commands:
- 'L': goes to (i, j - 1)
- 'R': goes to (i, j + 1)
- 'D': goes to (i - 1, j)
- 'U': goes to (i + 1, j)

Return 1 if there is such a cell for which the train always remains inside the grid. 
Otherwise return 0.

Example 1:
Input: 
n = 1, m = 1
s = "R"
Output: 0
Explanation: 
There is only one cell (1,1). On taking right(R) train moves to (1,2), which is 
out of grid. Therefore, no cell works.

Example 2:
Input: 
n = 2, m = 3
s = "LLRU"
Output: 1
Explanation: 
One possible starting cell is (1,3).
(1,3) --> L --> (1,2) --> L --> (1,1) --> R --> (1,2) --> U --> (2,2). 
The train remains inside the grid throughout tracing the route.

Core Idea:
Instead of trying every possible starting cell (which would be too slow), we can 
just simulate the path starting from an imaginary origin `(0, 0)`.
As we process the string and move around, we keep track of the maximum and 
minimum row and column we visit. This effectively calculates the "Bounding Box" 
of the path!

If at any point during the simulation, the height of our bounding box 
(`max_row - min_row + 1`) exceeds `n`, or the width of our bounding box 
(`max_col - min_col + 1`) exceeds `m`, it means the path is physically too large 
to fit inside the `n x m` grid, no matter where we start!

If we finish processing the string and the bounding box fits, then we can definitely 
slide this bounding box to fit inside the `n x m` grid, making it possible!

Approach:
1. Initialize `min_r = 0, max_r = 0, min_c = 0, max_c = 0`.
2. Initialize current position `r = 0, c = 0`.
3. Iterate through each character `ch` in the string `s`:
   - If `ch == 'L'`, `c--`.
   - If `ch == 'R'`, `c++`.
   - If `ch == 'D'`, `r--`.
   - If `ch == 'U'`, `r++`.
   - Update bounds: `min_r = min(min_r, r)`, `max_r = max(max_r, r)`, etc.
   - If `max_r - min_r >= n` OR `max_c - min_c >= m`, return `0`.
4. If the loop completes successfully, return `1`.

Time Complexity : O(|s|) — We iterate through the string of commands exactly once.
Space Complexity: O(1) — We only store a few integer variables.

GFG Link:
https://www.geeksforgeeks.org/problems/trace-path3840/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
   int isPossible(int n, int m, string s) {
      // Track the current position relative to an imaginary (0, 0) starting point
      int r = 0, c = 0;
      
      // Track the bounding box dimensions of the path
      int min_r = 0, max_r = 0;
      int min_c = 0, max_c = 0;
      
      for (char ch : s) {
         if (ch == 'L') c--;
         else if (ch == 'R') c++;
         else if (ch == 'D') r--;
         else if (ch == 'U') r++;
         
         // Expand the bounding box if we visited a new extreme
         min_r = min(min_r, r);
         max_r = max(max_r, r);
         min_c = min(min_c, c);
         max_c = max(max_c, c);
         
         // Note: max_r - min_r is the distance. 
         // The number of cells covered is max_r - min_r + 1.
         // If cells covered > n, then distance >= n.
         if (max_r - min_r >= n || max_c - min_c >= m) {
            return 0; // The path bounding box is too big to fit in the grid
         }
      }
      
      return 1; // The path fits!
   }
};

/*
Dry Run — Example 2:
n = 2, m = 3
s = "LLRU"

Initial: r=0, c=0, min_r=0, max_r=0, min_c=0, max_c=0

1. 'L': c = -1
   min_c = -1. 
   Height: 0 - 0 = 0 < 2
   Width:  0 - (-1) = 1 < 3

2. 'L': c = -2
   min_c = -2.
   Width:  0 - (-2) = 2 < 3

3. 'R': c = -1
   max_c stays 0, min_c stays -2.
   Width: 2 < 3

4. 'U': r = 1
   max_r = 1.
   Height: 1 - 0 = 1 < 2

Loop completes. Max height difference is 1 (fits in 2). Max width difference is 2 (fits in 3).
Returns 1. ✓
*/
