/*
GeeksforGeeks: Repeating Character
Difficulty: Easy

Given a string s, return the index of the first character that appears more than once in the string. If there is no repeated character, return -1.

Examples:

Input: s = "geeksforgeeks"
Output: 0
Explanation: We see that both 'e' and 'g' repeat as we move from left to right. But the leftmost is 'g' so we return leftmost index of 'g' that is 0.

Input: s = "abcd"
Output: -1
Explanation: No character repeats so we return -1.

Constraints:
1 <= |s| <= 10^5
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * Problem: Repeating Character
     * 
     * Find the index of the first character that appears more than once in the string.
     * 
     * Time Complexity: O(N) - two passes over the string
     * Space Complexity: O(1) - constant space for frequency array
     */
    int firstRepeating(string s) {
        vector<int> freq(256, 0);
        
        // Count frequencies of each character
        for (char c : s) {
            freq[c]++;
        }
        
        // Find the first character with frequency > 1
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i]] > 1) {
                return i;
            }
        }
        
        return -1;
    }
};

/*
Approach: Frequency Counting
- We need to find the first character in the string (from left to right) that occurs more than once overall.
- We can solve this efficiently by using an array to keep track of the frequency of each character.
- First Pass: Iterate through the string and count the frequency of each character using an integer array of size 256 (to cover all ASCII characters safely).
- Second Pass: Iterate through the string again from left to right. For each character, check its frequency in the array. 
- The first character we encounter with a frequency greater than 1 is our answer, and we return its index.
- If the loop finishes without finding any character with frequency > 1, it means no character repeats, so we return -1.

Complexity:
- Time Complexity: O(N) where N is the length of the string. We make exactly two passes through the string.
- Space Complexity: O(1) auxiliary space, as the frequency array requires a fixed size of 256 integers regardless of the string length.
*/
