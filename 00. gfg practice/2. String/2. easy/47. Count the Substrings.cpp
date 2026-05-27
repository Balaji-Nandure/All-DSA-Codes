/*
Problem: Count the Substrings

Given a string S. The task is to count the number of substrings which contains equal number of lowercase and uppercase letters. 

Example 1:
Input:
S = "gEEk"
Output: 3
Explanation: There are 3 substrings of the given string which satisfy the condition. They are "gE", "gEEk" and "Ek".

Example 2:
Input:
S = "WomensDAY"
Output: 4
Explanation: There are 4 substrings of the given string which satisfy the condition. They are "Wo", "ensDAY", "nsDA" and "sD"

Constraints:
1 <= |S| <= 10^3

--------------------------------------------------

Pattern:
String Processing + Nested Loops (Running Count)

--------------------------------------------------

Key Observation:
- We need to find the number of substrings with an equal count of uppercase and lowercase letters.
- Since the expected time complexity is O(N^2) and space complexity is O(1), we can just iterate through all possible starting points `i` of substrings.
- For each starting point `i`, we expand the substring by iterating the end point `j` from `i` to `N-1`.
- While expanding, we maintain a running count of uppercase and lowercase characters.
- If at any point the counts are equal, we increment our answer counter.

Note: An O(N) time and O(N) space solution is also possible using a hash map and prefix sums (treating uppercase as +1 and lowercase as -1), but O(N^2) time with O(1) space strictly satisfies the expected auxiliary space constraints.

--------------------------------------------------

Approach:
1. Initialize an `ans` variable to 0.
2. Iterate `i` from 0 to N-1 (representing the start index of the substring).
3. Inside the loop, initialize `u` (uppercase count) and `l` (lowercase count) to 0.
4. Iterate `j` from `i` to N-1 (representing the end index).
5. If `S[j]` is uppercase, increment `u`, else increment `l`.
6. If `u == l`, increment `ans`.
7. Return `ans` at the end.

--------------------------------------------------

Time Complexity: O(N^2)
Space Complexity: O(1) Auxiliary Space

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/count-the-substrings2527/1
*/

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int countSubstring(string S) {
        int ans = 0;
        int n = S.length();
        
        for (int i = 0; i < n; i++) {
            int u = 0; // uppercase count
            int l = 0; // lowercase count
            
            for (int j = i; j < n; j++) {
                // Check if the character is uppercase
                if (S[j] >= 'A' && S[j] <= 'Z') {
                    u++;
                } else { // Otherwise it must be lowercase
                    l++;
                }
                
                // If counts are perfectly balanced
                if (u == l) {
                    ans++;
                }
            }
        }
        
        return ans;
    }
};
