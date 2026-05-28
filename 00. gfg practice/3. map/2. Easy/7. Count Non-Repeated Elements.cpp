/*
Problem: Count Non-Repeated Elements

You are given an array of integers arr[]. You need to return the count of non-repeated elements in the array.

Constraints:
1 <= arr.size() <= 10^5
0 <= arr[i] <= 10^7

--------------------------------------------------

Pattern:
Hashing / Frequency Map

--------------------------------------------------

Key Observation:
- We need to identify all elements that appear exactly once in the array.
- A hash map (or frequency map) is perfectly suited for efficiently counting the occurrences of each element in a single linear pass.
- Once the map is fully populated, we can simply tally up how many entries have a frequency value of exactly 1.

--------------------------------------------------

Approach:
1. Initialize an `unordered_map<int, int> freq` to track the occurrence count of each element.
2. Iterate through the given array `arr` and for each element `num`, increment its count in the map: `freq[num]++`.
3. Initialize a `count` variable to 0.
4. Iterate through the key-value pairs in the `freq` map:
    a. If the mapped value (the frequency) is equal to 1, increment the `count`.
5. Return the final `count`.

--------------------------------------------------

Time Complexity: O(N) where N is the size of the array. Populating the unordered map takes O(1) time on average per element, and we iterate over the unique elements in the map at most N times.
Space Complexity: O(N) in the worst-case scenario (where all elements are completely distinct) to store the elements and their frequencies in the hash map.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/count-non-repeated-elements/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int countNonRepeated(vector<int>& arr) {
        unordered_map<int, int> freq;
        
        // Populate the frequency map
        for (int num : arr) {
            freq[num]++;
        }
        
        int count = 0;
        
        // Count elements with exactly a frequency of 1
        for (auto const& pair : freq) {
            if (pair.second == 1) {
                count++;
            }
        }
        
        return count;
    }
};
