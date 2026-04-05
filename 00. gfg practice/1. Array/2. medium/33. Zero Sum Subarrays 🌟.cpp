/*
PROBLEM: Zero Sum Subarrays

Given an array, find the total count of subarrays with sum equal to 0.

Example:
arr[] = [0, 0, 5, 5, 0, 0]
Output: 6
Subarrays: [0], [0], [0], [0], [0,0], [0,0]

arr[] = [6, -1, -3, 4, -2, 2, 4, 6, -12, -7]
Output: 4
Subarrays: [-1, -3, 4], [-2, 2], [2, 4, 6, -12], [-1, -3, 4, -2, 2]

--------------------------------------------------

INTUITION / APPROACH:

Key insight: If prefix_sum[i] == prefix_sum[j] where i < j
             then sum of subarray from (i+1) to j = 0

Algorithm:
1. Keep calculating prefix sum while iterating
2. Store prefix sum frequencies in a map
3. If current prefix sum exists in map → count subarray(s) with sum 0
4. Also count when prefix_sum = 0 itself (subarray from start)

Example: [6, -1, -3, 4, -2, 2]
prefix:   6,  5,  2, 6,  4, 6

At index 3: prefix = 6 (seen before)
            → subarray [2, 4] has sum 0 (indices 1-4... wait)

Actually better way to think:
prefix[0]=6, prefix[1]=5, prefix[2]=2, prefix[3]=6

When prefix[3]=6 appears again (already seen at prefix[0])
→ subarray sum from index 1 to 3 = 0 (indices 1,2,3 = -1,-3,4 = 0) ✓

--------------------------------------------------

PATTERN:
"Subarray with sum = X" → Use prefix sum + hashmap

--------------------------------------------------

TIME COMPLEXITY:
O(N) - single pass with map operations

SPACE COMPLEXITY:
O(N) - map for prefix sums

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/zero-sum-subarrays/1

LeetCode similar:
https://leetcode.com/problems/subarray-sum-equals-k/

--------------------------------------------------
*/

class Solution {
  public:
    long long findSubarray(vector<long long> arr) {
        unordered_map<long long, long long> prefixCount;
        long long prefixSum = 0;
        long long result = 0;
        
        prefixCount[0] = 1;  // For subarrays starting from index 0
        
        for(long long num : arr) {
            prefixSum += num;
            
            // If this prefix sum seen before → zero sum subarray exists
            if(prefixCount.find(prefixSum) != prefixCount.end()) {
                result += prefixCount[prefixSum];
            }
            
            prefixCount[prefixSum]++;
        }
        
        return result;
    }
};
// small version
// class Solution {
//   public:
//     int findSubarray(vector<int> &arr) {
//         unordered_map<long long, long long> mp;
//         long long sum = 0;
//         long long result = 0;
        
//         mp[0] = 1;
        
//         for(int num: arr){
//             sum += num;
//             result += mp[sum];
//             mp[sum]++;
//         }
        
//         return result;
//     }
// };


/*
---------------- DRY RUN ----------------

arr[] = [0, 0, 5, 5, 0, 0]

prefixCount initially: {0: 1}
prefixSum = 0

Index 0, num = 0:
  prefixSum = 0
  Found 0 in map → result += 1 = 1
  prefixCount = {0: 2}

Index 1, num = 0:
  prefixSum = 0
  Found 0 in map → result += 2 = 3
  prefixCount = {0: 3}

Index 2, num = 5:
  prefixSum = 5
  Not found
  prefixCount = {0: 3, 5: 1}

Index 3, num = 5:
  prefixSum = 10
  Not found
  prefixCount = {0: 3, 5: 1, 10: 1}

Index 4, num = 0:
  prefixSum = 10
  Found 10 in map → result += 1 = 4
  prefixCount = {0: 3, 5: 1, 10: 2}

Index 5, num = 0:
  prefixSum = 10
  Found 10 in map → result += 2 = 6
  prefixCount = {0: 3, 5: 1, 10: 3}

Result = 6 ✓
Subarrays: [0] at 0, [0] at 1, [0,0] at 0-1, [0] at 4, [0] at 5, [0,0] at 4-5

--------------------------------------------------

FINAL SUMMARY:

Category: Array
Pattern: Prefix Sum + HashMap
Key Idea: If two prefix sums are same, subarray between them has sum 0

Whenever problem says:
- Subarray with sum X
- Count subarrays
- Prefix sum patterns
→ Think HashMap + Prefix Sum

TIME: O(N)
SPACE: O(N)
*/
