/*
Problem: Anagram Palindrome

GFG: https://www.geeksforgeeks.org/problems/anagram-palindrome4720/1

Description:
Given a string s, determine whether its characters can be rearranged to form a palindrome. 
Return true if it is possible to rearrange the string into a palindrome; otherwise, return false.

Examples:

Input: s = "baba"
Output: true
Explanation: Can be rearranged to form a palindrome "abba" 

Input: s = "geeksogeeks"
Output: true
Explanation: The characters of the string can be rearranged to form the palindrome "geeksoskeeg".

Input: s = "geeksforgeeks"
Output: false
Explanation: The given string can't be converted into a palindrome.

Constraints:
1 ≤ s.length ≤ 10^6
s consists of only lowercase English letters.

Approach (Frequency Counting):
Key insight:
- Palindrome needs symmetric pairs of characters
- For even length strings: all characters must have even frequency
- For odd length strings: exactly one character can have odd frequency
- Count characters with odd frequency and check if ≤ 1

Algorithm:
1. Create frequency array of size 26
2. Count frequency of each character
3. Count how many characters have odd frequency
4. If odd count > 1, return false
5. Otherwise, return true

Time Complexity: O(n)
Space Complexity: O(1) - fixed size frequency array

Pattern: Hashing / Frequency Counting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
FREQUENCY COUNTING APPROACH
=====================================================

TC: O(n)
SC: O(1) - fixed size frequency array

🔥 PALINDROME FREQUENCY ANALYSIS
- Count character frequencies
- Check odd frequency count
- At most one odd frequency allowed

🧠 KEY INSIGHT:
Palindrome formation condition:
- Even length: all frequencies even
- Odd length: exactly one frequency odd
- Unified: odd count ≤ 1

🎯 ALGORITHM:
1. Count frequency of each character
2. Count characters with odd frequency
3. If odd count > 1: impossible
4. Else: possible

⚡ PALINDROME LOGIC:
s = "baba"

Step 1: Count frequencies
a -> 2 (even)
b -> 2 (even)

Step 2: Count odd frequencies
oddCount = 0

Step 3: Check condition
oddCount (0) ≤ 1 => true

Result: Can form palindrome "abba"

s = "aab"

Step 1: Count frequencies
a -> 2 (even)
b -> 1 (odd)

Step 2: Count odd frequencies
oddCount = 1

Step 3: Check condition
oddCount (1) ≤ 1 => true

Result: Can form palindrome "aba"

s = "abc"

Step 1: Count frequencies
a -> 1 (odd)
b -> 1 (odd)
c -> 1 (odd)

Step 2: Count odd frequencies
oddCount = 3

Step 3: Check condition
oddCount (3) > 1 => false

Result: Cannot form palindrome
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1) - fixed size frequency array

    bool isPossible(string s) {

        // Frequency array for lowercase letters
        int freq[26] = {0};

        // Count frequency of each character
        for(char ch : s) {
            freq[ch - 'a']++;
        }

        int oddCount = 0;

        // Count how many characters have odd frequency
        for(int i = 0; i < 26; i++) {

            if(freq[i] % 2 != 0) {
                oddCount++;
            }
        }

        // More than one odd frequency means impossible
        if(oddCount > 1) {
            return false;
        }

        return true;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    PALINDROME FORMATION
    + CHARACTER REARRANGEMENT
    + FREQUENCY ANALYSIS

Think immediately:
    FREQUENCY COUNTING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Palindrome needs symmetric pairs
2. Only middle character can be unpaired
3. Odd frequency count determines possibility
4. Frequency array is sufficient for lowercase

-----------------------------------------------------

COMMON MISTAKES:

1. Not considering odd length strings
2. Using complex data structures unnecessarily
3. Forgetting to check odd count condition
4. Not handling edge cases (empty string)

-----------------------------------------------------

SIMILAR PROBLEMS

- Palindrome permutation
- String rearrangement problems
- Anagram checking

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Check if string can form palindrome
- Need character frequency analysis
- Palindrome formation conditions

Think:
Frequency Counting with Odd Count Check

Algorithm:
1. Count character frequencies
2. Count odd frequencies
3. Apply palindrome condition
4. Return boolean result

Key insight:
Palindrome needs at most one odd frequency

-----------------------------------------------------
*/
