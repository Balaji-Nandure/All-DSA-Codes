/*
GeeksforGeeks: Unique rows in boolean matrix
Difficulty: Easy

Problem:
Given a binary matrix, your task is to find all unique rows of the given matrix 
in the order of their appearance in the matrix.

Example 1:
Input: 
mat[][] = [[1, 1, 0, 1], 
           [1, 0, 0, 1],
           [1, 1, 0, 1]]
Output: 
[[1, 1, 0, 1],
 [1, 0, 0, 1]]
Explanation:
The two unique rows are R1: [1 1 0 1] and R2: [1 0 0 1]. 
R1 first appeared at row-0 and R2 appeared at row-1. 
The third row is a duplicate of R1, so it is ignored.

Example 2:
Input: 
mat[][] = [[0, 0, 0, 1],
           [0, 0, 0, 1]]
Output: 
[[0, 0, 0, 1]]
Explanation: 
Only unique row is [0 0 0 1].

Core Idea:
We need to keep track of which rows we have already seen to avoid adding duplicates. 
Since C++ has a built-in `std::set` that can natively hash and compare `vector<int>`, 
we can use a `set<vector<int>>` to efficiently store and check for seen rows!

To ensure we return the unique rows strictly in the order they *first* appeared, 
we simply loop through the matrix from top to bottom. If the current row is NOT 
in our set, it means we are seeing it for the very first time. We can then add it 
to our `ans` array and insert it into our set to prevent future duplicates!

Approach:
1. Initialize an empty `set<vector<int>> seen` to track duplicates.
2. Initialize an empty `vector<vector<int>> ans` to store the unique rows in order.
3. Loop through each `row` in the matrix `mat`.
4. Check if `row` is in `seen`:
   - If not found: Push `row` into `ans`, and insert it into `seen`.
   - If found: Skip it.
5. Return `ans`.

Time Complexity : O(N * M * log(N)) — Where N is rows and M is cols. Set lookup takes O(log N) comparisons, and each comparison takes O(M) time to compare vectors.
Space Complexity: O(N * M) — To store the unique rows in the set and result array.

GFG Link:
https://www.geeksforgeeks.org/problems/unique-rows-in-boolean-matrix/1
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> uniqueRow(vector<vector<int>>& mat) {
        set<vector<int>> seen;
        vector<vector<int>> ans;
        
        // Iterate through each row in the matrix
        for (const auto& row : mat) {
            
            // If the row is not in our 'seen' set, it's unique (so far)
            if (seen.find(row) == seen.end()) {
                
                ans.push_back(row); // Add it to our answer array in order
                seen.insert(row);   // Mark it as seen
            }
        }
        
        return ans;
    }
};

/*
Dry Run — Example 1:
mat[][] = [[1, 1, 0, 1], 
           [1, 0, 0, 1],
           [1, 1, 0, 1]]

Initial:
seen = {}
ans = []

Iteration 1 (row = [1, 1, 0, 1]):
  - Not in `seen`.
  - ans becomes [[1, 1, 0, 1]]
  - seen becomes {[1, 1, 0, 1]}

Iteration 2 (row = [1, 0, 0, 1]):
  - Not in `seen`.
  - ans becomes [[1, 1, 0, 1], [1, 0, 0, 1]]
  - seen becomes {[1, 1, 0, 1], [1, 0, 0, 1]}

Iteration 3 (row = [1, 1, 0, 1]):
  - Found in `seen`! It's a duplicate.
  - Ignored.

Final Result:
[[1, 1, 0, 1], 
 [1, 0, 0, 1]]
✓ Matches expected output.
*/
