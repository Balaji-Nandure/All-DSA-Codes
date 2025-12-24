/*
 * Problem: The Number of Beautiful Subsets
 * 
 * LeetCode 2597: The Number of Beautiful Subsets
 * 
 * You are given an array nums of positive integers and a positive integer k.
 * A subset of nums is called beautiful if it does not contain two integers 
 * with an absolute difference equal to k.
 * 
 * Return the number of non-empty beautiful subsets of the array nums.
 * 
 * Example 1:
 * Input: nums = [2,4,6], k = 2
 * Output: 4
 * Explanation: The beautiful subsets of the array nums are: [2], [4], [6], [2, 6].
 * It can be shown that there are only 4 beautiful subsets in [2,4,6].
 * 
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: 1
 * Explanation: The beautiful subset of the array nums is [1].
 * It can be shown that there is only 1 beautiful subset in [1].
 * 
 * Constraints:
 * - 1 <= nums.length <= 20
 * - 1 <= nums[i], k <= 1000
 * 
 * Approach:
 * - Use backtracking to generate all subsets
 * - For each element, check if adding it would violate the constraint
 * - Track which numbers are in the current subset using a frequency map
 * - Before adding an element, check if (element - k) or (element + k) already exists
 * - Count all valid non-empty subsets
 * 
 * Time: O(2^n) - generate all 2^n subsets
 * Space: O(n) - recursion stack depth + frequency map
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Backtracking to count beautiful subsets
    // freq: frequency map to track numbers in current subset
    void backtrack(int idx, vector<int>& nums, int k, unordered_map<int, int>& freq, int& count) {
        // Base case: processed all elements
        if (idx == (int)nums.size()) {
            return;
        }
        
        // NOT PICK: Skip current element
        backtrack(idx + 1, nums, k, freq, count);
        
        // PICK: Try to include nums[idx]
        int num = nums[idx];
        
        // Check if adding this number would violate the constraint
        // We need to check if (num - k) or (num + k) already exists in subset
        if (freq[num - k] == 0 && freq[num + k] == 0) {
            // Safe to add: increment frequency
            freq[num]++;
            count++; // Increment count for this valid non-empty subset
            
            // Recurse to next element
            backtrack(idx + 1, nums, k, freq, count);
            
            // Backtrack: remove from frequency map
            freq[num]--;
        }
    }
    
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int count = 0;
        backtrack(0, nums, k, freq, count);
        return count;
    }
};