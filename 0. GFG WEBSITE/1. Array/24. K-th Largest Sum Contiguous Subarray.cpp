/*
 * Problem: K-th Largest Sum Contiguous Subarray
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/k-th-largest-sum-contiguous-subarray/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/k-th-largest-sum-contiguous-subarray/1
 * 
 * Given an array of integers. Write a program to find the K-th largest sum of 
 * contiguous subarray within the array of numbers which has negative and positive numbers.
 * 
 * Example 1:
 * Input: arr[] = {20, -5, -1}, K = 3
 * Output: 14
 * Explanation: All subarray sums: {20, 15, 14, -5, -6, -1}
 *              Sorted: {20, 15, 14, -1, -5, -6}
 *              3rd largest = 14
 * 
 * Example 2:
 * Input: arr[] = {10, -10, 20, -40}, K = 6
 * Output: -10
 * Explanation: All subarray sums: {10, 0, 20, -20, -10, 10, -30, -40, 30, -20}
 *              Sorted: {30, 20, 10, 10, 0, -10, -20, -20, -30, -40}
 *              6th largest = -10
 * 
 * Constraints:
 * - 1 <= N <= 10^5
 * - 1 <= K <= N*(N+1)/2
 * - -10^4 <= arr[i] <= 10^4
 * 
 * Approaches:
 * [Naive Approach - 1] Using Sorting - O(n^2 * log n) Time and O(n^2) Space
 *   Generate all subarray sums, store in array, sort in descending order, return K-th
 * 
 * [Naive Approach - 2] Using Prefix Sum and Sorting - O(n^2 * log n) Time and O(n^2) Space
 *   Use prefix sum to calculate subarray sums efficiently, then sort
 * 
 * [Expected Approach] Using Min Heap - O(n^2 * log k) Time and O(k) Space
 *   Use min heap of size K to maintain K largest sums
 *   For each subarray sum, if heap size < K, add it
 *   Otherwise, if sum > heap top, pop top and push sum
 * 
 * Time: O(n^2 * log k) - optimal approach
 * Space: O(k) - min heap of size k
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Using Min Heap - O(n^2 * log k) Time and O(k) Space
    int kthLargestSumHeap(vector<int>& arr, int k) {
        int n = arr.size();
        // Min heap to store k largest sums found so far
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < n; i++){
            int currSum = 0;
            // Generate all subarrays starting at index i
            for(int j = i; j < n; j++){
                currSum += arr[j]; // sum for subarray arr[i..j]
                
                if(pq.size() < k){
                    pq.push(currSum); // push if heap not full
                } else{
                    pq.push(currSum); // push current sum
                    pq.pop();         // pop smallest so only k largest remain
                }
            }
        }
        
        // Top of the min heap is the k-th largest sum
        return pq.top();
    }
};