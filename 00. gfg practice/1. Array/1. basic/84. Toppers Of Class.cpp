/*
 * Problem: Toppers Of Class
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/toppers-of-class/1
 * 
 * Find the top k marks scorers and return their indices. Return indices of 
 * students with highest marks first, then second highest, and so on. If multiple 
 * students have same marks, return their indices in ascending order.
 * 
 * Examples:
 * Input: arr[] = [2, 2, 1, 3, 1], k = 3
 * Output: [3, 0, 1, 2, 4]
 * Explanation: 
 * Highest (3): index 3
 * Second highest (2): indices 0, 1 (in ascending order)
 * Third highest (1): indices 2, 4 (in ascending order)
 * 
 * Input: arr[] = [1, 2, 3, 4], k = 1
 * Output: [3]
 * Explanation: Highest marks (4) is at index 3.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ k ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^8
 * 
 * Expected Time Complexity: O(n log n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Create pairs of (marks, index) to maintain association
 * - Sort using custom comparator:
 *   1. Primary: Sort by marks (descending - highest first)
 *   2. Secondary: Sort by index (ascending - smaller index first)
 * - Find k distinct mark values and collect all indices for those marks
 * - Return indices in the required order (grouped by marks, sorted within group)
 * 
 * Time: O(n log n) - sorting dominates
 * Space: O(n) - for pairs and result storage
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    
    // Custom comparator function
    static bool comp(const pair<int, int>& a, const pair<int, int>& b) {
        
        // Primary criteria: marks in descending order (highest first)
        if(a.first != b.first) {
            return a.first > b.first;
        }
        
        // Secondary criteria: index in ascending order (smaller index first)
        return a.second < b.second;
    }
    
    vector<int> kTop(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        // Create pairs of (marks, index)
        vector<pair<int, int>> students;
        
        for(int i = 0; i < n; i++) {
            students.push_back({arr[i], i});
        }
        
        // Sort using custom comparator
        sort(students.begin(), students.end(), comp);
        
        // Collect indices for top k distinct marks
        vector<int> result;
        set<int> distinctMarks;
        
        for(const auto& student : students) {
            
            int marks = student.first;
            int index = student.second;
            
            // Add current marks to set and check if we have k distinct marks
            distinctMarks.insert(marks);
            result.push_back(index);
            
            // Stop when we have collected indices for k distinct marks
            if(distinctMarks.size() == k) {
                break;
            }
        }
        
        return result;
    }
};