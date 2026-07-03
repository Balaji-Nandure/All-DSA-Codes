/*
    Problem Name: Powerful Integer
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given a 2D integer array intervals[][] of length n, where each intervals[i] = [start, end] represents a closed interval (i.e., all integers from start to end, inclusive). You are also given an integer k. An integer is called Powerful if it appears in at least k intervals. Find the maximum Powerful Integer.
    If no integer occurs at least k times return -1.

    Expected Complexities:
    Time Complexity: O(N log N), where N is the number of intervals. Inserting at most 2N endpoints into a map takes O(N log N) time. Iterating through the map takes O(N) time.
    Space Complexity: O(N) to store the endpoints in the map.

    Love Babbar Style Approach:
    1. The problem asks us to find the maximum integer that appears in at least `k` intervals. Since the interval ranges can be huge (up to 10^9), we cannot use a simple array for frequency counting.
    2. Instead, we can use the "Line Sweep" algorithm combined with a Map. A map perfectly keeps our keys (points on the line) sorted in ascending order.
    3. For every interval `[start, end]`, we mark the entry and exit points:
       - Increment the count at `start` by 1 (`mp[start]++`)
       - Decrement the count just after `end` by 1 (`mp[end + 1]--`)
    4. By iterating through the sorted keys of the map, we maintain a running sum (`curr_count`) which represents the number of overlapping active intervals at any given point.
    5. As we move from one key to the next `point`, if the `curr_count` (the number of active intervals BEFORE adding the current point's difference) is `>= k`, it means all integers strictly before `point` were present in at least `k` intervals.
    6. Since we want the MAXIMUM integer, the largest integer in that valid segment is simply `point - 1`. We keep track of the maximum of all such valid `point - 1` values!
    7. Update `curr_count` by adding the map's difference at `point` and continue.
    8. Return the maximum value found, or -1 if no such integer exists.

    Dry Run:
    Input: n = 3, intervals = [[1, 3], [4, 6], [3, 4]], k = 2
    Map updates:
    [1, 3] -> mp[1]++, mp[4]--
    [4, 6] -> mp[4]++, mp[7]--
    [3, 4] -> mp[3]++, mp[5]--
    
    Sorted Map state after processing all intervals:
    1:  1
    3:  1
    4:  0 (since +1 -1 cancels out)
    5: -1
    7: -1

    Iteration:
    - point = 1, diff =  1: curr_count was 0. Now curr_count = 1.
    - point = 3, diff =  1: curr_count was 1 (< 2). Now curr_count = 2.
    - point = 4, diff =  0: curr_count was 2 (>= 2). Valid range ends at 4-1 = 3. max_val = max(-1, 3) = 3. Now curr_count = 2.
    - point = 5, diff = -1: curr_count was 2 (>= 2). Valid range ends at 5-1 = 4. max_val = max(3, 4) = 4. Now curr_count = 1.
    - point = 7, diff = -1: curr_count was 1 (< 2). Now curr_count = 0.
    
    Result = 4. Matches Expected Output!
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int powerfullInteger(int n, vector<vector<int>> &intervals, int k) {
        map<int, int> mp;
        
        // Populate the difference array using a map for the line sweep
        for (int i = 0; i < n; i++) {
            mp[intervals[i][0]]++;
            mp[intervals[i][1] + 1]--;
        }
        
        int max_val = -1;
        int curr_count = 0;
        
        // Iterate through the sorted points
        for (auto it : mp) {
            int point = it.first;
            int diff = it.second;
            
            // If the active intervals before this point were >= k
            // Then the range up to point - 1 is valid. The max integer in it is point - 1.
            if (curr_count >= k) {
                max_val = max(max_val, point - 1);
            }
            
            // Update the running count of active intervals
            curr_count += diff;
        }
        
        return max_val;
    }
};

int main() {
    int t;
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n;
            
            vector<vector<int>> intervals(n, vector<int>(2));
            for (int i = 0; i < n; i++) {
                cin >> intervals[i][0] >> intervals[i][1];
            }
            cin >> k;
            
            Solution ob;
            cout << ob.powerfullInteger(n, intervals, k) << "\n";
        }
    }
    return 0;
}
