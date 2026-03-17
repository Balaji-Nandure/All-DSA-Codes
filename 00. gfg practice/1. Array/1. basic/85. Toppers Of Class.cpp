/*
 * Problem: Toppers Of Class
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/toppers-of-class/1
 * 
 * There is a class of some students and the task is to find the top k marks scorers. 
 * You need to print the index of the class's toppers, which will be the same as the 
 * student's index in the input array (use 0-based indexing). First, return the index 
 * of the students having the highest marks then the students with second highest and 
 * so on. If more than one student has the same marks then return their indices in 
 * ascending order. Suppose k = 2 and the students having the highest marks have 
 * indices 0 and 5 and students having second highest marks have indices 6 and 7 
 * then output will be 0 5 6 7.
 * 
 * Note: here k will be always less than equal to the number of distinct elements 
 * in marks of students arr[].
 * 
 * Examples:
 * Input: arr[] = [2, 2, 1, 3, 1], k = 3 
 * Output: [3, 0, 1, 2, 4]
 * Explanation: Topper with 3 marks is present at 3rd index, 2 marks is present at 
 * 0th index and next at 1st index. 1 marks is present at 2 and 4.
 * 
 * Input: arr[] = [1, 2, 3, 4], k = 1 
 * Output: [3]
 * Explanation: The highest marks is at index 3.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ k ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^8
 * 
 * Expected Time Complexity: O(N log N)
 * Expected Auxiliary Space: O(N)
 * 
 * Approach:
 * - Sort (marks desc, index asc)
 * - Traverse and pick indices until k distinct marks are covered
 * - This ensures all students with top k marks are included, with same marks indices in ascending order
 * 
 * Time: O(N log N) - sorting
 * Space: O(N) - pairs vector

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> kToppers(vector<int>& arr, int k) {
        
        int n = arr.size();
        vector<pair<int, int>> students;
        
        for(int i = 0; i < n; i++){
            students.push_back({arr[i], i});
        }
        
        // Sort: marks desc, then index asc
        sort(students.begin(), students.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if(a.first != b.first) return a.first > b.first;
            return a.second < b.second;
        });
        
        vector<int> result;
        
        int distinctCount = 0;
        int prevVal = -1;
        
        for(int i = 0; i < n; i++){
            int currVal = students[i].first;
            
            // new distinct value
            if(currVal != prevVal){
                distinctCount++;
                prevVal = currVal;
            }
            
            // stop after k distinct values
            if(distinctCount > k) break;
            
            result.push_back(students[i].second);
        }
        
        return result;
    }
};
