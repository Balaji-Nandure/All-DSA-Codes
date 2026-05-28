/*
Problem: Two Sum - Pair with Given Sum

Given an array arr[] of integers and another integer target. Determine if there exist two distinct indices such that the sum of their elements is equal to the target.

Constraints:
1 <= arr.size <= 10^5
-10^5 <= arr[i] <= 10^5
-2*10^5 <= target <= 2*10^5

--------------------------------------------------

Pattern:
Hashing / Set

--------------------------------------------------

Key Observation:
- We are looking for a pair of numbers `a` and `b` in the array such that `a + b = target`.
- This algebraic equation can be elegantly rewritten as `b = target - a`.
- As we iterate through the array, for each current element `a`, we can simply check if we have already encountered its required counterpart `target - a` earlier in the array.
- Using a hash set provides O(1) average time complexity for both inserting elements and checking for their existence.

--------------------------------------------------

Approach:
1. Initialize an `unordered_set<int> seen` to store the numbers we have traversed so far.
2. Iterate through each element `num` in the array `arr`:
    a. Calculate the required complement to reach the target: `req = target - num`.
    b. Check if `req` is present in the `seen` set.
    c. If it is present, it means we have successfully found a valid pair. Return `true`.
    d. If it is not present, insert the current `num` into the `seen` set and continue to the next element.
3. If the loop completes entirely without finding any valid pair, return `false`.

--------------------------------------------------

Time Complexity: O(N) as we iterate through the array once and set insertions/lookups take O(1) time on average.
Space Complexity: O(N) to store the visited elements in the hash set.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/key-pair5616/1
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool twoSum(vector<int>& arr, int target) {
        unordered_set<int> seen;
        
        for (int num : arr) {
            int req = target - num;
            
            // If the required complement is already in the set, a pair exists
            if (seen.find(req) != seen.end()) {
                return true;
            }
            
            // Otherwise, store the current number for future possible pairs
            seen.insert(num);
        }
        
        return false;
    }
};
