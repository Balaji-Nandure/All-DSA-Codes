/*
Problem: Time to Words

GFG: https://www.geeksforgeeks.org/problems/time-to-words/1

Description:
Convert time H:M (12-hour format) into words using rules:
- 0  -> "o' clock"
- 15 -> "quarter past"
- 30 -> "half past"
- 45 -> "quarter to" next hour
- otherwise use "minute(s) past/to"

Examples:

Input: H = 6, M = 0
Output: "six o' clock"

Input: H = 6, M = 10
Output: "ten minutes past six"

Constraints:
0 < H < 12
0 <= M < 60

Approach:
Map numbers 1..29 to words. Handle special cases (0,15,30,45), then general
past/to cases.

Time Complexity: O(1)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    string numberToWord(int n) {
        vector<string> words = {
            "", "one", "two", "three", "four", "five", "six", "seven",
            "eight", "nine", "ten", "eleven", "twelve", "thirteen",
            "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
            "nineteen", "twenty", "twenty one", "twenty two", "twenty three",
            "twenty four", "twenty five", "twenty six", "twenty seven",
            "twenty eight", "twenty nine"
        };
        return words[n];
    }

    string timeToWord(int H, int M) {

        if(M == 0) {
            return numberToWord(H) + " o' clock";
        }

        if(M == 15) {
            return "quarter past " + numberToWord(H);
        }

        if(M == 30) {
            return "half past " + numberToWord(H);
        }

        if(M == 45) {
            int nextHour = (H == 12) ? 1 : H + 1;
            return "quarter to " + numberToWord(nextHour);
        }

        if(M < 30) {
            string minuteWord = (M == 1) ? " minute past " : " minutes past ";
            return numberToWord(M) + minuteWord + numberToWord(H);
        }

        int minutesTo = 60 - M;
        int nextHour = (H == 12) ? 1 : H + 1;
        string minuteWord = (minutesTo == 1) ? " minute to " : " minutes to ";
        return numberToWord(minutesTo) + minuteWord + numberToWord(nextHour);
    }
};
