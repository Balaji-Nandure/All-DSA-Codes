/*
* Problem: Find k largest elements in an array
* 
* GeeksforGeeks: https://www.geeksforgeeks.org/k-largest-elements-in-an-array/
* Practice: https://practice.geeksforgeeks.org/problems/k-largest-elements4206/1
* 
* Given an array of N positive integers, print the k largest elements from the array.
* 
* Example 1:
* Input: arr[] = {12, 5, 787, 1, 23}, k = 2
* Output: 787 23
* Explanation: The two largest elements are 787 and 23
* 
* Example 2:
* Input: arr[] = {1, 23, 12, 9, 30, 2, 50}, k = 3
* Output: 50 30 23
* Explanation: The three largest elements are 50, 30, and 23
* 
* Constraints:
* - 1 <= k <= n <= 10^5
* - 1 <= arr[i] <= 10^6
* 
* Approach:
* - Method 1: Min Heap (Optimal) - O(n log k) time, O(k) space
*   Use min heap of size k to maintain k largest elements
*   For each element, if heap size < k, add it
*   Otherwise, if element > heap top, pop top and push element
* 
* - Method 2: Sorting - O(n log n) time, O(1) space
*   Sort array in descending order, return first k elements
* 
* - Method 3: Max Heap - O(n log n) time, O(n) space
*   Insert all elements in max heap, pop k times
* 
* - Method 4: QuickSelect - O(n) average time, O(1) space
*   Use quickselect to find k-th largest, return all >= k-th largest
* 
* Time: O(n log k) - min heap (optimal method)
* Space: O(k) - min heap
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [Expected Approach] Min Heap - O(n log k) Time and O(k) Space
    vector<int> kLargest(vector<int>& arr, int k) {
        int n = arr.size();
        
        // Min heap to store k largest elements
        priority_queue<int, vector<int>, greater<int>> pq;
        
        for (int i = 0; i < n; i++) {
            if (pq.size() < k) {
                pq.push(arr[i]);
            } else if (arr[i] > pq.top()) {
                pq.pop();
                pq.push(arr[i]);
            }
        }
        
        // Extract results from heap
        vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top());
            pq.pop();
        }
        
        // Reverse to get in descending order
        reverse(result.begin(), result.end());
        
        
        return result;
    }
    
};
