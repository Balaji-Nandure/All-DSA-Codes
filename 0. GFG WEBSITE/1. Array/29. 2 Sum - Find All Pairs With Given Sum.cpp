/*
 * Problem: 2 Sum - Find All Pairs With Given Sum
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-all-pairs-with-given-sum/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/find-all-pairs-whose-sum-is-x5808/1
 * 
 * Given an array of integers, find all pairs (a, b) such that a + b = target.
 * Return all unique pairs. Each pair should be sorted (a <= b).
 * 
 * Example 1:
 * Input: arr[] = {1, 5, 7, -1, 5}, target = 6
 * Output: (1, 5), (7, -1)
 * Explanation: 1 + 5 = 6, 7 + (-1) = 6
 * 
 * Example 2:
 * Input: arr[] = {2, 5, 17, -1}, target = 7
 * Output: (2, 5)
 * Explanation: 2 + 5 = 7
 * 
 * Example 3:
 * Input: arr[] = {1, 1, 1, 1}, target = 2
 * Output: (1, 1)
 * Explanation: Multiple pairs possible, but return unique pairs
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - -10^5 <= arr[i] <= 10^5
 * - -10^5 <= target <= 10^5
 * 
 * Approach:
 * - Method 1: Hash Map (Optimal) - O(n) time, O(n) space
 *   For each number, check if (target - num) exists in map
 *   Store frequency to handle duplicates correctly
 * 
 * - Method 2: Sorting and Two Pointers - O(n log n) time, O(1) space
 *   Sort array, use two pointers from both ends
 *   Handle duplicates by skipping same values
 * 
 * - Method 3: Brute Force - O(n^2) time, O(1) space
 * 
 * Time: O(n) - single pass (hash map approach)
 * Space: O(n) - hash map storage
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Hash Map - O(n) Time and O(n) Space
    vector<pair<int, int>> allPairs(vector<int>& arr, int n, int target) {
        vector<pair<int, int>> result;
        unordered_map<int, int> freq;  // Store frequency of each number
        
        for (int num : arr) {
            int complement = target - num;
            
            // If complement exists in map, form pairs
            if (freq.find(complement) != freq.end()) {
                // Add pairs: (complement, num) where complement <= num
                int count = freq[complement];
                for (int i = 0; i < count; i++) {
                    if (complement <= num) {
                        result.push_back({complement, num});
                    } else {
                        result.push_back({num, complement});
                    }
                }
            }
            
            // Add current number to map
            freq[num]++;
        }
        
        // Sort result to ensure consistent ordering
        sort(result.begin(), result.end());
        
        return result;
    }
    
};
