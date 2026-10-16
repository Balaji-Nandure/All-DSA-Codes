#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

/**
 * Problem: Rearrange characters in string such that no two adjacent are same
 * 
 * Given a string S, rearrange the characters of the string such that no two 
 * adjacent characters are the same. If no such arrangement is possible, return "".
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an interleaving constraint satisfaction problem.
 * - Unlike problems where we group identical elements together, here identical elements 
 *   must be separated by at least 1 other character.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Feasibility Condition (Pigeonhole Principle):
 *   If the maximum frequency of any character max_freq > (N + 1) / 2,
 *   it is mathematically impossible to separate them (e.g., in "aaa", N=3, max_freq=3 > 2 -> impossible).
 * 
 * - Approach 1: Max-Heap (Greedy Interleaving):
 *   Always place the character with the HIGHEST remaining frequency that is NOT identical 
 *   to the character placed immediately before it.
 *   - Use a max-heap storing pair<frequency, char>.
 *   - Extract the highest frequency char, append it to the result string, and temporarily "block" it.
 *   - Re-insert the previously blocked character back into the heap (since it is no longer adjacent).
 *   - Block the current character with frequency - 1.
 * 
 * - Approach 2: Linear Interleaved Placement (O(N)):
 *   Place the highest frequency character at even indices (0, 2, 4, ...).
 *   Then place the remaining characters filling remaining even indices, then odd indices (1, 3, 5, ...).
 */

class Solution {
public:
    string rearrangeString(string s) {
        int n = s.length();
        if (n <= 1) return s;

        // Step 1: Frequency map
        vector<int> freq(26, 0);
        int max_freq = 0;
        char max_char = 'a';

        for (char c : s) {
            freq[c - 'a']++;
            if (freq[c - 'a'] > max_freq) {
                max_freq = freq[c - 'a'];
                max_char = c;
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Pigeonhole Principle: If any character appears more than ceil(N / 2) times, collision is inevitable
        if (max_freq > (n + 1) / 2) {
            return "";
        }

        // Approach 1: Max-Heap Greedy Interleaving
        priority_queue<pair<int, char>> pq;
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                pq.push({freq[i], (char)('a' + i)});
            }
        }

        string result = "";
        pair<int, char> prev = {-1, '#'}; // Temporarily parked character

        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();

            // Append highest frequency character
            result += curr.second;

            // *** CRUCIAL LINE: Put previously parked character back into candidate pool ***
            if (prev.first > 0) {
                pq.push(prev);
            }

            // Park current character with decremented count so it cannot be chosen in consecutive step
            curr.first--;
            prev = curr;
        }

        return (result.length() == s.length()) ? result : "";
    }

    // Approach 2: Even-Odd Alternating Index Filling in O(N) Time
    string rearrangeStringEvenOdd(string s) {
        int n = s.length();
        vector<int> freq(26, 0);
        int max_freq = 0;
        char most_freq_char = 'a';

        for (char c : s) {
            freq[c - 'a']++;
            if (freq[c - 'a'] > max_freq) {
                max_freq = freq[c - 'a'];
                most_freq_char = c;
            }
        }

        if (max_freq > (n + 1) / 2) return "";

        string res(n, ' ');
        int idx = 0;

        // Fill most frequent character in even positions first
        while (freq[most_freq_char - 'a'] > 0) {
            res[idx] = most_freq_char;
            idx += 2;
            freq[most_freq_char - 'a']--;
        }

        // Fill remaining characters
        for (int i = 0; i < 26; i++) {
            while (freq[i] > 0) {
                if (idx >= n) idx = 1; // Switch to odd positions once even positions are filled
                res[idx] = (char)('a' + i);
                idx += 2;
                freq[i]--;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;
    string s1 = "aaabc";
    cout << "Rearranged 1 (Heap):     " << sol.rearrangeString(s1) << "\n";
    cout << "Rearranged 1 (Even-Odd): " << sol.rearrangeStringEvenOdd(s1) << "\n";

    string s2 = "aaabb";
    cout << "Rearranged 2 (Heap):     " << sol.rearrangeString(s2) << "\n";
    cout << "Rearranged 2 (Even-Odd): " << sol.rearrangeStringEvenOdd(s2) << "\n";

    string s3 = "aaaa";
    cout << "Rearranged 3: " << (sol.rearrangeString(s3).empty() ? "Impossible" : sol.rearrangeString(s3)) << "\n";

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Approach 1 (Max Heap): Time Complexity O(N log(Sigma)) where Sigma <= 26 alphabet size -> O(N).
 * - Approach 2 (Even-Odd): Time Complexity strictly O(N).
 * - Space Complexity: O(Sigma) = O(1) auxiliary frequency and heap storage.
 */
