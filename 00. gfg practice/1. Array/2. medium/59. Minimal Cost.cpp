/*
PROBLEM: Minimal Cost (Frog Jump with K Distance)
------------------------------------------------
Given:
- arr[i] = height of ith stone
- From i -> can jump to i+1, i+2, ..., i+k
- Cost = abs(arr[i] - arr[j])

Return:
- Minimum cost to reach last stone

Example:
arr = [10,30,40,50,20], k = 3 -> Output = 30

Constraints:
1 ≤ k ≤ arr.size() ≤ 10^5
0 ≤ arr[i] ≤ 10^4

------------------------------------------------
INTUITION / APPROACH:
------------------------------------------------
Pattern: 1D Dynamic Programming (generalized Frog Jump)

Key Idea:
- This is the classic frog jump problem generalized to k steps
- dp[i] = minimum cost to reach stone i from stone 0
- From any stone i, we can come from any of the previous k stones

Transition:
dp[i] = min(dp[i-j] + abs(arr[i] - arr[i-j])) for j = 1 to k

Base Cases:
dp[0] = 0 (starting point)
dp[1] = abs(arr[1] - arr[0]) (only from 0)

Space Optimization:
- Only need last k values -> use sliding window or deque
- Can maintain circular buffer of size k

------------------------------------------------
TIME COMPLEXITY:
O(n * k) where n = arr.size()

SPACE COMPLEXITY:
O(n) with full DP array
O(k) with space optimization

------------------------------------------------
GFG LINK:
https://www.geeksforgeeks.org/problems/minimal-cost/1

Related:
- Frog Jump (k=2): 30. Frog Jump.cpp
- Similar DP on index problems

------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ---------------- MEMOIZATION ----------------
    // TC: O(n*k)  SC: O(n) + recursion stack
    long long solveMemo(int idx, vector<int>& arr, int k, vector<long long>& dp) {
        
        if(idx == 0) return 0;
        
        if(dp[idx] != -1) return dp[idx];
        
        long long ans = LLONG_MAX;
        
        for(int j = 1; j <= k; j++) {
            if(idx - j >= 0) {
                long long cost = solveMemo(idx - j, arr, k, dp)
                         + abs(arr[idx] - arr[idx - j]);
                
                ans = min(ans, cost);
            }
        }
        
        return dp[idx] = ans;
    }


    // ---------------- TABULATION ----------------
    // TC: O(n*k)  SC: O(n)
    long long solveTab(vector<int>& arr, int k) {
        
        int n = arr.size();
        vector<long long> dp(n, LLONG_MAX);
        
        dp[0] = 0;
        
        for(int i = 1; i < n; i++) {
            
            for(int j = 1; j <= k; j++) {
                
                if(i - j >= 0 && dp[i - j] != LLONG_MAX) {
                    long long cost = dp[i - j] + abs(arr[i] - arr[i - j]);
                    dp[i] = min(dp[i], cost);
                }
            }
        }
        
        return dp[n - 1];
    }


    // ---------------- SPACE OPTIMIZATION ----------------
    // TC: O(n*k)  SC: O(k)
    long long solveSpace(vector<int>& arr, int k) {
        
        int n = arr.size();
        vector<long long> dp(k, 0);   // circular buffer
        
        dp[0] = 0;
        
        for(int i = 1; i < n; i++) {
            
            long long minEnergy = LLONG_MAX;
            
            for(int j = 1; j <= k; j++) {
                
                if(i - j >= 0) {
                    
                    int prevIndex = (i - j) % k;
                    
                    long long cost = dp[prevIndex]
                             + abs(arr[i] - arr[i - j]);
                    
                    minEnergy = min(minEnergy, cost);
                }
            }
            
            dp[i % k] = minEnergy;
        }
        
        return dp[(n - 1) % k];
    }

    // ---------------- MAIN FUNCTION ----------------
    int minimizeCost(int k, vector<int>& arr) {
        
        int n = arr.size();
        
        // Edge case: single element
        if(n == 1) return 0;
        
        // --------- CHOOSE ONE ---------
        
        // 1) Memoization
        // vector<long long> dp(n, -1);
        // return (int)solveMemo(n - 1, arr, k, dp);
        
        // 2) Tabulation (Recommended)
        return (int)solveTab(arr, k);
        
        // 3) Space Optimized
        // return (int)solveSpace(arr, k);
    }
};


/*
ALGORITHM SUMMARY:
--------------------------------
1. dp[i] = min cost to reach stone i from stone 0
2. Transition: dp[i] = min(dp[i-j] + |arr[i] - arr[i-j]|) for j = 1 to k
3. Base: dp[0] = 0
4. Answer: dp[n-1]

Key Insights:
- Generalized frog jump (k=2 is classic frog jump)
- Circular buffer optimization: only need last k values
- Use long long to avoid overflow

Interview Tips:
- Explain why we need O(n*k) time (k choices at each step)
- Mention space optimization with sliding window
- Compare with frog jump (k=2) for intuition

------------------------------------------------
TEST CASES:
--------------------------------
1. arr = [10,30,40,50,20], k = 3 -> 30
2. arr = [20,30,40,20], k = 2 -> 20 (classic frog jump)
3. arr = [10,10,10,10], k = 3 -> 0
4. arr = [100,1,1,100], k = 2 -> 99
5. arr = [1], k = 1 -> 0

------------------------------------------------
*/