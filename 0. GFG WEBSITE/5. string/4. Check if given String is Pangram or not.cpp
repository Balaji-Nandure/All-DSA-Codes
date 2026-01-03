/*
Problem:
Check if Given String is a Pangram or Not

Given a string s, check whether it is a Pangram.
A Pangram is a string that contains every letter of the English alphabet
('a' to 'z') at least once, irrespective of case.

Non-alphabetical characters are ignored.

Examples:
Input  : s = "The quick brown fox jumps over the lazy dog"
Output : true

Input  : s = "abcdefghijklmnopqrstuvwxyz"
Output : true

Input  : s = "Hello World"
Output : false


Approach (Expected / Optimal – Hashing / Boolean Array):
1. Create a boolean array of size 26 to track each alphabet letter.
2. Traverse the string character by character:
   - If character is an alphabet letter:
       - Convert it to lowercase.
       - Mark its position in the array as true.
3. After traversal, check if all 26 positions are true.
4. If yes, the string is a pangram; otherwise, it is not.

Why this works:
- Direct mapping of letters 'a'–'z' to indices 0–25.
- Case-insensitive handling ensures correctness.
- Extra characters do not interfere with logic.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-a-string-is-a-pangram/

LeetCode:
No direct equivalent problem.
(Related to string validation and character frequency problems)
*/

bool isPangram(string s) {
    vector<bool> seen(26, false);

    for (char ch : s) {
        if (isalpha(ch)) {
            ch = tolower(ch);
            seen[ch - 'a'] = true;
        }
    }

    // Check if all letters are present
    for (bool present : seen) {
        if (!present) {
            return false;
        }
    }

    return true;
}
