/*
Problem: The Modified String

GFG: https://www.geeksforgeeks.org/problems/the-modified-string-1587115621/1

Description:
Given a string s,
insert minimum characters so that
no three consecutive characters are same.

We can insert any character anywhere.

Examples:

Input: s = "aabbbcc"
Output: 1

Explanation:
Insert one character between bbb:
"aabbdbcc"

--------------------------------------------------

Input: s = "aaaaa"
Output: 2

Explanation:
Possible valid string:
"aababaa"

Constraints:
1 ≤ s.size() ≤ 10^5

Approach:
- Count consecutive same characters
- Whenever count reaches 3:
    insert one character
    reset count to 1

Why reset to 1?
Example:
"aaaaa"

After handling first "aaa":
we conceptually insert:
"aaXaa"

Current sequence again starts from:
last 'a'
so cnt = 1

Formula Insight:
For every group of size len:
insertions needed = len / 3

Dry Run:
s = "aabbbcc"

a -> cnt=1
a -> cnt=2

b -> cnt=1
b -> cnt=2
b -> cnt=3 ❌

Insert one char
ans=1
cnt=1

c -> cnt=1
c -> cnt=2

Answer = 1 ✅

--------------------------------------------------

Dry Run:
s = "aaaaa"

a -> 1
a -> 2
a -> 3 -> ans=1, cnt=1
a -> 2
a -> 3 -> ans=2, cnt=1

Answer = 2 ✅

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)  SC: O(1)
    int modified(string s) {

        int ans = 0;
        int cnt = 1;

        for(int i = 1; i < s.size(); i++) {

            if(s[i] == s[i - 1]) {

                cnt++;
            }
            else {

                ans += (cnt - 1) / 2;

                cnt = 1;
            }
        }

        // Last group
        ans += (cnt - 1) / 2;

        return ans;
    }
};