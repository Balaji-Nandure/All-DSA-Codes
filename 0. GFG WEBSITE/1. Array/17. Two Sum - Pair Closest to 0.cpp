/*
 * Problem: Two Sum Closest to Zero / Pair with Sum Closest to 0
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/two-elements-whose-sum-is-closest-to-zero/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/two-numbers-with-sum-closest-to-zero1737/1
 * 
 * Given an array of integers, find two numbers such that their sum is closest to 0.
 * Return the sum that is closest to 0.
 * 
 * Example 1:
 * Input: arr[] = {1, 60, -10, 70, -80, 85}
 * Output: -80 and 85 (sum = 5, closest to 0)
 * 
 * Example 2:
 * Input: arr[] = {-1, 1, 2, -4}
 * Output: -1 and 1 (sum = 0, exactly 0)
 * 
 * Example 3:
 * Input: arr[] = {1, 2, 3, 4}
 * Output: 1 and 2 (sum = 3, closest to 0)
 * 
 * Constraints:
 * - 2 <= n <= 10^5
 * - -10^5 <= arr[i] <= 10^5
 * 
 * Approach:
 * - Method 1: Sorting and Two Pointers (Optimal) - O(n log n) time, O(1) space
 *   Sort the array, use two pointers from both ends
 *   Track minimum absolute sum as we move pointers
 * 
 * - Method 2: Brute Force - O(n^2) time, O(1) space
 * 
 * Time: O(n log n) - sorting dominates
 * Space: O(1) - constant extra space (optimal method)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Sorting and Two Pointers (Optimal) - O(n log n) time, O(1) space
    int twoSumClosestToZero(vector<int>& arr) {
        int n = arr.size();
        if (n < 2) {
            return 0;
        }
        
        // Sort the array
        sort(arr.begin(), arr.end());
        
        int left = 0, right = n - 1;
        int minSum = INT_MAX;
        
        while (left < right) {
            int sum = arr[left] + arr[right];
            
            // Update closest sum if current sum is closer to 0
            if (abs(sum) < abs(minSum)) {
                minSum = sum;
            }
            
            // If sum is exactly 0, we found the best answer
            if (sum == 0) {
                return 0;
            }
            
            // Move pointers based on sum
            if (sum < 0) {
                left++;  // Need larger sum, move left pointer right
            } else {
                right--;  // Need smaller sum, move right pointer left
            }
        }
        
        return minSum;
    }
    
    // APPROACH 3: Brute Force - O(n^2) time, O(1) space
    int twoSumClosestToZeroBrute(vector<int>& arr) {
        int n = arr.size();
        int minSum = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int sum = arr[i] + arr[j];
                
                if (abs(sum) < abs(minSum)) {
                    minSum = sum;
                }
                
                if (minSum == 0) {
                    return 0;
                }
            }
        }
        
        return minSum;
    }
    
};
