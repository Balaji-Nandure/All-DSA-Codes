/*
GeeksforGeeks: Longest Substring with K Uniques
Difficulty: Medium

Problem:
You are given a string s consisting only lowercase alphabets and an integer k. Your task is to find the length of the longest substring that contains exactly k distinct characters.
Note : If no such substring exists, return -1. 

Examples:
Input: s = "aabacbebebe", k = 3
Output: 7
Explanation: The longest substring with exactly 3 distinct characters is "cbebebe", which includes 'c', 'b', and 'e'.

Input: s = "aaaa", k = 2
Output: -1
Explanation: There's no substring with 2 distinct characters.

Input: s = "aabaaab", k = 2
Output: 7
Explanation: The entire string "aabaaab" has exactly 2 unique characters 'a' and 'b', making it the longest valid substring.

Core Idea:
This is the quintessential Sliding Window (Two-Pointer) problem.
We can maintain a dynamic window `[l, r]` and use a frequency array to keep track of the characters currently inside the window. We also maintain a running count of `unique_count`.
As we actively expand our window by pushing `r` to the right:
- If we encounter a brand new character (frequency was 0), we increment `unique_count`.
- If `unique_count` exactly equals `k`, we have a valid window! We calculate the window length (`r - l + 1`) and potentially update our `max_len`.
- If `unique_count` strictly exceeds `k`, our window has become invalid. We must aggressively shrink it by moving our left pointer `l` forward and decrementing character frequencies until a character's frequency hits 0 (meaning `unique_count` drops back down to exactly `k`).

Approach:
1. Initialize a `vector<int> freq(26, 0)` to track alphabet counts (preferred over map for extreme O(1) performance).
2. Set `l = 0`, `max_len = -1`, and `unique_count = 0`.
3. Loop `r` through the string `s`:
   - Increment `freq[s[r] - 'a']`. If it goes from 0 to 1, increment `unique_count`.
   - While `unique_count > k`:
     - Decrement `freq[s[l] - 'a']`. 
     - If it drops to 0, decrement `unique_count`.
     - Increment `l`.
   - If `unique_count == k`, update `max_len = max(max_len, r - l + 1)`.
4. Return `max_len`.

Time Complexity: O(N) where N is the length of the string. Both `l` and `r` pointers only ever move forward, meaning they traverse the string at most once.
Space Complexity: O(1) auxiliary space, as the frequency vector always strictly requires 26 slots regardless of how massive the string gets.

GFG Link: https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestKSubstr(string s, int k) {
        // Direct-access frequency map (significantly faster than unordered_map)
        vector<int> freq(26, 0); 
        int l = 0;
        int max_len = -1;
        int unique_count = 0;
        
        for (int r = 0; r < s.length(); r++) {
            // Add right character to the window
            if (freq[s[r] - 'a'] == 0) {
                unique_count++;
            }
            freq[s[r] - 'a']++;
            
            // If we exceed K unique characters, shrink from the left
            while (unique_count > k) {
                freq[s[l] - 'a']--;
                if (freq[s[l] - 'a'] == 0) {
                    unique_count--;
                }
                l++;
            }
            
            // If we have exactly K unique characters, it's a valid candidate
            if (unique_count == k) {
                max_len = max(max_len, r - l + 1);
            }
        }
        
        return max_len;
    }
};

/*
Dry Run — Example 1:
Input: s = "aabacbebebe", k = 3
freq array tracks unique characters.

1. r=0..3 ("aaba"):
   unique_count = 2 (characters 'a', 'b'). 
   max_len = -1 (since unique_count < 3).

2. r=4 ('c') -> window: "aabac"
   unique_count = 3 ('a', 'b', 'c').
   max_len = max(-1, 4 - 0 + 1) = 5.

3. r=5 ('b') -> window: "aabacb"
   unique_count = 3 ('a', 'b', 'c').
   max_len = max(5, 5 - 0 + 1) = 6.

4. r=6 ('e') -> window: "aabacbe"
   unique_count = 4! ('a', 'b', 'c', 'e').
   - Exceeds k! Must shrink from left.
   - l=0 ('a'), freq['a'] drops to 2.
   - l=1 ('a'), freq['a'] drops to 1.
   - l=2 ('b'), freq['b'] drops to 1.
   - l=3 ('a'), freq['a'] drops to 0! -> unique_count drops to 3.
   - Loop breaks. l is now 4.
   Window is [4..6] -> "cbe" (len 3). max_len remains 6.

5. r=7..10 ("bebe"):
   r=7 ('b') -> window "cbeb" -> length 4
   r=8 ('e') -> window "cbebe" -> length 5
   r=9 ('b') -> window "cbebeb" -> length 6
   r=10 ('e') -> window "cbebebe" -> length 7
   unique_count remains exactly 3 ('c', 'b', 'e').
   max_len updates up to 7.

Return max_len = 7.
*/
