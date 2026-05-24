/*
Problem: Twice Counter

GFG: https://www.geeksforgeeks.org/problems/twice-counter4236/1

Description:
Given a list of words,
count how many words appear exactly twice.

Examples:

Input:
list[] = [Geeks, For, Geeks]

Output:
1

Explanation:
"Geeks" appears exactly 2 times.

--------------------------------------------------

Input:
list[] = [Tom, Jerry, Thomas, Tom,
          Jerry, Courage, Tom, Courage]

Output:
2

Explanation:
"Jerry" and "Courage"
appear exactly twice.

Constraints:
1 ≤ list.size() ≤ 10^4

Approach (Hash Map):
- Count frequency of each word
- Traverse frequency map
- Count words having freq == 2

Dry Run:

list = [Geeks, For, Geeks]

Freq Map:
Geeks -> 2
For   -> 1

Only "Geeks" has freq 2

Answer = 1 ✅

--------------------------------------------------

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(n)
    int countWords(vector<string>& list) {

        unordered_map<string, int> mp;

        for(string &word : list) {
            mp[word]++;
        }

        int cnt = 0;

        for(auto &it : mp) {

            if(it.second == 2) {
                cnt++;
            }
        }

        return cnt;
    }
};