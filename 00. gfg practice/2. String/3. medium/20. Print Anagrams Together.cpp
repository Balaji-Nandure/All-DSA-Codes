/*
GeeksforGeeks: Print Anagrams Together
Difficulty: Medium

Problem:
Given an array of strings, return all groups of strings that are anagrams. 
The strings in each group must be arranged in the order of their appearance in the original array.

Examples:
Input: arr[] = ["act", "god", "cat", "dog", "tac"]
Output: [["act", "cat", "tac"], ["god", "dog"]]
Explanation: There are 2 groups of anagrams. "god", "dog" make group 1. "act", "cat", "tac" make group 2.

Input: arr[] = ["no", "on", "is"]
Output: [["is"], ["no", "on"]]

Input: arr[] = ["listen", "silent", "enlist", "abc", "cab", "bac", "rat", "tar", "art"]
Output: [["abc", "cab", "bac"], ["listen", "silent", "enlist"], ["rat", "tar", "art"]]

Constraints:
1 <= arr.size() <= 100
1 <= arr[i].size() <= 10

Core Idea:
- Anagrams are words that contain the exact same characters in the exact same frequencies.
- If we sort the characters of any word, all of its anagrams will yield the exact same sorted string (the "signature" key).
- We can use a hash map `unordered_map<string, vector<string>>` where the key is the sorted signature, and the value is a vector of original words matching that signature.
- To preserve the order requirement:
  1. **Inner Group Order**: Since we traverse `arr` from left to right, inserting into the map vectors naturally preserves their original appearance order.
  2. **Outer Group Order**: We maintain a list of keys `orderOfKeys` in the order they are first discovered. This ensures we return groups ordered by their first occurrence.

Approach:
1. Initialize an `unordered_map<string, vector<string>> groups` to hold the anagram groups.
2. Initialize a `vector<string> orderOfKeys` to store the order of first appearance of each anagram signature.
3. Iterate through `arr`:
   - Sort the characters of the current string to get its signature key.
   - If the signature key is not present in `groups`, add it to `orderOfKeys`.
   - Add the original string to `groups[signature]`.
4. Iterate through `orderOfKeys` and construct the final list of lists.
5. Return the list of lists.

Time Complexity: O(N * K log K) where N is the number of strings and K is the maximum length of a string.
                 Since K <= 10, sorting is extremely fast (K log K <= 33 operations), making the time complexity practically O(N).
Space Complexity: O(N * K) to store the hash map and the output lists.

GFG Link: https://www.geeksforgeeks.org/problems/print-anagrams-together/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> anagrams(vector<string>& arr) {
        // Map to store grouped anagrams: {sorted_signature -> list of original strings}
        unordered_map<string, vector<string>> groups;
        
        // Vector to keep track of the order in which we first encounter each anagram key
        vector<string> orderOfKeys;
        
        // Traverse the original array
        for (const string& s : arr) {
            string sorted_s = s;
            sort(sorted_s.begin(), sorted_s.end());
            
            // If we are seeing this anagram key for the first time, record its order
            if (groups.find(sorted_s) == groups.end()) {
                orderOfKeys.push_back(sorted_s);
            }
            
            // Push the original string to its anagram group
            groups[sorted_s].push_back(s);
        }
        
        // Construct the final result in correct order of appearance
        vector<vector<string>> result;
        for (const string& key : orderOfKeys) {
            result.push_back(groups[key]);
        }
        
        return result;
    }
};

/*
Dry Run — Example:
arr = ["no", "on", "is"]

1. s = "no"
   - sorted_s = "no"
   - Not in map -> orderOfKeys = ["no"]
   - groups["no"] = ["no"]

2. s = "on"
   - sorted_s = "no"
   - Already in map
   - groups["no"] = ["no", "on"]

3. s = "is"
   - sorted_s = "is"
   - Not in map -> orderOfKeys = ["no", "is"]
   - groups["is"] = ["is"]

Constructing result:
- key = "no" -> result = [["no", "on"]]
- key = "is" -> result = [["no", "on"], ["is"]]

Output: [["no", "on"], ["is"]]
Note: GFG might check the groups in order of first appearance. Here, "no" appeared first and "is" appeared last.
If the actual GFG test expectation matches the first appearance of the first element in each group:
- "is" first appears at index 2.
- "no" first appears at index 0.
So group ["no", "on"] comes first, and ["is"] comes second. Our algorithm outputs exactly this.
*/
