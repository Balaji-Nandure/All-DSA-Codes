/*
Problem: Same frequency in two halves

GFG: https://www.geeksforgeeks.org/problems/same-frequency-in-two-halves/1

Description:
Split string S into two halves from the middle and check if both halves have
same character frequencies. If length is odd, ignore the middle character.

Examples:

Input: S = "abcdbca"
Output: YES

Input: S = "abbaab"
Output: NO

Constraints:
1 <= |S| <= 10^5

Approach:
Use one frequency map:
- add counts from left half
- subtract counts from right half
If all balances become zero, both halves have same frequencies.

Time Complexity: O(|S|)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O(n)
    // SC: O(1)

    bool passed(string S) {

        int n = S.size();
        map<char, int> freq;

        int leftEnd = n / 2 - 1;
        int rightStart = (n % 2 == 0) ? (n / 2) : (n / 2 + 1);

        for(int i = 0; i <= leftEnd; i++) {
            freq[S[i]]++;
        }

        for(int i = rightStart; i < n; i++) {
            freq[S[i]]--;
        }

        for(auto it : freq) {
            if(it.second != 0) {
                return false;
            }
        }

        return true;
    }
};
