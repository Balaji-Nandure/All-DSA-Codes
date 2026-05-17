/*
Problem: Ladoo problem

GFG: https://www.geeksforgeeks.org/problems/ladoo-problem4018/1

Description:
Bheem has one ladoo per day. A[i] denotes the day on which the i-th friend
wants a ladoo. If multiple friends want ladoo on the same day, Bheem can
serve only one of them. Unserved friends are lost.

Find maximum friends Bheem can keep.

Examples:

Input: N = 5, A[] = {3, 3, 1, 2, 4}
Output: 4

Input: N = 2, A[] = {1, 2}
Output: 2

Constraints:
1 <= N <= 10^5
1 <= A[i] <= 10^5

Approach:
Each distinct day can satisfy at most one friend.
So, answer = number of distinct values in A[].

Use an unordered_set (hashing) to store unique requested days.

Time Complexity: O(N) average
Space Complexity: O(N)

Pattern: Hashing / Distinct Count
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int divideLadoo(int N, vector<int> &A) {
        unordered_set<int> days;

        for (int i = 0; i < N; i++) {
            days.insert(A[i]);
        }

        return (int)days.size();
    }
};

