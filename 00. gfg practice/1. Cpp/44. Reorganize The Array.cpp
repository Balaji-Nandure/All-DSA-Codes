/*
 * Problem: Reorganize The Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/reorganize-the-array/1
 * 
 * Given an array of elements arr[] with indices ranging from 0 to arr.size() - 1, 
 * your task is to write a program that rearranges the elements of the array such 
 * that arr[i] = i. If an element i is not present in the array, -1 should be placed 
 * at the corresponding index.
 * 
 * Note : The arr[] doesn't contains any duplicate non-negative values.
 * 
 * Examples:
 * Input: arr[] = [-1, -1, 6, 1, 9, 3, 2, -1, 4, -1]
 * Output: [-1, 1, 2, 3, 4, -1, 6, -1, -1, 9]
 * Explanation: Here We can see there are 10 elements. So, the sorted array will look 
 *              like [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] but in our array we are not having 
 *              0, 5, 7 and 8. So, at there places we will be printing -1 and otherplaces 
 *              will be having elements.
 * 
 * Input: arr[] = [2, 0, 1]
 * Output: [0, 1, 2]
 * Explanation: Here We can see all the elements are present so no -1 is returned in array.
 * 
 * Constraints:
 * 0 ≤ arr.size() ≤ 10^5
 * -1 ≤ arr[i] ≤ arr.size()-1
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Create a result array of size n, initialized to -1
 * - Iterate through the input array
 * - For each element arr[i], if it's not -1, place it at result[arr[i]] = arr[i]
 * - This ensures arr[i] = i where the element i exists
 * - Elements not present remain -1 in the result array
 * 
 * Time: O(n) - single pass through array
 * Space: O(n) - result array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> rearrange(vector<int>& arr) {
        
        int n = arr.size();
        
        for (int i = 0; i < n; i++) {
            
            while (arr[i] != -1 && arr[i] != i) {
                
                int correctIndex = arr[i];
                
                // If the correct position already has correct value
                if (arr[correctIndex] == arr[i])
                    break;
                
                swap(arr[i], arr[correctIndex]);
            }
        }
        
        return arr;
    }
};
