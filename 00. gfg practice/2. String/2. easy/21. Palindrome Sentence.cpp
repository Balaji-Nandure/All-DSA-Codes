/*
Problem: Palindrome Sentence

GFG: https://www.geeksforgeeks.org/problems/palindrome-sentence5952/1

Description:
Given a string s,
check whether it is a palindrome sentence or not.

Rules:
- Ignore spaces and punctuation
- Ignore non-alphanumeric characters
- Convert uppercase letters to lowercase
- Check palindrome on processed string

Examples:

Input:
s = "Too hot to hoot"

Output:
true

Explanation:
Processed string:
"toohottohoot"
It reads same forward and backward.

--------------------------------------------------

Input:
s = "Abc 012..## 10cbA"

Output:
true

Explanation:
Processed string:
"abc01210cba"

Palindrome ✅

--------------------------------------------------

Input:
s = "ABC $. def01ASDF"

Output:
false

Explanation:
Processed string:
"abcdef01asdf"

Not palindrome ❌

Constraints:
1 ≤ s.length() ≤ 10^6

Approach (Two Pointers):
- Use two pointers:
    left at start
    right at end

- Skip non-alphanumeric characters
- Convert uppercase to lowercase before comparison
- If mismatch found:
    return false
- Otherwise continue inward

Why Efficient?
- No extra string needed
- Directly checks palindrome in original string

Dry Run:
s = "Too hot to hoot"

Processed comparison:

t == t ✅
o == o ✅
o == o ✅
h == h ✅
...

All matched → true ✅

--------------------------------------------------

Dry Run:
s = "ABC $. def01ASDF"

a != f ❌

Return false

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    bool isPalinSent(string &s) {

        int left = 0;
        int right = s.size() - 1;

        while(left < right) {

            // Skip non-alphanumeric from left
            while(left < right && !isalnum(s[left])) {
                left++;
            }

            // Skip non-alphanumeric from right
            while(left < right && !isalnum(s[right])) {
                right--;
            }

            // Convert to lowercase before compare
            char ch1 = tolower(s[left]);
            char ch2 = tolower(s[right]);

            // Mismatch found
            if(ch1 != ch2) {
                return false;
            }

            left++;
            right--;
        }

        return true;
    }
};