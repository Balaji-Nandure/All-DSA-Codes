#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Problem: Print all palindromic partitions of a string
 * 
 * Given a string S, partition the string such that every substring of the partition 
 * is a palindrome. Return all possible palindromic partitions.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Palindromic Partitioning (Minimum Cuts)" we only needed the minimum integer count of cuts (DP in O(N^2)).
 * - Here, we must generate and return EVERY complete set of palindromic substrings.
 * - This requires Backtracking to reconstruct each partition.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with In-Place Palindrome Check:
 *   1. Function dfs(start, current_partition, result):
 *      - If start == S.length():
 *        We have successfully partitioned the entire string into palindromes!
 *        Add current_partition to result.
 *      - For end from start to S.length() - 1:
 *        Check if substring S[start ... end] is a palindrome.
 *        - If NOT a palindrome: Prune immediately (do not explore this cut).
 *        - If YES:
 *          Push S[start ... end] into current_partition.
 *          Recursively explore dfs(end + 1, ...).
 *          *** CRUCIAL BACKTRACKING STEP ***: pop_back() to restore partition vector.
 *   
 *   2. Optimization:
 *      Can precompute isPalindrome[i][j] via a 2D DP table in O(N^2) time to allow 
 *      O(1) palindrome queries during the recursive exploration.
 */

class Solution {
    bool isPalindrome(const string& s, int l, int r) {
        while (l < r) {
            if (s[l++] != s[r--]) return false;
        }
        return true;
    }

    void backtrack(int start, const string& s, vector<string>& current, vector<vector<string>>& result) {
        // Base case: Full string consumed
        if (start == (int)s.length()) {
            result.push_back(current);
            return;
        }

        for (int end = start; end < (int)s.length(); end++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Only recurse if the prefix cut S[start...end] is a valid palindrome
            if (isPalindrome(s, start, end)) {
                current.push_back(s.substr(start, end - start + 1));

                // Recurse on remaining suffix
                backtrack(end + 1, s, current, result);

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Backtrack: Remove last partitioned token to explore longer palindrome substring cuts
                current.pop_back();
            }
        }
    }

public:
    vector<vector<string>> allPalindromicPerms(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(0, s, current, result);
        return result;
    }
};

int main() {
    Solution sol;
    string s = "geek";
    vector<vector<string>> partitions = sol.allPalindromicPerms(s);

    cout << "Palindromic partitions of \"" << s << "\":\n";
    for (const auto& part : partitions) {
        cout << "  [ ";
        for (const string& str : part) {
            cout << "\"" << str << "\" ";
        }
        cout << "]\n";
    }
    // Expected:
    // [ "g" "e" "e" "k" ]
    // [ "g" "ee" "k" ]

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * 2^N). There are 2^(N-1) possible partition points, and palindrome checks take O(N).
 * - Space Complexity: O(N) recursion stack depth and current partition buffer.
 */
