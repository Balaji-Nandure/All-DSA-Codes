/*
Problem:
Most Frequent Element in an Array

Given an integer array arr[], find the element that appears most frequently.
If multiple elements have the same highest frequency, return the largest among them.

Examples:
Input  : [1, 3, 2, 1, 4, 1]
Output : 1

Input  : [10, 20, 10, 20, 30, 20, 20]
Output : 20

Input  : [1, 2, 2, 4, 1]
Output : 2


Approach (Expected / Optimal – Hashing):
1. Use an unordered_map to count frequency of each element.
2. Maintain:
   - maxFreq → maximum frequency seen so far
   - ans     → element corresponding to maxFreq
3. For each element while updating frequency:
   - If freq > maxFreq → update maxFreq and ans
   - If freq == maxFreq → choose the larger value (tie-breaking rule)
4. Return ans.

Why this works:
- Hashing gives O(1) average-time frequency updates.
- Tie-breaking is handled during traversal itself.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-the-most-frequent-element-in-an-array/

LeetCode:
No direct equivalent problem.
(Related pattern: frequency counting using hash maps)
*/

int mostFrequentElement(vector<int>& arr) {
    unordered_map<int, int> freq;

    int maxFreq = 0;
    int ans = INT_MIN;

    for (int x : arr) {
        freq[x]++;

        // Higher frequency found
        if (freq[x] > maxFreq) {
            maxFreq = freq[x];
            ans = x;
        }
        // Same frequency → pick larger value
        else if (freq[x] == maxFreq) {
            ans = max(ans, x);
        }
    }

    return ans;
}
