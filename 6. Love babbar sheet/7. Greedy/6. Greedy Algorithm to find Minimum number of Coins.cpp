/**
 * ============================================================================
 * Problem: Greedy Algorithm for Minimum Coins & Choose and Swap
 * Category: Greedy
 * 
 * Problem Statement:
 * Part 1: Minimum Number of Coins (Indian Coin System)
 * Given a value V. Find the minimum number of coins and/or notes needed to make 
 * the change for V using Indian currency denominations:
 *   coins = {1, 2, 5, 10, 20, 50, 100, 200, 500, 2000}.
 * 
 * Part 2: Choose and Swap (GFG Practice Problem for this topic)
 * You are given a string S of lowercase English letters. You can choose any two 
 * distinct characters in the string and swap all occurrences of character 1 with 
 * character 2 and vice versa. Find the lexicographically smallest string you 
 * can obtain by performing this operation at most ONCE.
 * 
 * Example 1 (Coins):
 * Input: V = 43
 * Output: {20, 20, 2, 1} -> 4 coins
 * 
 * Example 2 (Choose and Swap):
 * Input: S = "ccad"
 * Output: "aacd" (choose 'c' and 'a', swap all 'c's with 'a's and 'a's with 'c's)
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Canonical vs Non-Canonical Coin Systems:
 *    - In an arbitrary coin system (e.g. {1, 7, 10} for V = 14), greedy fails
 *      (10 + 1 + 1 + 1 + 1 = 5 coins vs 7 + 7 = 2 coins) and DP is required.
 *    - In the standard Indian currency system, the denominations form a canonical
 *      system where Greedy is mathematically proven to always be optimal.
 * 2. Earliest Inversion in Choose and Swap:
 *    - To make a string lexicographically as small as possible, the most significant
 *      difference must occur as far LEFT as possible.
 *    - We find the first character from the left that can be replaced by a strictly
 *      smaller character that appears later in the string.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Part 1 (Greedy Coins):
 *   - Iterate from largest denomination to smallest.
 *   - Greedily pick `count = V / coin[i]`, and update `V %= coin[i]`.
 * 
 * Part 2 (Choose and Swap):
 *   - Track the first occurrence index of every character using an array `firstIndex[26]`.
 *   - Scan characters from left to right:
 *       For character `S[i]`, check all characters 'a' <= ch < S[i]:
 *         If `firstIndex[ch] > firstIndex[S[i]]`:
 *           We found our pair! Swap `S[i]` and `ch` across the entire string and break!
 *   - Time: O(26 * N) = O(N) linear time.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Part 1: Greedy Coin Change for Canonical Indian Currency
     */
    vector<int> minPartition(int V) {
        vector<int> denominations = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
        vector<int> result;

        for (int coin : denominations) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // In canonical coin systems, taking the maximal multiple of the largest
            // available coin leaves a residue that is provably minimized.
            while (V >= coin) {
                result.push_back(coin);
                V -= coin;
            }
        }

        return result;
    }

    /**
     * Part 2: Choose and Swap (Lexicographically Smallest via 1 Swap)
     */
    string chooseAndSwap(string s) {
        int n = s.length();
        vector<int> firstOccurrence(26, -1);

        // Record the first index of each character
        for (int i = 0; i < n; ++i) {
            if (firstOccurrence[s[i] - 'a'] == -1) {
                firstOccurrence[s[i] - 'a'] = i;
            }
        }

        char char1 = '\0', char2 = '\0';

        // Find the first character from left that has a smaller character appearing later
        for (int i = 0; i < n; ++i) {
            char curr = s[i];
            bool found = false;

            for (char ch = 'a'; ch < curr; ++ch) {
                // If character 'ch' is smaller and appeared later in the string
                if (firstOccurrence[ch - 'a'] > firstOccurrence[curr - 'a']) {
                    char1 = curr;
                    char2 = ch;
                    found = true;
                    break;
                }
            }

            if (found) break;
        }

        // If a valid pair is identified, swap all their occurrences
        if (char1 != '\0') {
            for (int i = 0; i < n; ++i) {
                if (s[i] == char1) s[i] = char2;
                else if (s[i] == char2) s[i] = char1;
            }
        }

        return s;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Part 1: Minimum Coins for V = 43
    // Expected: 20, 20, 2, 1 -> 4 coins
    int V = 43;
    vector<int> coins = solver.minPartition(V);
    cout << "Minimum Coins for V = " << V << ": ";
    for (int c : coins) cout << c << " ";
    cout << "\n";

    // Test Part 2: Choose and Swap for "ccad"
    // Expected: "aacd" (swap 'c' with 'a')
    string s = "ccad";
    cout << "Choose and Swap(\"ccad\") = " << solver.chooseAndSwap(s) 
         << " (Expected: aacd)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Part 1 (Coin Change):
 *   - Time Complexity: O(Number of Denominations) = O(10) = O(1) constant time.
 *   - Space Complexity: O(1) auxiliary space.
 * 
 * Part 2 (Choose and Swap):
 *   - Time Complexity: O(26 * N) = O(N) linear time.
 *   - Space Complexity: O(26) = O(1) fixed alphabet storage.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Greedy choice works for coin systems where no combination of smaller coins
 *    can surpass a larger coin without matching it.
 * 2. Lexicographical minimization always prioritizes modifying the leftmost possible character.
 */
