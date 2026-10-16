#include <iostream>
#include <vector>
#include <climits>
#include <numeric>

using namespace std;

/**
 * Problem: Optimal Binary Search Tree (Optimal BST)
 * 
 * Given a sorted array of distinct keys keys[0 ... N-1] and an array freq[0 ... N-1] 
 * of their search frequencies.
 * Construct a Binary Search Tree (BST) of all keys such that the total search cost is MINIMIZED:
 * Total Cost = sum_{i=0}^{N-1} (depth(keys[i]) * freq[i])   where root is at depth 1.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "5. Catalan Number", we counted structurally distinct BSTs.
 * - In "6. Matrix Chain Multiplication (MCM)", we partitioned matrices at an intermediate multiplication.
 * - Here, partitioning at root key `r` places `r` at depth 1 and INCREASES the depth of EVERY 
 *   node in both left [i ... r-1] and right [r+1 ... j] subtrees by 1!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Interval Dynamic Programming:
 *   Let cost[i][j] be the minimum search cost for keys keys[i ... j].
 *   
 *   Mathematical Property:
 *     If keys[r] is chosen as the root of the sub-BST for keys[i ... j]:
 *     - Left subtree spans keys[i ... r - 1].
 *     - Right subtree spans keys[r + 1 ... j].
 *     Because making keys[r] the parent pushes every node in [i ... j] one level deeper,
 *     the extra cost incurred is exactly the SUM of frequencies of all keys in [i ... j]:
 *       sum_freq(i, j) = sum_{k=i}^j freq[k].
 *     
 *     Recurrence:
 *       cost[i][j] = sum_freq(i, j) + min_{i <= r <= j} { cost[i][r - 1] + cost[r + 1][j] }
 *     
 *   Base Cases:
 *     cost[i][i] = freq[i] (single key at root, cost is 1 * freq[i]).
 *     cost[i][j] = 0 when i > j (empty subtree).
 */

class Solution {
    // Helper to calculate sum of frequencies from index i to j in O(1) via prefix sums
    int sumFreq(const vector<int>& prefix, int i, int j) {
        if (i == 0) return prefix[j];
        return prefix[j] - prefix[i - 1];
    }

public:
    int optimalSearchTree(int keys[], int freq[], int n) {
        // Precompute prefix sums of frequencies
        vector<int> prefix(n, 0);
        prefix[0] = freq[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + freq[i];
        }

        // cost[i][j] stores min search cost for keys[i ... j]
        vector<vector<int>> cost(n, vector<int>(n, 0));

        // Subtree sizes from L = 1 to n
        for (int L = 1; L <= n; L++) {
            for (int i = 0; i <= n - L; i++) {
                int j = i + L - 1;

                if (L == 1) {
                    cost[i][j] = freq[i];
                } else {
                    cost[i][j] = INT_MAX;
                    int f_sum = sumFreq(prefix, i, j);

                    // Try every key r in [i ... j] as root
                    for (int r = i; r <= j; r++) {
                        int left_cost  = (r > i) ? cost[i][r - 1] : 0;
                        int right_cost = (r < j) ? cost[r + 1][j] : 0;

                        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                        // Cost = frequency sum of all elements + cost of left subtree + cost of right subtree
                        int total_candidate_cost = f_sum + left_cost + right_cost;
                        cost[i][j] = min(cost[i][j], total_candidate_cost);
                    }
                }
            }
        }

        return cost[0][n - 1];
    }
};

int main() {
    Solution sol;
    int keys[] = {10, 12, 20};
    int freq[] = {34, 8, 50};
    int n = sizeof(keys) / sizeof(keys[0]);

    cout << "Optimal BST Search Cost: " << sol.optimalSearchTree(keys, freq, n) << "\n";
    // If 20 is root: 10 is left child, 12 is right child of 10.
    // Cost = 1*50 + 2*34 + 3*8 = 50 + 68 + 24 = 142. Expected: 142.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N^3). Three nested loops: chain length L, start index i, and root candidate r.
 *   (Can be reduced to O(N^2) using Knuth's optimization).
 * - Space Complexity: O(N^2) for the cost table.
 */
