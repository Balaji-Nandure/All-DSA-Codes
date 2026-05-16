/*
Problem: Minimize string value

GFG: https://www.geeksforgeeks.org/problems/minimize-string-value/1

Description:
Given a lowercase string s and an integer k, remove exactly k characters so that
the string value is minimum.
Value = sum of squares of frequencies of distinct characters.

Examples:

Input: s = "abccc", k = 1
Output: 6

Input: s = "aaab", k = 2
Output: 2

Constraints:
1 <= k, |s| <= 10^4

Approach (Greedy + Max Heap):
To reduce sum of squares the most, always remove one occurrence from the
character with current highest frequency.

Time Complexity: O((|s| + k) log |s|)
Space Complexity: O(26)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // TC: O((n + k) log n) in general
    // For lowercase English letters, heap size <= 26
    // SC: O(1)

    int minValue(string s, int k) {

        vector<int> freq(26, 0);
        for(char ch : s) {
            freq[ch - 'a']++;
        }

        priority_queue<int> pq;
        for(int count : freq) {
            if(count > 0) {
                pq.push(count);
            }
        }

        while(k > 0 && !pq.empty()) {
            int topFreq = pq.top();
            pq.pop();

            topFreq--;
            k--;

            if(topFreq > 0) {
                pq.push(topFreq);
            }
        }

        long long answer = 0;
        while(!pq.empty()) {
            long long count = pq.top();
            pq.pop();
            answer += count * count;
        }

        return (int)answer;
    }
};
