/*
 * Problem: Swap and Maximize
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/swap-and-maximize4038/1
 * 
 * Given an array of positive integers (circular array). We can rearrange elements 
 * in any order. Maximize: |a1 - a2| + |a2 - a3| + ... + |an - a1|
 * 
 * Example: (assuming example from problem)
 * Input: arr[] = [4, 2, 1, 8]
 * Output: 18
 * Explanation: Rearrange as 1, 8, 2, 4: |1-8| + |8-2| + |2-4| + |4-1| = 7+6+2+3 = 18
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(n log n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Sort the array to have elements in order
 * - Create new arrangement by alternating smallest and largest
 * - Use two pointers: left (smallest), right (largest)
 * - Build temp array: push arr[left], arr[right], increment left, decrement right
 * - Handle odd length by placing middle element
 * - Compute circular absolute difference sum using (i+1)%n
 * - This maximizes the sum by placing small next to large values
 * 
 * Time: O(n log n) - sorting dominates
 * Space: O(n) - temporary array for rearrangement
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long int maxSum(vector<int>& arr) {
        
        int n = arr.size();
        
        sort(arr.begin(), arr.end());
        
        vector<int> temp;
        temp.reserve(n);
        
        int left = 0;
        int right = n - 1;
        
        // Alternate smallest and largest
        while (left <= right) {
            
            if (left == right) {
                temp.push_back(arr[left]);
                break;
            }
            
            temp.push_back(arr[left]);
            temp.push_back(arr[right]);
            
            left++;
            right--;
        }
        
        long long sum = 0;
        
        // Calculate circular absolute difference
        for (int i = 0; i < n; i++) {
            sum += abs(temp[i] - temp[(i + 1) % n]);
        }
        
        return sum;
    }
};
