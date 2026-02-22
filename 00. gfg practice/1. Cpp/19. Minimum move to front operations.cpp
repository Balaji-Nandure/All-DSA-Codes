/*
 * Problem: Minimum move to front operations
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/minimum-move-to-front-operations/0
 * 
 * Given an array arr[] of distinct integers from 1 to arr.size(), count the minimum 
 * number of moveToFront operations needed to arrange the elements in ascending order.
 * A moveToFront operation picks any element arr[i] and places it at the first position.
 * 
 * Examples:
 * Input: arr[] = [3, 2, 1, 4]
 * Output: 2
 * Explanation: We need to perform moveToFront on 1 and 2 to make the array sorted.
 * 
 * Input: arr[] = [5, 7, 4, 3, 2, 6, 1]
 * Output: 6
 * Explanation: We need to perform moveToFront on 1, 2, 3, 4, 5, and 6 to make the array sorted.
 * 
 * Constraints:
 * 1 <= arr.size() <= 10^6
 * Elements in arr are distinct and range from 1 to arr.size()
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - We want to find the largest suffix of the sequence 1, 2, ..., N that already exists 
 *   in the array in the correct relative order (ending at the last position).
 * - Specifically, we look for the longest subsequence of the form k, k+1, ..., N ending at the end.
 * - We iterate from the end of the array to the beginning.
 * - We maintain a variable 'expected' initialized to N (the largest element).
 * - If we find the 'expected' element, it means this element is in its correct relative position 
 *   with respect to the suffix we have built so far. We then decrement 'expected' to look for the 
 *   next smaller element.
 * - If we don't find 'expected', it means the current element must be moved to the front.
 * - The number of elements remaining to be found (i.e., the final value of 'expected') is the answer.
 * 
 * Time: O(n) - Single pass through the array from right to left.
 * Space: O(1) - Constant extra space.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& arr) {
        int n = arr.size();
        int expected = n;
        
        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {
            // If we find the expected element, we look for the next smaller one
            if (arr[i] == expected) {
                expected--;
            }
        }
        
        // The remaining expected count represents the number of elements 
        // that were not part of the valid suffix subsequence and thus need to be moved.
        return expected;
    }
};
