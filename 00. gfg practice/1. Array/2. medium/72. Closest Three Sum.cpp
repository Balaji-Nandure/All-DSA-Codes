/*
Problem: Closest Three Sum

GFG: https://www.geeksforgeeks.org/problems/closest-three-sum/1

Description:
Given an array, arr[] of integers, and another number target, find three integers in the array such that their sum is closest to the target. Return the sum of the three integers.

Note: If there are multiple solutions, return the maximum one.

Examples:

Input: arr[] = [-7, 9, 8, 3, 1, 1], target = 2
Output: 2
Explanation: There is only one triplet present in the array where elements are -7,8,1 whose sum is 2.

Input: arr[] = [5, 2, 7, 5], target = 13
Output: 14
Explanation: There is one triplet with sum 12 and other with sum 14 in the array. Triplet elements are 5, 2, 5 and 2, 7, 5 respectively. Since abs(13-12) == abs(13-14) maximum triplet sum will be preferred i.e 14.

Constraints:
3 ≤ arr.size() ≤ 10^3
-10^5 ≤ arr[i] ≤ 10^5
1 ≤ target ≤ 10^5

Approach (Sorting + Two Pointer):
1. Sort array
2. Fix one element (i)
3. Use two pointers:
   left = i + 1
   right = n - 1

4. Compute:
   sum = arr[i] + arr[left] + arr[right]

5. Compare:
   - If closer → update answer
   - If equal diff → take MAX sum

6. Move pointers:
   - If sum < target → increase sum → left++
   - If sum > target → decrease sum → right--

Why it works:
- Sorting enables efficient two-pointer scanning
- Helps move toward target intelligently
- Two-pointer technique explores all possible triplets in O(n^2)
- Tie-breaking rule ensures maximum sum when distances are equal

Time Complexity: O(n^2)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int closest3Sum(vector<int>& arr, int target) {
        
        int n = arr.size();
        
        sort(arr.begin(), arr.end());
        
        int best = arr[0] + arr[1] + arr[2]; // initial answer
        
        for (int i = 0; i < n - 2; i++) {
            
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                
                int sum = arr[i] + arr[left] + arr[right];
                
                // Update best answer
                if (abs(sum - target) < abs(best - target)) {
                    best = sum;
                }
                else if (abs(sum - target) == abs(best - target)) {
                    best = max(best, sum); // tie → take maximum
                }
                
                // Move pointers
                if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return best;
    }
};
