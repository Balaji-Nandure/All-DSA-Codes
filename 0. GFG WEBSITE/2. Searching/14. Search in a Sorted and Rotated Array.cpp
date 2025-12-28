/*
 * Problem: Search in Rotated Sorted Array
 * 
 * LeetCode: https://leetcode.com/problems/search-in-rotated-sorted-array/
 * GeeksforGeeks: https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
 * Practice: https://practice.geeksforgeeks.org/problems/search-in-a-rotated-array4618/1
 * 
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at an unknown 
 * pivot index k (1 <= k < nums.length) such that the resulting array is 
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
 * 
 * Given the array nums after the rotation and an integer target, return the index 
 * of target if it is in nums, or -1 if it is not in nums.
 * 
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * Explanation: 0 is at index 4 in the rotated array
 * 
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * Explanation: 3 is not in the array
 * 
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 * 
 * Constraints:
 * - 1 <= nums.length <= 5000
 * - -10^4 <= nums[i] <= 10^4
 * - All values of nums are unique
 * - nums is an ascending array that is possibly rotated
 * - -10^4 <= target <= 10^4
 * 
 * Approach:
 * - Method 1: Binary Search (Optimal) - O(log n) time, O(1) space
 *   At least one half is always sorted
 *   Check which half is sorted, then check if target is in that sorted half
 *   If yes, search in sorted half; else search in other half
 * 
 * - Method 2: Find Pivot then Binary Search - O(log n) time, O(1) space
 *   First find the pivot point, then binary search in appropriate half
 * 
 * - Method 3: Linear Search - O(n) time, O(1) space
 *   Traverse array and find target
 * 
 * Time: O(log n) - binary search (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Binary Search - O(log n) Time and O(1) Space
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Found target
            if (nums[mid] == target) {
                return mid;
            }
            
            // Check which half is sorted
            if (nums[left] <= nums[mid]) {
                // Left half is sorted
                if (nums[left] <= target && target < nums[mid]) {
                    // Target is in sorted left half
                    right = mid - 1;
                } else {
                    // Target is in right half
                    left = mid + 1;
                }
            } else {
                // Right half is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    // Target is in sorted right half
                    left = mid + 1;
                } else {
                    // Target is in left half
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
    
    // APPROACH 2: Find Pivot then Binary Search - O(log n) Time and O(1) Space
    int searchWithPivot(vector<int>& nums, int target) {
        int n = nums.size();
        
        // Find pivot (smallest element index)
        int pivot = findPivot(nums);
        
        // If no pivot found, array is not rotated
        if (pivot == -1) {
            return binarySearch(nums, 0, n - 1, target);
        }
        
        // If target is at pivot
        if (nums[pivot] == target) {
            return pivot;
        }
        
        // Decide which half to search
        if (target >= nums[0] && target <= nums[pivot - 1]) {
            // Search in left half (before pivot)
            return binarySearch(nums, 0, pivot - 1, target);
        } else {
            // Search in right half (from pivot to end)
            return binarySearch(nums, pivot, n - 1, target);
        }
    }
    
private:
    // Helper: Find pivot (index of smallest element)
    int findPivot(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[right]) {
                // Pivot is in right half
                left = mid + 1;
            } else {
                // Pivot is in left half (including mid)
                right = mid;
            }
        }
        
        return left;
    }
    
    // Helper: Binary search in sorted array
    int binarySearch(vector<int>& nums, int left, int right, int target) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
public:
    // APPROACH 3: Linear Search - O(n) Time and O(1) Space
    int searchLinear(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                return i;
            }
        }
        return -1;
    }
    
    // APPROACH 4: Alternative Binary Search Implementation
    int searchAlt(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            }
            
            // Determine which side is sorted
            bool leftSorted = nums[left] <= nums[mid];
            
            if (leftSorted) {
                // Left side is sorted
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // Right side is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
    
    // APPROACH 5: Check if target exists (return bool)
    bool searchExists(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return true;
            }
            
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return false;
    }
};

int main() {
    Solution sol;
    
    // Test case 1
    vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    cout << "Test 1: " << sol.search(nums1, target1) << endl;  // Expected: 4
    
    // Test case 2
    int target2 = 3;
    cout << "Test 2: " << sol.search(nums1, target2) << endl;  // Expected: -1
    
    // Test case 3
    vector<int> nums3 = {1};
    int target3 = 0;
    cout << "Test 3: " << sol.search(nums3, target3) << endl;  // Expected: -1
    
    // Test case 4: Using pivot approach
    cout << "Test 4 (Pivot): " << sol.searchWithPivot(nums1, target1) << endl;  // Expected: 4
    
    // Test case 5: Using linear search
    cout << "Test 5 (Linear): " << sol.searchLinear(nums1, target1) << endl;  // Expected: 4
    
    return 0;
}

