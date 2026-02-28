/*
 * Problem: Kth Distance
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/kth-distance3757/1
 * 
 * Given an unsorted array arr[] and an integer k. Return true if there exists 
 * any duplicate element such that the distance between its two occurrences ≤ k. 
 * Otherwise return false.
 * 
 * Example:
 * arr = [1, 2, 3, 1, 4, 5], k = 3
 * Index difference of 1 → |3 - 0| = 3 → valid → return true
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ k ≤ arr.size()
 * -10^9 ≤ arr[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Use sliding window with unordered_set to track elements in current window
 * - For each element, check if it already exists in the set (duplicate within k)
 * - Insert current element into set
 * - If set size exceeds k, remove the element that is now out of window
 * - Window always maintains elements from i-k to i
 * - If duplicate found, return true; else false after full traversal
 * 
 * Time: O(n) - each element processed once
 * Space: O(min(n, k)) - set stores at most k elements
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkDuplicatesWithinK(vector<int>& arr, int k) {
        
        unordered_set<int> window;
        
        for (int i = 0; i < arr.size(); i++) {
            
            // If already present → duplicate within k
            if (window.find(arr[i]) != window.end())
                return true;
            
            window.insert(arr[i]);
            
            // Maintain window size
            if (window.size() > k)  
                window.erase(arr[i - k]);
        }
        
        return false;
    }
};
