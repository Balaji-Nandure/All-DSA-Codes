/*
GeeksforGeeks: Wifi Range
Difficulty: Easy

There are n rooms in a straight line in Geekland State University's hostel. 
You are given a binary string s of length n, where s[i] = '1' means there is a WiFi router in the i-th room, 
and s[i] = '0' means there is no WiFi in that room.
Each WiFi router has a range of x, meaning it can cover up to x rooms to its left and x rooms to its right.
Given x and s, determine whether all rooms are covered by at least one WiFi router. 
Return true if all rooms are covered; otherwise, return false.

Example 1:
Input: x = 0, s = "010"
Output: false

Example 2:
Input: x = 1, s = "10010"
Output: truegeeksforgeeks
Search...
Courses
Tutorials
Practice
Jobs

12
N


Balanced Splits of a Binary String
Difficulty: EasyAccuracy: 50.02%Submissions: 31K+Points: 2
Given binary string s . find the maximum number of substrings it can be splitted into such that all substrings have equal number of 0s and 1s. If it is not possible to split s satisfying the conditions then return -1.

Examples:

Input: s = "0100110101"
Output: 4
Explanation: 
The required substrings are 01, 0011, 01 and 01.
Input: s = "0111100010"
Output: 3
Input: s = "0010"
Output: -1
Constraints:
1 ≤ s.length ≤ 105

Expected Complexities
Topic Tags
Related Articles
If you are facing any issue on this page. Please let us know.
C++ (17)



        



Custom Input


Constraints:
1 <= n <= 10^5
0 <= x <= 10^5
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
     * Problem: Wifi Range
     * 
     * Determine if all rooms are covered by at least one WiFi router.
     * Each router has range X (covers i - X to i + X).
     * 
     * Time Complexity: O(N) - single pass scan
     * Space Complexity: O(1) - constant auxiliary space
     */
    bool wifiRange(int N, string S, int X) {
        // maxReach tracks the index of the rightmost room covered so far
        int maxReach = -1;
        
        for (int i = 0; i < N; i++) {
            if (S[i] == '1') {
                // The current router covers rooms starting from i - X.
                // The rooms up to i - X - 1 must have been covered by previous routers.
                // If the rightmost room covered so far is less than i - X - 1, 
                // there is a gap that can never be covered.
                if (i - X - 1 > maxReach) {
                    return false;
                }
                
                // Update the rightmost room covered by this router (i + X)
                maxReach = max(maxReach, i + X);
            }
        }
        
        // After checking all routers, ensure the last room (N - 1) is covered
        return maxReach >= N - 1;
    }
};

/*
Approach: Greedy Range Extension
- We traverse the hostel rooms from left to right.
- We maintain a variable `maxReach` initialized to -1, which represents the rightmost room covered so far.
- When we find a router at index `i` (S[i] == '1'):
  - The leftmost room this router covers is `i - X`.
  - The rooms to the left of `i - X` must be covered by previous routers. So `maxReach` must be at least `i - X - 1`.
  - If `i - X - 1 > maxReach`, it means there's an uncovered gap between `maxReach` and `i - X`. Since we process from left to right, no future router can cover this gap. Thus, we return false.
  - Otherwise, we update `maxReach` to be the maximum of its current value and the rightmost room this router covers, which is `i + X`.
- After scanning the entire string, we verify if the last room (index N - 1) is covered by checking if `maxReach >= N - 1`.

Complexity:
- Time Complexity: O(N) since we iterate through the string of length N exactly once.
- Space Complexity: O(1) auxiliary space as we only use a single variable `maxReach` to keep track of coverage.
*/
