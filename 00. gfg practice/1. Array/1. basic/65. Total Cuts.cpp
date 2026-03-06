/*
 * Problem: Total Cuts
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/total-cuts/1
 * 
 * You are given an array A of N integers and an integer K. Find the total number 
 * of cuts that you can make such that for each cut these two conditions are satisfied:
 * 1. A cut divides an array into two parts of equal or unequal length (non-zero).
 * 2. Sum of the largest element in the left part and the smallest element in the 
 *    right part is greater than or equal to K.
 * 
 * Examples:
 * Input: N=3, K=3, A[]={1,2,3}
 * Output: 2
 * Explanation: Two valid cuts:
 * {1} and {2,3} → 1+2 = 3 ≥ 3 (satisfies)
 * {1,2} and {3} → 2+3 = 5 ≥ 3 (satisfies)
 * 
 * Input: N=5, K=5, A[]={1,2,3,4,5}
 * Output: 3
 * Explanation: Three valid cuts:
 * {1,2} and {3,4,5} → 2+3 = 5 ≥ 5 (satisfies)
 * {1,2,3} and {4,5} → 3+4 = 7 ≥ 5 (satisfies)
 * {1,2,3,4} and {5} → 4+5 = 9 ≥ 5 (satisfies)
 * 
 * Constraints:
 * 1 ≤ N ≤ 10^6
 * 0 ≤ K ≤ 10^6
 * 0 ≤ A[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(N)
 * 
 * Approach:
 * - For each possible cut position i (1 to N-1), we need:
 *   max(A[0...i-1]) + min(A[i...N-1]) ≥ K
 * - Precompute suffix minimum array: suffixMin[i] = min(A[i...N-1])
 * - Compute prefix maximum on the fly while iterating through cuts
 * - For cut at position i: check if currentMax + suffixMin[i] ≥ K
 * - Count all valid cuts
 * 
 * Time: O(N) - two passes for suffix preprocessing and counting
 * Space: O(N) - only for suffix minimum array (reduced from 2N to N)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int totalCuts(int N, int K, vector<int> &A) {
        
        // Precompute suffix minimum
        vector<int> suffixMin(N);
        suffixMin[N-1] = A[N-1];
        
        for(int i = N-2; i >= 0; i--) {
            suffixMin[i] = min(suffixMin[i+1], A[i]);
        }
        
        // Count valid cuts with prefix maximum computed on the fly
        int totalCuts = 0;
        int maxLeft = A[0];  // Running maximum of left part
        
        for(int i = 1; i < N; i++) {
            // Cut between index i-1 and i
            // Left part: A[0...i-1], Right part: A[i...N-1]
            int minRight = suffixMin[i];
            
            if(maxLeft + minRight >= K) {
                totalCuts++;
            }
            
            // Update running maximum for next iteration
            maxLeft = max(maxLeft, A[i]);
        }
        
        return totalCuts;
    }
};