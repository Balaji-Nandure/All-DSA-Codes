/*
    Problem Name: Count distinct pairs with difference k
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an integer array of size n and a non-negative integer k, count all distinct pairs with a difference equal to k, i.e., |A[i] - A[j]| = k.

    Expected Complexities:
    Time Complexity: O(N), where N is the size of the array. Building the frequency map takes O(N) time, and iterating over the unique elements takes O(N) time.
    Space Complexity: O(N) to store the frequencies of the array elements in a Hash Map.

    Love Babbar Style Approach:
    1. The problem asks for the count of *distinct* pairs with a difference of `k`.
    2. We can use a Hash Map (unordered_map in C++) to store the frequency of each element in the array. This takes O(N) time and O(N) space.
    3. Iterate through each unique element in the Hash Map (`for (auto it : map)`):
       - Case 1 (`k == 0`): Since the difference is 0, we need pairs of the exact same number. A distinct pair of `(x, x)` can only be formed if the frequency of `x` is strictly greater than 1. So, if `it.second > 1`, increment the `count`.
       - Case 2 (`k > 0`): We want pairs `(x, y)` such that `y - x = k`, meaning `y = x + k`. For each unique element `x` in the map, simply check if `x + k` exists in the map. If it does, increment the `count`. We only check `x + k` (and NOT `x - k`) because iterating over all `x` guarantees we'll see every possible pair exactly once, naturally avoiding double-counting!
    4. Return the total `count`.

    Dry Run:
    Input: array = {1, 5, 3}, k = 2
    Map updates:
    mp[1] = 1, mp[5] = 1, mp[3] = 1
    
    Iteration over map:
    - x = 1: check if 1 + 2 = 3 exists in map? Yes! count = 1.
    - x = 5: check if 5 + 2 = 7 exists in map? No. count = 1.
    - x = 3: check if 3 + 2 = 5 exists in map? Yes! count = 2.
    
    Result = 2. Matches Expected Output!
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int TotalPairs(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int count = 0;
        
        // Step 1: Build the frequency map
        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++;
        }
        
        // Step 2: Check for valid pairs
        for (auto it : freq) {
            if (k == 0) {
                // For k == 0, we need at least 2 occurrences of the same number
                if (it.second > 1) {
                    count++;
                }
            } else {
                // For k > 0, we only check for x + k to avoid double counting pairs
                if (freq.find(it.first + k) != freq.end()) {
                    count++;
                }
            }
        }
        
        return count;
    }
};

int main() {
    int t;
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n >> k;
            
            vector<int> nums(n);
            for (int i = 0; i < n; i++) {
                cin >> nums[i];
            }
            
            Solution ob;
            cout << ob.TotalPairs(nums, k) << "\n";
        }
    }
    return 0;
}
