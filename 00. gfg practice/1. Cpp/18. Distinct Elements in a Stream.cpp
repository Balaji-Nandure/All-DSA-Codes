/*
 * Problem: Distinct Elements in a Stream
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/distinct-elements-in-a-stream/0
 * 
 * Given an array of integers arr[], the task is to return the no of distinct elements in 
 * subarray arr[0, i] for 0 <= i < arr.size(). The array will have positive and negative values. 
 * positive value means you have to append it into your data and negative value means you have 
 * to remove it from your data. Note: If the element is not present in the data and you get 
 * the -ve of that element then no changes should occur.
 * 
 * Examples:
 * Input: arr[] = [5, 5, 7, -5, -7, 1, 2, -2]
 * Output: [1, 1, 2, 2, 1, 2, 3, 2]
 * Explanation: Proper adding and removal of integers will give this output.
 * 
 * Input: arr[] = [9, 9, 3, -9, -3, -9]
 * Output: [1, 1, 2, 2, 1, 0]
 * Explanation: Proper adding and removal of integers will give this output.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * -10^6 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Use a hash map to keep track of frequency of each element in the current data
 * - For positive numbers: increment frequency and add to distinct count if first occurrence
 * - For negative numbers: decrement frequency of absolute value if present, remove from distinct count if frequency becomes 0
 * - Maintain current distinct count and add to result after each operation
 * - Handle edge case: trying to remove element not present in data
 * 
 * Time: O(n) - single pass through array
 * Space: O(n) - hash map to store frequencies
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getDistinct(vector<int>& arr) {
        unordered_map<int, int> freq;
        vector<int> result;
        int distinctCount = 0;
        
        for (int x : arr) {
            if (x > 0) {
                // Add positive number
                freq[x]++;
                if (freq[x] == 1) {
                    distinctCount++;
                }
            } else {
                // Remove negative number (use absolute value)
                int absVal = abs(x);
                if (freq[absVal] > 0) {
                    freq[absVal]--;
                    if (freq[absVal] == 0) {
                        distinctCount--;
                    }
                }
                // If element not present, no changes occur
            }
            result.push_back(distinctCount);
        }
        
        return result;
    }
};
