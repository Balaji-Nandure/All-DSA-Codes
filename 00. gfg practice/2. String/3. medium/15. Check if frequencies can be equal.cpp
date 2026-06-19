/*
GeeksforGeeks: Check if frequencies can be equal
Difficulty: Medium

Problem:
Given a string s consisting only lowercase alphabetic characters, check whether it is possible to remove at most one character such that the frequency of each distinct character in the string becomes same. Return true if it is possible; otherwise, return false.

Examples:
Input: s = "xyyz"
Output: true 
Explanation: Removing one 'y' will make frequency of each distinct character to be 1.

Input: s = "xyyzz"
Output: true
Explanation: Removing one 'x' will make frequency of each distinct character to be 2.

Input: s = "xxxxyyzz"
Output: false
Explanation: Frequency can not be made same by removing at most one character.

Constraints:
1 <= s.size() <= 10^5

Core Idea:
Since the character set size is tiny (at most 26 lowercase English letters), we can check all possible removals:
1. Count the frequencies of all characters in the string.
2. If all non-zero frequencies are already equal, return `true`.
3. Otherwise, try removing exactly one occurrence of each character type one by one:
   - Decrement the character's frequency.
   - Check if all remaining non-zero frequencies are equal.
   - If they are, return `true`.
   - Restore (backtrack) the frequency of the character.
4. If no single character removal yields equal frequencies, return `false`.

Approach:
1. Maintain a frequency array of size 26 initialized to 0.
2. Fill the frequency array by scanning the string `s`.
3. Create a helper function `allSame(freq)` that returns true if all non-zero elements in the frequency array are equal.
4. Check `allSame(freq)`. If true, return `true`.
5. Loop `i` from 0 to 25:
   - If `freq[i] > 0`:
     - Decrement `freq[i]` by 1.
     - If `allSame(freq)` is true, return `true`.
     - Increment `freq[i]` by 1 (backtrack).
6. Return `false`.

Time Complexity: O(N) where N is the length of string `s`. Counting frequencies takes O(N) time, and checking the 26 character variations takes at most 26 * 26 operations, which is O(1).
Space Complexity: O(1) auxiliary space as the frequency array size is constant (26).

GFG Link: https://www.geeksforgeeks.org/problems/check-frequencies4211/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to check if all non-zero frequencies are equal
    bool allSame(const vector<int> &freq) {
        int commonFreq = -1;
        for (int f : freq) {
            if (f > 0) {
                if (commonFreq == -1) {
                    commonFreq = f;
                } else if (f != commonFreq) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool sameFreq(string s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Case 1: Already has same frequencies
        if (allSame(freq)) {
            return true;
        }
        
        // Case 2: Try removing one character of any type
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                freq[i]--; // Simulate removal
                if (allSame(freq)) {
                    return true;
                }
                freq[i]++; // Backtrack
            }
        }
        
        return false;
    }
};

/*
Dry Run — Example:
s = "xyyzz"

Initial frequencies:
x: 1, y: 2, z: 2

- Check allSame: commonFreq = 1, next is 2 (y) -> false
- i = 'x': freq['x'] becomes 0.
  - Remaining non-zero frequencies: y:2, z:2.
  - Check allSame: commonFreq = 2, next is 2 -> true.
  - Returns true.
Output: true
*/
