/*
 * Problem: Majority Element
 * 
 * LeetCode: https://leetcode.com/problems/majority-element/
 * GeeksforGeeks: https://www.geeksforgeeks.org/majority-element/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/majority-element-1587115620/1
 * 
 * LeetCode 169: Majority Element
 * 
 * Given an array nums of size n, return the majority element.
 * 
 * The majority element is the element that appears more than ⌊n / 2⌋ times.
 * You may assume that the majority element always exists in the array.
 * 
 * Example 1:
 * Input: nums = [3,2,3]
 * Output: 3
 * 
 * Example 2:
 * Input: nums = [2,2,1,1,1,2,2]
 * Output: 2
 * 
 * Constraints:
 * - n == nums.length
 * - 1 <= n <= 5 * 10^4
 * - -10^9 <= nums[i] <= 10^9
 * 
 * Approach:
 * - Method 1: Boyer-Moore Voting Algorithm (Optimal) - O(n) time, O(1) space
 *   Track a candidate and count, increment count for same element, decrement for different
 *   If count becomes 0, change candidate. Final candidate is majority element.
 * 
 * - Method 2: Hash Map - O(n) time, O(n) space
 *   Count frequency of each element, return element with frequency > n/2
 * 
 * - Method 3: Sorting - O(n log n) time, O(1) space
 *   Sort array, middle element is majority (since it appears > n/2 times)
 * 
 * Time: O(n) - single pass (optimal method)
 * Space: O(1) - constant extra space (optimal method)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: Boyer-Moore Voting Algorithm (Optimal) - O(n) time, O(1) space
    int majorityElement(vector<int>& nums) {
        int candidate = nums[0];
        int count = 1;
        
        // Phase 1: Find candidate
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == candidate) {
                count++;
            } else {
                count--;
                if (count == 0) {
                    candidate = nums[i];
                    count = 1;
                }
            }
        }
        
        // Phase 2: Verify candidate (if problem doesn't guarantee majority exists)
        // Since problem guarantees majority exists, we can return directly
        // But for completeness, we can verify:
        count = 0;
        for (int num : nums) {
            if (num == candidate) {
                count++;
            }
        }
        
        // Return candidate if it's majority, otherwise -1 (shouldn't happen)
        return (count > nums.size() / 2) ? candidate : -1;
    }
    
    // APPROACH 2: Hash Map - O(n) time, O(n) space
    int majorityElementHashMap(vector<int>& nums) {
        unordered_map<int, int> freq;
        int n = nums.size();
        
        // Count frequency of each element
        for (int num : nums) {
            freq[num]++;
            
            // If frequency > n/2, return immediately
            if (freq[num] > n / 2) {
                return num;
            }
        }
        
        return -1;  // Should not reach here
    }
    
    // APPROACH 3: Sorting - O(n log n) time, O(1) space
    int majorityElementSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        // Since majority element appears more than n/2 times,
        // it must be at the middle position
        return nums[nums.size() / 2];
    }
    
    // APPROACH 4: Brute Force - O(n^2) time, O(1) space
    int majorityElementBrute(vector<int>& nums) {
        int n = nums.size();
        int majorityCount = n / 2;
        
        for (int num : nums) {
            int count = 0;
            for (int x : nums) {
                if (x == num) {
                    count++;
                }
            }
            if (count > majorityCount) {
                return num;
            }
        }
        
        return -1;
    }
    
};
