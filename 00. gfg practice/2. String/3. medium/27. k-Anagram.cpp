/*
GeeksforGeeks: k-Anagram
Difficulty: Medium

Problem:
Two strings are called k-anagrams if:
1. Both have the same number of characters.
2. Two strings can become anagrams by changing at most k characters in one of the strings.

Given two strings s1 and s2 of lowercase alphabets and an integer value k,
find if they are k-anagrams of each other.

Examples:
Input: s1 = "fodr", s2 = "gork", k = 2
Output: true
Explanation: We can change 'f' -> 'g' and 'd' -> 'k' in s1.

Input: s1 = "geeks", s2 = "eggkf", k = 1
Output: false
Explanation: We can update or modify only 1 value but there is a need to modify 2 characters: 'g' and 'f' in s2.

Input: s1 = "adb", s2 = "fdab", k = 2
Output: false
Explanation: Both the strings have different numbers of characters.

Constraints:
1 <= s1.size(), s2.size() <= 10^5
1 <= k <= 10^5

Core Idea:
- If lengths of s1 and s2 are not equal, they can never be anagrams. In that case, return false.
- To find the minimum characters we need to change in s1 to make it an anagram of s2:
  - We can count the frequency of each character in both strings.
  - Let `diff` count how many characters present in s1 are in excess compared to s2.
  - Specifically, for each alphabet character c from 'a' to 'z':
    - If frequency in s1 > frequency in s2, then we need to change `freq1[c] - freq2[c]` characters of 'c' to match the missing characters in s2.
    - So, we sum `max(0, freq1[c] - freq2[c])` for all characters.
  - If this sum `diff` is less than or equal to k, we return true. Else, return false.

Approach:
1. If `s1.length() != s2.length()`, return false.
2. Initialize a frequency array of size 26 (initialized to 0).
3. We can use a single array `freq` to count relative frequencies:
   - For each character in `s1`, increment `freq[c - 'a']`.
   - For each character in `s2`, decrement `freq[c - 'a']`.
4. Traverse the `freq` array:
   - If `freq[i] > 0`, it means `s1` has `freq[i]` excess characters of character `i` compared to `s2`.
   - Sum these excess counts: `diff += freq[i]`.
5. Return `diff <= k`.

Time Complexity: O(N) where N is the length of strings s1 and s2. We do a single pass to count character frequencies.
Space Complexity: O(1) auxiliary space as we only use a fixed-size array of 26 integers.

GFG Link: https://www.geeksforgeeks.org/problems/check-if-two-strings-are-k-anagrams-or-not/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool areKAnagrams(string s1, string s2, int k) {
        // Step 1: Check if lengths match
        if (s1.length() != s2.length()) {
            return false;
        }
        
        // Step 2: Use a single frequency array to track relative character counts
        vector<int> freq(26, 0);
        
        for (int i = 0; i < s1.length(); i++) {
            freq[s1[i] - 'a']++;
            freq[s2[i] - 'a']--;
        }
        
        // Step 3: Count the excess characters in s1
        int diff = 0;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                diff += freq[i];
            }
        }
        
        // Step 4: Return whether we can balance the strings with at most k edits
        return diff <= k;
    }
};

/*
Dry Run — Example:
s1 = "fodr", s2 = "gork", k = 2
Length s1 = 4, Length s2 = 4. (Match!)

freq array relative counts:
- s1[0] = 'f' -> freq['f'] = 1
- s2[0] = 'g' -> freq['g'] = -1
- s1[1] = 'o' -> freq['o'] = 1
- s2[1] = 'o' -> freq['o'] = 0 (1 - 1)
- s1[2] = 'd' -> freq['d'] = 1
- s2[2] = 'r' -> freq['r'] = -1
- s1[3] = 'r' -> freq['r'] = 0 (-1 + 1)
- s2[3] = 'k' -> freq['k'] = -1

Final positive frequencies:
- freq['f'] = 1
- freq['d'] = 1
- Others <= 0

diff = freq['d'] + freq['f'] = 1 + 1 = 2.
Return diff <= k (2 <= 2) which is true.

Output: true
*/
