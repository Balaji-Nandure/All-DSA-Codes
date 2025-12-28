/*
 * Problem: Find the first repeating element in an array of integers
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-first-repeating-element-array-integers/
 * Practice: https://practice.geeksforgeeks.org/problems/first-repeating-element4018/1
 * 
 * Given an array of integers, find the first element that repeats.
 * If there are multiple repeating elements, return the one whose first occurrence 
 * has the smallest index.
 * 
 * Example 1:
 * Input: arr[] = {10, 5, 3, 4, 3, 5, 6}
 * Output: 5
 * Explanation: 5 is the first element that repeats (first occurrence at index 1)
 * 
 * Example 2:
 * Input: arr[] = {6, 10, 5, 4, 9, 120, 4, 6, 10}
 * Output: 6
 * Explanation: 6 is the first element that repeats (first occurrence at index 0)
 * 
 * Example 3:
 * Input: arr[] = {1, 2, 3, 4}
 * Output: -1
 * Explanation: No repeating element
 * 
 * Constraints:
 * - 1 <= n <= 10^6
 * - 0 <= arr[i] <= 10^6
 * 
 * Approach:
 * - Method 1: Hash Map (Optimal) - O(n) time, O(n) space
 *   Use hash map to store first occurrence index of each element
 *   Traverse again to find element that appears again with smallest first index
 * 
 * - Method 2: Naive Approach - O(n^2) time, O(1) space
 *   For each element, check if it appears again later in array
 *   Return first such element
 * 
 * Time: O(n) - hash map (optimal method)
 * Space: O(n) - hash map
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 3: Hash Map with Set (Track seen elements)
    int firstRepeatedSet(vector<int>& arr) {
        int n = arr.size();
        unordered_set<int> seen;
        
        // Find first element that we've seen before
        for (int i = 0; i < n; i++) {
            if (seen.find(arr[i]) != seen.end()) {
                return arr[i];
            }
            seen.insert(arr[i]);
        }
        
        return -1;
    }
    
    // [Naive Approach] Brute Force - O(n^2) Time and O(1) Space
    int firstRepeatedNaive(vector<int>& arr) {
        int n = arr.size();
        
        // For each element, check if it appears again later
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] == arr[j]) {
                    return arr[i];
                }
            }
        }
        
        return -1;
    }
};