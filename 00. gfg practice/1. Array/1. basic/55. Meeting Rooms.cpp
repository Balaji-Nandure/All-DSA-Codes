/*
 * Problem: Meeting Rooms
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/meeting-rooms/1
 * 
 * Given a 2D array arr[][], where arr[i][0] is the starting time of ith meeting 
 * and arr[i][1] is the ending time of ith meeting, the task is to check if it is 
 * possible for a person to attend all the meetings such that he can attend only 
 * one meeting at a particular time.
 * 
 * Note: A person can attend a meeting if its starting time is greater than or 
 * equal to the previous meeting's ending time.
 * 
 * Examples:
 * Input: arr[][] = [[1, 4], [10, 15], [7, 10]]
 * Output: true
 * Explanation: Since all the meetings are held at different times, it is possible 
 * to attend all the meetings.
 * 
 * Input: arr[][] = [[2, 4], [9, 12], [6, 10]]
 * Output: false
 * Explanation: Since the second and third meeting overlap, a person cannot attend 
 * all the meetings.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 2*10^6
 * 
 * Expected Time Complexity: O(N log N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Sort the meetings by their start times
 * - Iterate through the sorted meetings
 * - For each meeting, check if its start time is less than the previous meeting's end time
 * - If overlap found, return false
 * - If no overlaps, return true
 * - This checks for non-overlapping intervals efficiently after sorting
 * 
 * Time: O(N log N) - sorting
 * Space: O(1) - no extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool canAttend(vector<vector<int>>& arr) {
        
        int n = arr.size();
        if(n <= 1) return true;
        
        // Sort by start time       
        sort(arr.begin(), arr.end());
        
        for(int i = 1; i < n; i++) {
            
            int prevEnd = arr[i - 1][1];
            int currStart = arr[i][0];
            
            if(currStart < prevEnd)
                return false;
        }
        
        return true;
    }
};
