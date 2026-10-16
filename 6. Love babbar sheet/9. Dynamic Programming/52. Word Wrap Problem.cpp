#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * Problem: Word Wrap Problem (Knuth-Plass Line Breaking)
 * 
 * Given an array nums[] of size N where nums[i] is the length of the i-th word, 
 * and a line width limit K.
 * Wrap words onto lines such that each line contains at most K characters 
 * (with exactly 1 space separating words on the same line).
 * Cost of a line with trailing spaces is: (extra_spaces)^2.
 * The LAST line has cost 0.
 * Find the minimum total cost to wrap all words.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is typesetting layout optimization.
 * - Unlike Greedy wrapping (which fills as many words as possible on each line, creating 
 *   ugly ragged text with huge gaps at the end), Dynamic Programming distributes spaces 
 *   evenly across lines to minimize quadratic penalty.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backward 1D Dynamic Programming in O(N * K) Time:
 *   Let dp[i] be the minimum cost to arrange words from index i to N - 1.
 *   
 *   Base Case:
 *     dp[N] = 0 (no words left, cost 0).
 *   
 *   Transitions for i from N - 1 down to 0:
 *     Try putting words nums[i ... j] on the current line:
 *     Current line length = sum_{k=i}^j nums[k] + (j - i) spaces.
 *     
 *     If length > K:
 *       Line overflow -> break (no more words can fit on this line).
 *     
 *     If j == N - 1 (last line):
 *       By problem rules, the last line has COST 0!
 *       dp[i] = 0; break;
 *     
 *     Else (internal line):
 *       extra_spaces = K - length
 *       line_cost = extra_spaces * extra_spaces
 *       dp[i] = min(dp[i], line_cost + dp[j + 1])
 *   
 *   Result:
 *     dp[0] gives the global optimal cost starting from the very first word.
 */

class Solution {
public:
    int solveWordWrap(vector<int> nums, int k) {
        int n = nums.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[n] = 0; // Base case: end of text has 0 cost

        for (int i = n - 1; i >= 0; i--) {
            int current_len = -1; // -1 to account for no leading space on the first word

            for (int j = i; j < n; j++) {
                current_len += nums[j] + 1; // 1 space + word length

                // If line exceeds capacity, cannot add more words to this line
                if (current_len > k) {
                    break;
                }

                // If this is the last line containing words up to n - 1, cost is 0
                if (j == n - 1) {
                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    dp[i] = 0;
                    break;
                }

                // Internal line: compute quadratic penalty of unused trailing spaces
                int extra = k - current_len;
                int cost = extra * extra;

                if (dp[j + 1] != INT_MAX) {
                    // *** CRUCIAL LINE: Minimize current line cost + future lines cost ***
                    dp[i] = min(dp[i], cost + dp[j + 1]);
                }
            }
        }

        return dp[0];
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {3, 2, 2, 5};
    int k1 = 6;
    cout << "Min Wrap Cost 1: " << sol.solveWordWrap(nums1, k1) << "\n";
    // Line 1: word 0 (3) -> extra = 6 - 3 = 3 -> cost 9.
    // Line 2: word 1 (2), word 2 (2) -> length 2+1+2 = 5 -> extra 1 -> cost 1.
    // Line 3: word 3 (5) [last line, cost 0].
    // Total cost = 9 + 1 + 0 = 10.
    // Or: Line 1: word 0 (3), word 1 (2) -> length 3+1+2 = 6 -> extra 0 -> cost 0!
    // Line 2: word 2 (2) -> cost 16. Line 3: word 3 (5) -> cost 0. Total = 16.
    // Optimal: Line 1: (3, 2) -> extra 0 (cost 0). Wait, 3+1+2 = 6! Extra = 0!
    // Line 2: (2) -> extra 4 -> cost 16.
    // Line 3: (5) -> last line -> cost 0. Total = 16.
    // Wait, what about Line 1: (3) -> cost 9; Line 2: (2, 2) -> extra 1, cost 1; Line 3: (5) -> cost 0. Total = 9 + 1 = 10!
    // Minimum is 10! Expected: 10.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * K) because at most K words can fit on any single line.
 * - Space Complexity: O(N) auxiliary space for the 1D dp array.
 */
