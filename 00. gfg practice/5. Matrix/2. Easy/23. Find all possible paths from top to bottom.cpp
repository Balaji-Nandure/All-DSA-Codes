/*
GeeksforGeeks: Find all possible paths from top to bottom
Difficulty: Easy

Problem:
Given a n x m matrix mat[][]. Your task is to find and return all possible paths from the top-left cell (0, 0) to the bottom-right cell (n-1, m-1).
From each cell, you can move only in the following two directions:
- Right -> (i, j+1)
- Down -> (i+1, j)
Return all possible paths, where each path is represented as a list of matrix elements encountered along the path.

Example 1:
Input: 
mat[][] = [[1, 2, 3],
           [4, 5, 6]]
Output: [[1, 4, 5, 6],
         [1, 2, 5, 6], 
         [1, 2, 3, 6]]
Explanation: We can see that there are 3 paths from the cell (0,0) to (1,2).

Core Idea:
To find all possible paths, we can use Depth First Search (DFS) with Backtracking. 
We start at the top-left corner (0, 0). At any cell (i, j), we first try moving Down (i+1, j) and then Right (i, j+1). 
We maintain a current `path` array. When we reach the bottom-right cell (n-1, m-1), we add the current `path` to our result list. 
After exploring all paths from a cell, we backtrack (remove the cell from our `path`) so that it can be used for other paths.

Approach:
1. Create a `result` list of lists and a `path` list.
2. Define a recursive `dfs(i, j)` function.
3. Base cases: If `i >= n` or `j >= m`, we are out of bounds, so return.
4. Add the current element `grid[i][j]` to `path`.
5. If `i == n-1` and `j == m-1`, we reached the destination. Add a copy of `path` to `result`.
6. Otherwise, recursively call `dfs(i + 1, j)` for the Down direction, and then `dfs(i, j + 1)` for the Right direction. (Exploring Down first matches the expected lexicographical output in the examples).
7. After the recursive calls, remove the last element from `path` (backtrack).
8. Start the DFS from `(0, 0)` and return the `result`.

Time Complexity : O(2^(N+M)) — In the worst-case, the number of paths is mathematically (N+M-2) C (N-1). For each path, we take O(N+M) time to copy it to the result array.
Space Complexity: O(N+M) — Auxiliary space for the recursion stack and the `path` list. (Excluding the space required to store the final output).

GFG Link:
https://www.geeksforgeeks.org/problems/find-all-possible-paths-from-top-to-bottom/1
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    void dfs(int i, int j, int n, int m, vector<vector<int>>& grid, vector<int>& path, vector<vector<int>>& result) {
        // Base case: out of bounds
        if (i >= n || j >= m) {
            return;
        }
        
        // Add current cell to path
        path.push_back(grid[i][j]);
        
        // If we reached the bottom-right cell
        if (i == n - 1 && j == m - 1) {
            result.push_back(path);
        } else {
            // Explore Down first
            dfs(i + 1, j, n, m, grid, path, result);
            // Explore Right next
            dfs(i, j + 1, n, m, grid, path, result);
        }
        
        // Backtrack: remove the current cell before returning to the previous caller
        path.pop_back();
    }

public:
    vector<vector<int>> findAllPossiblePaths(int n, int m, vector<vector<int>>& grid) {
        vector<vector<int>> result;
        vector<int> path;
        
        dfs(0, 0, n, m, grid, path, result);
        
        return result;
    }
};

/*
Dry Run — Example 1:
Input: 
mat = [
  [1, 2, 3],
  [4, 5, 6]
]
n = 2, m = 3

Start DFS at (0, 0): path = [1]
  -> Move Down to (1, 0): path = [1, 4]
    -> Move Down to (2, 0): out of bounds, return.
    -> Move Right to (1, 1): path = [1, 4, 5]
      -> Move Down to (2, 1): out of bounds, return.
      -> Move Right to (1, 2): path = [1, 4, 5, 6]. Reached destination! Add to result.
      -> Backtrack to (1, 1): path = [1, 4, 5]
    -> Backtrack to (1, 0): path = [1, 4]
  -> Backtrack to (0, 0): path = [1]
  
  -> Move Right to (0, 1): path = [1, 2]
    -> Move Down to (1, 1): path = [1, 2, 5]
      -> Move Down to (2, 1): out of bounds.
      -> Move Right to (1, 2): path = [1, 2, 5, 6]. Reached destination! Add to result.
      -> Backtrack to (1, 1)
    -> Backtrack to (0, 1): path = [1, 2]
    
    -> Move Right to (0, 2): path = [1, 2, 3]
      -> Move Down to (1, 2): path = [1, 2, 3, 6]. Reached destination! Add to result.
      -> Backtrack to (0, 2)
  -> Backtrack to (0, 0).

Done! 
Result: [[1, 4, 5, 6], [1, 2, 5, 6], [1, 2, 3, 6]]
*/
