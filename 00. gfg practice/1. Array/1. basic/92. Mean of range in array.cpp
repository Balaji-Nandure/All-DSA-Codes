/*
Problem: Mean of range in array

Approach:
1. Build prefix sum array
2. For each query:
   - Get range sum using prefix
   - Divide by count → floor mean

Why it works:
- Prefix sum allows constant time range sum query

Time Complexity: O(n + q)
Space Complexity: O(n)

GFG: https://www.geeksforgeeks.org/problems/mean-of-range-in-array/1
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findMean(int arr[], int n, int queries[], int q) {
    
    // Step 1: Build prefix sum
    vector<long long> prefix(n);
    
    prefix[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    // Step 2: Process queries
    vector<int> result;

    for (int i = 0; i < 2 * q; i += 2) {
        
        int l = queries[i];
        int r = queries[i + 1];

        long long sum;

        if (l == 0) {
            sum = prefix[r];
        } else {
            sum = prefix[r] - prefix[l - 1];
        }

        int count = r - l + 1;

        result.push_back(sum / count); // floor automatically
    }

    return result;
}
