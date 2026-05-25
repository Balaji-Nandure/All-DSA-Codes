/*
Problem: Make Palindrome

GFG: https://www.geeksforgeeks.org/problems/make-palindrome4047/1

Description:
Given an array of equal-length strings,
check whether we can concatenate all strings
in some order to form a palindrome.

Examples:

Input:
arr = {"djfh", "gadt", "hfjd", "tdag"}

Output:
YES

Explanation:
"djfh" reverse -> "hfjd"
"gadt" reverse -> "tdag"

Possible palindrome:
"djfh" + "gadt" + "tdag" + "hfjd"

--------------------------------------------------

Input:
arr = {"jhjdf", "sftas", "fgsdf"}

Output:
NO

Constraints:
1 ≤ n ≤ 10^4

Approach:
For palindrome:
- Every string must have its reverse present
- At most ONE string can itself be palindrome
  and appear odd number of times

Method:
- Count frequency using map
- For every string:
    check reverse string frequency

Palindrome Condition:
1) Non-palindrome strings:
   freq(str) == freq(reverse)

2) Palindrome strings:
   odd frequency allowed for only one string

Dry Run:

arr = {"ab", "ba", "cd", "dc"}

ab <-> ba ✅
cd <-> dc ✅

Possible → YES

--------------------------------------------------

arr = {"aa", "bb", "cc"}

All are self-palindrome
Odd count = 3 ❌

Only one odd allowed

Answer = NO

Time Complexity: O(n * k)
k = string length

Space Complexity: O(n * k)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n * k)  SC: O(n * k)
    bool makePalindrome(int n, vector<string> &arr) {

        unordered_map<string, int> mp;

        for(string &s : arr) {
            mp[s]++;
        }

        int odd = 0;

        for(auto &it : mp) {

            string s = it.first;

            string rev = s;

            reverse(rev.begin(), rev.end());

            // Self palindrome string
            if(s == rev) {

                if(it.second % 2) {
                    odd++;
                }
            }
            else {

                // Reverse pair mismatch
                if(mp[s] != mp[rev]) {
                    return false;
                }
            }
        }

        return odd <= 1;
    }
};