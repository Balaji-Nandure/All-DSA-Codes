/*
 * Problem: Find the left over element
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/find-the-left-over-element/1
 * 
 * Given an array arr[], the size is reduced by 1 element at each step. In the first 
 * step, the maximum element would be removed, while in the second step, the minimum 
 * element of the remaining array would be removed, in the third step again the maximum, 
 * and so on. Continue this till the array contains only one element. And find the 
 * final element remaining in the array.
 * 
 * Examples:
 * Input: arr[] = [7, 8, 3, 4, 2, 9, 5]
 * Output: 5
 * Explanation: In first step '9' would be removed, in 2nd step '2' will be removed, 
 * in third step '8' will be removed and so on. So the last remaining element would be '5'.
 * 
 * Input: arr[] = [8, 1, 2, 9, 4, 3, 7, 5]
 * Output: 4
 * Explanation: In first step '9' would be removed, in 2nd step '1' will be removed, 
 * in third step '8' will be removed and so on. So the last remaining element would be '4'.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(N log N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Sort the array in ascending order
 * - Use two pointers: left at start, right at end
 * - Alternate removing maximum (from right) and minimum (from left)
 * - Continue until left >= right
 * - The remaining element is the one at left (or right, same position)
 * - This simulates the process efficiently without modifying the array multiple times
 * 
 * Time: O(N log N) - sorting
 * Space: O(1) - no extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int leftOverElement(int arr[], int n) {
        
        sort(arr, arr + n);
        
        int left = 0;
        int right = n - 1;
        bool removeMax = true;
        
        while(left < right) {
            
            if(removeMax)
                right--;
            else
                left++;
            
            removeMax = !removeMax;
        }
        
        return arr[left];   // or arr[right]
    }
};
