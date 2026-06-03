/*
GeeksforGeeks: Frequency Game
Difficulty: Easy

Problem:
Given an array arr[]. The elements of the array consist of positive integers. 
You need to find the largest element with minimum frequency.

Examples:
Input: arr[] = 2 2 5 50 1
Output: 50
Explanation: All elements are having frequency 1 except 2. 
50 is the maximum element with minimum frequency.

Input: arr[] = 3 3 5 5
Output: 5
Explanation: Both 3 and 5 have the same frequency, so 5 should be returned.

Core Idea:
This problem requires two pieces of information for every unique element: its value and its frequency.
A Hash Map (`unordered_map`) naturally gives us exactly this by mapping `element -> frequency`.
Once we build the frequency map, we just need to iterate through it to find the element that has the smallest frequency. 
If there's a tie (multiple elements have the same smallest frequency), we pick the one with the maximum value.

Approach:
1. Initialize an `unordered_map<int, int> freq` to store the count of each element.
2. Iterate through the array `arr` and populate the map (`freq[x]++`).
3. Initialize `min_freq` to a very large value (e.g., `INT_MAX`) and `ans` to `-1`.
4. Iterate through all key-value pairs in the map:
   - If `current_freq < min_freq`:
     - Update `min_freq = current_freq`.
     - Update `ans = current_val`.
   - Else if `current_freq == min_freq`:
     - Update `ans = max(ans, current_val)` to ensure we keep the largest element.
5. Return `ans`.

Time Complexity: O(N) where N is the number of elements in the array. Building the map takes O(N) and traversing the map takes O(U) where U is unique elements (U <= N).
Space Complexity: O(N) to store the elements and frequencies in the map.

GFG Link: https://www.geeksforgeeks.org/problems/frequency-game/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int LargButMinFreq(int arr[], int n) {
        // Step 1: Count frequencies
        unordered_map<int, int> freq;
        for (int i = 0; i < n; i++) {
            freq[arr[i]]++;
        }
        
        int min_freq = INT_MAX;
        int ans = -1;
        
        // Step 2: Find largest element with minimum frequency
        for (auto& entry : freq) {
            int val = entry.first;
            int count = entry.second;
            
            if (count < min_freq) {
                // Found a new strict minimum frequency
                min_freq = count;
                ans = val;
            } else if (count == min_freq) {
                // Tie on minimum frequency, pick the maximum value
                ans = max(ans, val);
            }
        }
        
        return ans;
    }
};

/*
Dry Run — Example 1:
Input: arr[] = [2, 2, 5, 50, 1]

1. Build freq map:
   freq[2] = 2
   freq[5] = 1
   freq[50] = 1
   freq[1] = 1

2. Iterate over map (order may vary, but let's assume {2:2, 5:1, 50:1, 1:1}):
   - min_freq = INT_MAX, ans = -1
   
   - entry (2, 2):
     count(2) < min_freq(INT_MAX) -> min_freq = 2, ans = 2
     
   - entry (5, 1):
     count(1) < min_freq(2) -> min_freq = 1, ans = 5
     
   - entry (50, 1):
     count(1) == min_freq(1) -> ans = max(ans(5), val(50)) = 50
     
   - entry (1, 1):
     count(1) == min_freq(1) -> ans = max(ans(50), val(1)) = 50

3. Final ans = 50.

Output: 50
*/
