/*
Problem:
Check if One String is a Subsequence of Another

Given two strings:
- str : the main string
- sub : the string to be checked

Determine whether sub is a subsequence of str.
A subsequence is formed by deleting zero or more characters
from str without changing the order of remaining characters.

Examples:
Input  : str = "abcde", sub = "ace"
Output : true

Input  : str = "abcde", sub = "aec"
Output : false

Input  : str = "abc", sub = ""
Output : true


Approach (Expected / Optimal – Two Pointers):
1. Initialize two pointers:
   - i for str
   - j for sub
2. Traverse str using pointer i:
   - If str[i] == sub[j], increment j.
   - Always increment i.
3. If j reaches sub.length(),
   it means all characters of sub were found in order.
4. Return true if j == sub.length(), else false.

Why this works:
- Subsequence only requires relative order, not contiguity.
- Two-pointer scan ensures order is preserved.
- Each character is visited at most once.

Time Complexity:
O(n)   (n = length of str)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-a-string-is-subsequence-of-another/

LeetCode:
https://leetcode.com/problems/is-subsequence/
*/

bool isSubsequence(string str, string sub) {
    int i = 0, j = 0;

    while (i < str.size() && j < sub.size()) {
        if (str[i] == sub[j]) {
            j++;
        }
        i++;
    }

    return j == sub.size();
}
