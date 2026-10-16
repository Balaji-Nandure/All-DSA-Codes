/**
 * ============================================================================
 * Problem: Minimize Cash Flow Among Given Set of Friends (Splitwise Debt Settlement)
 * Category: Greedy / Graph Flow
 * 
 * Problem Statement:
 * Given a set of N friends who have borrowed money from one another. A 2D transaction
 * matrix `graph[N][N]` is given where `graph[i][j]` indicates the amount person `i`
 * owes to person `j`.
 * 
 * Minimize the total number of cash transactions needed to completely settle 
 * all debts among the N friends.
 * 
 * Example:
 * Input (3 friends: 0, 1, 2):
 *   graph = [
 *     [0, 1000, 2000],  // Person 0 owes 1000 to 1, and 2000 to 2
 *     [0,    0, 5000],  // Person 1 owes 5000 to 2
 *     [0,    0,    0]   // Person 2 owes nothing
 *   ]
 * Output:
 *   Person 1 pays 4000 to Person 2
 *   Person 0 pays 3000 to Person 2
 * Explanation:
 *   Original transactions: 3
 *   Minimized transactions: 2 (and total cash flow simplified)
 * 
 * Constraints:
 * 1 <= N <= 100
 * 0 <= graph[i][j] <= 10^5
 * Must settle all debts in at most (N - 1) transactions.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Multi-Party Debt Simplification:
 *    - In previous graph problems, paths and platform assignments were fixed.
 *    - Here, the identity of WHO pays WHOM is completely fluid; only the NET BALANCE
 *      of each individual person matters!
 * 2. Net Zero Sum Conservation:
 *    - The sum of all net credits and net debts is strictly zero: sum(net[i]) == 0.
 *    - By greedily settling the maximum debtor against the maximum creditor at
 *      each step, at least one person's net balance is completely zeroed out,
 *      guaranteeing completion in at most (N - 1) transactions.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy Maximum-Creditor vs Maximum-Debtor Pairing:
 *   - Step 1: Calculate net balance for each person `i`:
 *       `netAmount[i] = (incoming to i) - (outgoing from i)`
 *       `netAmount[i] = sum_j graph[j][i] - sum_j graph[i][j]`.
 *   - Step 2: Recursively settle debts:
 *       - Find person with maximum debt (most negative net): `maxDebtor`.
 *       - Find person with maximum credit (most positive net): `maxCreditor`.
 *       - If both balances are 0: all debts are fully cleared, terminate.
 *       - Compute transferable amount:
 *           `transfer = min(-netAmount[maxDebtor], netAmount[maxCreditor]);`
 *       - Record: `maxDebtor pays transfer to maxCreditor`.
 *       - Update:
 *           `netAmount[maxDebtor] += transfer;`
 *           `netAmount[maxCreditor] -= transfer;`
 *       - Recurse for remaining non-zero net amounts.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Transaction {
    int from;
    int to;
    int amount;
};

class Solution {
private:
    /**
     * Finds the index of the person with the maximum net credit (largest positive balance).
     */
    int getMaxCreditor(const vector<int>& netAmount, int n) {
        int maxIdx = 0;
        for (int i = 1; i < n; ++i) {
            if (netAmount[i] > netAmount[maxIdx]) {
                maxIdx = i;
            }
        }
        return maxIdx;
    }

    /**
     * Finds the index of the person with the maximum net debt (most negative balance).
     */
    int getMaxDebtor(const vector<int>& netAmount, int n) {
        int minIdx = 0;
        for (int i = 1; i < n; ++i) {
            if (netAmount[i] < netAmount[minIdx]) {
                minIdx = i;
            }
        }
        return minIdx;
    }

    /**
     * Recursive greedy helper to pair max debtor with max creditor.
     */
    void settleCashFlow(vector<int>& netAmount, int n, vector<Transaction>& transactions) {
        int maxCreditor = getMaxCreditor(netAmount, n);
        int maxDebtor = getMaxDebtor(netAmount, n);

        // Base case: If both maximum credit and maximum debt are 0, all balances settled!
        if (netAmount[maxCreditor] == 0 && netAmount[maxDebtor] == 0) {
            return;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Transfer the maximum possible amount that fully settles either the debtor or creditor:
        // transfer = min(debt of maxDebtor, credit of maxCreditor).
        int transferAmount = min(-netAmount[maxDebtor], netAmount[maxCreditor]);

        netAmount[maxCreditor] -= transferAmount;
        netAmount[maxDebtor] += transferAmount;

        transactions.push_back({maxDebtor, maxCreditor, transferAmount});

        // Recurse for the remaining balances
        settleCashFlow(netAmount, n, transactions);
    }

public:
    /**
     * Minimizes the cash flow across N friends.
     * @param graph 2D matrix where graph[i][j] is amount person i owes to person j.
     * @return Vector of minimized transactions.
     */
    vector<Transaction> minCashFlow(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> netAmount(n, 0);

        // Step 1: Calculate net balance for each friend
        for (int p = 0; p < n; ++p) {
            for (int q = 0; q < n; ++q) {
                netAmount[p] += (graph[q][p] - graph[p][q]);
            }
        }

        vector<Transaction> transactions;

        // Step 2: Greedily eliminate debts
        settleCashFlow(netAmount, n, transactions);

        return transactions;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case: 3 friends
    // 0 owes 1000 to 1, 2000 to 2
    // 1 owes 5000 to 2
    vector<vector<int>> graph = {
        {0, 1000, 2000},
        {0,    0, 5000},
        {0,    0,    0}
    };

    vector<Transaction> result = solver.minCashFlow(graph);

    cout << "Minimized Transactions (Total: " << result.size() << "):\n";
    for (auto& t : result) {
        cout << "Person " << t.from << " pays " << t.amount 
             << " to Person " << t.to << "\n";
    }
    // Expected:
    // Person 1 pays 4000 to Person 2
    // Person 0 pays 3000 to Person 2

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Computing net amount matrix: O(N^2).
 *   - Each settlement step completely zeroes out at least one person's balance.
 *   - Therefore, at most (N - 1) recursive transactions occur.
 *   - Finding min/max debtor/creditor takes O(N) per step.
 *   - Total Time: O(N^2).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(N) for net amount array and recursion stack.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Debts can be decoupled from pairwise relationships into global net balances.
 * 2. Pairing the extreme debtor with the extreme creditor guarantees that any
 *    debt network can be fully settled in at most N - 1 transactions.
 */
