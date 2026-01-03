/*
Problem:
Palindrome String

Given a string s, check whether it is a palindrome or not.
A palindrome is a string that reads the same forward and backward.

Rules (as per common GfG interpretation):
- Case insensitive comparison.
- Ignore all non-alphanumeric characters.

Examples:
Input  : s = "A man, a plan, a canal: Panama"
Output : true

Input  : s = "abba"
Output : true

Input  : s = "race a car"
Output : false


Approach (Expected / Optimal – Two Pointers):
1. Use two pointers:
   - left starting at beginning of string
   - right starting at end of string
2. Move left forward until it points to an alphanumeric character.
3. Move right backward until it points to an alphanumeric character.
4. Compare characters at left and right after converting both to lowercase:
   - If they differ → not a palindrome.
5. Move both pointers inward and repeat until left >= right.

Why this works:
- Palindrome condition only depends on relative symmetry.
- Skipping non-alphanumeric characters ensures valid comparison.
- Two-pointer method avoids extra space.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-a-string-is-palindrome/

LeetCode:
https://leetcode.com/problems/valid-palindrome/
*/

bool isPalindrome(string s) {
    int left = 0;
    int right = s.size() - 1;

    while (left < right) {

        // Skip non-alphanumeric characters from left
        while (left < right && !isalnum(s[left])) {
            left++;
        }

        // Skip non-alphanumeric characters from right
        while (left < right && !isalnum(s[right])) {
            right--;
        }

        // Compare characters (case-insensitive)
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}
