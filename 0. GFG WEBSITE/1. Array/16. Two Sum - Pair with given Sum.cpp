/*
 * Problem: Two Sum
 * 
 * LeetCode: https://leetcode.com/problems/two-sum/
 * GeeksforGeeks: https://www.geeksforgeeks.org/given-an-array-a-and-a-number-x-check-for-pair-in-a-with-sum-as-x/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/key-pair5616/1
 * 
 * LeetCode 1: Two Sum
 * 
 * Given an array of integers nums and an integer target, return indices of the 
 * two numbers such that they add up to target.
 * 
 * You may assume that each input would have exactly one solution, and you may 
 * not use the same element twice.
 * 
 * You can return the answer in any order.
 * 
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 * 
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 * 
 * Example 3:
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 * 
 * Constraints:
 * - 2 <= nums.length <= 10^4
 * - -10^9 <= nums[i] <= 10^9
 * - -10^9 <= target <= 10^9
 * - Only one valid answer exists.
 * 
 * Approach:
 * - Method 1: Hash Map (Optimal) - O(n) time, O(n) space
 *   For each number, check if (target - num) exists in map
 *   If found, return indices; otherwise add current number to map
 * 
 * - Method 2: Two Pointers (for sorted array) - O(n log n) time, O(1) space
 * - Method 3: Brute Force - O(n^2) time, O(1) space
 * 
 * Time: O(n) - single pass
 * Space: O(n) - hash map storage
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Hash Map (Optimal) - O(n) time, O(n) space
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;  // value -> index
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in map
            if (map.find(complement) != map.end()) {
                return {map[complement], i};
            }
            
            // Store current number and its index
            map[nums[i]] = i;
        }
        
        return {};  // Should not reach here (problem guarantees solution)
    }
    
    // APPROACH 2: Two Pointers (for sorted array) - O(n log n) time, O(1) space
    // Note: This returns values, not indices (since sorting changes indices)
    vector<int> twoSumSorted(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            
            if (sum == target) {
                return {nums[left], nums[right]};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return {};
    }
    
    // APPROACH 4: Brute Force - O(n^2) time, O(1) space
    vector<int> twoSumBrute(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        
        return {};
    }
};
