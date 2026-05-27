/*
Problem: Rearrange a string

Given a string containing uppercase alphabets and integer digits (from 0 to 9), the task is to print the alphabets in the lexicographical order followed by the sum of digits.

Example 1:
Input: S = "AC2BEW3"
Output: "ABCEW5"
Explanation: 2 + 3 = 5 and we print all alphabets in the lexicographical order. 

Example 2:
Input: S = "ACCBA10D2EW30"
Output: "AABCCDEW6"
Explanation: 0+1+2+3 = 6 and we print all alphabets in the lexicographical order. 

Constraints:
1 <= |S| <= 10^5
S contains only upper case alphabets and digits.

--------------------------------------------------

Pattern:
String Processing + Counting Sort (Frequency Array)

--------------------------------------------------

Key Observation:
- We need to sort the uppercase letters lexicographically and sum up the digits.
- Since there are only 26 possible uppercase English letters, we can use a frequency array of size 26 to count the occurrences of each letter. This gives us O(N) sorting (Counting Sort principle).
- While scanning the string, if we encounter a digit, we can simply add its numerical value to a running `sum`.
- A critical edge case: we should track if *any* digit was present at all using a boolean flag `hasDigit`. This ensures that if the input has no digits (e.g., "ABC"), we don't accidentally append a "0" at the end. However, if there are digits and their sum is 0 (e.g., "A0"), we correctly append "0".

--------------------------------------------------

Approach:
1. Initialize a frequency vector `charCount` of size 26 with 0s.
2. Initialize `sum = 0` and a boolean `hasDigit = false`.
3. Iterate through each character `c` in the string `S`:
   - If `c` is an uppercase letter, increment `charCount[c - 'A']`.
   - If `c` is a digit, add `c - '0'` to `sum` and set `hasDigit = true`.
4. Initialize an empty string `ans`.
5. Iterate `i` from 0 to 25. For each index, append the character `('A' + i)` to `ans` exactly `charCount[i]` times.
6. If `hasDigit` is true, append `to_string(sum)` to `ans`.
7. Return `ans`.

--------------------------------------------------

Time Complexity: O(|S|) since we iterate the string once. Rebuilding the string takes O(|S|) operations as well.
Space Complexity: O(26) -> O(1) Auxiliary Space.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/rearrange-a-string4100/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string arrangeString(string S) {
        vector<int> charCount(26, 0);
        int sum = 0;
        bool hasDigit = false;
        
        // Count character frequencies and calculate sum of digits
        for (char c : S) {
            if (c >= 'A' && c <= 'Z') {
                charCount[c - 'A']++;
            } else if (c >= '0' && c <= '9') {
                sum += (c - '0');
                hasDigit = true;
            }
        }
        
        string ans = "";
        
        // Append characters in lexicographical order (Counting Sort logic)
        for (int i = 0; i < 26; i++) {
            while (charCount[i] > 0) {
                ans += (char)('A' + i);
                charCount[i]--;
            }
        }
        
        // Append the sum only if at least one digit was present in the string
        if (hasDigit) {
            ans += to_string(sum);
        }
        
        return ans;
    }
};
