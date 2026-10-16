// Problem: Given a Sequence of Words, Print All Anagrams Together (Group Anagrams)
// Link (GFG): https://www.geeksforgeeks.org/problems/print-anagrams-together/1
// Article: https://www.geeksforgeeks.org/dsa/given-a-sequence-of-words-print-all-anagrams-together-using-stl/
// Difficulty: Medium
// Topic: String, Hash Map, Sorting, Equivalence Partitioning

/*
Problem Statement:
Given an array of strings `string_list`, group all anagrams together.
Two strings are anagrams of each other if they contain the exact same characters 
with the exact same frequencies, but possibly in a different order.

Example 1:
Input: string_list = ["act", "god", "cat", "dog", "tac"]
Output: 
[["act", "cat", "tac"], 
 ["god", "dog"]]

Example 2:
Input: string_list = ["no", "on", "is"]
Output: 
[["no", "on"], 
 ["is"]]

Constraints:
- 1 <= string_list.length <= 10^4
- 1 <= string_list[i].length <= 100
- Strings consist of lowercase English alphabets.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 3 (Duplicate Characters):
//   * We counted duplicate characters in a single string.
// - In Problem 36 (Group Anagrams):
//   * We must partition an ENTIRE LIST of words into equivalence classes.
//   * Two words belong to the same equivalence class if and only if their sorted character 
//     forms (or character frequency signatures) are identical!
//   * This canonical signature serves as a hash map key to collect anagrams together.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Hash Map with Sorted Canonical Key (Optimal & Standard)
//   - Maintain an `unordered_map<string, vector<string>> anagramGroups`.
//   - For each word `w` in `string_list`:
//       * Create a copy `canonicalKey = w`.
//       * Sort `canonicalKey`: E.g., "cat", "act", "tac" all sort to `"act"`.
//       * Insert original word into bucket: `anagramGroups[canonicalKey].push_back(w)`.
//   - Extract all bucket vectors into the final result.
//   - Complexity: O(N * K log K) where N is number of words, K is max length of a word.
//   - Space Complexity: O(N * K) to store all words in hash map.
//   - Why this approach: Highly intuitive, robust, and clean implementation.

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> Anagrams(vector<string>& string_list) {
        // Map from canonical sorted signature to list of original words
        unordered_map<string, vector<string>> anagramGroups;

        for (const string& word : string_list) {
            string key = word;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Sorting the characters creates a UNIQUE CANONICAL REPRESENTATION for any set of anagrams.
            // All permutations of the same letters map to the EXACT same hash key!
            sort(key.begin(), key.end());

            anagramGroups[key].push_back(word);
        }

        vector<vector<string>> result;
        result.reserve(anagramGroups.size());

        for (auto& pair : anagramGroups) {
            result.push_back(std::move(pair.second));
        }

        return result;
    }
};

int main() {
    Solution sol;
    vector<string> words = {"act", "god", "cat", "dog", "tac"};

    vector<vector<string>> groups = sol.Anagrams(words);
    cout << "Anagram Groups:\n";
    for (const auto& group : groups) {
        cout << "[ ";
        for (const string& w : group) cout << "\"" << w << "\" ";
        cout << "]\n";
    }

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * K log K) where N = number of words, K = max word length.
  * For K <= 100, sorting a 100-character string takes negligible microseconds.
- Space Complexity: O(N * K) to store the grouped words in the hash map.

Key Takeaways:
- Canonical hashing (transforming varied equivalent inputs into a single standard form)
  is the most reliable technique for equivalence grouping.
*/
