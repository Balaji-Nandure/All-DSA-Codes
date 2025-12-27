/*
 * Problem: Increasing Triplet Subsequence
 * 
 * LeetCode: https://leetcode.com/problems/increasing-triplet-subsequence/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-a-sorted-subsequence-of-size-3-in-linear-time/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/sorted-subsequence-of-size-3/1
 * 
 * LeetCode 334: Increasing Triplet Subsequence
 * 
 * Given an integer array nums, return true if there exists a triple of indices 
 * (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. 
 * If no such indices exists, return false.
 * 
 * Example 1:
 * Input: nums = [1,2,3,4,5]
 * Output: true
 * Explanation: Any triplet where i < j < k is valid.
 * 
 * Example 2:
 * Input: nums = [5,4,3,2,1]
 * Output: false
 * Explanation: No triplet exists.
 * 
 * Example 3:
 * Input: nums = [2,1,5,0,4,6]
 * Output: true
 * Explanation: The triplet (1, 2, 4) is valid because nums[1] = 1 < nums[2] = 5 < nums[4] = 4.
 *              Actually: nums[2] = 5, nums[4] = 4, nums[5] = 6 -> (2,4,5) works: 5 < 4 < 6? No.
 *              Better: nums[1] = 1, nums[2] = 5, nums[5] = 6 -> (1,2,5): 1 < 5 < 6 ✓
 * 
 * Constraints:
 * - 1 <= nums.length <= 5 * 10^5
 * - -2^31 <= nums[i] <= 2^31 - 1
 * Time: O(n) - single pass
 * Space: O(1) - constant extra space (optimal method)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Method 1: Two Pointers (Optimal) - O(n) time, O(1) space
    // Track smallest and second smallest, if we find a number > both, return true
    // Checks if there exists an increasing subsequence of length 3 (triplet) in nums
    // Time: O(n), Space: O(1)
    bool increasingTriplet(vector<int>& nums) {
        int first = INT_MAX;
        int second = INT_MAX;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= first) {
                first = nums[i];
            }
            else if (nums[i] <= second) {
                second = nums[i];
            }
            else {
                return true;
            }
        }

        return false;
    }
};
