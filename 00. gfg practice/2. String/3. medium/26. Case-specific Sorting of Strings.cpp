/*
GeeksforGeeks: Case-specific Sorting of Strings
Difficulty: Medium

Problem:
Given a string s consisting of only uppercase and lowercase characters. 
The task is to sort uppercase and lowercase letters separately such that if the ith place in the original string 
had an Uppercase character then it should not have a lowercase character after being sorted and vice-versa.

Examples:
Input: s = "GEekS", n = 5
Output: EGekS
Explanation: Sorted form of given string with the same case of character will result in output as EGekS.
             Uppercase letters are 'G', 'E', 'S' -> sorted: 'E', 'G', 'S'.
             Lowercase letters are 'e', 'k' -> sorted: 'e', 'k'.
             Placing them back in original positions: E, G, e, k, S.

Input: s = "XWMSPQ", n = 6
Output: MPQSWX

Constraints:
1 <= s.length() <= 10^5

Core Idea:
- To sort the uppercase and lowercase letters separately in O(N) time and O(1) auxiliary space, we can use Count Sort.
- We count frequencies of uppercase letters ('A' - 'Z') in an array of size 26.
- We count frequencies of lowercase letters ('a' - 'z') in an array of size 26.
- We then iterate through the original string again:
  - If s[i] is uppercase, we replace it with the next available uppercase character from the uppercase frequency array.
  - If s[i] is lowercase, we replace it with the next available lowercase character from the lowercase frequency array.
- This modifies the string in-place and is much faster than standard sorting which would take O(N log N) time and O(N) space.

Approach:
1. Initialize two frequency arrays: `upper` of size 26 and `lower` of size 26, both with 0.
2. Traverse `s` and populate the frequencies:
   - If `isupper(c)`, increment `upper[c - 'A']`.
   - Else, increment `lower[c - 'a']`.
3. Set two pointers `u_idx = 0` and `l_idx = 0` to scan the frequency tables.
4. Traverse `s` from index 0 to n-1:
   - If `isupper(s[i])`:
     - Advance `u_idx` until `upper[u_idx] > 0`.
     - Assign `s[i] = 'A' + u_idx` and decrement `upper[u_idx]`.
   - Else:
     - Advance `l_idx` until `lower[l_idx] > 0`.
     - Assign `s[i] = 'a' + l_idx` and decrement `lower[l_idx]`.
5. Return `s`.

Time Complexity: O(N) where N is the length of the string. We do a single pass to count frequencies, and a second pass to construct the string.
Space Complexity: O(1) auxiliary space since frequency arrays are of fixed size 26.

GFG Link: https://www.geeksforgeeks.org/problems/case-specific-sorting-of-strings4845/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class Solution {
public:
    string caseSort(string str, int n) {
        vector<int> upper(26, 0);
        vector<int> lower(26, 0);
        
        // Step 1: Count occurrences of each character case-specifically
        for (char c : str) {
            if (isupper(c)) {
                upper[c - 'A']++;
            } else {
                lower[c - 'a']++;
            }
        }
        
        int u_idx = 0; // Pointer for uppercase frequency array
        int l_idx = 0; // Pointer for lowercase frequency array
        
        // Step 2: Reconstruct the string by placing sorted characters in place
        for (int i = 0; i < n; i++) {
            if (isupper(str[i])) {
                // Find next available uppercase character in sorted order
                while (u_idx < 26 && upper[u_idx] == 0) {
                    u_idx++;
                }
                str[i] = 'A' + u_idx;
                upper[u_idx]--;
            } else {
                // Find next available lowercase character in sorted order
                while (l_idx < 26 && lower[l_idx] == 0) {
                    l_idx++;
                }
                str[i] = 'a' + l_idx;
                lower[l_idx]--;
            }
        }
        
        return str;
    }
};

/*
Dry Run — Example:
str = "GEekS", n = 5

1. Frequency Count:
   - upper array counts:
     E: 1 (index 4)
     G: 1 (index 6)
     S: 1 (index 18)
   - lower array counts:
     e: 1 (index 4)
     k: 1 (index 10)

2. Reconstruct:
   - i = 0: str[0] ('G') is uppercase.
     - u_idx starts at 0. Finds first non-zero at index 4 (char 'E').
     - str[0] = 'E', upper[4] becomes 0.
   - i = 1: str[1] ('E') is uppercase.
     - u_idx advances to index 6 (char 'G').
     - str[1] = 'G', upper[6] becomes 0.
   - i = 2: str[2] ('e') is lowercase.
     - l_idx starts at 0. Finds first non-zero at index 4 (char 'e').
     - str[2] = 'e', lower[4] becomes 0.
   - i = 3: str[3] ('k') is lowercase.
     - l_idx advances to index 10 (char 'k').
     - str[3] = 'k', lower[10] becomes 0.
   - i = 4: str[4] ('S') is uppercase.
     - u_idx advances to index 18 (char 'S').
     - str[4] = 'S', upper[18] becomes 0.

Result: "EGekS"
Output: "EGekS"
*/
