/*
Problem: Max Profit from Two Machines

GFG: https://www.geeksforgeeks.org/problems/max-profit-from-two-machines/1

Description:
Given two machines, Machine A and Machine B, and a set of n tasks. The profit earned for performing each task is given in two arrays a[] and b[] such that if Machine A performs the i-th task, the profit is a[i], and if Machine B performs it, the profit is b[i].

Machine A can process at most x tasks, and Machine B can process at most y tasks. It is guaranteed that x + y ≥ n, so all tasks can be assigned. Return the maximum possible profit after assigning each task to either Machine A or Machine B.

Examples:

Input: x = 3, y = 3, a[] = [1, 2, 3, 4, 5], b[] = [5, 4, 3, 2, 1]
Output: 21
Explanation: Machine A performs tasks with indices [2, 3, 4], and Machine B performs the rest [0, 1], giving profits (3 + 4 + 5) + (5 + 4) = 21.

Input: x = 4, y = 4, a[] = [1, 4, 3, 2, 7, 5, 9, 6], b[] = [1, 2, 3, 6, 5, 4, 9, 8]
Output: 43
Explanation: Machine A performs tasks with indices [1, 4, 5, 7], and Machine B performs the rest [0, 2, 3, 6], giving profits (4 + 7 + 5 + 6) + (1 + 3 + 6 + 9) = 41.

Input: x = 3, y = 4, a[] = [8, 7, 15, 19, 16, 16, 18], b[] = [1, 7, 15, 11, 12, 31, 9]
Output: 110
Explanation: Machine A performs tasks with indices [0, 3, 6], and Machine B performs the rest [1, 2, 4, 5], giving profits (8 + 19 + 18) + (7 + 15 + 12 + 31) = 110.

Constraints:
1 ≤ a.size() == b.size() ≤ 10^5
1 ≤ x, y ≤ 10^5
1 ≤ a[i], b[i] ≤ 10^4

Approach (Greedy + Sorting):
1. Create array of indices
2. Sort indices based on descending order of:
       |a[i] - b[i]|

3. Traverse sorted tasks:
    - If a[i] > b[i]:
          Prefer A (if capacity left)
          else → assign to B
    - Else:
          Prefer B (if capacity left)
          else → assign to A

Why it works:
- For each task, we need to decide: Should it go to A or B?
- Compare difference: diff[i] = |a[i] - b[i]|
- If difference is large → wrong choice = big loss
- So prioritize those tasks first
- Greedy assignment ensures we minimize opportunity cost

Time Complexity: O(n log n) → sorting
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(int x, int y, vector<int>& a, vector<int>& b) {
        
        int n = a.size();
        
        // Step 1: store indices
        vector<int> idx(n);
        for (int i = 0; i < n; i++) {
            idx[i] = i;
        }
        
        // Step 2: sort by descending absolute difference
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return abs(a[i] - b[i]) > abs(a[j] - b[j]);
        });
        
        int profit = 0;
        
        // Step 3: assign greedily
        for (int i : idx) {
            
            if (a[i] > b[i]) {
                if (x > 0) {
                    profit += a[i];
                    x--;
                } else {
                    profit += b[i];
                    y--;
                }
            } else {
                if (y > 0) {
                    profit += b[i];
                    y--;
                } else {
                    profit += a[i];
                    x--;
                }
            }
        }
        
        return profit;
    }
};
