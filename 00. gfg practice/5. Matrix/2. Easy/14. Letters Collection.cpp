/*
GeeksforGeeks: Letters Collection
Difficulty: Easy

Problem:
The Postmaster wants to write a program to answer queries regarding letter 
collection in a city. A city is represented as a matrix mat of size n*m. 
Each cell represents a house and contains a number of letters.
The program should answer q queries of the following types:
- 1 i j : Sum all letters exactly at a 1-hop distance from (i,j)
- 2 i j : Sum all letters exactly at a 2-hop distance from (i,j)

A 1-hop distance is the 8 immediate surrounding neighbors (like a King in chess).
A 2-hop distance is the 16 surrounding neighbors that form the outer boundary 
ring of a 5x5 square centered at (i,j).

Example 1:
Input: 
n = 4, m = 5
mat = {{1, 2, 3, 4, 10}, 
       {5, 6, 7, 8, 10}, 
       {9, 1, 3, 4, 10}, 
       {1, 2, 3, 4, 10}}
q = 2
queries = {{1, 0, 1}, 
           {2, 0, 1}}
Output: [22, 29]
Explanation: 
- Query 1 (hop=1 from 0,1): Sum is 1(0,0) + 3(0,2) + 5(1,0) + 6(1,1) + 7(1,2) = 22. 
- Query 2 (hop=2 from 0,1): Sum is 9(2,0) + 1(2,1) + 3(2,2) + 4(2,3) + 8(1,3) + 4(0,3) = 29.

Core Idea:
This problem asks us to find the sum of elements on the "boundary" of a square 
centered at `(i, j)` with a radius of `hop`.
In mathematical terms, this distance is known as the **Chebyshev Distance**.
For a given `hop` (distance `d`), the cells `(ni, nj)` that are exactly `d` hops 
away are those where `max(abs(ni - i), abs(nj - j)) == d`.

This gives us a beautiful algorithm: 
Instead of hardcoding 8 or 16 direction vectors, we can just run two loops for 
the row offsets `dr` and col offsets `dc` ranging from `-hop` to `+hop`.
We know a cell is exactly on the boundary ring if either `abs(dr) == hop` OR 
`abs(dc) == hop`! 
If it is, we just add it to our sum (provided it doesn't fall outside the matrix).

Approach:
1. Loop through each query to extract `hop`, `r`, and `c`.
2. Initialize `sum = 0`.
3. Loop `dr` from `-hop` to `+hop`.
4. Loop `dc` from `-hop` to `+hop`.
5. Check if the current offset is strictly on the boundary: 
   `if (abs(dr) == hop || abs(dc) == hop)`
6. Calculate neighbor coordinates: `ni = r + dr`, `nj = c + dc`.
7. If `(ni, nj)` is within bounds (`ni >= 0 && ni < n`, etc.), add `mat[ni][nj]` to `sum`.
8. Push `sum` to our answer vector and return it at the end.

Time Complexity : O(Q) — For each query, we check at most 25 cells (for hop=2). This acts as a constant O(1), making total time O(Q).
Space Complexity: O(Q) — To store the answer array. O(1) auxiliary space.

GFG Link:
https://www.geeksforgeeks.org/problems/letters-collection4559/1
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> matrixSum(int n, int m, vector<vector<int>> mat, int q, vector<int> queries[]) {
        vector<int> ans;
        
        for (int k = 0; k < q; k++) {
            int hop = queries[k][0];
            int r = queries[k][1];
            int c = queries[k][2];
            
            int sum = 0;
            
            // Loop through a square centered at (r, c) with radius 'hop'
            for (int dr = -hop; dr <= hop; dr++) {
                for (int dc = -hop; dc <= hop; dc++) {
                    
                    // We only want the OUTER RING (the exact 'hop' boundary).
                    // An element is on the outer ring if its row OR col offset is exactly 'hop'.
                    if (abs(dr) == hop || abs(dc) == hop) {
                        
                        int ni = r + dr;
                        int nj = c + dc;
                        
                        // Ensure the neighbor is within the matrix bounds
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            sum += mat[ni][nj];
                        }
                    }
                }
            }
            
            ans.push_back(sum);
        }
        
        return ans;
    }
};

/*
Dry Run — Query 2 (hop=2, r=0, c=1):
Outer ring of radius 2:

dr = -2: abs(dr)==2 -> Checks all dc from -2 to 2 (Top edge)
dr = -1: abs(dr)!=2 -> Checks ONLY dc=-2 and dc=2 (Left & Right edges)
dr =  0: abs(dr)!=2 -> Checks ONLY dc=-2 and dc=2 (Left & Right edges)
dr =  1: abs(dr)!=2 -> Checks ONLY dc=-2 and dc=2 (Left & Right edges)
dr =  2: abs(dr)==2 -> Checks all dc from -2 to 2 (Bottom edge)

This elegantly and automatically selects exactly the 16 cells that make up 
the 2-hop boundary! Valid ones are summed up perfectly. ✓
*/
