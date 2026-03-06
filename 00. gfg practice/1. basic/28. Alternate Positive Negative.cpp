/*
 * Problem: Alternate Positive Negative
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/alternate-positive-negative/0
 * 
 * Given an unsorted array arr containing both positive and negative numbers. 
 * Your task is to rearrange the array and convert it into an array 
 * of alternate positive and negative numbers without changing the relative order.
 * 
 * Note:
 * - Resulting array should start with a positive integer (0 will also be considered as a positive integer).
 * - If any of the positive or negative integers are exhausted, then add the remaining 
 *   integers in the answer as it is by maintaining the relative order.
 * - The array may or may not have equal number of positive and negative integers.
 * 
 * Examples:
 * Input: arr[] = [9, 4, -2, -1, 5, 0, -5, -3, 2]
 * Output: [9, -2, 4, -1, 5, -5, 0, -3, 2]
 * Explanation: The positive numbers are [9, 4, 5, 0, 2] and the negative integers 
 *              are [-2, -1, -5, -3]. Since, we need to start with a positive 
 *              integer first and then negative integer and so on (by maintaining the relative 
 *              order as well), hence we will take 9 from the positive set of elements 
 *              and then -2 after that 4 and then -1 and so on.
 * 
 * Input: arr[] = [-5, -2, 5, 2, 4, 7, 1, 8, 0, -8]
 * Output: [5, -5, 2, -2, 4, -8, 7, 1, 8, 0]
 * Explanation : The positive numbers are [5, 2, 4, 7, 1, 8, 0] and the negative 
 *              integers are [-5,-2,-8]. According to the given conditions, we will start 
 *              from the positive integer 5 and then negative integer and so on. After reaching 
 *              -8 there are no negative elements left, so according to the given rule, we will 
 *              add the remaining elements (in this case positive elements are remaining) as it is 
 *              by maintaining the relative order.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * -10^6 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Separate positive and negative numbers while maintaining relative order
 * - Start with positive numbers first (0 is considered positive)
 * - Alternate between positive and negative lists
 * - Add remaining elements from whichever list has elements left
 * - Single pass through array for separation
 * - Second pass for alternating and adding remaining
 * 
 * Time: O(n) - two passes through array
 * Space: O(n) - storing positive and negative lists
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rearrange(vector<int>& arr) {
        vector<int> pos, neg;
        
        // Separate positive and negative numbers maintaining relative order
        for (int x : arr) {
            if (x >= 0) pos.push_back(x);
            else neg.push_back(x);
        }
        
        int i = 0, j = 0, k = 0;
        
        // Alternate between positive and negative lists
        while (i < pos.size() && j < neg.size()) {
            arr[k++] = pos[i++];
            arr[k++] = neg[j++];
        }
        
        // Add remaining positive elements
        while (i < pos.size()) {
            arr[k++] = pos[i++];
        }
        
        // Add remaining negative elements
        while (j < neg.size()) {
            arr[k++] = neg[j++];
        }
    }
};
