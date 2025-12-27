/*
 * Problem: Single Number
 * 
 * LeetCode: https://leetcode.com/problems/single-number/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-element-appears-array-every-element-appears-twice/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/single-number1014/1
 * 
 * LeetCode 136: Single Number
 * 
 * Given a non-empty array of integers nums, every element appears twice except 
 * for one. Find that single one.
 * 
 * You must implement a solution with a linear runtime complexity and use only 
 * constant extra space.
 * 
 * Example 1:
 * Input: nums = [2,2,1]
 * Output: 1
 * 
 * Example 2:
 * Input: nums = [4,1,2,1,2]
 * Output: 4
 * 
 * Example 3:
 * Input: nums = [1]
 * Output: 1
 * 
 * Constraints:
 * - 1 <= nums.length <= 3 * 10^4
 * - -3 * 10^4 <= nums[i] <= 3 * 10^4
 * - Each element in the array appears twice except for one element which appears only once.
 * 
 * Approach:
 * - Use XOR bitwise operation
 * - XOR properties: a ^ a = 0, a ^ 0 = a, XOR is commutative and associative
 * - XOR all numbers: pairs cancel out (a^a=0), only single number remains
 * - This works because XOR of same numbers gives 0, and 0 XOR any number = that number
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 1: XOR Bit Manipulation (Optimal) - LeetCode Style
    int singleNumber(vector<int>& nums) {
        int result = 0;
        
        // XOR all numbers
        // Pairs will cancel out (a^a=0), only single number remains
        for (int num : nums) {
            result ^= num;
        }
        
        return result;
    }
    
    // APPROACH 2: Using Hash Map (O(n) space)
    int singleNumberHashMap(vector<int>& nums) {
        unordered_map<int, int> freq;
        
        // Count frequency of each number
        for (int num : nums) {
            freq[num]++;
        }
        
        // Find the number with frequency 1
        for (auto& pair : freq) {
            if (pair.second == 1) {
                return pair.first;
            }
        }
        
        return -1;  // Should not reach here
    }
    
    // APPROACH 3: Using Set (O(n) space)
    int singleNumberSet(vector<int>& nums) {
        unordered_set<int> seen;
        
        for (int num : nums) {
            // If already seen, remove it (it's a pair)
            if (seen.find(num) != seen.end()) {
                seen.erase(num);
            } else {
                // First time seeing this number
                seen.insert(num);
            }
        }
        
        // Only single number remains in set
        return *seen.begin();
    }
    
    // APPROACH 5: Sorting (O(n log n) time, O(1) space if in-place)
    int singleNumberSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        // Check pairs
        for (int i = 0; i < nums.size() - 1; i += 2) {
            if (nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
        
        // If we reach here, single number is at the end
        return nums[nums.size() - 1];
    }

    // APPROACH 1: Brute Force (O(n^2) time, O(1) space)
    int singleNumberBruteForce(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (nums[i] == nums[j]) {
                    count++;
                }
            }
            if (count == 1) {
                return nums[i];
            }
        }
        return -1; // Should not reach here if input is valid
    }
};
