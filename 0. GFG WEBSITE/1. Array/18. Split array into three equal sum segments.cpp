/*
 * Problem: Split Array into Three Equal Sum Segments
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/split-array-three-equal-sum-subarrays/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/split-array-in-three-equal-sum-subarrays/1
 * 
 * Given an array of integers, determine if it can be split into three 
 * non-empty segments with equal sums.
 * 
 * Example 1:
 * Input: arr[] = {1, 3, 4, 0, 4}
 * Output: true
 * Explanation: Split at indices 1 and 3
 *              Segment 1: [1, 3] = 4
 *              Segment 2: [4] = 4
 *              Segment 3: [0, 4] = 4
 * 
 * Example 2:
 * Input: arr[] = {2, 3, 4, 1, 4, 5}
 * Output: false
 * Explanation: Cannot be split into three equal sum segments
 * 
 * Example 3:
 * Input: arr[] = {1, 1, 1, 1, 1, 1}
 * Output: true
 * Explanation: Split at indices 2 and 4
 *              Each segment has sum = 2
 * 
 * Constraints:
 * - 3 <= n <= 10^5
 * - -10^4 <= arr[i] <= 10^4
 * 
 * Approach:
 * - Calculate total sum of array
 * - If total sum is not divisible by 3, return false
 * - Each segment should have sum = totalSum / 3
 * - Find two indices i and j such that:
 *   - Prefix sum at i = totalSum / 3
 *   - Prefix sum at j = 2 * totalSum / 3
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr) {
        int totalSum = 0;
        for (int num : arr) {
            totalSum += num;
        }

        // If total sum is not divisible by 3, impossible
        if (totalSum % 3 != 0) return false;

        int target = totalSum / 3;
        int curSum = 0;
        int count = 0;

        for (int i = 0; i < arr.size(); i++) {
            curSum += arr[i];
            if (curSum == target) {
                count++;
                curSum = 0;
                if (count == 2 && i < arr.size() - 1) {
                    return true;
                }
            }
        }

        return false;
    }
};
    