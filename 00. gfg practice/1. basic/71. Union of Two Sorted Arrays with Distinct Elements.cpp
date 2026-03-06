/*
 * Problem: Union of Two Sorted Arrays with Distinct Elements
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/union-of-two-sorted-arrays-with-distinct-elements/1
 * 
 * Given two sorted arrays a[] and b[], where each array contains distinct elements, 
 * return the elements in the union of the two arrays in sorted order. Union can be 
 * defined as the set containing distinct elements present in either of the arrays.
 * 
 * Examples:
 * Input: a[] = [1, 2, 3, 4, 5], b[] = [1, 2, 3, 6, 7]
 * Output: 1 2 3 4 5 6 7
 * Explanation: Distinct elements from both arrays: 1 2 3 4 5 6 7.
 * 
 * Input: a[] = [2, 3, 4, 5], b[] = [1, 2, 3, 4]
 * Output: 1 2 3 4 5
 * Explanation: Distinct elements from both arrays: 1 2 3 4 5.
 * 
 * Input: a[] = [1], b[] = [2]
 * Output: 1 2
 * Explanation: Distinct elements from both arrays: 1 2.
 * 
 * Constraints:
 * 1 ≤ a.size(), b.size() ≤ 10^5
 * -10^9 ≤ a[i], b[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(n + m)
 * Expected Auxiliary Space: O(n + m)
 * 
 * Approach:
 * - Use merge technique from merge sort since both arrays are sorted
 * - Use two pointers to traverse both arrays simultaneously
 * - Compare elements and add smaller one to result
 * - Skip duplicates when both elements are equal
 * - Add remaining elements from the non-exhausted array
 * - This maintains sorted order and handles duplicates efficiently
 * 
 * Time: O(n + m) - single pass through both arrays
 * Space: O(n + m) - for result vector
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> findUnion(vector<int> &a, vector<int> &b) {
        
        vector<int> result;
        int i = 0, j = 0;
        int n = a.size(), m = b.size();
        
        // Merge technique: compare elements from both arrays
        while(i < n && j < m) {
            
            if(a[i] < b[j]) {
                result.push_back(a[i]);
                i++;
            }
            else if(a[i] > b[j]) {
                result.push_back(b[j]);
                j++;
            }
            else {
                // Both elements are equal, add only once
                result.push_back(a[i]);
                i++;
                j++;
            }
        }
        
        // Add remaining elements from array a
        while(i < n) {
            result.push_back(a[i]);
            i++;
        }
        
        // Add remaining elements from array b
        while(j < m) {
            result.push_back(b[j]);
            j++;
        }
        
        return result;
    }
};