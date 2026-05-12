/*
Problem:
Given two lowercase strings s1 and s2,
find minimum deletions required
to make them anagrams.

Allowed operation:
- Delete characters only

Example:
s1 = "bcadeh"
s2 = "hea"

Remove:
b, c, d from s1

Answer = 3

Approach:
1. Count frequency of every character in s1.
2. Count frequency of every character in s2.
3. For every character:
      deletions += absolute difference
4. Return total deletions.

Why this works?
- For anagrams,
  frequency of every character must match.
- Extra occurrences must be deleted.

Example:
s1 = "aab"
s2 = "abbb"

a -> |2 - 1| = 1 deletion
b -> |1 - 3| = 2 deletions

Total = 3

Pattern:
Hashing / Frequency Counting

Time Complexity: O(N + M)
Space Complexity: O(1)

GFG Link:
https://www.geeksforgeeks.org/problems/make-anagram-1587115620/1
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int remAnagrams(string s1, string s2) {

        // Frequency array
        int freq[26] = {0};

        // Count characters from s1
        for(char ch : s1) {
            freq[ch - 'a']++;
        }

        // Remove characters using s2
        for(char ch : s2) {
            freq[ch - 'a']--;
        }

        int deletions = 0;

        // Sum of absolute differences
        for(int i = 0; i < 26; i++) {

            deletions += abs(freq[i]);
        }

        return deletions;
    }
};

/*
Summary:
- Same frequencies needed for anagrams
- Difference in frequencies = deletions needed
- Use one frequency array for optimization
*/
