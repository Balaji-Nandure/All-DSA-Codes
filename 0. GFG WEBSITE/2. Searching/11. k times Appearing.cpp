/*
 * Problem: Find all elements in array that appear more than n/k times
 *
 * GeeksforGeeks: https://www.geeksforgeeks.org/print-all-elements-that-appear-more-than-nk-times/
 * 
 * Given an array of size n and a number k, find all elements that appear more than n/k times.
 * 
 * Example:
 * Input: arr[] = {3, 1, 2, 2, 1, 2, 3, 3}, n = 8, k = 4
 * Output: 2 3
 * (Frequency of 2 is 3, frequency of 3 is 3, both > 8/4 = 2)
 * 
 * Approach (Hashing):
 * - Count frequencies using hash map.
 * - Collect elements whose frequency > n/k.
 * 
 * Time: O(n)
 * Space: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> moreThanNdK(vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    int n = arr.size();
    for (int num : arr) {
        freq[num]++;
    }
    vector<int> result;
    for (auto &p : freq) {
        if (p.second > n / k)
            result.push_back(p.first);
    }
    // Optional: sort for consistent output
    sort(result.begin(), result.end());
    return result;
}