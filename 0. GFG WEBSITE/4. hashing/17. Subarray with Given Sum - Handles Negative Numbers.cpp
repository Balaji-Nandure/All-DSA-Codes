/*
Problem:
Subarray with Given Sum (Handles Negative Numbers)

Given an integer array arr[] (which may contain positive, negative,
and zero values) and an integer target,
check whether there exists a subarray with sum equal to target.
If yes, return true; otherwise, return false.

Examples:
Input  : arr = [10, 2, -2, -20, 10], target = -10
Output : true
Explanation:
Subarray [2, -2, -20, 10] has sum = -10

Input  : arr = [1, 4, 20, 3, 10, 5], target = 33
Output : true
Explanation:
Subarray [20, 3, 10] has sum = 33

Input  : arr = [1, 2, 3], target = 7
Output : false


Approach (Expected / Optimal – Prefix Sum + Hashing):
1. Maintain a running prefix sum.
2. Use an unordered_set (or map) to store all prefix sums seen so far.
3. At each index:
   - If prefixSum == target → subarray from index 0 exists.
   - If (prefixSum - target) exists in the set:
       A subarray with given sum exists.
4. Insert prefixSum into the set.
5. Continue till the end.

Why this works:
- Handles negative numbers, unlike sliding window.
- Based on the identity:
    If prefixSum[j] - prefixSum[i] = target,
    then subarray (i+1 to j) has sum = target.
- Hashing allows constant-time lookup.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/

LeetCode:
https://leetcode.com/problems/subarray-sum-equals-k/
(Note: LeetCode counts subarrays; existence logic is identical)
*/

bool subarrayWithGivenSum(vector<int>& arr, int target) {
    unordered_set<int> prefixSums;

    int prefixSum = 0;

    for (int x : arr) {
        prefixSum += x;

        // Case 1: Subarray from start
        if (prefixSum == target) {
            return true;
        }

        // Case 2: Subarray in between
        if (prefixSums.count(prefixSum - target)) {
            return true;
        }

        prefixSums.insert(prefixSum);
    }

    return false;
}

// to count the number of subarrays with given sum
class Solution {
    public:
        int subarraySum(vector<int>& nums, int k) {
            // // // Approach 3: prefix sum + hashmap
            int n = nums.size();
            int count = 0;
            int prefixSum = 0; // current prefix sum
            unordered_map<int, int> mp;
            mp[0] = 1; // zero prefix occurs when we are considationg no element form array
            for(int i=0; i<n; i++){
                prefixSum += nums[i];
                int diff = prefixSum - k;
                if(mp.find(diff) != mp.end()){
                    count += mp[diff];
                }
                mp[prefixSum]++;
            }
            return count;
        }
    };
