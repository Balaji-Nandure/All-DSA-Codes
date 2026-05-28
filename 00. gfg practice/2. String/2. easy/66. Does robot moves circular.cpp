/*
Problem: Does robot moves circular

Given a sequence of moves for a robot. Check if the sequence is circular or not.
A sequence of moves is circular if the first and last positions of the robot are the same. A move can be one of the following :
    G - Go one unit
    L - Turn left
    R - Turn right

Constraints:
1 <= |path| <= 10^5

--------------------------------------------------

Pattern:
Simulation / Coordinate Geometry

--------------------------------------------------

Key Observation:
- We can simulate the robot's movement on a 2D Cartesian plane.
- The robot starts at origin (0, 0) and initially faces North.
- A direction variable can keep track of the current orientation:
  0: North (y+1)
  1: East  (x+1)
  2: South (y-1)
  3: West  (x-1)
- Turning Right ('R') increments the direction: `(dir + 1) % 4`.
- Turning Left ('L') decrements the direction: `(dir + 3) % 4`.
- Moving 'G' updates the (x, y) coordinates based on the current direction.
- After processing all moves, we check if the robot has returned exactly to (0, 0).

--------------------------------------------------

Approach:
1. Initialize `x = 0`, `y = 0` and `dir = 0` (facing North).
2. Iterate through each character `c` in the string `path`.
3. If `c == 'R'`, update `dir = (dir + 1) % 4`.
4. If `c == 'L'`, update `dir = (dir + 3) % 4`.
5. If `c == 'G'`, update `x` and `y` according to the current `dir`.
6. Finally, if `x == 0` and `y == 0`, return "Circular". Else, return "Not Circular".

--------------------------------------------------

Time Complexity: O(|S|) as we iterate through the sequence of moves exactly once.
Space Complexity: O(1) as we only use a few integer variables for coordinates and direction.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/does-robot-moves-circular0414/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string isCircular(string path) {
        int x = 0, y = 0;
        int dir = 0; // 0: North, 1: East, 2: South, 3: West
        
        for (char c : path) {
            if (c == 'R') {
                dir = (dir + 1) % 4;
            } else if (c == 'L') {
                dir = (dir + 3) % 4;
            } else if (c == 'G') {
                if (dir == 0) y++;
                else if (dir == 1) x++;
                else if (dir == 2) y--;
                else if (dir == 3) x--;
            }
        }
        
        if (x == 0 && y == 0) {
            return "Circular";
        }
        return "Not Circular";
    }
};
