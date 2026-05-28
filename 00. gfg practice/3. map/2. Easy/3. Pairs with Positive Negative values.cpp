/*
Problem: Pairs with Positive Negative values

Given an array of integers, return all the elements such that both the positive and negative values of a number exist in the array. The order of elements in the output should be based on the order of first appearance of any element in a pair in input. For example, in a pair (x, y) if any of x or y appear first in the input array, then the whole pair will appear first.

Constraints:
1 <= arr.size() <= 10^5
-10^5 <= arr[i] <= 10^5

--------------------------------------------------

Pattern:
Hashing / Map

--------------------------------------------------

Key Observation:
- We need to find pairs of `x` and `-x` in the array.
- The order of the output must follow the exact order in which the first element of any valid pair appears in the original array.
- By using a hash map (or frequency map), we can precompute the availability of all numbers.
- A second pass through the array allows us to pick elements in their original order. Whenever we find a number whose opposite also exists (and both haven't been fully used up), we add both to our result and decrement their counts.

--------------------------------------------------

Approach:
1. Initialize an `unordered_map<int, int> count` to store the frequency of each number in the array.
2. Iterate through the array `arr` and populate the `count` map.
3. Initialize an empty `vector<int> ans` to store the resulting pairs.
4. Iterate through the array `arr` again:
    a. For each number `x`, if it's not 0 (as 0 is neither positive nor negative), check if `count[x] > 0` and `count[-x] > 0`.
    b. If both are available, it means we have a valid pair.
    c. Push `x` and then `-x` to `ans`.
    d. Decrement `count[x]` and `count[-x]` so they aren't reused improperly.
5. Return the populated `ans` vector.

--------------------------------------------------

Time Complexity: O(N) where N is the length of the array, as we make two linear passes and map lookups take O(1) time on average.
Space Complexity: O(N) to store the frequencies in the hash map and the resulting pairs.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/pairs-with-positive-negative-values3719/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> PosNegPair(vector<int>& arr) {
        unordered_map<int, int> count;
        vector<int> ans;
        
        // Populate the frequency map
        for (int x : arr) {
            count[x]++;
        }
        
        // Traverse again to maintain original order
        for (int x : arr) {
            if (x != 0 && count[x] > 0 && count[-x] > 0) {
                ans.push_back(x);
                ans.push_back(-x);
                count[x]--;
                count[-x]--;
            }
        }
        
        return ans;
    }
};
