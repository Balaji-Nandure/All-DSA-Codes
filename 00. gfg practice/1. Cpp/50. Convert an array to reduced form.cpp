/*
 * Problem: Convert an array to reduced form
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/convert-an-array-to-reduced-form/1
 * 
 * Given an array with N distinct elements, convert the given array to a reduced form 
 * where all elements are in range from 0 to N-1. The order of elements is same, i.e., 
 * 0 is placed in place of smallest element, 1 is placed for second smallest element, 
 * and N-1 is placed for the largest element.
 * 
 * Note: You don't have to return anything. You just have to change the given array.
 * 
 * Examples:
 * Input: N = 3, Arr[] = {10, 40, 20}
 * Output: 0 2 1
 * Explanation: 10 is the least element so it is replaced by 0. 40 is the largest 
 * element so it is replaced by 3-1 = 2. And 20 is the 2nd smallest element so it is 
 * replaced by 1.
 * 
 * Input: N = 5, Arr[] = {5, 10, 40, 30, 20}
 * Output: 0 1 4 3 2
 * Explanation: As 5 is smallest element, it's replaced by 0. Then 10 is 2nd smallest 
 * element, so it's replaced by 1. Then 20 is 3rd smallest element, so it's replaced by 2. 
 * And so on.
 * 
 * Constraints:
 * 1 ≤ N ≤ 10^5
 * 1 ≤ Arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(N log N)
 * Expected Auxiliary Space: O(N)
 * 
 * Approach:
 * - Create a duplicate vector and copy all elements from the original array
 * - Sort the duplicate vector to get elements in order
 * - Create an unordered_map to map each element to its rank (0-based index in sorted array)
 * - Iterate through the original array and replace each element with its corresponding rank
 * - This ensures the order is preserved while elements are converted to their relative ranks
 * 
 * Time: O(N log N) - dominated by sorting the duplicate array
 * Space: O(N) - for duplicate vector and unordered_map
 */

#include <bits/stdc++.h>
using namespace std;

// User function template for C++
class Solution {
  public:
    // Converts arr[0..n-1] to reduced form.
    void convert(int arr[], int n) {
        // code here
        
        vector<int> dup;
        for(int i = 0; i < n; i++){
            dup.push_back(arr[i]);
        }
        
        sort(dup.begin(), dup.end());
        
        unordered_map<int, int> mp;
        for(int i = 0; i < n; i++){
            mp.insert({dup[i], i});
        }
        
        for(int i = 0; i < n; i++){
            arr[i] = mp[arr[i]];
        }
        
    }
};
