/*
 * Problem: Generating All Subarrays
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/generating-subarrays-using-recursion/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/subarray-range-with-given-sum0128/1
 * 
 * Given an array arr[] of size N, generate all possible subarrays (contiguous subarrays).
 * 
 * Note: 
 * - A subarray is a contiguous part of an array
 * - For array of size n, there are n*(n+1)/2 subarrays
 * 
 * Example 1:
 * Input: arr[] = {1, 2, 3}
 * Output: 
 * [1]
 * [1, 2]
 * [1, 2, 3]
 * [2]
 * [2, 3]
 * [3]
 * 
 * Example 2:
 * Input: arr[] = {1, 2}
 * Output:
 * [1]
 * [1, 2]
 * [2]
 * 
 * Constraints:
 * - 1 <= N <= 100
 * - 0 <= arr[i] <= 10^5
 * 
 * Approach:
 * - Use nested loops: outer loop for starting index, inner loop for ending index
 * - For each starting index i, consider all subarrays starting at i
 * - Print/store each subarray from index i to j (where j >= i)
 * 
 * Time: O(n^3) - n^2 subarrays, each printed in O(n)
 * Space: O(1) - excluding output storage
 */

#include <bits/stdc++.h>
using namespace std;

// APPROACH 2: Store all subarrays in a vector
vector<vector<int>> getAllSubarrays(int arr[], int n) {
    vector<vector<int>> result;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            vector<int> subarray;
            for (int k = i; k <= j; k++) {
                subarray.push_back(arr[k]);
            }
            result.push_back(subarray);
        }
    }
    
    return result;
}
