/*
Problem: Find Maximum value

GFG: https://www.geeksforgeeks.org/problems/find-maximum-value/1

Description: Given an array arr[] you have to find the maximum value of abs(i – j) *min(arr[i], arr[j]) where i and j vary from 0 to n-1 and i != j.

Examples:

Input: arr[] = [3, 2, 1, 4]
Output: 9
Explanation: Here, a[0] = 3 and a[3] = 4 and thus result is abs(0-3)*min(3,4) = 9.
Input: arr[] = [8, 1, 9, 4]
Output: 16
Explanation: Here, a[0] = 8 and a[2] = 9 and thus result is abs(0-2)*min(8,9)=16.

Constraints:
2 <= arr.size() <=106
-105 <= arr[i] <=105

Approach:
1. Use two pointers (i = 0, j = n-1)
2. Compute value = (j - i) * min(arr[i], arr[j])
3. Move pointer with smaller value

Why it works:
- This is similar to the "Container With Most Water" problem, where we maximize the area by considering the width (distance) and the minimum height.
- The width decreases as we move pointers inward, so to maximize the product, we need to maximize the min value.
- By moving the pointer with the smaller value, we potentially find a larger min value in the next iteration, compensating for the reduced width.
- This greedy approach ensures we consider the best possible pairs without checking all combinations.

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxValue(vector<int>& arr) {
        
        int n = arr.size();
        int i = 0, j = n - 1;
        long long ans = 0;

        while (i < j) {
            
            long long curr = 1LL * (j - i) * min(arr[i], arr[j]);
            ans = max(ans, curr);

            // move smaller value
            if (arr[i] < arr[j]) {
                i++;
            } else {
                j--;
            }
        }

        return ans;
    }
};
