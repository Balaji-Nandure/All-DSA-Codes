/*
Problem: Sum of Middle of Two Sorted Arrays

GFG: https://www.geeksforgeeks.org/problems/sum-of-middle-elements-of-two-sorted-arrays2305/1

Description:
Given two sorted integer arrays arr1[] and arr2[] of the same size. Find the sum of the middle elements of two sorted arrays arr1 and arr2.

Examples:

Input: arr1[] = [1, 2, 4, 6], arr2[] = [4, 5, 6, 9]
Output: 9
Explanation: The merged array looks like [1, 2, 4, 4, 5, 6, 6, 9,]. Sum of middle elements is 9 (4 + 5).

Input: arr1[] = [1, 12, 15, 26, 38], arr2[] = [2, 13, 17, 30, 45]
Output: 32
Explanation: The merged array looks like [1, 2, 12, 13, 15, 17, 26, 30, 38, 45]. Sum of middle elements is 32 (15 + 17).

Constraints:
1 ≤ arr1.size() == arr2.size() ≤ 10^3
1 ≤ arr1[i] ≤ 10^6
1 ≤ arr2[i] ≤ 10^6

Approach (Two Pointers - Merge Simulation):
1. Use two pointers i, j
2. Traverse like merge sort
3. Maintain counter
4. When count == n-1 → store first middle
5. When count == n → store second middle
6. Return sum

Why it works:
- Simulates merge process without actually merging
- Middle elements in merged array of size 2n are at positions n-1 and n
- Two-pointer approach finds these positions efficiently

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int SumofMiddleElements(vector<int> &a, vector<int> &b) {
        
        int n = a.size();
        int i = 0, j = 0;
        int count = 0;
        
        int m1 = -1, m2 = -1;
        
        while(i < n && j < n){
            int val;
            
            if(a[i] <= b[j]){
                val = a[i++];
            } else {
                val = b[j++];
            }
            
            count++;  // 🔥 increment FIRST
            
            if(count == n) m1 = val;
            if(count == n + 1){
                m2 = val;
                break;
            }
        }
        
        while(i < n){
            int val = a[i++];
            
            count++;
            
            if(count == n) m1 = val;
            if(count == n + 1){
                m2 = val;
                break;
            }
        }
        
        while(j < n){
            int val = b[j++];
            
            count++;
            
            if(count == n) m1 = val;
            if(count == n + 1){
                m2 = val;
                break;
            }
        }
        
        return m1 + m2;
    }
};

/*
Alternative Approach (Binary Search Partition):

1. Always binary search on smaller array
2. Partition both arrays such that:
   left size = n
3. Check valid partition:
   left1 <= right2 AND left2 <= right1
4. Answer:
   max(left1,left2) + min(right1,right2)

--------------------------------------------------

Time: O(log n)
Space: O(1)

--------------------------------------------------

GFG:
https://www.geeksforgeeks.org/problems/sum-of-middle-elements-of-two-sorted-arrays2305/1

LeetCode:
https://leetcode.com/problems/median-of-two-sorted-arrays/

--------------------------------------------------
*/

class SolutionBS {
public:
    int findMidSum(vector<int>& a, vector<int>& b) {
        int n = a.size();
        
        int low = 0, high = n;
        
        while(low <= high) {
            int cut1 = (low + high) / 2;
            int cut2 = n - cut1;
            
            int l1 = (cut1 == 0) ? INT_MIN : a[cut1 - 1];
            int l2 = (cut2 == 0) ? INT_MIN : b[cut2 - 1];
            
            int r1 = (cut1 == n) ? INT_MAX : a[cut1];
            int r2 = (cut2 == n) ? INT_MAX : b[cut2];
            
            // valid partition
            if(l1 <= r2 && l2 <= r1) {
                return max(l1, l2) + min(r1, r2);
            }
            else if(l1 > r2) {
                high = cut1 - 1;
            }
            else {
                low = cut1 + 1;
            }
        }
        
        return 0; // never happens
    }
};
