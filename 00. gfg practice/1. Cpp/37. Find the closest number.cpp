/*
 * Problem: Find the closest number
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/find-the-closest-number5513/1
 * 
 * Given a sorted array arr[] of positive integers. The task is to find the closest 
 * value in the array to the given number k. The array may contain duplicate values.
 * Note: If the difference with k is the same for two values in the array return the greater value.
 * 
 * Examples:
 * Input: arr[] = [1, 3, 6, 7], k = 4
 * Output: 3
 * Explanation: We have array arr={1, 3, 6, 7} and target is 4. If we look at the absolute 
 *              difference of target with every element of the array we will get { |1-4|, |3-4|, |6-4|, |7-4| }  
 *              = {3, 1, 2, 3}. So, the closest number is 3.
 * 
 * Input: arr[] = [1, 2, 3, 5, 6, 8, 9], k = 4
 * Output: 5
 * Explanation: The absolute difference of 4 is 1 from both 3 and 5. According to the question, 
 *              we have to return greater value, which is 5.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ k ≤ 10^9
 * 1 ≤ arr[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(log n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use binary search to find the insertion point for k
 * - Handle edge cases where k is outside array bounds
 * - After binary search, left points to smallest element > k, right to largest element < k
 * - Compare absolute differences between k and arr[left], arr[right]
 * - Return closer element, or greater element if distances are equal
 * - Binary search finds exact match if exists
 * 
 * Time: O(log n) - binary search for position
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findClosest(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        // If k is smaller than first element
        if (k <= arr[0])
            return arr[0];
            
        // If k is larger than last element
        if (k >= arr[n - 1])
            return arr[n - 1];
        
        int left = 0;
        int right = n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == k)
                return arr[mid];
                
            if (arr[mid] < k)
                left = mid + 1;
            else
                right = mid - 1;
        }
        
        // Now:
        // right -> largest element < k
        // left  -> smallest element > k
        
        if (abs(arr[left] - k) < abs(arr[right] - k))
            return arr[left];
        else if (abs(arr[left] - k) > abs(arr[right] - k))
            return arr[right];
        else
            return max(arr[left], arr[right]); // tie case
    }
};
