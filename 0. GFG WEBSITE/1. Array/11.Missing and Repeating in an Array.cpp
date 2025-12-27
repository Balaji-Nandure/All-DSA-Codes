/*
 * Problem: Find Missing and Repeating Number
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/find-missing-and-repeating2512/1
 * 
 * Given an unsorted array arr of size N of positive integers. One number 'A' 
 * from set {1, 2, …N} is missing and one number 'B' occurs twice in array. 
 * Find numbers A and B.
 * 
 * Example 1:
 * Input: N = 2, arr[] = {2, 2}
 * Output: 2 1
 * Explanation: Repeating number is 2 and missing number is 1.
 * 
 * Example 2:
 * Input: N = 3, arr[] = {1, 3, 3}
 * Output: 3 2
 * Explanation: Repeating number is 3 and missing number is 2.
 * 
 * Example 3:
 * Input: N = 4, arr[] = {1, 2, 3, 3}
 * Output: 3 4
 * Explanation: Repeating number is 3 and missing number is 4.
 * 
 * Constraints:
 * - 1 <= N <= 10^6
 * - 1 <= arr[i] <= N
 * 
 * Approach:
 * - Method 1: Using equations (sum and sum of squares)
 *   Let S = sum of array, S2 = sum of squares
 *   Let expected sum = n*(n+1)/2, expected sum of squares = n*(n+1)*(2n+1)/6
 *   Let x = repeating, y = missing
 *   x - y = S - expected_sum
 *   x^2 - y^2 = S2 - expected_sum_squares
 *   Solve for x and y
 * 
 * - Method 2: Using XOR (bit manipulation)
 * - Method 3: Using hash map
 * - Method 4: Using array as hash map (marking visited)
 * 
 * Time: O(n) - single pass
 * Space: O(1) - constant extra space (optimal methods)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    // APPROACH 4: Using Array as Hash Map (Marking visited) - O(n) time, O(1) space
    // How it works:
    // - Every number from 1 to n should appear once. We use index mapping to track existing numbers.
    // - For each number, map its value to an index (number x -> index x-1).
    // - Mark the presence by negating the value at that index.
    // - If we encounter a number whose spot is already negative, it's the repeated number.
    // - Afterwards, the index whose value is positive (unmarked) did not occur in the array, so that's the missing number.
    vector<int> findTwoElementMarking(vector<int>& arr, int n) {
        int repeating = 0, missing = 0;
        
        // Step 1: Mark visited numbers by making their corresponding index negative
        for (int i = 0; i < n; i++) {
            int index = abs(arr[i]) - 1;          // Value x should be at index x-1
            if (arr[index] < 0) {                 // Already negative? This number appeared before (repeating)
                repeating = abs(arr[i]);
            } else {
                arr[index] = -arr[index];         // Mark it as visited by making negative
            }
        }
        
        // Step 2: Find the index that is still positive (never visited), that's the missing number
        for (int i = 0; i < n; i++) {
            if (arr[i] > 0) {         // Positive value means index i+1 never appeared
                missing = i + 1;
                break;
            }
        }
        
        // --- DRY RUN ---
        /*
        Example: arr = [1, 3, 3], n = 3
        Step 1: Marking visited
            i=0: arr[0]=1 -> index=0. arr[0] becomes -1. => arr=[-1,3,3]
            i=1: arr[1]=3 -> index=2. arr[2] becomes -3. => arr=[-1,3,-3]
            i=2: arr[2]=-3 -> abs(-3)=3, index=2. arr[2]=-3 already < 0, so repeating=3.

        Step 2: Find missing
            i=0: arr[0]=-1 (<0) continue
            i=1: arr[1]=3 (>0) so missing=2

        Result: {repeating, missing} = {3, 2}
        */
        
        return {repeating, missing};
    }
    
};
