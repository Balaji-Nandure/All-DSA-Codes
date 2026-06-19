/*
GeeksforGeeks: Substrings with K Distinct
Difficulty: Medium

Problem:
You are given a string s consisting of lowercase characters and an integer k. You have to count all possible substrings that have exactly k distinct characters.

Examples:
Input: s = "abc", k = 2
Output: 2
Explanation: Possible substrings are ["ab", "bc"]

Input: s = "aba", k = 2
Output: 3
Explanation: Possible substrings are ["ab", "ba", "aba"]

Input: s = "aa", k = 1
Output: 3
Explanation: Possible substrings are ["a", "a", "aa"]

Constraints:
1 <= s.size() <= 10^6
1 <= k <= 26

Core Idea:
Counting substrings with *exactly* k distinct characters directly with a sliding window is challenging because shrinking the window doesn't naturally keep the distinct count at exactly k.
However, we can reformulate the problem:
`exactly(k) = atMost(k) - atMost(k - 1)`
where `atMost(k)` returns the count of substrings containing at most `k` distinct characters.
Since both `atMost(k)` and `atMost(k - 1)` can be easily computed in O(N) using standard sliding window with two pointers, we can find the exact count in linear time.

Approach:
1. Helper function `atMostK(s, k)`:
   - If `k <= 0`, return 0.
   - Use two pointers, `left` and `right`.
   - Maintain a frequency array of size 26 for lowercase characters.
   - Keep a count of distinct characters currently in the window.
   - Expand the window by moving `right` from `0` to `N-1`.
   - If a character's frequency becomes 1, increment `distinctCount`.
   - If `distinctCount > k`, shrink the window from `left` by decrementing frequencies and `distinctCount` until `distinctCount <= k`.
   - Add the number of valid substrings ending at `right` to the total count: `count += (right - left + 1)`.
2. Return `atMostK(s, k) - atMostK(s, k - 1)`.

Time Complexity: O(N) since both `atMostK(s, k)` and `atMostK(s, k - 1)` process the string of length N in a single pass.
Space Complexity: O(1) auxiliary space as the frequency array is of constant size 26.

GFG Link: https://www.geeksforgeeks.org/problems/substrings-with-k-distinct-characters2859/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    long long int atMostK(string &s, int k) {
        if (k <= 0) return 0;
        
        int n = s.length();
        long long int count = 0;
        int left = 0;
        vector<int> freq(26, 0);
        int distinctCount = 0;
        
        for (int right = 0; right < n; right++) {
            // Include s[right] in the window
            if (freq[s[right] - 'a'] == 0) {
                distinctCount++;
            }
            freq[s[right] - 'a']++;
            
            // Shrink the window if distinct characters exceed k
            while (distinctCount > k) {
                freq[s[left] - 'a']--;
                if (freq[s[left] - 'a'] == 0) {
                    distinctCount--;
                }
                left++;
            }
            
            // All substrings starting from index 'left' up to 'right' ending at 'right'
            // have at most k distinct characters
            count += (right - left + 1);
        }
        
        return count;
    }

public:
    long long int substrCount(string s, int k) {
        return atMostK(s, k) - atMostK(s, k - 1);
    }
};

/*
Dry Run — Example:
s = "aba", k = 2

Calculating atMostK(s, 2):
- right = 0: s[0] = 'a', freq['a'] = 1, distinctCount = 1 <= 2. count += 0 - 0 + 1 = 1.
- right = 1: s[1] = 'b', freq['b'] = 1, distinctCount = 2 <= 2. count += 1 - 0 + 1 = 2 (Total = 3).
- right = 2: s[2] = 'a', freq['a'] = 2, distinctCount = 2 <= 2. count += 2 - 0 + 1 = 3 (Total = 6).
atMostK(s, 2) = 6

Calculating atMostK(s, 1):
- right = 0: s[0] = 'a', freq['a'] = 1, distinctCount = 1 <= 1. count += 0 - 0 + 1 = 1.
- right = 1: s[1] = 'b', freq['b'] = 1, distinctCount = 2 > 1. 
             Shrink: freq['a'] = 0, distinctCount = 1, left = 1. count += 1 - 1 + 1 = 1 (Total = 2).
- right = 2: s[2] = 'a', freq['a'] = 1, distinctCount = 2 > 1. 
             Shrink: freq['b'] = 0, distinctCount = 1, left = 2. count += 2 - 2 + 1 = 1 (Total = 3).
atMostK(s, 1) = 3

Result:
substrCount("aba", 2) = atMostK(s, 2) - atMostK(s, 1) = 6 - 3 = 3.
*/
