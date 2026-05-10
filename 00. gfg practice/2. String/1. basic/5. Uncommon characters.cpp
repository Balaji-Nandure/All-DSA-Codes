/*
Problem: Uncommon characters

GFG: https://www.geeksforgeeks.org/problems/uncommon-characters/1

Description:
You are given two strings s1 and s2. Your task is to identify the characters that appear in either string but not in both (i.e., characters that are unique to one of the strings). Return the result as a sorted string.

Examples:

Input: s1 = "geeksforgeeks", s2 = "geeksquiz"
Output: "fioqruz"
Explanation: The characters 'f', 'i', 'o', 'q', 'r', 'u', and 'z' are present in either s1 or s2, but not in both.

Input: s1 = "characters", s2 = "alphabets"
Output: "bclpr"
Explanation: The characters 'b', 'c', 'l', 'p', and 'r' are present in either s1 or s2, but not in both.

Input: s1 = "rome", s2 = "more"
Output: ""
Explanation: Both strings contain the same characters, so there are no unique characters. The output is an empty string.

Constraints:
1 <= s1.size(), s2.size() <= 10^5
Both strings contain only lowercase English letters.

Approach (Frequency Counting):
This is a character frequency problem where we need to find characters that appear in exactly one string.

Key insight:
- Count frequency of each character in both strings
- Characters with frequency 1 are uncommon (appear in exactly one string)
- Sort the result alphabetically

Algorithm:
1. Create frequency array of size 26 (for 'a' to 'z')
2. Count occurrences in s1 (increment frequency)
3. Count occurrences in s2 (increment frequency)
4. Characters with frequency 1 are uncommon
5. Build result string with uncommon characters in sorted order

Time Complexity: O(n + m + 26log26) ≈ O(n + m)
Space Complexity: O(26) = O(1)

Pattern: Frequency Counting / Character Analysis
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
FREQUENCY COUNTING APPROACH
=====================================================

TC: O(n + m)
SC: O(1) - constant 26 size array

🔥 FREQUENCY ARRAY APPROACH
- Count character occurrences in both strings
- Characters with count 1 are uncommon
- Sort result alphabetically

🧠 KEY INSIGHT:
Character appears in exactly one string:
- Total frequency = 1
- If appears in both strings: frequency = 2
- Use frequency array for O(1) space

🎯 ALGORITHM:
1. Initialize freq[26] = {0}
2. Count characters in s1: freq[char-'a']++
3. Count characters in s2: freq[char-'a']++
4. Collect chars with freq == 1
5. Sort and return result string

⚡ FREQUENCY LOGIC:
s1 = "abc", s2 = "bcd"
freq['a'] = 1 (uncommon)
freq['b'] = 2 (common)
freq['c'] = 2 (common)
freq['d'] = 1 (uncommon)
Result: "ad" (sorted)
*/

class Solution {
public:

    // TC: O(n + m)
    // SC: O(1)

    string uncommonChars(string s1, string s2) {

        int freq[26] = {0};

        // Count characters in first string
        for(char c : s1) {

            freq[c - 'a']++;
        }

        // Count characters in second string
        for(char c : s2) {

            freq[c - 'a']++;
        }

        string result = "";

        // Collect uncommon characters (frequency == 1)
        for(int i = 0; i < 26; i++) {

            if(freq[i] == 1) {

                result.push_back('a' + i);
            }
        }

        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    CHARACTER COMPARISON
    + TWO STRINGS
    + UNIQUE ELEMENTS

Think immediately:
    FREQUENCY COUNTING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Uncommon character appears in exactly one string
2. Frequency 1 means unique to one string
3. Frequency 2+ means common to both strings
4. Fixed alphabet size (26) enables O(1) space

-----------------------------------------------------

COMMON MISTAKES:

1. Using unordered_set (loses frequency info)
2. Not sorting the result alphabetically
3. Using large arrays for fixed alphabet
4. Forgetting to initialize frequency array

-----------------------------------------------------

SIMILAR PROBLEMS

- Character frequency analysis
- String comparison problems
- Unique element identification

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Find unique/rare characters
- Compare character frequencies
- Fixed character set (lowercase/uppercase)

Think:
Frequency Array

Algorithm:
1. Initialize freq[26] = {0}
2. Count in both strings
3. Collect elements with target frequency
4. Sort if needed

Key insight:
Frequency 1 = appears in exactly one string

-----------------------------------------------------
*/
