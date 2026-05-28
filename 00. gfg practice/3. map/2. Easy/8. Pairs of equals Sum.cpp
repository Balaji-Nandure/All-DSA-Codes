/*
Problem: Pairs of equals Sum

Given an array arr. Find if there are two pairs (a, b) and (c, d) such that a+b = c+d.

Constraints:
1 <= arr.size() <= 10^3
1 <= arr[i] <= 10^4

--------------------------------------------------

Pattern:
Hashing / Set (Pair Generation)

--------------------------------------------------

Key Observation:
- We need to find if there are at least two distinct pairs of indices whose elements sum to the exact same value.
- The array size is up to 1000. Generating all possible pairs takes O(N^2) time, which is ~1,000,000 operations. This is perfectly fine for a typical 1-second time limit.
- We can iterate through all unique pairs `(arr[i], arr[j])` where `i < j`, calculate their sum, and check if we have seen this sum before using a Hash Set.
- The very first time we encounter a sum that is already in our set, we can guarantee that two pairs with an equal sum exist.

--------------------------------------------------

Approach:
1. Initialize an `unordered_set<int> sums` to keep track of the pair sums we've observed.
2. Use a nested loop to generate all unique pairs:
    a. Outer loop `i` from `0` to `n - 1`.
    b. Inner loop `j` from `i + 1` to `n - 1`.
3. For each pair, calculate `sum = arr[i] + arr[j]`.
4. If `sum` exists in `sums`, it means we've previously found a different pair with this exact sum. Return `true`.
5. If `sum` doesn't exist, insert it into `sums`.
6. If both loops complete without finding any duplicate sums, return `false`.

--------------------------------------------------

Time Complexity: O(N^2) as we generate all possible pairs from the array, with set insertions/lookups taking O(1) on average.
Space Complexity: O(N^2) in the absolute worst case to store every unique sum in the hash set.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/pairs-of-equals-sum/1
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool findPairs(vector<int>& arr) {
        unordered_set<int> sums;
        int n = arr.size();
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int sum = arr[i] + arr[j];
                
                // If we've seen this sum before, we found two equal pairs
                if (sums.find(sum) != sums.end()) {
                    return true;
                }
                
                // Store the sum of the current pair
                sums.insert(sum);
            }
        }
        
        return false;
    }
};
