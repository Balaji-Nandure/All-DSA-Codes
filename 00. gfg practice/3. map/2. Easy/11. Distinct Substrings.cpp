/*
Problem: Distinct Substrings

Given a string s consisting of uppercase and lowercase alphabetic characters. Return the number of distinct substrings of size 2 that appear in s as contiguous substrings.

Constraints:
1 <= |s| <= 100

--------------------------------------------------

Pattern:
Hashing / Set + String Processing

--------------------------------------------------

Key Observation:
- We need to find and count the *unique* contiguous substrings of exactly size 2.
- A Hash Set inherently prevents duplicate entries from being stored. 
- By extracting every single 2-character sliding window from the string and inserting it into a Hash Set, any overlapping repetitions are automatically filtered out.
- The final answer is simply the count of the elements sitting in the Hash Set!

--------------------------------------------------

Approach:
1. Handle the edge case: If the string length is strictly less than 2, it's impossible to have a substring of size 2, so immediately return 0.
2. Initialize an `unordered_set<string> seen` to store our unique 2-character segments.
3. Iterate through the string `s` from index `0` up to `s.length() - 2`:
    a. Extract the exact substring of length 2 starting at index `i` via `s.substr(i, 2)`.
    b. Insert this newly extracted substring into the `seen` set.
4. Return `seen.size()`, which gives the total count of distinct size-2 substrings.

--------------------------------------------------

Time Complexity: O(|s|) as we iterate through the string of length N exactly once, extracting length-2 substrings in O(1) time.
Space Complexity: O(|s|) to securely store the distinct extracted substrings within the Hash Set.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/distinct-substrings2516/1
*/

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int fun(string s) {
        if (s.length() < 2) {
            return 0;
        }
        
        unordered_set<string> seen;
        
        for (int i = 0; i < s.length() - 1; ++i) {
            seen.insert(s.substr(i, 2));
        }
        
        return seen.size();
    }
};
