#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * Problem: Boolean Parenthesization Problem
 * 
 * Given a boolean expression S consisting of symbols 'T' (true), 'F' (false) 
 * and operators '&' (AND), '|' (OR), '^' (XOR).
 * Count the number of ways to parenthesize the expression such that it evaluates to TRUE.
 * Return the result modulo 1003.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an Interval DP on Boolean Logic.
 * - Unlike "6. Matrix Chain Multiplication" which only tracked minimum scalar operations,
 *   here we must track TWO simultaneous quantities for every sub-interval [i ... j]:
 *   1. T[i][j]: Ways to evaluate to TRUE.
 *   2. F[i][j]: Ways to evaluate to FALSE.
 *   Why track FALSE?
 *   Because boolean operators depend critically on false sub-evaluations 
 *   (e.g., in XOR (^): TRUE is achieved by (T ^ F) and (F ^ T)!).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dual-Table Interval Dynamic Programming:
 *   Let string S have symbols at even indices (0, 2, 4...) and operators at odd indices (1, 3, 5...).
 *   Let m be the number of symbols: m = (N + 1) / 2.
 *   
 *   Base Case (L = 1, single symbol):
 *     If symbol[i] == 'T': T[i][i] = 1, F[i][i] = 0.
 *     If symbol[i] == 'F': T[i][i] = 0, F[i][i] = 1.
 *   
 *   Transitions for chain length L from 2 to m:
 *     For split point k from i to j - 1:
 *       Let operator = operators[k].
 *       LT = T[i][k], LF = F[i][k]
 *       RT = T[k+1][j], RF = F[k+1][j]
 *       
 *       Depending on operator:
 *       - '&' (AND):
 *         True:  LT * RT
 *         False: (LT * RF) + (LF * RT) + (LF * RF)
 *       - '|' (OR):
 *         True:  (LT * RT) + (LT * RF) + (LF * RT)
 *         False: LF * RF
 *       - '^' (XOR):
 *         True:  (LT * RF) + (LF * RT)
 *         False: (LT * RT) + (LF * RF)
 */

class Solution {
    const int MOD = 1003;
public:
    int countWays(int n, string S) {
        // Extract symbols and operators
        string symbols = "";
        string ops = "";
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) symbols += S[i];
            else ops += S[i];
        }

        int m = symbols.length();
        vector<vector<int>> T(m, vector<int>(m, 0));
        vector<vector<int>> F(m, vector<int>(m, 0));

        // Base cases
        for (int i = 0; i < m; i++) {
            if (symbols[i] == 'T') {
                T[i][i] = 1;
                F[i][i] = 0;
            } else {
                T[i][i] = 0;
                F[i][i] = 1;
            }
        }

        // Sub-expression length from 2 to m
        for (int L = 2; L <= m; L++) {
            for (int i = 0; i <= m - L; i++) {
                int j = i + L - 1;

                for (int k = i; k < j; k++) {
                    char op = ops[k];

                    long long LT = T[i][k];
                    long long LF = F[i][k];
                    long long RT = T[k + 1][j];
                    long long RF = F[k + 1][j];

                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Truth and falsity evaluations according to boolean operator truth tables
                    if (op == '&') {
                        T[i][j] = (T[i][j] + (LT * RT)) % MOD;
                        F[i][j] = (F[i][j] + (LT * RF) + (LF * RT) + (LF * RF)) % MOD;
                    } else if (op == '|') {
                        T[i][j] = (T[i][j] + (LT * RT) + (LT * RF) + (LF * RT)) % MOD;
                        F[i][j] = (F[i][j] + (LF * RF)) % MOD;
                    } else if (op == '^') {
                        T[i][j] = (T[i][j] + (LT * RF) + (LF * RT)) % MOD;
                        F[i][j] = (F[i][j] + (LT * RT) + (LF * RF)) % MOD;
                    }
                }
            }
        }

        return T[0][m - 1];
    }
};

int main() {
    Solution sol;
    string s1 = "T|T&F^T";
    cout << "Ways to evaluate TRUE 1: " << sol.countWays(s1.length(), s1) << "\n";
    // Expected: 4

    string s2 = "T^F|F";
    cout << "Ways to evaluate TRUE 2: " << sol.countWays(s2.length(), s2) << "\n";
    // Expected: 2 ((T^F)|F and T^(F|F))

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(M^3) where M is the number of boolean symbols (M <= N/2).
 * - Space Complexity: O(M^2) for the dual T and F interval matrices.
 */
