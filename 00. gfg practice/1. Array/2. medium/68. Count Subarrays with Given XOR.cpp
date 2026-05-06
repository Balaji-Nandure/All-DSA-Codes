/*
Problem: Count Subarrays with Given XOR

Given:
- Find number of subarrays with XOR = k

--------------------------------------------------

Approach (Prefix XOR + HashMap):

1. Maintain prefix XOR (xr)
2. Use map to store frequency of prefix XOR
3. For each index:
   - xr ^= arr[i]
   - If xr == k → count++
   - Check if (xr ^ k) exists in map → add frequency
   - Store xr in map

--------------------------------------------------

Why it works:
- XOR property:
  A ^ B = C  =>  A = B ^ C
- We reverse engineer previous prefix XOR

--------------------------------------------------

Time Complexity:
- O(n)

Space Complexity:
- O(n)

--------------------------------------------------

GFG:
https://www.geeksforgeeks.org/problems/count-subarray-with-given-xor/1

LeetCode:
https://leetcode.com/problems/subarray-sum-equals-k/ (similar pattern with sum)

--------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraysXor(vector<int>& arr, int k) {
        int n = arr.size();
        
        unordered_map<int, int> mp;
        int xr = 0;
        int count = 0;
        
        for(int i = 0; i < n; i++) {
            
            // Step 1: update prefix XOR
            xr ^= arr[i];
            
            // Step 2: if whole prefix XOR = k
            if(xr == k) count++;
            
            // Step 3: check required previous XOR
            int need = xr ^ k;
            
            if(mp.find(need) != mp.end()) {
                count += mp[need];
            }
            
            // Step 4: store current prefix XOR
            mp[xr]++;
        }
        
        return count;
    }
};
