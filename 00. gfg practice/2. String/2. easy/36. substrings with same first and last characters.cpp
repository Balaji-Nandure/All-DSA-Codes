/*
GeeksforGeeks: Substrings with same first and last characters
Difficulty: Easy

Given a string s consisting of lowercase characters, the task is to find the count of all substrings that start and end with the same character.

Examples:

Input: s = "abcab"
Output: 7
Explanation: There are 7 substrings where the first and last characters are the same: "a", "abca", "b", "bcab", "c", "a", and "b"

Input: s = "aba"
Output: 4
Explanation: There are 4 substrings where the first and last characters are the same: "a", "aba", "b", "a"

Constraints:
1 <= |s| <= 10^4
s contains lower case english alphabets
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * Problem: Substrings with same first and last characters
     * 
     * Find the count of all substrings that start and end with the same character.
     * 
     * Time Complexity: O(N) - single pass counting frequencies
     * Space Complexity: O(1) - constant auxiliary space (size 26 vector)
     */
    int countSubstringWithSameEnds(string s) {
        vector<int> freq(26, 0);
        
        // Count frequencies of each lowercase English character
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        int count = 0;
        // For each character with frequency f, it contributes f * (f + 1) / 2 substrings
        for (int i = 0; i < 26; i++) {
            int f = freq[i];
            count += (f * (f + 1)) / 2;
        }
        
        return count;
    }
};


// This is also correct
class Solution2 {
  public:
    int countSubstring(string &s) {
        // code here
        vector<int> freq(26, 0);
        int ans = 0; 
        for(char ch: s) {
            freq[ch - 'a']++;
            ans += (freq[ch - 'a']);
        }
        
        return ans;
        
    }
};

/*
Approach: Frequency Counting & Combinatorics
- Let a character `c` appear `f` times in the string `s`.
- Any substring starting and ending with `c` is uniquely defined by choosing two occurrences of `c` (a start index and an end index, where the start index <= end index).
- Choosing two distinct occurrences of `c` gives us the substrings of length > 1:
  Number of ways = f * (f - 1) / 2
- Choosing the same occurrence of `c` for both start and end gives us the substrings of length 1 (individual characters):
  Number of ways = f
- Adding these two terms together:
  f * (f - 1) / 2 + f = f * (f + 1) / 2
- Thus, we can compute the answer in a single pass:
  1. Record the frequency of all 26 lowercase English letters.
  2. For each character, add its contribution `f * (f + 1) / 2` to the total count.
  3. Return the total count.

Complexity:
- Time Complexity: O(N) where N is the length of the string `s`, since we traverse the string once to count frequencies.
- Space Complexity: O(1) auxiliary space, because our frequency array has a fixed size of 26.
*/
