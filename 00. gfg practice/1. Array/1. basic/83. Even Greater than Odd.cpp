/*
 * Problem: Even Greater than Odd
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/even-greater-than-odd/1
 * 
 * Rearrange array elements according to 1-based indexing such that:
 * - For every even index i: arr[i] >= arr[i-1]
 * - For every odd index i: arr[i] <= arr[i-1]
 * Return the rearranged array satisfying these conditions.
 * 
 * Examples:
 * Input: arr[] = [1, 2, 2, 1]
 * Output: [1, 2, 1, 2]
 * Explanation: Pattern: small, large, small, large
 * Index 1(odd): 2 >= 1 ✓, Index 2(even): 1 <= 2 ✓, Index 3(odd): 2 >= 1 ✓
 * 
 * Input: arr[] = [1, 3, 2]
 * Output: [1, 3, 2]
 * Explanation: Index 1(odd): 3 >= 1 ✓, Index 2(even): 2 <= 3 ✓
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^4
 * 
 * Expected Time Complexity: O(n log n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Pattern analysis: We need alternating small-large-small-large pattern
 * - Sort the array first to get elements in order
 * - Use two pointers: one for smaller half, one for larger half
 * - Place elements alternately: small at even indices, large at odd indices
 * - This ensures the wave-like pattern satisfying all conditions
 * - Alternative: Sort and then swap adjacent pairs to create wave pattern
 * 
 * Time: O(n log n) - sorting dominates
 * Space: O(1) - in-place rearrangement after sorting
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> rearrangeArray(vector<int>& arr) {
        
        int n = arr.size();
        
        // Sort the array first
        sort(arr.begin(), arr.end());
        
        // Create wave pattern by swapping adjacent pairs
        // This creates: small, large, small, large pattern
        for(int i = 1; i < n; i += 2) {
            swap(arr[i], arr[i-1]);
        }
        
        return arr;
    }
};