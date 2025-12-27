/*
 * Problem: 3 Sum - Triplet Sum in Array
 * 
 * LeetCode: https://leetcode.com/problems/3sum/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-a-triplet-that-sum-to-a-given-value/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/triplet-sum-in-array-1587115621/1
 * 
 * LeetCode 15: 3Sum
 * 
 * Given an array of integers, find all unique triplets (a, b, c) such that a + b + c = target.
 * The solution set must not contain duplicate triplets.
 * 
 * Example 1:
 * Input: nums = [-1, 0, 1, 2, -1, -4], target = 0
 * Output: [[-1, -1, 2], [-1, 0, 1]]
 * Explanation: 
 * -1 + -1 + 2 = 0
 * -1 + 0 + 1 = 0
 * 
 * Example 2:
 * Input: nums = [0, 1, 1], target = 0
 * Output: []
 * Explanation: No triplets sum to 0
 * 
 * Example 3:
 * Input: nums = [0, 0, 0], target = 0
 * Output: [[0, 0, 0]]
 * 
 * Constraints:
 * - 3 <= n <= 10^3
 * - -10^5 <= nums[i] <= 10^5
 * - -10^5 <= target <= 10^5
 * 
 * Approach:
 * - Method 1: Sorting and Two Pointers (Optimal) - O(n^2) time, O(1) space
 *   Sort array, fix first element, use two pointers for remaining two
 *   Skip duplicates to avoid duplicate triplets
 * 
 * - Method 2: Hash Map - O(n^2) time, O(n) space
 *   For each pair, check if (target - a - b) exists in map
 * 
 * - Method 3: Brute Force - O(n^3) time, O(1) space
 * 
 * Time: O(n^2) - sorting + two nested loops (optimal method)
 * Space: O(1) - constant extra space (optimal method, excluding result array)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Sorting and Two Pointers - O(n^2) Time and O(1) Space
    vector<vector<int>> threeSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n = nums.size();
        
        if (n < 3) return result;
        
        // Sort array to use two-pointer technique
        sort(nums.begin(), nums.end());
        
        // Fix first element
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            int left = i + 1;
            int right = n - 1;
            int targetSum = target - nums[i];
            
            // Two pointers for remaining two elements
            while (left < right) {
                int sum = nums[left] + nums[right];
                
                if (sum == targetSum) {
                    // Found a triplet
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for second element
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    // Skip duplicates for third element
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    
                    left++;
                    right--;
                } else if (sum < targetSum) {
                    left++;  // Need larger sum
                } else {
                    right--;  // Need smaller sum
                }
            }
        }
        
        return result;
    }
    
    // APPROACH 2: Check if triplet exists (GFG style - return true/false)
    bool find3Numbers(vector<int>& arr, int n, int target) {
        if (n < 3) return false;
        
        sort(arr.begin(), arr.end());
        
        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;
            int targetSum = target - arr[i];
            
            while (left < right) {
                int sum = arr[left] + arr[right];
                
                if (sum == targetSum) {
                    return true;
                } else if (sum < targetSum) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return false;
    }
    
};
