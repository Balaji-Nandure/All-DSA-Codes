/*
Problem:
Check if Two Strings are Anagrams of Each Other

Given two strings s1 and s2, check whether they are anagrams.
Two strings are anagrams if they contain the same characters
with the same frequencies, possibly in a different order.

Rules:
- Comparison is case-insensitive.
- Non-alphabetical characters are considered as normal characters
  unless specified otherwise (GfG considers full string comparison).

Examples:
Input  : s1 = "listen", s2 = "silent"
Output : true

Input  : s1 = "triangle", s2 = "integral"
Output : true

Input  : s1 = "hello", s2 = "world"
Output : false


Approach (Expected / Optimal – Frequency Counting):
1. If lengths of s1 and s2 are different, they cannot be anagrams.
2. Use a frequency array (or hash map) to count characters of s1.
3. Traverse s2 and decrement corresponding frequencies.
4. If any frequency becomes negative, return false.
5. If all frequencies balance to zero, strings are anagrams.

Why this works:
- Anagrams require identical frequency distribution of characters.
- Frequency counting captures this requirement exactly.
- Linear scan ensures optimal performance.

Time Complexity:
O(n)

Space Complexity:
O(1)   (constant space for fixed character set)


GeeksforGeeks:
https://www.geeksforgeeks.org/check-whether-two-strings-are-anagram-of-each-other/

LeetCode:
https://leetcode.com/problems/valid-anagram/
*/

bool areAnagrams(string s1, string s2) {
    if (s1.size() != s2.size()) {
        return false;
    }

    vector<int> freq(256, 0);

    // Count characters of s1
    for (char ch : s1) {
        freq[ch]++;
    }

    // Decrement using s2
    for (char ch : s2) {
        freq[ch]--;
        if (freq[ch] < 0) {
            return false;
        }
    }

    return true;
}
