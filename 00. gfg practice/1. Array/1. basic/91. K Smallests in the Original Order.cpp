/*
Problem: K Smallest Elements in Original Order

Approach:
1. Copy array and sort it
2. Take first k elements → these are k smallest
3. Store their frequency in unordered_map
4. Traverse original array:
   - If element exists in map → print and decrease frequency

Why it works:
- Sorting ensures we get k smallest values
- Map ensures correct count of duplicates
- Traversing original array preserves order

Time Complexity: O(n log n)
Space Complexity: O(n)

GFG: https://www.geeksforgeeks.org/problems/k-smallest-elements-in-original-order/1
LeetCode: Similar concept (No exact same problem)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> kSmallest(int arr[], int n, int k) {
    
    // Step 1: Copy array
    vector<int> temp(arr, arr + n);

    // Step 2: Sort copy
    sort(temp.begin(), temp.end());

    // Step 3: Store frequency of k smallest
    unordered_map<int, int> freq;
    for (int i = 0; i < k; i++) {
        freq[temp[i]]++;
    }

    // Step 4: Traverse original array and collect answer
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (freq[arr[i]] > 0) {
            result.push_back(arr[i]);
            freq[arr[i]]--;   // decrease count
        }
    }

    return result;
}
