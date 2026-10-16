/**
 * Problem: Minimize Cash Flow Among a Given Set of Friends Who Borrowed Money
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Given an arbitrary matrix of peer-to-peer debts, naive settlement requires up to N*(N-1) transactions.
 * - However, individual transactions are fungible; only the NET balance of each individual matters.
 * - By greedily matching the biggest debtor with the biggest creditor, we can settle all debts in at most N - 1 transactions.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Net Balance Settlement:
 *   1. Calculate the net amount for each person:
 *      `net[p] = (total received by p) - (total paid by p)`.
 *      - If `net[p] > 0`, person `p` is owed money (creditor).
 *      - If `net[p] < 0`, person `p` owes money (debtor).
 *   2. Find the person with maximum net credit (`maxCreditor`) and person with maximum net debt (`maxDebtor`).
 *   3. If both net amounts are 0, all debts are completely settled!
 *   4. Transfer `min(-net[maxDebtor], net[maxCreditor])` from `maxDebtor` to `maxCreditor`.
 *   5. Update both net amounts and recurse until all debts are settled.
 * 
 * TIME COMPLEXITY:
 * - O(N^2): Finding min/max creditor and debtor takes O(N) per step, running at most N - 1 steps.
 * 
 * SPACE COMPLEXITY:
 * - O(N) for the net balance array.
 */

#include <iostream>
#include <vector>
#include <algorithm>

int getMinIndex(const std::vector<int>& net) {
    int minIdx = 0;
    for (int i = 1; i < (int)net.size(); i++) {
        if (net[i] < net[minIdx]) {
            minIdx = i;
        }
    }
    return minIdx;
}

int getMaxIndex(const std::vector<int>& net) {
    int maxIdx = 0;
    for (int i = 1; i < (int)net.size(); i++) {
        if (net[i] > net[maxIdx]) {
            maxIdx = i;
        }
    }
    return maxIdx;
}

void minCashFlowRec(std::vector<int>& net) {
    int maxCreditIdx = getMaxIndex(net);
    int maxDebitIdx = getMinIndex(net);

    // If both max credit and max debit are 0, all debts are cleared
    if (net[maxCreditIdx] == 0 && net[maxDebitIdx] == 0) {
        return;
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Settle the minimum of the max debt and max credit between the two most polarized individuals.
    int transferAmount = std::min(-net[maxDebitIdx], net[maxCreditIdx]);

    net[maxCreditIdx] -= transferAmount;
    net[maxDebitIdx] += transferAmount;

    std::cout << "Person " << maxDebitIdx << " pays " << transferAmount << " to Person " << maxCreditIdx << "\n";

    // Recurse for remaining amounts
    minCashFlowRec(net);
}

void minCashFlow(int N, const std::vector<std::vector<int>>& graph) {
    // net[p] stores net balance of person p
    std::vector<int> net(N, 0);

    for (int p = 0; p < N; p++) {
        for (int i = 0; i < N; i++) {
            net[p] += (graph[i][p] - graph[p][i]);
        }
    }

    minCashFlowRec(net);
}

int main() {
    int N = 3;
    // graph[i][j] indicates amount person i owes to person j
    std::vector<std::vector<int>> graph = {
        {0, 1000, 2000},
        {0, 0, 5000},
        {0, 0, 0}
    };

    std::cout << "Optimized Cash Flow Transactions:\n";
    minCashFlow(N, graph);
    // Person 1 pays 4000 to Person 2
    // Person 0 pays 3000 to Person 2

    return 0;
}
