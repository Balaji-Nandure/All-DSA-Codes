/*
Problem:
Minimum Insertions to Form a Palindrome (Permutations Allowed)

Given a string s, find the minimum number of insertions required
to make any permutation of the string a palindrome.

Important:
- Reordering (permutation) of characters is ALLOWED.
- Only insertions are counted.

Palindrome Property:
- For even length palindrome → all characters must have even frequency.
- For odd length palindrome  → exactly one character can have odd frequency.

Examples:
Input  : s = "abc"
Output : 2

Input  : s = "aabb"
Output : 0

Input  : s = "aaab"
Output : 1


Approach (Expected / Optimal – Hash Map Frequency Counting):
1. Use a map / unordered_map to count frequency of each character.
2. Count number of characters with odd frequency → oddCount.
3. If oddCount ≤ 1:
   - No insertion needed.
4. Otherwise:
   - Minimum insertions required = oddCount - 1.

Why this works:
- Each insertion fixes one odd-frequency character.
- At most one odd-frequency character is allowed in a palindrome.
- Permutation freedom simplifies the problem to parity checking.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/minimum-insertions-to-form-a-palindrome-with-permutations-allowed/

LeetCode:
No direct equivalent problem.
*/


int minInsertionsToMakePalindrome(string s) {
    unordered_map<char, int> freq;

    // Step 1: Count frequency of each character
    for (char ch : s) {
        freq[ch]++;
    }

    // Step 2: Count odd frequencies
    int oddCount = 0;
    for (auto& it : freq) {
        if (it.second % 2 != 0) {
            oddCount++;
        }
    }

    // Step 3: Calculate minimum insertions
    if (oddCount <= 1) {
        return 0;
    }

    return oddCount - 1;
}
