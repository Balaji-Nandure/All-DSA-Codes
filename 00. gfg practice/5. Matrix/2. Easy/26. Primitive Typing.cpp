/*
GeeksforGeeks: Primitive Typing
Difficulty: Easy

Problem:
Given a screen containing alphabets from a-z, we can go from one character to another character using a remote. 
The remote contains left, right, top and bottom keys.
Screen:
a b c d e
f g h i j
k l m n o
p q r s t
u v w x y
z

Find the minimum number of moves to type all characters of the given string `str` using the remote. 
The initial position is at 'a' (top left). Moving UP, DOWN, LEFT, RIGHT takes 1 move. 
Pressing OK to type the character also takes 1 move.

Example 1:
Input: str = "abc"
Output: 5
Explanation: 
- Remote's position is initially at 'a'.
- Type 'a': press OK (1 move).
- Move to 'b': 1 step RIGHT. Type 'b': press OK (1 move). Total for 'b' = 2 moves.
- Move to 'c': 1 step RIGHT. Type 'c': press OK (1 move). Total for 'c' = 2 moves.
Total moves = 1 + 2 + 2 = 5.

Example 2:
Input: str = "a"
Output: 1
Explanation: 
- Remote is initially at 'a'.
- Type 'a': press OK (1 move). Total = 1.

Core Idea:
The screen can be seen as a 2D grid where each character has a specific (row, column) coordinate.
Since the grid has 5 columns, for any character `ch`:
- `row = (ch - 'a') / 5`
- `col = (ch - 'a') % 5`
Because there are no obstacles in this grid (the missing cells next to 'z' don't block any shortest paths between valid characters), the minimum number of moves between any two characters is simply their Manhattan distance:
`|current_row - target_row| + |current_col - target_col|`.
For each character in the string, we add this distance plus `1` for the "OK" press, and then update our current position.

Approach:
1. Initialize `current_row = 0` and `current_col = 0` (since we start at 'a').
2. Initialize `total_moves = 0`.
3. Loop through each character `ch` in the string `str`.
4. Calculate the target coordinates: `target_row = (ch - 'a') / 5`, `target_col = (ch - 'a') % 5`.
5. Add the Manhattan distance `abs(current_row - target_row) + abs(current_col - target_col)` to `total_moves`.
6. Add `1` to `total_moves` for the "OK" press.
7. Update `current_row = target_row` and `current_col = target_col`.
8. Return `total_moves`.

Time Complexity : O(|str|) — We process each character of the string exactly once.
Space Complexity: O(1) — We only use a few integer variables.

GFG Link:
https://www.geeksforgeeks.org/problems/primitive-typing/1
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    int FindPath(string str) {
        int total_moves = 0;
        int current_row = 0;
        int current_col = 0;
        
        for (char ch : str) {
            // Calculate target coordinates on the 5-column grid
            int target_row = (ch - 'a') / 5;
            int target_col = (ch - 'a') % 5;
            
            // Add Manhattan distance and 1 for the 'OK' press
            total_moves += abs(current_row - target_row) + abs(current_col - target_col) + 1;
            
            // Update current position
            current_row = target_row;
            current_col = target_col;
        }
        
        return total_moves;
    }
};

/*
Dry Run — Example: str = "za"
Initial state: current_row = 0, current_col = 0, total_moves = 0

1. Character 'z':
   target_row = ('z' - 'a') / 5 = 25 / 5 = 5
   target_col = ('z' - 'a') % 5 = 25 % 5 = 0
   Manhattan distance = |0 - 5| + |0 - 0| = 5
   total_moves += 5 + 1 (OK) = 6
   current_row = 5, current_col = 0

2. Character 'a':
   target_row = ('a' - 'a') / 5 = 0
   target_col = ('a' - 'a') % 5 = 0
   Manhattan distance = |5 - 0| + |0 - 0| = 5
   total_moves += 5 + 1 (OK) = 12
   current_row = 0, current_col = 0

Final total_moves = 12. ✓
*/
