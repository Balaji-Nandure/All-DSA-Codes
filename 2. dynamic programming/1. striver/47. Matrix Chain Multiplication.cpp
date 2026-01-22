#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: Matrix Chain Multiplication
LeetCode: N/A (Classic DP problem)
GeeksforGeeks: https://practice.geeksforgeeks.org/problems/matrix-chain-multiplication0303/1

Given an array p[] which represents the chain of matrices such that the ith matrix 
Ai is of dimension p[i-1] x p[i]. We need to write a function that should return 
the minimum number of multiplications needed to multiply the chain.

The dimensions of matrices are given in an array arr[] of size N (such that N = number of matrices + 1)
where arr[i-1] x arr[i] represents the dimension of the ith matrix.

Constraints:
- 2 <= N <= 100
- 1 <= arr[i] <= 500

Example:
arr = [40, 20, 30, 10, 30]
Matrices: A1(40x20), A2(20x30), A3(30x10), A4(10x30)
Optimal: (A1(A2A3))A4 = 26000 multiplications

Key Insight:
- We need to find the optimal way to parenthesize matrix multiplication
- For matrices A[i] x A[j] and A[j] x A[k], cost = i * j * k
- dp[i][j] = minimum cost to multiply matrices from index i to j

DP State: dp[i][j] = minimum number of multiplications needed to multiply 
matrices from index i to j (0-indexed, where matrix i has dimensions arr[i] x arr[i+1])

Recurrence:
- dp[i][j] = min(dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j]) for all k from i to j-1
- For each partition point k, we split into [i..k] and [k+1..j]
- Cost of multiplying result = arr[i-1] * arr[k] * arr[j]

Base Cases:
- dp[i][i] = 0 (single matrix, no multiplication needed)
- dp[i][j] = INF for i > j (invalid range)

Time Complexity: O(n^3) where n is the number of matrices
Space Complexity: O(n^2) for dp array

Note: This is a range DP problem. We fill the table diagonally (by length of chain).
*/

// 1. Recursive approach
class MatrixChainMultiplicationRecursive {
public:
    // TC: O(2^n) exponential, SC: O(n) recursion stack
    int solve(int i, int j, vector<int>& arr) {
        // Base case: single matrix, no multiplication needed
        if (i >= j) return 0;
        
        int minCost = INF;
        
        // Try all possible partition points
        for (int k = i; k < j; k++) {
            // Cost = cost of left part + cost of right part + cost of multiplying them
            int cost = solve(i, k, arr) + solve(k + 1, j, arr) + 
                       arr[i - 1] * arr[k] * arr[j];
            minCost = min(minCost, cost);
        }
        
        return minCost;
    }
    
    int matrixMultiplication(int N, vector<int>& arr) {
        // N is the size of arr, so we have N-1 matrices
        // Matrices are from index 1 to N-1 (1-indexed thinking)
        // But we use 0-indexed, so from 1 to N-2
        return solve(1, N - 1, arr);
    }
};

// 2. Memoization (Top-down DP)
class MatrixChainMultiplicationMemoization {
public:
    // TC: O(n^3), SC: O(n^2) for dp array + O(n) recursion stack
    int solve(int i, int j, vector<int>& arr, vector<vector<int>>& dp) {
        if (i >= j) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        
        int minCost = INF;
        
        for (int k = i; k < j; k++) {
            int cost = solve(i, k, arr, dp) + solve(k + 1, j, arr, dp) + 
                       arr[i - 1] * arr[k] * arr[j];
            minCost = min(minCost, cost);
        }
        
        return dp[i][j] = minCost;
    }
    
    int matrixMultiplication(int N, vector<int>& arr) {
        vector<vector<int>> dp(N, vector<int>(N, -1));
        return solve(1, N - 1, arr, dp);
    }
};
