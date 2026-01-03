/*
Problem:
K-th Non-Repeating Character

Given a string s and an integer k,
find the k-th non-repeating character in the string.
If there are fewer than k non-repeating characters, return '-1'.

Definition:
- Non-repeating character appears exactly once.
- Order is based on appearance in the original string.

Examples:
Input  : s = "geeksforgeeks", k = 2
Output : 'f'
Explanation:
Non-repeating characters in order: ['f', 'o', 'r']
2nd non-repeating character is 'f'

Input  : s = "abcd", k = 3
Output : 'c'

Input  : s = "aabb", k = 1
Output : '-1'


-----------------------------------
Approach (Expected / Optimal – Hashing + Order Preservation):
-----------------------------------
1. Use an unordered_map to count frequency of each character.
2. Traverse the string again from left to right:
   - For each character with frequency == 1,
     decrement k.
   - When k becomes 0, return that character.
3. If traversal ends and k > 0, return '-1'.

Why this works:
- Hash map identifies non-repeating characters.
- Second traversal preserves original order.
- Ensures correct k-th selection.

Time Complexity:
O(n)

Space Complexity:
O(1)   (bounded by fixed character set)


GeeksforGeeks:
https://www.geeksforgeeks.org/kth-non-repeating-character/

LeetCode:
No direct equivalent problem.
(Related to frequency counting and string traversal problems)
*/

char kthNonRepeatingCharacter(string s, int k) {
    unordered_map<char, int> freq;

    // Step 1: Count character frequencies
    for (char ch : s) {
        freq[ch]++;
    }

    // Step 2: Find k-th non-repeating character
    for (char ch : s) {
        if (freq[ch] == 1) {
            k--;
            if (k == 0) {
                return ch;
            }
        }
    }

    return '-1';
}

