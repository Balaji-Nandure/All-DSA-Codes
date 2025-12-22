/*
 * Problem: Power Set (All Subsets)
 *
 * Print all subsets (power set) of a string using recursion and backtracking.
 *
 * Example: "abc"
 * Output: "", "a", "b", "c", "ab", "ac", "bc", "abc"
 *
 * Approach: For each character, either include or exclude it.
 * Use backtracking to build current subset.
 *
 * Time: O(2^n * n) - 2^n subsets, each printed in O(n)
 * Space: O(n) - recursion stack depth is n
 */

#include <iostream>
#include <string>
using namespace std;

// Generate all subsets (power set) using recursion and backtracking
void powerSet(const string &str, int idx, string &curr) {
    // Base case: processed all characters, print current subset
    if (idx == str.length()) {
        cout << "\"" << curr << "\"" << endl;
        return;
    }
    // NOT TAKE: Exclude current character
    powerSet(str, idx + 1, curr);

    // TAKE: Include current character
    curr.push_back(str[idx]);
    powerSet(str, idx + 1, curr);
    curr.pop_back(); // Backtrack: remove to try other combinations
}

int main() {
    string str = "abc";
    cout << "All subsets (power set) of \"" << str << "\":" << endl;
    string curr;
    powerSet(str, 0, curr);
    return 0;
}
