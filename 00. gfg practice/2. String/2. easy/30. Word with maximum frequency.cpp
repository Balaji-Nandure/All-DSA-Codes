/*
Problem: Word with maximum frequency

GFG: https://www.geeksforgeeks.org/problems/word-with-maximum-frequency/1

Description:
Given a sentence s,
find:
- word with maximum frequency
- its frequency

If multiple words have same maximum frequency,
return the word that appears first in sentence.

Examples:

Input:
s = "the devil in the sky"

Output:
"the 2"

Explanation:
"the" appears 2 times.

--------------------------------------------------

Input:
s = "this is not right"

Output:
"this 1"

Explanation:
All words appear once.
"this" occurs first.

Constraints:
1 ≤ s.size() ≤ 10^6

Approach:
- Extract words using stringstream
- Count frequency using map
- Store order of first appearance
- Traverse words again:
    pick word with highest frequency
    first occurring word automatically handled

Dry Run:
s = "the devil in the sky"

Words:
the devil in the sky

Freq:
the -> 2
others -> 1

Maximum frequency:
the -> 2

Answer:
"the 2" ✅

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(n)
    string maxFrequency(string s) {

        unordered_map<string, int> mp;

        vector<string> words;

        stringstream ss(s);

        string word;

        // Extract words
        while(ss >> word) {

            mp[word]++;

            words.push_back(word);
        }

        string ans = "";
        int mx = 0;

        // Find first word with max frequency
        for(string &w : words) {

            if(mp[w] > mx) {

                mx = mp[w];

                ans = w;
            }
        }

        return ans + " " + to_string(mx);
    }
};