/*
Problem: String Duplicates Removal

Given a string s which may contain lowercase and uppercase characters. The task is to remove all duplicate characters from the string and find the resultant string. The order of remaining characters in the output should be same as in the original string.

Constraints:
1 <= N <= 10^6
String contains uppercase and lowercase english letters.

--------------------------------------------------

Pattern:
Hashing / Map

--------------------------------------------------

Key Observation:
- We need to remove duplicates while preserving the original order of characters.
- To achieve O(N) time complexity, we can use a hash map or a boolean array to keep track of characters we have already encountered.
- When traversing the string from left to right, we append a character to the result only if it hasn't been seen before.

--------------------------------------------------

Approach:
1. Initialize an empty string `ans` to store the result.
2. Initialize a boolean array `seen` of size 256 to `false` to keep track of visited ASCII characters (which acts as a fast map/set).
3. Iterate through each character `c` in the string `s`.
4. If `seen[c]` is false:
    a. Append `c` to `ans`.
    b. Mark `seen[c]` as true.
5. Return the resulting string `ans`.

--------------------------------------------------

Time Complexity: O(N) where N is the length of the string, as we do a single pass over the string.
Space Complexity: O(1) since the boolean array size is fixed at 256, strictly adhering to O(1) auxiliary space constraints.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/remove-duplicates3034/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string removeDuplicates(string str) {
        string ans = "";
        vector<bool> seen(256, false);
        
        for (char c : str) {
            if (!seen[c]) {
                ans += c;
                seen[c] = true;
            }
        }
        
        return ans;
    }
};
