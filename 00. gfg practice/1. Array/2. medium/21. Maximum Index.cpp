/*
Problem: Maximum Index

GFG: https://www.geeksforgeeks.org/find-the-maximum-j-i-such-that-arrj-arri/

Description: Given an array arr of positive integers. You have to return maximum of j - i such that arr[i] < arr[j] and i < j.

Examples:

Input: arr[] = [1, 10]
Output: 1
Explanation: arr[0] < arr[1] so (j-i) is 1-0 = 1.
Input: arr[] = [5, 4, 3]
Output: 0
Explanation: There is no pair that satisfies given condition.
Input: arr[] = [34, 8, 10, 3, 2, 80, 30, 33, 1]
Output: 6
Explanation: In given array arr[1] < arr[7] satisfying required condition(arr[i] < arr[j]) thus giving maximum difference of j - i which is 6(7-1).

Constraints:
1 ≤ arr.size ≤ 105
0 ≤ arr[i] ≤ 109

Striver Intuition:

We need maximum distance j - i such that arr[i] < arr[j].

Brute Force:
Check all pairs (i, j)
Time = O(n^2)

Optimal Approach:
We want to find the maximum j-i where arr[i] < arr[j].

Key insight: We need arr[i] to be as small as possible and arr[j] to be as large as possible.

Build RMax array:
RMax[j] = maximum element from j to n-1

Then use two pointers:
i starts from 0 (left)
j starts from 0 (right)

If arr[i] <= RMax[j]:
- This means we can use current i and j
- Update answer and move j++ to try for larger distance
Else:
- arr[i] is too large, move i++ to find smaller element

Pattern:
Suffix Max + Two Pointer

Time Complexity: O(n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxIndexDiff(vector<int>& arr) {
        int n = arr.size();

        // Build RMax array only
        vector<int> RMax(n);
        RMax[n - 1] = arr[n - 1];
        for(int j = n - 2; j >= 0; j--) {
            RMax[j] = max(arr[j], RMax[j + 1]);
        }

        // Two pointer approach
        int i = 0, j = 0;
        int ans = 0;

        while(i < n && j < n) {
            if(arr[i] <= RMax[j]) {
                ans = max(ans, j - i);
                j++;
            } else {
                i++;
            }
        }

        return ans;
    }
};

/*
Final Summary (Interview Revision):

1. We need arr[i] < arr[j] and maximize j - i.
2. Build RMax[j] = maximum from j to end.
3. Use two pointers: i from left, j from right.
4. If arr[i] <= RMax[j] → valid → update ans, j++
5. Else move i++
6. Time = O(n), Space = O(n)

Memory Trick:
"Build RMax, Two Pointer, Check arr[i] <= RMax[j]"
*/
