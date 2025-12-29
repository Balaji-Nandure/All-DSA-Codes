/*
 * Problem: Find Maximum in Rotated Sorted Array
 * 
 * Links for reference:
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-maximum-element-in-a-sorted-and-rotated-array/
 * 
 * There is an integer array nums sorted in ascending order (with distinct values).
 * Prior to being passed to your function, nums is possibly rotated at an unknown 
 * pivot index k (1 <= k < nums.length) such that the resulting array is 
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]].
 * 
 * Find the maximum element in the rotated sorted array.
 * 
 * Example 1:
 * Input: nums = [3,4,5,1,2]
 * Output: 5
 * 
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2]
 * Output: 7
 * 
 * Example 3:
 * Input: nums = [11,13,15,17]
 * Output: 17
 *
 * Constraints:
 * - 1 <= nums.length <= 5000
 * - -10^4 <= nums[i] <= 10^4
 * - All values of nums are unique
 * - nums is an ascending array that is possibly rotated
 * 
 * Approach:
 * - Optimal: Binary Search (O(log n) Time, O(1) Space)
 *   At each step, check if mid element is greater than its next, it's the maximum.
 *   If mid element is greater than the rightmost, maximum lies to the right.
 *   Otherwise, the maximum is in the left half (including mid).
 *   If array is not rotated: return nums[n-1] (last element is max)
 */
 int findMax(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        // Minimum is in right half
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        }
        // Minimum is in left half (including mid)
        else {
            // 🌟🌟🌟🌟
            right = mid;
        }
    }

    // left is minimum, just -1 to left  is maximum;
    // left is index of minimum
    if (left == 0) {
        return nums[nums.size() - 1];
    } else {
        return nums[left - 1];
    }
}


// APPROACH 2: Linear Search - O(n) Time and O(1) Space (for understanding/completeness)
class Solution2 {
public:
    int findMax(vector<int>& nums) {
        int mx = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            mx = max(mx, nums[i]);
        }
        return mx;
    }
};