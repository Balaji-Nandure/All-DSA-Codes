/*
Problem: Subarray Range With Given Sum

GFG: https://www.geeksforgeeks.org/problems/subarray-range-with-given-sum/

Description:
Given an unsorted array of integers arr[], and a target tar, determine the number of subarrays whose elements sum up to the target value.

Examples:

Input: arr[] = [10, 2, -2, -20, 10], tar = -10
Output: 3
Explanation: Subarrays with sum -10 are: [10, 2, -2, -20], [2, -2, -20, 10] and [-20, 10].

Input: arr[] = [1, 4, 20, 3, 10, 5], tar = 33
Output: 1
Explanation: Subarray with sum 33 is: [20, 3, 10].

Constraints:
1 ≤ arr.size() ≤ 10^6
-10^5 ≤ arr[i] ≤ 10^5
-10^5 ≤ tar ≤ 10^5

Approach (Prefix Sum + Hashing):
This is a classic prefix sum problem where we need to count subarrays with given sum.

Key insight:
- Sliding window doesn't work due to negative numbers
- Use prefix sum and hashmap to track frequencies
- If prefixSum - target exists in hashmap, we found valid subarrays

Algorithm:
1. Initialize hashmap with mp[0] = 1 (for subarrays starting from index 0)
2. Maintain running prefix sum
3. For each element:
   - Calculate needed = prefixSum - target
   - If needed exists in hashmap, add its frequency to answer
   - Increment frequency of current prefix sum

Time Complexity: O(n)
Space Complexity: O(n)

Pattern: Prefix Sum + HashMap
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
PREFIX SUM HASHING
=====================================================

TC: O(n)
SC: O(n)

🔥 PREFIX SUM + HASHMAP APPROACH
- Sliding window fails with negatives
- Prefix sum + hashmap works for any integers
- Count all subarrays with given sum

🧠 CORE INSIGHT:
If prefixSum - target already appeared,
then subarray between them has sum = target.

🎯 ALGORITHM:
1. prefixSum = current cumulative sum
2. needed = prefixSum - target
3. If needed exists: add its frequency to answer
4. Store current prefixSum frequency

⚡ WHY IT WORKS:
prefixSum[j] - prefixSum[i] = target
=> sum(arr[i+1...j]) = target
*/

class PrefixSumHashingSolution {
public:

    int subArraySum(vector<int>& arr, int tar) {
        
        unordered_map<long long, int> mp;
        
        // Base prefix sum for subarrays starting from index 0
        mp[0] = 1;
        
        long long prefixSum = 0;
        
        int ans = 0;
        
        for (int num : arr) {
            
            prefixSum += num;
            
            // Needed previous prefix to form target sum
            long long need = prefixSum - tar;
            
            // Valid subarrays found
            if (mp.count(need)) {
                
                ans += mp[need];
            }
            
            // Store current prefix sum frequency
            mp[prefixSum]++;
        }
        
        return ans;
    }
};



/*
=====================================================
FINAL GFG CLASS
=====================================================
*/

class Solution {
public:

    int subArraySum(vector<int>& arr, int tar) {
        
        PrefixSumHashingSolution obj;
        
        return obj.subArraySum(arr, tar);
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever:
    "count subarrays with given sum"

Think immediately:
    PREFIX SUM + HASHMAP

-----------------------------------------------------

IMPORTANT:

Positive-only arrays:
    Sliding Window possible

Arrays with negatives:
    Prefix Sum required

-----------------------------------------------------

SIMILAR PROBLEMS

- Subarray Sum Equals K
- Binary Subarrays With Sum
- Count Equal 0s and 1s
- Longest Subarray With Sum K

-----------------------------------------------------
*/
