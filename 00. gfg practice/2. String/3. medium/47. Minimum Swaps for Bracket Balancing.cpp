#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Minimum Swaps for Bracket Balancing (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/minimum-swaps-for-bracket-balancing2704/1
 *
 * Problem Statement:
 *   You are given a string s of 2*n characters consisting of n '[' brackets and n ']' brackets.
 *   Calculate the minimum number of swaps of adjacent characters necessary to make the string balanced.
 *
 * Core Intuition / Idea:
 *   - We traverse the string from left to right and keep track of count of open '[' and close ']' brackets.
 *   - When we see more ']' than '[', we have an imbalance.
 *   - An imbalance is measured by: `imbalance = close - open`.
 *   - When we subsequently find an open bracket '[', and we have a positive `imbalance`, we swap that
 *     '[' with the first unbalanced ']' from the left.
 *   - The number of adjacent swaps required to move the '[' to the position of that unbalanced ']'
 *     is exactly equal to `imbalance`.
 *   - After the swap, the imbalance decreases by 1.
 *
 * Approach (Love Babbar Style - 3 Golden Steps):
 *   1️⃣ **Track Bracket Counts & Imbalance:** Initialize `open = 0`, `close = 0`, `swaps = 0`, and `imbalance = 0`.
 *   2️⃣ **Scan Characters:** For each character:
 *       - If it is '[', increment `open`. If `imbalance > 0`, we add `imbalance` to `swaps`, and decrement `imbalance` (as one imbalance is resolved).
 *       - If it is ']', increment `close` and update `imbalance = close - open`.
 *   3️⃣ **Return Swaps:** The accumulated `swaps` is the minimum adjacent swaps required.
 *
 * Complexity Analysis:
 *   - Time Complexity (TC): O(N) where N is the length of string `S`. We do a single pass over the string.
 *   - Space Complexity (SC): O(1) auxiliary space as we only use a few integer variables.
 *
 * Dry Run:
 *   S = "[]][]["
 *   - i=0: '[' -> open=1. imbalance=0. swaps=0.
 *   - i=1: ']' -> close=1. imbalance=close-open = 1-1 = 0.
 *   - i=2: ']' -> close=2. imbalance=close-open = 2-1 = 1.
 *   - i=3: '[' -> open=2. Since imbalance(1) > 0: swaps += 1 (swaps=1), imbalance-- (imbalance=0).
 *   - i=4: ']' -> close=3. imbalance=close-open = 3-2 = 1.
 *   - i=5: '[' -> open=3. Since imbalance(1) > 0: swaps += 1 (swaps=2), imbalance-- (imbalance=0).
 *   - i=6: '[' -> open=4. Since imbalance(0) == 0: no change.
 *   - Return swaps = 2.
 */

class Solution {
public:
    int minimumNumberOfSwaps(string S) {
        int n = S.length();
        int open = 0, close = 0;
        int swaps = 0, imbalance = 0;
        
        for (int i = 0; i < n; i++) {
            if (S[i] == '[') {
                open++;
                // If there is any active imbalance, we resolve one using this '['
                if (imbalance > 0) {
                    swaps += imbalance;
                    imbalance--;
                }
            } else if (S[i] == ']') {
                close++;
                // Update the current imbalance
                imbalance = close - open;
            }
        }
        
        return swaps;
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    vector<string> tests = {
        "[]][][",      // Expected: 2
        "[][]",        // Expected: 0
        "[[[][][]]]"   // Expected: 0
    };
    for (string s : tests) {
        cout << "String: " << s << " -> Min Swaps: " << sol.minimumNumberOfSwaps(s) << endl;
    }
    return 0;
}
