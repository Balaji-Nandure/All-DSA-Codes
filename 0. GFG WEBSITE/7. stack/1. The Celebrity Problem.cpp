/*
Problem:
The Celebrity Problem

There are N people at a party, labeled from 0 to N-1.
Each person may or may not know another person.

You are given a NxN matrix M where:
M[i][j] = 1 means person i knows person j
M[i][j] = 0 means person i does NOT know person j

A celebrity is someone who:
- Knows no one.
- Is known by everyone else.

Return the index of the celebrity if one exists, otherwise return -1.

Rules:
- A celebrity’s row must contain all 0s.
- A celebrity’s column must contain all 1s except the diagonal.

Example:
Input:
M = [
  [0, 1, 0],
  [0, 0, 0],
  [0, 1, 0]
]

Output:
1

Explanation:
Person 1 knows no one,
and everyone else knows person 1.



-----------------------------------
Approach (Expected / Optimal – Two Pointer Elimination):
-----------------------------------
1. Use two pointers `i = 0` and `j = N-1`.
2. While `i < j`:
   a) If M[i][j] == 1, then person `i` knows `j`,
      so `i` cannot be a celebrity → increment `i`.
   b) Else person `j` cannot be a celebrity → decrement `j`.
3. After the loop, `i` is the only possible celebrity candidate.
4. Verify the candidate:
   - Candidate must not know anyone.
   - Everyone else must know the candidate.
5. If verification passes, return the candidate index.
6. Otherwise, return -1.

Why this works:
- Every comparison eliminates exactly one non-celebrity.
- Only one possible candidate remains.
- Final verification ensures correctness.


Time Complexity:
O(N)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/the-celebrity-problem/

LeetCode:
https://leetcode.com/problems/find-the-celebrity/
*/


class Solution {
public:
    int celebrity(vector<vector<int>>& M, int n) {

        int i = 0, j = n - 1;

        // Step 1: Eliminate non-celebrities
        while (i < j) {
            if (M[i][j] == 1) {
                // i knows j → i is not a celebrity
                i++;
            } else {
                // i does not know j → j is not a celebrity
                j--;
            }
        }

        int candidate = i;

        // Step 2: Verify the candidate
        for (int k = 0; k < n; k++) {
            if (k != candidate) {
                // Candidate should know no one
                // Everyone should know the candidate
                if (M[candidate][k] == 1 || M[k][candidate] == 0) {
                    return -1;
                }
            }
        }

        return candidate;
    }
};
