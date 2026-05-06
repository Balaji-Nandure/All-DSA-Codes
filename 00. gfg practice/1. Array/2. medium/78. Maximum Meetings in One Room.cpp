/*
Problem: Maximum Meetings in One Room

GFG: https://www.geeksforgeeks.org/problems/maximum-meetings-in-one-room/1

Description:
Given two arrays s[] and f[], where s[i] denotes the start time and f[i] denotes the finish time of the i-th meeting. There is only one meeting room, find the maximum number of meetings that can be scheduled in the room such that no two selected meetings overlap in time. Return the indices(1-based) of the selected meetings in sorted (increasing) order.

Note: If two meetings can be chosen for the same slot then choose meeting that finishes earlier.

Examples:

Input: s[] = [1, 3, 0, 5, 8, 5], f[] = [2, 4, 6, 7, 9, 9] 
Output: [1, 2, 4, 5]
Explanation:
We can attend the 1st meeting from (1 to 2), then the 2nd meeting from (3 to 4), then the 4th meeting from (5 to 7), and the last meeting we can attend is the 5th from (8 to 9). It can be shown that this is the maximum number of meetings we can attend.

Input: s[] = [3] , f[] = [7]
Output: [1]
Explanation:
Since there is only one meeting, we can attend the meeting.

Constraints:
1 ≤ s.size() = f.size() ≤ 10^5
0 ≤ s[i] ≤ f[i] ≤ 10^9

Approach (Greedy - Activity Selection):
1. Store meetings as: (finish, start, index)
2. Sort by finish time (ascending)
3. Traverse:
   - pick first meeting
   - for next: if start > last_end → pick it

Why it works:
- Always pick meeting that finishes earliest
- Leaves maximum room for future meetings
- Greedy approach ensures optimal selection

Important: Use strict condition (start > last_end) not (start >= last_end)

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxMeetings(vector<int>& s, vector<int>& f) {
        
        int n = s.size();
        
        // (finish, start, index)
        vector<tuple<int,int,int>> meetings;
        
        for (int i = 0; i < n; i++) {
            meetings.push_back({f[i], s[i], i + 1});
        }
        
        // Sort by finish time
        sort(meetings.begin(), meetings.end());
        
        vector<int> result;
        
        int lastEnd = -1;
        
        for (auto &m : meetings) {
            // int finish = get<0>(m);
            // int start  = get<1>(m);
            // int idx    = get<2>(m);
            auto [finish, start, idx] = m;
            
            // Strict condition
            if (start > lastEnd) {
                result.push_back(idx);
                lastEnd = finish;
            }
        }
        
        // Return indices in sorted order
        sort(result.begin(), result.end());
        
        return result;
    }
};
