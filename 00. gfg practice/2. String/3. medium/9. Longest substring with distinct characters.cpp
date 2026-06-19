/*
GeeksforGeeks: Longest substring with distinct characters
Difficulty: Medium

Problem:
Given a string s, find the length of the longest substring with all distinct characters.

Examples:
Input: s = "geeksforgeeks"
Output: 7
Explanation: "eksforg" is the longest substring with all distinct characters.

Input: s = "aaa"
Output: 1
Explanation: "a" is the longest substring with all distinct characters.

Input: s = "abcdefabcbb"
Output: 6
Explanation: The longest substring with all distinct characters is "abcdef", which has a length of 6.

Constraints:
1 <= s.size() <= 10^5
s consists of lowercase English letters.

Core Idea:
This problem can be solved optimally using the sliding window (two-pointer) technique:
- We maintain a window `[left, right]` of characters containing only unique characters.
- To do this efficiently, we keep track of the last seen index of each character in an array/vector (e.g., `lastSeen` of size 256, initialized to -1).
- As we expand the window by moving `right` from `0` to `N - 1`:
  - If we see a character `s[right]` that we have seen before within our current window (i.e., `lastSeen[s[right]] >= left`), we must shrink the window from the left by setting `left = lastSeen[s[right]] + 1`.
  - Update the last seen index of `s[right]` to `right`.
  - Update our maximum length found so far: `maxLen = max(maxLen, right - left + 1)`.

Approach:
1. Initialize `lastSeen` array of size 256 with `-1`.
2. Initialize `left = 0` and `maxLen = 0`.
3. Loop `right` from `0` to `n - 1`:
   - If `lastSeen[s[right]] >= left`, update `left = lastSeen[s[right]] + 1`.
   - Update `lastSeen[s[right]] = right`.
   - Update `maxLen = max(maxLen, right - left + 1)`.
4. Return `maxLen`.

Time Complexity: O(N) since we traverse the string of length N exactly once with the `right` pointer.
Space Complexity: O(1) auxiliary space as the `lastSeen` table uses a constant size of 256.

GFG Link: https://www.geeksforgeeks.org/problems/longest-distinct-characters-in-string5848/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestUniqueSubstr(string s) {
        vector<int> lastSeen(256, -1);
        int left = 0;
        int maxLen = 0;
        int n = s.length();
        
        for (int right = 0; right < n; right++) {
            // If the character is already present in the current window,
            // shift the left boundary past the previous occurrence of s[right]
            if (lastSeen[s[right]] >= left) {
                left = lastSeen[s[right]] + 1;
            }
            
            // Record the current index as the last seen index of s[right]
            lastSeen[s[right]] = right;
            
            // Update the maximum length of unique substring
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};

/*
Dry Run — Example:
s = "geeksforgeeks"

- right = 0, s[0] = 'g': lastSeen['g'] = -1 < left (0) -> lastSeen['g'] = 0, maxLen = max(0, 0-0+1) = 1
- right = 1, s[1] = 'e': lastSeen['e'] = -1 < left (0) -> lastSeen['e'] = 1, maxLen = max(1, 1-0+1) = 2
- right = 2, s[2] = 'e': lastSeen['e'] = 1 >= left (0) -> left = 2, lastSeen['e'] = 2, maxLen = max(2, 2-2+1) = 2
- right = 3, s[3] = 'k': lastSeen['k'] = -1 < left (2) -> lastSeen['k'] = 3, maxLen = max(2, 3-2+1) = 2
- right = 4, s[4] = 's': lastSeen['s'] = -1 < left (2) -> lastSeen['s'] = 4, maxLen = max(2, 4-2+1) = 3
- right = 5, s[5] = 'f': lastSeen['f'] = -1 < left (2) -> lastSeen['f'] = 5, maxLen = max(3, 5-2+1) = 4
- right = 6, s[6] = 'o': lastSeen['o'] = -1 < left (2) -> lastSeen['o'] = 6, maxLen = max(4, 6-2+1) = 5
- right = 7, s[7] = 'r': lastSeen['r'] = -1 < left (2) -> lastSeen['r'] = 7, maxLen = max(5, 7-2+1) = 6
- right = 8, s[8] = 'g': lastSeen['g'] = 0 < left (2)  -> lastSeen['g'] = 8, maxLen = max(6, 8-2+1) = 7
- right = 9, s[9] = 'e': lastSeen['e'] = 2 >= left (2) -> left = 3, lastSeen['e'] = 9, maxLen = max(7, 9-3+1) = 7
- right = 10, s[10] = 'k': lastSeen['k'] = 3 >= left (3) -> left = 4, lastSeen['k'] = 10, maxLen = max(7, 10-4+1) = 7
- right = 11, s[11] = 's': lastSeen['s'] = 4 >= left (4) -> left = 5, lastSeen['s'] = 11, maxLen = max(7, 11-5+1) = 7

Final Output: 7
*/
