#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/**
 * Problem: GERGOVIA - Wine trading in Gergovia (SPOJ)
 * 
 * N houses in Gergovia are arranged in a straight line.
 * House i has demand a[i]:
 * - a[i] > 0 means the inhabitant wants to buy a[i] units of wine.
 * - a[i] < 0 means the inhabitant wants to sell -a[i] units of wine.
 * - Total sum of all a[i] is guaranteed to be 0 (total supply = total demand).
 * Moving 1 unit of wine between adjacent houses (distance 1) takes 1 unit of work.
 * Find the minimum total work required to satisfy all demands.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "11. Minimize Cash Flow", any person could settle debt directly with any other person in O(1) cost.
 * - Here, physical space matters: transportation cost is linear in distance (|i - j|).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Cut Invariant / Prefix Flow Analysis:
 *   Consider the cut separating houses {1, 2, ..., i} from houses {i+1, ..., N}.
 *   The net wine demand of the first i houses is:
 *     PrefixBalance(i) = sum_{k=1}^i a[k].
 *   If PrefixBalance(i) > 0, exactly this much wine MUST flow from the right into the left across edge (i, i+1).
 *   If PrefixBalance(i) < 0, exactly |PrefixBalance(i)| wine MUST flow from the left to the right across edge (i, i+1).
 *   In both cases, exactly |PrefixBalance(i)| units of wine cross the edge between house i and house i+1.
 *   
 *   Because wine on the left cannot be magically teleported, this flow across edge (i, i+1) is mandatory.
 *   Therefore:
 *     Total Minimum Work = sum_{i=1}^{N-1} |PrefixBalance(i)|
 *   
 * - This gives an optimal O(N) single-pass greedy algorithm with O(1) extra space!
 */

class Solution {
public:
    long long minWork(int N, vector<int>& a) {
        long long total_work = 0;
        long long current_balance = 0;

        for (int i = 0; i < N; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Add current house's demand/supply to the rolling balance
            current_balance += a[i];

            // Every unit of imbalance must be transported to the next adjacent house
            // *** CRUCIAL LINE: Work is the absolute net flow crossing between house i and house i+1 ***
            total_work += abs(current_balance);
        }

        return total_work;
    }
};

int main() {
    Solution sol;
    vector<int> a1 = {5, -4, 1, -3, 1};
    int N1 = a1.size();
    cout << "Minimum Work 1: " << sol.minWork(N1, a1) << "\n";
    // Balances:
    // i=0: 5       -> work += 5
    // i=1: 5-4 = 1  -> work += 1
    // i=2: 1+1 = 2  -> work += 2
    // i=3: 2-3 = -1 -> work += 1
    // i=4: -1+1 = 0 -> work += 0
    // Total work = 9

    vector<int> a2 = {-1000, -1000, -1000, 1000, 1000, 1000};
    int N2 = a2.size();
    cout << "Minimum Work 2: " << sol.minWork(N2, a2) << "\n"; // Expected: 9000

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear pass over the houses.
 * - Space Complexity: O(1) auxiliary space (tracks only rolling balance and total work).
 */
