/*
Problem:
Find the Earliest Repeating Character

Given a string s, find the character whose FIRST appearance
occurs earliest among all characters that repeat.
If no repeating character exists, return '-1'.

Definition:
- Repeating character: appears more than once.
- Earliest: smallest index of first occurrence.

Examples:
Input  : s = "geeksforgeeks"
Output : 'g'
Explanation:
'g' repeats and its first occurrence index (0) is the earliest.

Input  : s = "abcd"
Output : '-1'
Explanation:
No repeating characters.

Input  : s = "abca"
Output : 'a'


-----------------------------------
Approach (Expected / Optimal – Frequency + First Index):
-----------------------------------
1. Use a hash map to store:
   - frequency of each character
   - first index of each character
2. Traverse the string:
   - Update frequency
   - If first time seen, store index
3. Traverse the map (or string again) to:
   - Consider only characters with frequency > 1
   - Find the one with minimum first index
4. Return corresponding character.

Simpler Variant:
- Count frequency first.
- Scan string from left to right:
  the first character with freq > 1 is the answer.

Why this works:
- Left-to-right scan preserves order.
- First repeated character encountered is the earliest.

Time Complexity:
O(n)

Space Complexity:
O(1)   (constant alphabet size)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-the-first-repeating-character-in-a-string/

LeetCode:
No direct equivalent problem.
(Related to string frequency problems)
*/

char earliestRepeatingChar(string s) {
    unordered_map<char, int> freq;

    // Step 1: Count frequencies
    for (char ch : s) {
        if (freq[ch] == 1) {
            return ch;
        }
        freq[ch]++;
    }

    return '-1';
}
