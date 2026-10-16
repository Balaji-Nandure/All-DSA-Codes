#include <iostream>
#include <vector>

using namespace std;

/**
 * Problem: Coin game winner where every player has three choices
 * 
 * Two players A and B are playing a game with N coins.
 * In each turn, a player can pick either 1, X, or Y coins.
 * Player A always moves first, and both players play optimally.
 * The player who picks the last coin wins.
 * Determine whether Player A wins or Player B wins.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is Combinatorial Game Theory (Impartial Game / Sprague-Grundy theorem).
 * - Unlike optimization problems (finding maximum sum or minimum count),
 *   here each state is binary: either a WINNING state (N-position) or a LOSING state (P-position).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Game Theory Dynamic Programming (Win/Loss State Evaluation):
 *   Let dp[i] be true if the player who moves from state i has a forced WINNING strategy.
 *   
 *   Fundamental Axioms of Impartial Games:
 *   1. Base Case: dp[0] = false.
 *      (0 coins remaining means the player whose turn it is has no valid move and loses).
 *   
 *   2. Win/Loss Invariant:
 *      A state i is a WINNING state (true) if and only if there exists AT LEAST ONE legal move 
 *      that leaves the opponent in a LOSING state (false)!
 *      
 *      From state i, the player can move to:
 *      - (i - 1) coins
 *      - (i - X) coins (if i >= X)
 *      - (i - Y) coins (if i >= Y)
 *      
 *      If ANY of dp[i - 1], dp[i - X], or dp[i - Y] is FALSE, the current player simply 
 *      makes that move, handing the opponent a losing position!
 *      
 *      Recurrence:
 *        dp[i] = (!dp[i - 1]) || 
 *                (i >= X && !dp[i - X]) || 
 *                (i >= Y && !dp[i - Y])
 *   
 *   Result:
 *     If dp[N] == true, Player A wins.
 *     If dp[N] == false, Player B wins.
 */

class Solution {
public:
    char findWinner(int n, int x, int y) {
        vector<bool> dp(n + 1, false);

        // Base case: 0 coins means current player loses
        dp[0] = false;
        // 1 coin: current player picks 1 and wins immediately
        dp[1] = true;

        for (int i = 2; i <= n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Current state is WINNING if ANY move leads to a state where the opponent loses (!dp[...])
            if (!dp[i - 1]) {
                dp[i] = true;
            } else if (i >= x && !dp[i - x]) {
                dp[i] = true;
            } else if (i >= y && !dp[i - y]) {
                dp[i] = true;
            } else {
                // All possible moves lead to winning states for the opponent -> current state is losing
                dp[i] = false;
            }
        }

        return dp[n] ? 'A' : 'B';
    }
};

int main() {
    Solution sol;
    int n1 = 5, x1 = 3, y1 = 4;
    cout << "Winner (N=5, X=3, Y=4): " << sol.findWinner(n1, x1, y1) << "\n";
    // A picks 4 coins -> leaves 1 coin for B. B picks 1 coin and wins?
    // Wait: A picks 3 coins -> leaves 2 coins. B can only pick 1 -> leaves 1 for A. A picks 1 and wins!
    // Output: A. Expected: A.

    int n2 = 2, x2 = 3, y2 = 4;
    cout << "Winner (N=2, X=3, Y=4): " << sol.findWinner(n2, x2, y2) << "\n";
    // Neither 3 nor 4 can be picked. A picks 1 -> leaves 1 for B. B picks 1 and wins!
    // Output: B. Expected: B.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single pass from 2 to N with O(1) transitions.
 * - Space Complexity: O(N) boolean array.
 */
