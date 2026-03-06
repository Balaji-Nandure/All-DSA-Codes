/*
 * Problem: Adding Array Elements
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/adding-array-element4756/1
 * 
 * Given an array Arr[] of size N and an integer K, you have to choose the first two 
 * minimum elements of the array and erase them, then insert the sum of these two 
 * elements in the array until all the elements are greater than or equal to K and 
 * find the number of such operations required.
 * 
 * Examples:
 * Input: N = 6, K = 6, Arr[] = {1, 10, 12, 9, 2, 3}
 * Output: 2
 * Explanation: First we add (1 + 2), now the new list becomes 3 10 12 9 3, then we add 
 * (3 + 3), now the new list becomes 6 10 12 9, Now all the elements in the list are greater 
 * than 6. Hence the output is 2 i.e. 2 operations are required.
 * 
 * Input: N = 4, K = 4, Arr[] = {5, 4, 6, 4}
 * Output: 0
 * Explanation: Every element in the given array is greater than or equal to K.
 * 
 * Constraints:
 * 1 ≤ N, K ≤ 10^5
 * 1 ≤ Arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(N log N)
 * Expected Auxiliary Space: O(N)
 * 
 * Approach:
 * - Use a min-heap (priority_queue with greater) to always access the two smallest elements
 * - While the heap size >= 2 and the smallest element < K, perform the operation:
 *   - Pop the two smallest, sum them, push the sum back
 *   - Increment the operation count
 * - After operations, if the heap is empty or the top < K, return -1 (impossible)
 * - Otherwise, return the operation count
 * - This efficiently simulates the process using heap operations
 * 
 * Time: O(N log N) - heap insertions and extractions
 * Space: O(N) - for the priority queue
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minOperations(int arr[], int n, int k) {
        
        priority_queue<int, vector<int>, greater<int>> pq;
        
        for(int i = 0; i < n; i++){
            pq.push(arr[i]);
        }
        
        int ops = 0;
        
        while(pq.size() >= 2 && pq.top() < k){
            
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();
            
            int sum = a + b;
            pq.push(sum);
            
            ops++;
        }
        
        if(pq.empty() || pq.top() < k){
            return -1;
        }
        
        return ops;
    }
};
