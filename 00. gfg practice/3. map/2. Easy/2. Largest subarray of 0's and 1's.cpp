/*
Problem: Largest subarray of 0's and 1's

Given an array arr of 0s and 1s. Find and return the length of the longest subarray with equal number of 0s and 1s.

Constraints:
1 <= arr.size() <= 10^5
0 <= arr[i] <= 1

--------------------------------------------------

Pattern:
Prefix Sum + Hash Map

--------------------------------------------------

Key Observation:
- If we treat all `0`s in the array as `-1`, the problem neatly translates to finding the longest subarray with a sum equal to 0.
- A subarray sum of 0 between two indices implies that the running prefix sum at both these points is exactly the same.
- We can maintain a hash map that stores the very first time we see each unique prefix sum.
- When we see a prefix sum again at a later index, the difference between the current index and the initially recorded index gives the length of the valid subarray.

--------------------------------------------------

Approach:
1. Initialize an `unordered_map<int, int> preSum` to store the first occurrence index of each prefix sum.
2. Initialize `sum = 0` and `max_len = 0`.
3. Iterate through the array `arr` with index `i`:
    a. If `arr[i] == 0`, add `-1` to `sum`. Else, add `1` to `sum`.
    b. If `sum == 0`, it means the subarray right from index `0` to `i` is balanced. Update `max_len = max(max_len, i + 1)`.
    c. Check if the current `sum` is already recorded in the map:
        - If it is, we found a balanced subarray. Calculate its length as `i - preSum[sum]` and update `max_len` if it's larger.
        - If it is not, store `sum` along with its index `i` into the map (we only store the first occurrence to maximize the length later).
4. Return `max_len`.

--------------------------------------------------

Time Complexity: O(N) as we traverse the array of length N once, and unordered_map lookups take O(1) on average.
Space Complexity: O(N) to store the prefix sums and their first occurrence indices in the hash map.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/largest-subarray-of-0s-and-1s/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxLen(vector<int>& arr) {
        unordered_map<int, int> preSum;
        int sum = 0;
        int max_len = 0;
        
        for (int i = 0; i < arr.size(); ++i) {
            sum += (arr[i] == 0) ? -1 : 1;
            
            if (sum == 0) {
                max_len = max(max_len, i + 1);
            }
            
            if (preSum.find(sum) != preSum.end()) {
                max_len = max(max_len, i - preSum[sum]);
            } else {
                preSum[sum] = i;
            }
        }
        
        return max_len;
    }
};
