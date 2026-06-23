/*
    Problem Name: Find the longest string
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array of strings words[]. Find the longest string in words[] such that every prefix of it is also present in the array words[]. 
    If multiple strings have the same maximum length, return the lexicographically smallest one.

    Expected Complexities:
    Time Complexity: O(N * log(N) * L) where N is length of words array and L is maximum length of a word.
    Space Complexity: O(N * L) to store valid words in a hash set.

    Love Babbar Style Approach:
    1. Sorting: First, we sort the `words` array. We sort them primarily by their lengths in ascending order. If two strings have the same length, we sort them lexicographically in ascending order.
    2. Initialization: We use an `unordered_set<string> valid_set` to store strings that have all their prefixes valid. We also keep a string `longest` to track our answer.
    3. Traversal: We iterate over each string `w` in the sorted `words` array:
       - If the length of `w` is 1, it's inherently valid because it has no smaller prefixes. We insert it into `valid_set`.
       - If the length is > 1, we check if its prefix of length `w.length() - 1` (i.e., `w` without the last character) exists in `valid_set`. If it does, it implies all smaller prefixes are also present. We insert `w` into `valid_set`.
       - After inserting, if `w.length() > longest.length()`, we update `longest = w`. Because we already sorted lexicographically for equal lengths, the first valid string of a new maximum length will be the lexicographically smallest.
    4. Result: Return the `longest` string. If no such string exists, the default empty string is returned.

    Dry Run:
    Input: words = ["ab", "a", "abc", "abd"]
    - Sorted words: ["a", "ab", "abc", "abd"]
    - Initialization: valid_set = {}, longest = ""
    Iteration:
    - w = "a": length 1, valid! valid_set = {"a"}. w.length() > longest.length() -> longest = "a"
    - w = "ab": length 2, prefix "a" is in valid_set. valid_set = {"a", "ab"}. w.length() > longest.length() -> longest = "ab"
    - w = "abc": length 3, prefix "ab" is in valid_set. valid_set = {"a", "ab", "abc"}. longest = "abc"
    - w = "abd": length 3, prefix "ab" is in valid_set. valid_set = {"a", "ab", "abc", "abd"}. w.length() is 3, longest.length() is 3, so longest is NOT updated.
    Result: "abc"
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
  public:
    string longestString(vector<string> &words) {
        // Sort by length, then lexicographically
        sort(words.begin(), words.end(), [](const string& a, const string& b) {
            if (a.length() == b.length()) {
                return a < b; // Ascending lexicographically
            }
            return a.length() < b.length(); // Ascending by length
        });

        unordered_set<string> valid_set;
        string longest = "";

        for (const string& w : words) {
            // A word is valid if it's a single character or its prefix is already valid
            if (w.length() == 1 || valid_set.count(w.substr(0, w.length() - 1))) {
                valid_set.insert(w);
                if (w.length() > longest.length()) {
                    longest = w;
                }
            }
        }
        
        return longest;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<string> words(n);
            for (int i = 0; i < n; i++) {
                cin >> words[i];
            }
            Solution ob;
            cout << ob.longestString(words) << "\n";
        }
    }
    return 0;
}
