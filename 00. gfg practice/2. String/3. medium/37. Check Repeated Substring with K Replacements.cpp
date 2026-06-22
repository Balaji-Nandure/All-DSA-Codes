#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Check Repeated Substring with K Replacements (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/check-repeated-substring-with-k-replacements/1
 *
 * Problem Statement:
 *   Given a string `s` and an integer `k`, we may perform **at most one** operation:
 *   replace any substring of length `k` whose starting index `i` satisfies `i % k == 0`
 *   (i.e. a block aligned with the pattern) with any other string of length `k`.
 *   After this operation (or without any operation) we want the whole string to become
 *   a repetition of a single substring of length `k`.
 *   Return `true` if it is possible, otherwise `false`.
 *
 * Observation:
 *   The string can be viewed as a sequence of blocks of length `k`:
 *       B0, B1, ..., B(m-1)  where m = s.length() / k.
 *   For the final string to be a repetition of a pattern, **all blocks must be
 *   identical**. Since we are allowed to modify only one block, the condition is
 *   straightforward:
 *       • All blocks are already the same → `true`.
 *       • Exactly two distinct block values exist and one of them appears only
 *         once (the block we can replace) → `true`.
 *       • Any other situation (more than two distinct blocks or two distinct
 *         blocks with both appearing more than once) → `false`.
 *   If the length of `s` is not a multiple of `k`, we can never obtain a perfect
 *   repetition → `false`.
 *
 * Algorithm (O(N) time, O(N/k) extra space):
 *   1. If `s.size() % k != 0` return false.
 *   2. Split `s` into blocks of length `k` and count their frequencies using an
 *      unordered_map<string,int>.
 *   3. Let `m` be the total number of blocks.
 *   4. If map size == 1 → true.
 *   5. If map size == 2 and one of the values equals 1 and the other equals `m-1`
 *      → true.
 *   6. Otherwise → false.
 *
 * Complexity:
 *   Time   : O(|s|) – we scan the string once.
 *   Memory : O(m)   – at most `m` distinct blocks, `m = |s|/k` ≤ 10^5.
 */

class Solution {
public:
    bool checkRepeatedSubstring(string s, int k) {
        int n = (int)s.size();
        if (k <= 0) return false;
        if (n % k != 0) return false;                // length not divisible by k
        int blocks = n / k;
        unordered_map<string, int> freq;
        for (int i = 0; i < n; i += k) {
            string block = s.substr(i, k);
            freq[block]++;
            if(freq.size() > 2) return false;
        }
        if (freq.size() == 1) return true;           // already uniform
        if (freq.size() == 2) {
            for (auto &p : freq) {
                int cnt = p.second;
                if (cnt == 1) {
                    // the other block must appear blocks-1 times
                    return true; // because total = blocks, the other count is blocks-1
                }
            }
        }
        return false;
    }
};

// Optional driver for local testing
int main() {
    Solution sol;
    vector<tuple<string,int,bool>> tests = {
        {"abcbedabcabc", 3, true},
        {"bdac", 2, true},
        {"abcdabcd", 2, false},
        {"aaaa", 2, true},
        {"abcaab", 3, false}
    };
    for (auto &t : tests) {
        string s; int k; bool exp; tie(s,k,exp) = t;
        bool ans = sol.checkRepeatedSubstring(s,k);
        cout << "s='" << s << "', k=" << k << " => " << (ans?"true":"false")
             << " (expected " << (exp?"true":"false") << ")\n";
    }
    return 0;
}
