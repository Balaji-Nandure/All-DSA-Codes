/*
Problem: Maximum Occurred Integer in Ranges

GFG: https://www.geeksforgeeks.org/problems/maximum-occurred-integer4602/1

Description:
Given two arrays L[] and R[], each pair (L[i], R[i]) represents a range.
Find the integer that appears in the maximum number of ranges.
If multiple integers have same maximum frequency, return the smallest one.

Examples:
Input: L[] = [1, 4, 3, 1], R[] = [15, 8, 5, 4]
Output: 4

Input: L[] = [1, 5, 9, 13, 21], R[] = [15, 8, 12, 20, 30]
Output: 5

Constraints:
1 ≤ N ≤ 1e6
0 ≤ L[i], R[i] ≤ 1e6

Approach (Difference Array / Prefix Sum Trick):
- Instead of marking all numbers inside every range (which is O(N * range)),
  we use a smart trick:
  
  For each range [L, R]:
    diff[L] += 1
    diff[R + 1] -= 1

- Then compute prefix sum on diff[]:
    This gives how many ranges cover each number.

- Track the index with maximum value.
- If tie occurs, smallest index is automatically chosen.

Why it works:
Prefix sum converts difference array into actual frequency counts.
Each position tells how many ranges include that number.

Time Complexity: O(N + MAX_RANGE)
Space Complexity: O(MAX_RANGE)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOccured(vector<int>& L, const vector<int>& R) {
        int maxx = 0;
        int n = R.size();
        for(int x: R) maxx = max(maxx, x);
        
        vector<int> diff(maxx + 5, 0);
        for(int i = 0; i < n; i++){
            diff[L[i]]++;
            diff[R[i] + 1]--;
        }
        
        int maxFreq = diff[0];
        int result = 0;
        
        for(int i = 1; i <= maxx; i++){
            diff[i] += diff[i - 1];
            
            if(diff[i] > maxFreq){
                maxFreq = diff[i];
                result = i;
            }
        }
        
        return result;
    }
};
