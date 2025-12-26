/*
 * Problem: Letter Tile Possibilities
 * 
 * LeetCode 1079: Letter Tile Possibilities
 * 
 * You have n tiles, where each tile has one letter tiles[i] printed on it.
 * 
 * Return the number of possible non-empty sequences of letters you can make 
 * using the letters printed on those tiles.
 * 
 * Note: Each tile can only be used once in a sequence.
 * 
 * Example 1:
 * Input: tiles = "AAB"
 * Output: 8
 * Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", 
 *              "ABA", "BAA".
 * 
 * Example 2:
 * Input: tiles = "AAABBC"
 * Output: 188
 * 
 * Example 3:
 * Input: tiles = "V"
 * Output: 1
 * 
 * Constraints:
 * - 1 <= tiles.length <= 7
 * - tiles consists of uppercase English letters.
 * 
 * Approach:
 * - We need to count all non-empty sequences (permutations) of any length
 * - Use backtracking with frequency map to handle duplicates
 * - At each step, we can pick any available letter
 * - Count sequences of length 1, 2, 3, ..., up to tiles.length
 * - Use a set to avoid counting duplicate sequences
 * - Alternative: Use frequency map to track available letters and count directly
 * 
 * Time: O(2^n) - exponential, trying all possible sequences
 * Space: O(n) - recursion stack + frequency map
 */

#include <bits/stdc++.h>
using namespace std;

// APPROACH 1 — OPTIMAL (Frequency-based Backtracking)
// Instead of permuting positions, count letters:
// AAB → freq[A] = 2, freq[B] = 1
// At each step:
// Try placing any letter whose frequency > 0
class Solution {
public:
    void backtrack(vector<int> &freq, int &count) {
        // In your frequency-based backtracking, the base case is implicit:
        // Base case condition: when no letter has freq[i] > 0.
        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) continue;

            // choose this letter
            freq[i]--;

            // count this sequence
            count += 1;

            // extend the sequence further
            backtrack(freq, count);

            // backtrack
            freq[i]++;
        }
    }

    int numTilePossibilities(string tiles) {
        vector<int> freq(26, 0);

        // build frequency map
        for (char c : tiles) {
            freq[c - 'A']++;
        }

        int count = 0;
        backtrack(freq, count);
        return count;
    }
};
    
// (it is faster than approach 1)
// APPROACH 2 — USING MAP (Frequency-based Backtracking)
// Same idea as approach 1, but uses a map/unordered_map instead of a fixed 26 array.
class Solution_Map {
public:
    void backtrack(unordered_map<char, int> &freq, int &count) {
        for (auto &kv : freq) {
            int &f = kv.second;
            if (f == 0) continue;

            // choose this letter
            f--;

            // count this sequence
            count += 1;

            // extend further
            backtrack(freq, count);

            // backtrack
            f++;
        }
    }

    int numTilePossibilities(string tiles) {
        unordered_map<char, int> freq;
        for (char c : tiles) freq[c]++;

        int count = 0;
        backtrack(freq, count);
        return count;
    }
};


// APPROACH 3 — BRUTE FORCE (Generate everything + Set)
class Solution_SetBrute {
public:
    unordered_set<string> st;

    void generate(string &tiles, vector<bool> &used, string &current) {
        if (!current.empty()) {
            st.insert(current);
        }

        for (int i = 0; i < tiles.size(); i++) {
            if (used[i]) continue;

            used[i] = true;
            current.push_back(tiles[i]);

            generate(tiles, used, current);

            // backtrack
            current.pop_back();
            used[i] = false;
        }
    }

    int numTilePossibilities(string tiles) {
        vector<bool> used(tiles.size(), false);
        string current = "";

        generate(tiles, used, current);

        return st.size();
    }
};
    