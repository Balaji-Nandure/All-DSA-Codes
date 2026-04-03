/*
Problem: Form the Largest Number

GFG: https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array/1

Description: Given an array arr[] of non-negative integers, reorder them so that concatenating their decimal
representations in order yields the largest possible number. Return that number as a string (it may not fit in 64-bit).

Examples:

Input: arr[] = [3, 30, 34, 5, 9]
Output: "9534330"
Explanation: Order [9, 5, 34, 3, 30] gives 9 || 5 || 34 || 3 || 30 = 9534330.

Input: arr[] = [54, 546, 548, 60]
Output: "6054854654"
Explanation: Order [60, 548, 546, 54] beats sorting by numeric value alone.

Input: arr[] = [3, 4, 6, 5, 9]
Output: "96543"

Input: arr[] = [0, 0]
Output: "0"
Explanation: Leading zeros are not allowed — the whole answer is 0.

Constraints:
1 ≤ arr.size() ≤ 10^5
0 ≤ arr[i] ≤ 10^5

Striver Intuition:

This is a classic Custom Sort / Greedy String problem.

Brute Force:
Try all n! permutations, concatenate, take max.
Time = O(n! · totalDigits) — impossible for large n.

Why naive descending sort fails:
Compare 9 vs 34: 9 > 34 numerically, but we need "934" vs "349" — 9 should come first.
So the order depends on how pairs concatenate, not raw integer order.

Optimal Approach:
1. Convert each number to string (or compare via to_string in the comparator).
2. Sort strings with comparator: a should come before b iff (a + b) > (b + a) lexicographically.
   This is the correct local rule for global maximum (exchange argument / greedy proof).
3. Concatenate sorted strings.
4. If the largest string is "0", the answer is "0" (all zeros).

Pattern:
Custom comparator sorting — “largest concatenation” = sort by (a+b) vs (b+a).

Time Complexity: O(n log n · L) where L is typical string length (comparisons are O(L))
Space Complexity: O(n · L) for the string array (or similar if comparing with to_string on the fly)

GFG:
https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array/1

LeetCode:
https://leetcode.com/problems/largest-number/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string printLargest(vector<int>& arr) {
        vector<string> s;
        s.reserve(arr.size());
        for (int x : arr) {
            s.push_back(to_string(x));
        }

        sort(s.begin(), s.end(), [](const string& a, const string& b) {
            return a + b > b + a;
        });

        if (s[0] == "0") {
            return "0";
        }

        string ans;
        for (const string& t : s) {
            ans += t;
        }
        return ans;
    }
};

/*
Final Summary (Interview Revision):

1. Sort string forms with (a + b) > (b + a).
2. Edge case: all zeros → return "0", not a string of many zeros.
3. Proof idea: if an adjacent swap would increase the concatenation, do it — bubble-style → sort with this comparator.

Memory Trick:
"Concat compare: a+b vs b+a — then check all-zero → '0'"
*/
