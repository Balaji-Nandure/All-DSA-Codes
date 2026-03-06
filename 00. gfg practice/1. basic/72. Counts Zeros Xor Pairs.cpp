/*
 * Problem: Counts Zeros Xor Pairs
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/counts-zeros-xor-pairs/1
 * 
 * Given an array A[] of size N. Find the number of pairs (i, j) such that
 * Ai XOR Aj = 0, and 1 ≤ i < j ≤ N.
 * 
 * Examples:
 * Input: arr[] = {1, 3, 4, 1, 4}
 * Output: 2
 * Explanation: Index(0, 3) and (2, 4) are pairs whose XOR is zero.
 * 1 XOR 1 = 0 and 4 XOR 4 = 0, so count is 2.
 * 
 * Input: arr[] = {2, 2, 2}
 * Output: 3
 * Explanation: All pairs (0,1), (0,2), (1,2) have XOR = 0.
 * 
 * Constraints:
 * 2 ≤ N ≤ 10^5
 * 1 ≤ A[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(N*Log(N))
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Key insight: A XOR B = 0 if and only if A = B
 * - Count frequency of each element using hash map
 * - For each element with frequency f, number of pairs = f*(f-1)/2
 * - This is the combination formula C(f,2) = f!/(2!(f-2)!) = f*(f-1)/2
 * - Sum up pairs for all unique elements
 * - Use long long to handle potential overflow
 * 
 * Time: O(N) - single pass + hash map operations
 * Space: O(N) - for hash map storage
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    long long int calculate(int a[], int n) {
        
        unordered_map<int, int> mp;
        
        // Count frequency of each element
        for(int i = 0; i < n; i++) {
            mp[a[i]]++;
        }
        
        long long result = 0;
        
        // For each unique element, calculate pairs
        for(auto &x : mp) {
            long long f = x.second;
            
            // Number of pairs from f identical elements = C(f,2) = f*(f-1)/2
            result += (f * (f - 1)) / 2;
        }
        
        return result;
    }
};