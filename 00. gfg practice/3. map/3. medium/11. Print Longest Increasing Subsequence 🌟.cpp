/*
    Problem Name: Print Longest Increasing Subsequence
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given an array of integers arr[], return the Longest Increasing Subsequence (LIS) of the given array.
    If multiple LIS of the same maximum length exist, return the one that appears first based on the lexicographical order of their indices.

    Expected Complexities:
    Time Complexity: O(N^2)
    Space Complexity: O(N)

    Optimal Approach (1D DP + Hash Array):
    1. We maintain a 1D DP array `dp` where `dp[i]` stores the length of the LIS ending at index `i`.
    2. We maintain a `hash` array to trace back our choices. `hash[i]` stores the previous index that gave the optimal LIS length for `dp[i]`.
    3. We iterate `i` from 0 to N-1, and for each `i`, we check all previous elements `j` (from 0 to i-1).
    4. If `arr[j] < arr[i]` and picking `arr[j]` gives a strictly better length (`1 + dp[j] > dp[i]`), we update `dp[i]` and set `hash[i] = j`.
       - Using `>` strictly ensures we keep the earliest (lexicographically smallest) index on ties.
    5. We track the overall maximum length (`maxLen`) and its ending index (`lastIndex`).
    6. Finally, we trace back from `lastIndex` using the `hash` array, push the elements into a list, reverse it, and return.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> longestIncreasingSubsequence(int n, vector<int>& arr) {
        // dp[i] stores the max length of LIS ending at index i
        vector<int> dp(n, 1);
        // hash[i] stores the index of the previous element in the LIS
        vector<int> hash(n);
        
        for (int i = 0; i < n; i++) {
            hash[i] = i; // Initially, every element is an LIS of length 1 ending at itself
        }
        
        int maxLen = 1;
        int lastIndex = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // If appending arr[i] to the LIS ending at j creates a longer sequence
                if (arr[j] < arr[i] && 1 + dp[j] > dp[i]) {
                    dp[i] = 1 + dp[j];
                    hash[i] = j; // Remember the path
                }
            }
            // Track the globally longest sequence
            // Using strictly > ensures we keep the earliest index on a tie
            if (dp[i] > maxLen) {
                maxLen = dp[i];
                lastIndex = i;
            }
        }
        
        // Trace back the LIS using the hash array
        vector<int> lis;
        lis.push_back(arr[lastIndex]);
        while (hash[lastIndex] != lastIndex) {
            lastIndex = hash[lastIndex];
            lis.push_back(arr[lastIndex]);
        }
        
        // The elements are collected in reverse order, so we reverse it to get the correct order
        reverse(lis.begin(), lis.end());
        
        return lis;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            
            Solution ob;
            vector<int> res = ob.longestIncreasingSubsequence(n, arr);
            for (int i = 0; i < res.size(); i++) {
                cout << res[i] << (i == res.size() - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }
    return 0;
}
