/*
Problem: Pairs with Difference less than K

GFG: https://www.geeksforgeeks.org/problems/pairs-with-difference-less-than-k/1

Description: Given an array arr[] of positive integers, the task is to find all pairs with an absolute difference less than k.

NOTE: Pair (i, j) is considered the same as (j, i)

Examples:

Input : arr[] = [1, 10, 4, 2], k = 3
Output : 2
Explanation: We have an array arr[] = [1, 10, 4, 2] and k = 3 We can make only two pairs with a difference of less than 3. (1, 2) and (4, 2). So, the answer is 2.
Input : arr[] = [2, 3, 4], k = 5
Output : 3
Explanation:  For the given array arr[] = [2, 3, 4] and k = 5, there are 3 valid pairs where the absolute difference between the pair's elements is less than 5. These pairs are (2, 3), (2, 4), and (3, 4). Hence, the output is 3.

Constraints:
1 ≤ arr.size() ≤ 105
0 ≤ k ≤ 105
1 ≤ arr[i] ≤ 105

Approach:
1. Sort the array
2. Use two pointers (i, j)
3. While j < n:
   - If arr[j] - arr[i] < k: all pairs (i,i+1...j-1) with j are valid
   - Else: move i forward
4. Count pairs efficiently

Why it works:
- Sorting ensures difference calculation is simple (arr[j] - arr[i])
- When arr[j] - arr[i] < k, all elements between i and j-1 also satisfy condition
- Two-pointer technique gives O(n) after sorting

Time Complexity: O(n log n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPairs(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());

        int i = 0, j = 1;
        int count = 0;

        while (j < n) {
            if (arr[j] - arr[i] < k) {
                count += (j - i);
                j++;
            } else {
                i++;
            }
        }

        return count;
    }
};
