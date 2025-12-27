/*
 * Problem: Trapping Rain Water
 * 
 * LeetCode: https://leetcode.com/problems/trapping-rain-water/
 * GeeksforGeeks: https://www.geeksforgeeks.org/trapping-rain-water/
 * Practice: https://practice.geeksforgeeks.org/problems/trapping-rain-water-1587115621/1
 * 
 * Given n non-negative integers representing an elevation map where the width 
 * of each bar is 1, compute how much water it can trap after raining.
 * 
 * Example 1:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by 
 * array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water 
 * (blue section) are being trapped.
 * 
 * Example 2:
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 * 
 * Constraints:
 * - n == height.length
 * - 1 <= n <= 2 * 10^4
 * - 0 <= height[i] <= 10^5
 * 
 * Approach:
 * - Method 1: Two Pointers (Optimal) - O(n) time, O(1) space
 *   Use two pointers from both ends, track max left and max right
 *   Water trapped = min(maxLeft, maxRight) - height[i]
 * 
 * - Method 2: Stack - O(n) time, O(n) space
 *   Use stack to track decreasing heights, calculate water when height increases
 * 
 * - Method 3: Prefix/Suffix Max Arrays - O(n) time, O(n) space
 *   Precompute max left and max right for each position
 * 
 * - Method 4: Brute Force - O(n^2) time, O(1) space
 *   For each position, find max left and max right
 * 
 * Time: O(n) - two pointers approach (optimal method)
 * Space: O(1) - two pointers approach (optimal method)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Two Pointers - O(n) Time and O(1) Space
    // Function to compute how much trapped rain water can be calculated
    // from the given elevation map using the two pointers approach
    int trap(vector<int>& arr) {
        int n = arr.size();
        int left = 1;
        int right = arr.size() - 2;
        int lMax = arr[0];
        int rMax = arr[n - 1];

        int res = 0;
        while (left <= right) {
        
            // If rMax is smaller, then we can 
            // decide the amount of water for arr[right]
            if (rMax <= lMax) {
            
                // Add the water for arr[right]
                res += max(0, rMax - arr[right]);

                // Update right max
                rMax = max(rMax, arr[right]);

                // Update right pointer as we have 
                // decided the amount of water for this
                right -= 1;
            } else { 
                // Add the water for arr[left]
                res += max(0, lMax - arr[left]);

                // Update left max
                lMax = max(lMax, arr[left]);

                // Update left pointer as we have 
                // decided water for this
                left += 1;
            }
        }
        return res;
    }

    
    // APPROACH 6: Optimized Prefix/Suffix (Single Pass) - O(n) Time and O(n) Space
    int trapOptimized(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;
        
        vector<int> leftMax(n), rightMax(n);
        
        // Fill leftMax array
        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }
        
        // Fill rightMax array and calculate water simultaneously
        rightMax[n - 1] = height[n - 1];
        int water = 0;
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
            water += min(leftMax[i], rightMax[i]) - height[i];
        }
        
        return water;
    }
    
    // [Naive Approach] Brute Force - O(n^2) Time and O(1) Space
    int trapBrute(vector<int>& height) {
        int n = height.size();
        if (n <= 2) return 0;
        
        int water = 0;
        
        for (int i = 1; i < n - 1; i++) {
            // Find max height to the left
            int maxLeft = 0;
            for (int j = 0; j < i; j++) {
                maxLeft = max(maxLeft, height[j]);
            }
            
            // Find max height to the right
            int maxRight = 0;
            for (int j = i + 1; j < n; j++) {
                maxRight = max(maxRight, height[j]);
            }
            
            // Calculate trapped water at position i
            int minHeight = min(maxLeft, maxRight);
            if (minHeight > height[i]) {
                water += minHeight - height[i];
            }
        }
        
        return water;
    }
    
};

int main() {
    Solution sol;
    
    // Test case 1
    vector<int> height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Test 1: " << sol.trap(height1) << endl;  // Expected: 6
    
    // Test case 2
    vector<int> height2 = {4, 2, 0, 3, 2, 5};
    cout << "Test 2: " << sol.trap(height2) << endl;  // Expected: 9
    
    return 0;
}
