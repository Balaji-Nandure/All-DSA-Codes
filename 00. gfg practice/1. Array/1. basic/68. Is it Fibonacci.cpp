/*
 * Problem: Is it Fibonacci
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/is-it-fibonacci/1
 * 
 * Geek defines a new series called Geeky numbers. Here the next number is the 
 * sum of the K preceding numbers. You are given an array of size K, GeekNum[], 
 * where the ith element represents the ith Geeky number. Return its Nth term.
 * 
 * Examples:
 * Input: N = 6, K = 1, GeekNum[] = {4}
 * Output: 4
 * Explanation: Terms are 4, 4, 4, 4, 4, 4 (each term is sum of previous 1 term)
 * 
 * Input: N = 5, K = 3, GeekNum[] = {0, 1, 2}
 * Output: 6
 * Explanation: Terms are 0, 1, 2, 3, 6
 * - 4th term: 0+1+2 = 3
 * - 5th term: 1+2+3 = 6
 * 
 * Constraints:
 * 1 ≤ K < 30
 * 1 ≤ N ≤ 70
 * K ≤ N
 * 0 < GeekNum[] < 100
 * 
 * Expected Time Complexity: O(N)
 * Expected Space Complexity: O(1)
 * 
 * Approach:
 * - Reuse the existing GeekNum array as circular buffer (no extra space!)
 * - Maintain a running sum of K elements to avoid recalculating
 * - For each new term: add it to sum, remove the oldest element
 * - Use modulo arithmetic to implement circular buffer in-place
 * - This reduces time complexity from O(N*K) to O(N) and space to O(1)
 * - Use long long to handle potential integer overflow
 * 
 * Time: O(N) - single pass with constant time updates
 * Space: O(1) - reuse input array, no extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long solve(int N, int K, vector<long long> GeekNum) {
        
        // If N <= K, return the (N-1)th element from given array
        if(N <= K) {
            return GeekNum[N-1];
        }
        
        // Calculate initial sum of first K terms
        long long currentSum = 0;
        for(int i = 0; i < K; i++) {
            currentSum += GeekNum[i];
        }
        
        // Generate remaining terms using GeekNum array as circular buffer
        for(int i = K; i < N; i++) {
            
            // Next term is sum of current K terms
            long long temp = currentSum;
            
            // Update circular buffer and sum in-place
            int pos = i % K;  // Position in circular buffer
            currentSum = currentSum - GeekNum[pos] + temp;
            GeekNum[pos] = temp;  // Reuse GeekNum array!
        }
        
        // Return the last computed term (at position (N-1) % K)
        return GeekNum[(N-1) % K];
    }
};