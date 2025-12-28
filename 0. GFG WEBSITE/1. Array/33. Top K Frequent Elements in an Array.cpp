/*
 * Problem: Top K Frequent Elements
 * 
 * LeetCode: https://leetcode.com/problems/top-k-frequent-elements/
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-k-numbers-occurrences-given-array/
 * Practice: https://practice.geeksforgeeks.org/problems/top-k-frequent-elements-in-array/1
 * 
 * Given an integer array nums and an integer k, return the k most frequent elements.
 * You may return the answer in any order.
 * 
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 * Explanation: 1 appears 3 times, 2 appears 2 times. Return [1,2]
 * 
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 * 
 * Constraints:
 * - 1 <= nums.length <= 10^5
 * - -10^4 <= nums[i] <= 10^4
 * - k is in the range [1, the number of unique elements in the array]
 * - It is guaranteed that the answer is unique.
 * 
 * Approach:
 * - Method 1: Hash Map + Min Heap (Optimal) - O(n log k) time, O(n) space
 *   Count frequencies, use min heap of size k to get top k elements
 * 
 * - Method 2: Hash Map + Sorting - O(n log n) time, O(n) space
 *   Count frequencies, sort by frequency, return top k
 * 
 * - Method 3: Bucket Sort - O(n) time, O(n) space
 *   Use array of lists indexed by frequency (when frequencies are bounded)
 * 
 * - Method 4: QuickSelect - O(n) average time, O(n) space
 *   Use quickselect to find k-th most frequent element
 * 
 * Time: O(n log k) - hash map + min heap (optimal method)
 * Space: O(n) - hash map and heap
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Hash Map + Min Heap - O(n log k) Time and O(n) Space
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // Count frequencies
        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Min heap to store k most frequent elements
        // Pair: (frequency, element) - min heap by frequency
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        for (auto& [num, count] : freq) {
            if (pq.size() < k) {
                pq.push({count, num});
            } else if (count > pq.top().first) {
                pq.pop();
                pq.push({count, num});
            }
        }
        
        // Extract results from heap
        vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }
        
        // Reverse to get in descending order of frequency (optional)
        reverse(result.begin(), result.end());
        
        return result;
    }
    
};