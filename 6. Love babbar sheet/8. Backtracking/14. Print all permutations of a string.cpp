#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Print all permutations of a string
 * 
 * Given a string S, return all unique permutations of the string in lexicographically sorted order.
 * The string may contain duplicate characters.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Word Break" or "Rat in a Maze", decisions were positional subsets or paths.
 * - Here, every permutation MUST use all N characters of the string.
 * - If duplicate characters exist (e.g. "AAB"), naive swapping produces duplicate permutations.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Sorted Backtracking with Boolean `used` Array:
 *   1. Initial Sort:
 *      Sort string S in ascending order so identical characters become contiguous: S[0] <= S[1] <= ...
 *   2. State:
 *      Maintain a boolean array `used[N]` indicating whether character S[i] is already placed.
 *   3. Duplicate Skipping Condition:
 *      If S[i] == S[i - 1] and !used[i - 1]:
 *        SKIP character S[i]!
 *      Why? Because S[i-1] was already used at this current position in the previous branch.
 *      Using S[i] now would generate an identical subtree of permutations.
 *   4. Backtracking:
 *      - Push S[i] to current string, mark used[i] = true.
 *      - Recurse: backtrack(current, result, used).
 *      - Backtrack: Pop character, mark used[i] = false.
 *   5. Guarantees:
 *      Produces strictly UNIQUE permutations in strictly LEXICOGRAPHICAL order with zero overhead!
 */

class Solution {
    void backtrack(const string& s, string& current, vector<bool>& used, vector<string>& result) {
        // Base case: All N characters used
        if (current.length() == s.length()) {
            result.push_back(current);
            return;
        }

        for (int i = 0; i < (int)s.length(); i++) {
            // If already used in this permutation prefix, skip
            if (used[i]) continue;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Deduplication: If current character is identical to predecessor and predecessor was not used,
            // picking current would produce duplicate permutation tree. Skip!
            if (i > 0 && s[i] == s[i - 1] && !used[i - 1]) {
                continue;
            }

            // Choose
            used[i] = true;
            current.push_back(s[i]);

            // Recurse
            backtrack(s, current, used, result);

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Backtrack: Undo choice to free character for next permutations
            current.pop_back();
            used[i] = false;
        }
    }

public:
    vector<string> findPermutation(string S) {
        vector<string> result;
        string current = "";
        vector<bool> used(S.length(), false);

        // Sort to bring identical characters together and ensure lexicographical generation
        sort(S.begin(), S.end());

        backtrack(S, current, used, result);
        return result;
    }
};

int main() {
    Solution sol;
    string s1 = "ABC";
    vector<string> perms1 = sol.findPermutation(s1);
    cout << "Permutations of \"" << s1 << "\":\n";
    for (const string& p : perms1) cout << p << " ";
    cout << "\n";
    // Expected: ABC ACB BAC BCA CAB CBA

    string s2 = "AAB";
    vector<string> perms2 = sol.findPermutation(s2);
    cout << "Permutations of \"" << s2 << "\" (with duplicates handled):\n";
    for (const string& p : perms2) cout << p << " ";
    cout << "\n";
    // Expected: AAB ABA BAA

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N! * N) when all characters are distinct. If duplicates exist, time is O((N! / (f1! * f2!...)) * N).
 * - Space Complexity: O(N) recursion stack and boolean visited array.
 */
