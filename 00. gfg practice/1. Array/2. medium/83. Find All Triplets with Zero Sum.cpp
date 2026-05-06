/*
Problem: Find All Triplets with Zero Sum

GFG: https://www.geeksforgeeks.org/problems/find-all-triplets-with-zero-sum/1

Description:
Given an array arr[], find all possible triplets i, j, k in arr[] whose sum of elements is equals to zero. Returned triplet should also be internally sorted i.e. i<j<k.

Examples:

Input: arr[] = [0, -1, 2, -3, 1]
Output: [[0, 1, 4], [2, 3, 4]]
Explanation: Triplets with sum 0 are:
arr[0] + arr[1] + arr[4] = 0 + (-1) + 1 = 0
arr[2] + arr[3] + arr[4] = 2 + (-3) + 1 = 0

Input: arr[] = [1, -2, 1, 0, 5]
Output: [[0, 1, 2]]
Explanation: Only triplet which satisfies condition is arr[0] + arr[1] + arr[2] = 1 + (-2) + 1 = 0

Input: arr[] = [2, 3, 1, 0, 5]
Output: [[]]
Explanation: There is no triplet with sum 0.

Constraints:
3 ≤ arr.size() ≤ 10^3
-10^4 ≤ arr[i] ≤ 10^4

Approach (Hashing + Fix Two Elements):
Since problem asks for INDICES (not values), we need to preserve original positions.

1. Fix first index i
2. Use hashmap for elements after i
3. For every j:
   needed = -(arr[i] + arr[j])
4. If needed exists:
   form triplet: [i, storedIndex, j]
5. Sort triplet internally
6. Use set to avoid duplicates

Why it works:
- Brute force would be O(n^3)
- Using hashing reduces to O(n^2)
- Hashmap preserves original indices
- Set prevents duplicate triplets

Time Complexity: O(n^2)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findTriplets(vector<int>& arr) {
        
        int n = arr.size();
        
        set<vector<int>> uniqueTriplets;
        
        // Fix first index
        for (int i = 0; i < n - 2; i++) {
            
            unordered_map<int, int> mp;
            
            // Find remaining two
            for (int j = i + 1; j < n; j++) {
                
                int needed = -(arr[i] + arr[j]);
                
                // If complement exists
                if (mp.count(needed)) {
                    
                    vector<int> triplet = {
                        i,
                        mp[needed],
                        j
                    };
                    
                    sort(triplet.begin(), triplet.end());
                    
                    uniqueTriplets.insert(triplet);
                }
                
                // Store current element with index
                mp[arr[j]] = j;
            }
        }
        
        // Convert set → vector
        vector<vector<int>> ans(
            uniqueTriplets.begin(),
            uniqueTriplets.end()
        );
        
        // If no triplets
        if (ans.empty()) {
            return {{}};
        }
        
        return ans;
    }
};
