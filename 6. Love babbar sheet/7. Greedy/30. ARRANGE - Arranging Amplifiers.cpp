#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: ARRANGE - Arranging Amplifiers (SPOJ)
 * 
 * Scientists have built N signal amplifiers. Amplifier i has amplification factor A[i] >= 1.
 * When amplifiers are placed in a line A1, A2, ..., An, the amplified signal 
 * evaluates as: A1^(A2^(A3^(...^An))).
 * Arrange the amplifiers to produce the maximum possible output signal.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an exponentiation tower optimization problem.
 * - Unlike multiplication where order does not matter (A * B = B * A),
 *   exponentiation is non-commutative (A^B != B^A).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Mathematical Exponentiation Rules:
 *   1. Handling of 1s:
 *      For any number X > 1, X^1 = X, but 1^X = 1.
 *      To prevent 1 from dampening large powers in exponents, ALL 1s must be placed 
 *      at the very beginning so they form 1^(...) and do not weaken other exponential products.
 *   
 *   2. The General Rule for Numbers >= 2:
 *      In general, for two numbers a > b >= 3:
 *      b^a > a^b (e.g. 3^4 = 81 > 4^3 = 64; 3^5 = 243 > 5^3 = 125).
 *      Thus, larger numbers should be placed in the exponent (i.e. later in evaluation, 
 *      which corresponds to descending order from left to right).
 *   
 *   3. The Famous Exception for {2, 3}:
 *      2^3 = 8, but 3^2 = 9.
 *      Here 3^2 > 2^3!
 *      So when the remaining set is strictly {2, 3}, placing 2 before 3 gives 2^3 vs 3^2.
 *      Therefore, if remaining elements are exactly {2, 3}, the order must be `2 3`.
 *   
 *   4. All other remaining elements (> 1):
 *      Sort in strictly descending order.
 */

class Solution {
public:
    vector<int> arrangeAmplifiers(int n, vector<int>& a) {
        int count1 = 0;
        vector<int> rem;

        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                count1++;
            } else {
                rem.push_back(a[i]);
            }
        }

        vector<int> result;

        // Step 1: All 1s come first
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        for (int i = 0; i < count1; i++) {
            result.push_back(1);
        }

        // Step 2: Special case when the remaining numbers are exactly {2, 3}
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        if (rem.size() == 2 && ((rem[0] == 2 && rem[1] == 3) || (rem[0] == 3 && rem[1] == 2))) {
            result.push_back(2);
            result.push_back(3);
            return result;
        }

        // Step 3: For all other configurations, sort remaining elements in descending order
        sort(rem.begin(), rem.end(), greater<int>());
        for (int x : rem) {
            result.push_back(x);
        }

        return result;
    }
};

int main() {
    Solution sol;
    // Case 1: with 1s
    vector<int> a1 = {1, 4, 1, 5, 3};
    int n1 = a1.size();
    vector<int> ans1 = sol.arrangeAmplifiers(n1, a1);
    cout << "Arrangement 1: ";
    for (int x : ans1) cout << x << " ";
    cout << "\n"; // Expected: 1 1 5 4 3

    // Case 2: exactly 2 and 3
    vector<int> a2 = {2, 3};
    int n2 = a2.size();
    vector<int> ans2 = sol.arrangeAmplifiers(n2, a2);
    cout << "Arrangement 2: ";
    for (int x : ans2) cout << x << " ";
    cout << "\n"; // Expected: 2 3

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting the remaining elements.
 * - Space Complexity: O(N) to store remaining elements and return the arranged sequence.
 */
