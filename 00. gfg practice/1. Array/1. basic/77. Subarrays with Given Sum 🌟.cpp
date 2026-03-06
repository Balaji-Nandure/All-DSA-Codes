/*
 * Problem: Subarrays with Given Sum
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/subarrays-with-given-sum/1
 * 
 * Given an unsorted array arr[] of integers and a sum k. Count the number of 
 * subarrays that add to the given number k.
 * 
 * Examples:
 * Input: arr[] = [10, 2, -2, -20, 10], k = -10
 * Output: 3
 * Explanation: Subarrays with sum -10 are: 
 * [10, 2, -2, -20], [2, -2, -20, 10] and [-20, 10].
 * 
 * Input: arr[] = [1, 4, 20, 3, 10, 5], k = 33
 * Output: 1
 * Explanation: Subarray [4, 20, 3, 10] has sum 33.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * -10^6 ≤ arr[i], k ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Use prefix sum technique with hash map
 * - Key insight: If prefixSum[j] - prefixSum[i-1] = k, then subarray[i...j] has sum k
 * - Rearranging: prefixSum[i-1] = prefixSum[j] - k
 * - For each position j, check if (currentSum - k) exists in hash map
 * - Hash map stores: prefixSum → count of occurrences
 * - Add current prefix sum to map after checking
 * - Handle edge case: initialize map with {0 → 1} for subarrays starting from index 0
 * 
 * Time: O(n) - single pass through array
 * Space: O(n) - hash map for prefix sums
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findSubArraySum(vector<int> arr, int k) {
        
        unordered_map<int, int> prefixSumCount;
        
        int count = 0;
        int currentSum = 0;
        
        // Initialize with 0 sum occurring once (for subarrays starting from index 0)
        prefixSumCount[0] = 1;
        
        for(int i = 0; i < arr.size(); i++) {
            
            // Update current prefix sum
            currentSum += arr[i];
            
            // Check if (currentSum - k) exists in map
            // This means there's a subarray ending at current index with sum k
            if(prefixSumCount.count(currentSum - k)) {
                count += prefixSumCount[currentSum - k];
            }
            
            // Add current prefix sum to map
            prefixSumCount[currentSum]++;
        }
        
        return count;
    }
};