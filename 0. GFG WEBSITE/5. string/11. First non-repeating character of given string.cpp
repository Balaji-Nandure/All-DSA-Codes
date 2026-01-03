/*
Problem:
First Non-Repeating Character of a Given String

Given a string s, find the first character that does NOT repeat
(i.e., appears exactly once in the string).
If no such character exists, return '-1'.

Examples:
Input  : s = "geeksforgeeks"
Output : 'f'
Explanation:
'f' is the first character with frequency 1.

Input  : s = "aabbcc"
Output : '-1'
Explanation:
Every character repeats.

Input  : s = "abc"
Output : 'a'


-----------------------------------
Approach (Expected / Optimal – Hashing + Order Preservation):
-----------------------------------
1. Use an unordered_map to count frequency of each character.
2. Traverse the string again from left to right:
   - The first character with frequency == 1
     is the answer.
3. If no such character is found, return '-1'.

Why this works:
- Hash map captures exact frequency.
- Second traversal preserves original order.
- Guarantees the first non-repeating character.

Time Complexity:
O(n)

Space Complexity:
O(1)   (constant alphabet size)


GeeksforGeeks:
https://www.geeksforgeeks.org/first-non-repeating-character-of-given-string/

LeetCode:
https://leetcode.com/problems/first-unique-character-in-a-string/
*/


char firstNonRepeatingCharacter(string s) {
    unordered_map<char, int> freq;

    // Step 1: Count frequencies
    for (char ch : s) {
        freq[ch]++;
    }

    // Step 2: Find first character with frequency 1
    for (char ch : s) {
        if (freq[ch] == 1) {
            return ch;
        }
    }

    return '-1';
}
