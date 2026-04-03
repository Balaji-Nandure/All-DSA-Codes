/*
Problem: Majority Element - More Than n/3

GFG: https://www.geeksforgeeks.org/problems/majority-vote/1
Visualizer (HTML, same folder): 27. Majority Element - More Than n by 3 - visualizer.html

Description: Given an array arr[] of n integers, find every value that occurs strictly more than floor(n/3) times.
Return those elements in sorted order (ascending). If none qualify, return an empty array.

Note: There can be at most two such elements. If one exists, the answer has size 1; if two exist, size 2.

Examples:

Input: arr[] = [2, 2, 3, 1, 3, 2, 1, 1]
Output: [1, 2]
Explanation: n = 8, floor(n/3) = 2. Values 1 and 2 each appear 3 times, and 3 > 2.

Input: arr[] = [-5, 3, -5]
Output: [-5]
Explanation: n = 3, floor(n/3) = 1. -5 appears twice, and 2 > 1.

Input: arr[] = [3, 2, 2, 4, 1, 4]
Output: []
Explanation: n = 6, floor(n/3) = 2. No value appears more than twice.

Constraints:
1 ≤ arr.size() ≤ 10^6
-10^5 ≤ arr[i] ≤ 10^5

Striver Intuition:

This is the extended Boyer–Moore Majority Vote algorithm (at most k−1 candidates for "more than n/k"; here k = 3, so at most 2 candidates).

Brute Force:
Count frequency of every distinct value (hash map) or nested loops.
Time = O(n) space with map, or O(n^2) time with nested loops.

Optimal Approach:
O(n) time, O(1) extra space: two-pass voting + verification.

Key insight:
If a value appears more than n/3 times, there can be at most two such values.
Pair up three distinct numbers in one "cancellation" — each triple removes one occurrence from each of three different values; true > n/3 frequencies cannot all be wiped out.

Algorithm:
1. First pass — maintain two (value, count) slots:
   - If current element matches slot 1 (and slot 1 is active), increment count1.
   - Else if it matches slot 2, increment count2.
   - Else if slot 1 is empty, occupy it with this element.
   - Else if slot 2 is empty, occupy it with this element.
   - Else decrement both counts (one "vote" removed from each candidate; represents discarding one copy of three distinct values).
2. Second pass — count real frequencies of candidate1 and candidate2 in the whole array.
3. If count > n/3, push that value. Use cand1 != cand2 when checking the second bucket to avoid duplicates if they ever collided.
4. Sort the result.

Why check count before equality in pass 1?
So that "empty" slots (count 0) are not confused with the number 0 (or any value) as a stored candidate.

Pattern:
Boyer–Moore voting — extended to two candidates for n/3 threshold.

Time Complexity: O(n)
Space Complexity: O(1) excluding the output vector

GFG:
https://www.geeksforgeeks.org/problems/majority-vote/1

LeetCode (same idea, tie-breaking note may differ):
https://leetcode.com/problems/majority-element-ii/
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findMajority(vector<int>& arr) {
        int n = (int)arr.size();
        int c1 = 0, c2 = 0;
        int cand1 = 0, cand2 = 0;

        for (int x : arr) {
            if (c1 > 0 && x == cand1) {
                c1++;
            } else if (c2 > 0 && x == cand2) {
                c2++;
            } else if (c1 == 0) {
                cand1 = x;
                c1 = 1;
            } else if (c2 == 0) {
                cand2 = x;
                c2 = 1;
            } else {
                c1--;
                c2--;
            }
        }

        int cnt1 = 0, cnt2 = 0;
        for (int x : arr) {
            if (x == cand1) cnt1++;
            else if (x == cand2) cnt2++;
        }

        vector<int> out;
        int need = n / 3;
        if (cnt1 > need) out.push_back(cand1);
        if (cand2 != cand1 && cnt2 > need) out.push_back(cand2);

        sort(out.begin(), out.end());
        return out;
    }
};

/*
Final Summary (Interview Revision):

1. At most two values can appear > n/3 times.
2. Pass 1: extended Boyer–Moore with two slots; always test c1>0 / c2>0 before comparing x to cand1/cand2.
3. Pass 2: count occurrences of cand1 and cand2; keep those with count > n/3.
4. Guard second push with cand2 != cand1; sort answer.
5. O(n) time, O(1) extra space.

Memory Trick:
"n/3 majority → two candidates max → vote + verify → sort"
*/
