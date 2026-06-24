/*
    Problem Name: Prefix Suffix Strings
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two arrays of strings, s1[] and s2[], count the number of strings in s2[] that occur as either a prefix or a suffix of at least one string in s1[]. Return the total count.

    Expected Complexities:
    Time Complexity: O(N * L + M * L) where N is |s1|, M is |s2|, and L is max length of strings. Building and searching in Tries take linear time w.r.t total characters.
    Space Complexity: O(N * L) to store the Tries.

    Love Babbar Style Approach:
    1. Trie Data Structure: Checking if a string is a prefix or suffix of a set of strings is perfectly suited for a Trie (Prefix Tree).
    2. Dual Tries:
       - Prefix Trie: We insert every string from `s1` into a Prefix Trie. This allows us to rapidly check if any string from `s2` is a prefix of a string in `s1`.
       - Suffix Trie: We insert the reverse of every string from `s1` into a Suffix Trie. This allows us to rapidly check if the reverse of a string from `s2` is a prefix of any reversed string in `s1` (which exactly equates to being a suffix of the original string).
    3. Optimized Implementation: Instead of using dynamically allocated pointers which are slow and memory-fragmenting, we use a `vector<vector<int>>` to represent our Trie nodes. This provides lightning-fast contiguous memory access and automatic memory management.
    4. Execution:
       - For each string `s` in `s2`:
         - First, check if `s` exists in the Prefix Trie. If it does, it's a prefix. Increment count and move to the next string.
         - If not, reverse `s` and check if it exists in the Suffix Trie. If it does, it's a suffix. Increment count.
    5. Result: Return the final count.

    Dry Run:
    s1 = ["cat", "catanddog", "lion"]
    s2 = ["cat", "dog", "rat"]
    - Build Prefix Trie with "cat", "catanddog", "lion".
    - Build Suffix Trie with "tac", "goddnatac", "noil".
    - Check s2[0] = "cat":
      - Exists in Prefix Trie? Yes ("cat" matches prefix of "catanddog" and "cat"). Count = 1.
    - Check s2[1] = "dog":
      - Exists in Prefix Trie? No.
      - Reverse = "god". Exists in Suffix Trie? Yes ("god" is prefix of "goddnatac"). Count = 2.
    - Check s2[2] = "rat":
      - Exists in Prefix Trie? No.
      - Reverse = "tar". Exists in Suffix Trie? No.
    Result: 2
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Trie {
  private:
    vector<vector<int>> nodes;
  public:
    Trie() {
        nodes.push_back(vector<int>(26, -1)); // Root node
    }
    
    void insert(const string& word) {
        int curr = 0;
        for (char c : word) {
            int idx = c - 'a';
            if (nodes[curr][idx] == -1) {
                nodes[curr][idx] = nodes.size();
                nodes.push_back(vector<int>(26, -1));
            }
            curr = nodes[curr][idx];
        }
    }
    
    bool searchPrefix(const string& prefix) {
        int curr = 0;
        for (char c : prefix) {
            int idx = c - 'a';
            if (nodes[curr][idx] == -1) {
                return false;
            }
            curr = nodes[curr][idx];
        }
        return true;
    }
};

class Solution {
  public:
    int prefixSuffixString(vector<string> &s1, vector<string> s2) {
        Trie prefixTrie;
        Trie suffixTrie;
        
        // Insert all strings from s1 into the prefix and suffix tries
        for (const string& s : s1) {
            prefixTrie.insert(s);
            
            string rev_s = s;
            reverse(rev_s.begin(), rev_s.end());
            suffixTrie.insert(rev_s);
        }
        
        int count = 0;
        
        // Check strings in s2
        for (const string& s : s2) {
            // Check prefix
            if (prefixTrie.searchPrefix(s)) {
                count++;
                continue; // No need to check suffix if prefix matches
            }
            
            // Check suffix
            string rev_s = s;
            reverse(rev_s.begin(), rev_s.end());
            if (suffixTrie.searchPrefix(rev_s)) {
                count++;
            }
        }
        
        return count;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n, m;
            cin >> n >> m;
            vector<string> s1(n);
            vector<string> s2(m);
            for (int i = 0; i < n; i++) cin >> s1[i];
            for (int i = 0; i < m; i++) cin >> s2[i];
            Solution ob;
            cout << ob.prefixSuffixString(s1, s2) << "\n";
        }
    }
    return 0;
}
