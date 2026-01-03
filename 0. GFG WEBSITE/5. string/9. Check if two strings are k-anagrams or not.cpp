/*
Problem:
Check if Two Strings are K-Anagrams or Not

Given two strings s1 and s2 and an integer k,
check whether the two strings are k-anagrams of each other.

Definition:
Two strings are called k-anagrams if:
- They have the same length, and
- They can be made anagrams of each other by changing
  at most k characters in one of the strings.

Examples:
Input  : s1 = "anagram", s2 = "grammar", k = 3
Output : true

Input  : s1 = "geeks", s2 = "eggkf", k = 1
Output : false

Input  : s1 = "fodr", s2 = "gork", k = 2
Output : true


Approach (Expected / Optimal – Frequency Difference Counting):
1. If lengths of s1 and s2 are different, return false.
2. Build frequency count of characters in s1.
3. Traverse s2 and decrement corresponding frequencies.
4. After this, any positive frequency indicates extra characters in s1
   that need to be changed.
5. Count total positive frequencies.
6. If total changes required ≤ k, return true; otherwise false.

Why this works:
- Only excess characters in one string need replacement.
- Each replacement fixes exactly one excess character.
- Counting positive frequency directly maps to number of changes needed.

Time Complexity:
O(n)

Space Complexity:
O(1)   (constant space for fixed alphabet)


GeeksforGeeks:
https://www.geeksforgeeks.org/check-two-strings-k-anagrams-not/

LeetCode:
No direct equivalent problem.
(Related to anagram and frequency manipulation problems)
*/

bool areKAnagrams(string s1, string s2, int k) {
    if (s1.size() != s2.size()) {
        return false;
    }

    vector<int> freq(26, 0);

    // Count frequencies of s1
    for (char ch : s1) {
        freq[ch - 'a']++;
    }

    // Subtract frequencies using s2
    for (char ch : s2) {
        freq[ch - 'a']--;
    }

    // Count excess characters in s1
    int changes = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            changes += freq[i];
        }
    }

    return changes <= k;
}
