#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Problem: Find smallest number with given number of digits and sum of digits
 * 
 * Given two integers S (sum of digits) and D (number of digits), find the smallest 
 * number with exactly D digits whose digits sum to S.
 * If no such D-digit number exists, return "-1".
 * Note: A valid D-digit number cannot have leading zeros (except the number 0 itself if D = 1).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is a positional number construction problem with fixed sum constraints.
 * - Because the value of a digit is multiplied by 10^(position), leftmost digits have 
 *   exponentially higher significance than rightmost digits.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Allocation from Right to Left:
 *   1. Feasibility Check:
 *      The maximum possible digit sum with D digits is 9 * D (all 9s).
 *      If S > 9 * D, it's impossible.
 *      If S == 0:
 *        - If D == 1, answer is "0".
 *        - If D > 1, impossible (a number cannot start with 0).
 *   
 *   2. To make the number as SMALL as possible:
 *      We want the most significant digits (left) to be as close to 0 (or 1) as possible,
 *      and the least significant digits (right) to absorb as much of the sum as possible (up to 9).
 *   
 *   3. Algorithm:
 *      - Deduct 1 from S in advance to reserve the leading digit of at least 1: S = S - 1.
 *      - Fill digits from index D - 1 (units place) down to 1:
 *        digit[i] = min(S, 9);
 *        S -= digit[i];
 *      - For the most significant digit (index 0):
 *        digit[0] = 1 + S; (guaranteed to be between 1 and 9).
 */

class Solution {
public:
    string smallestNumber(int S, int D) {
        // Impossible cases
        if (S > 9 * D) return "-1";
        if (S == 0) {
            return (D == 1) ? "0" : "-1";
        }

        vector<int> digits(D, 0);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Reserve 1 for the most significant digit to prevent illegal leading zeros
        S -= 1;

        // Fill from least significant digit (rightmost) to index 1
        for (int i = D - 1; i > 0; i--) {
            if (S >= 9) {
                // *** CRUCIAL LINE: Greedily dump maximum possible value (9) into lower significance digits ***
                digits[i] = 9;
                S -= 9;
            } else {
                digits[i] = S;
                S = 0;
            }
        }

        // Most significant digit receives 1 + whatever remainder of S is left
        digits[0] = 1 + S;

        string result = "";
        for (int d : digits) {
            result += to_string(d);
        }

        return result;
    }
};

int main() {
    Solution sol;
    cout << "Smallest (S=9, D=2):  " << sol.smallestNumber(9, 2) << "\n";  // Expected: "18"
    cout << "Smallest (S=20, D=3): " << sol.smallestNumber(20, 3) << "\n"; // Expected: "299"
    cout << "Smallest (S=25, D=2): " << sol.smallestNumber(25, 2) << "\n"; // Expected: "-1" (max is 18)
    cout << "Smallest (S=0, D=1):  " << sol.smallestNumber(0, 1) << "\n";  // Expected: "0"

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(D) single pass across the D digits.
 * - Space Complexity: O(D) to construct the result string.
 */
