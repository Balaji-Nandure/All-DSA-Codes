/*
 * Problem: Contains Duplicate II
 * 
 * LeetCode: https://leetcode.com/problems/contains-duplicate-ii/
 * 
 * LeetCode 219: Contains Duplicate II
 * 
 * Given an integer array nums and an integer k, return true if there are two 
 * distinct indices i and j in the array such that nums[i] == nums[j] and 
 * abs(i - j) <= k.
 * 
 * Example 1:
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 * Explanation: nums[0] = nums[3] and abs(0 - 3) = 3 <= 3
 * 
 * Example 2:
 * Input: nums = [1,0,1,1], k = 1
 * Output: true
 * Explanation: nums[2] = nums[3] and abs(2 - 3) = 1 <= 1
 * 
 * Example 3:
 * Input: nums = [1,2,3,1,2,3], k = 2
 * Output: false
 * Explanation: All duplicates are more than k positions apart
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^9 <= nums[i] <= 10^9
 * - 0 <= k <= 10^5
 * 
 * Approach:
 * - Use a hash map to store the last seen index of each number
 * - For each element, check if we've seen it before within k distance
 * - If yes, return true; otherwise update the map with current index
 * - This maintains a sliding window of size k+1
 * 
 * Time: O(n) - single pass through the array
 * Space: O(min(n, k)) - hash map stores at most k+1 elements
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Hash Map (Optimal) - LeetCode Style
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> lastIndex;  // value -> last seen index
        
        for (int i = 0; i < nums.size(); i++) {
            // If we've seen this number before
            if (lastIndex.find(nums[i]) != lastIndex.end()) {
                // Check if distance is <= k
                if (abs(i - lastIndex[nums[i]]) <= k) {
                    return true;
                }
            }
            // Update the last seen index
            lastIndex[nums[i]] = i;
        }
        
        return false;
    }
    
    // APPROACH 2: Sliding Window with Set (Alternative)
    // Maintain a set of size k+1, if we see duplicate in window, return true
    bool containsNearbyDuplicateSet(vector<int>& nums, int k) {
        unordered_set<int> window;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove element that's out of window (if window size > k)
            if (i > k) {
                window.erase(nums[i - k - 1]);
            }
            
            // If current element exists in window, we found a duplicate
            if (window.find(nums[i]) != window.end()) {
                return true;
            }
            
            // Add current element to window
            window.insert(nums[i]);
        }
        
        return false;
    }

    
    // APPROACH 3: Brute Force (O(n*k)) - Not optimal but simple
    bool containsNearbyDuplicateBrute(vector<int>& nums, int k) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j <= i + k && j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};