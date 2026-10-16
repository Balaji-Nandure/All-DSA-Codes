#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Combinational Sum (Combination Sum I)
 * 
 * Given an array of integers A and a target value B, find all unique combinations 
 * in A where the candidate numbers sum to B.
 * The same candidate number may be chosen from A an unlimited number of times.
 * Combinations must be returned in sorted order without duplicates.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "8. Subset Sum Problem", each array element could be picked AT MOST ONCE.
 * - In Combination Sum, each element can be reused an UNLIMITED number of times (self-loop transitions).
 * - Therefore, the recursive call keeps the same candidate index `i`, rather than advancing to `i + 1`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Sorted Backtracking with Unbounded Selection:
 *   1. Deduplication and Sorting:
 *      Sort input array A ascending and remove duplicates to guarantee all generated combinations 
 *      are unique and lexicographically ordered.
 *   2. Pruned Backtracking:
 *      Function backtrack(idx, remaining_target, current_combo):
 *      - If remaining_target == 0:
 *        Found a valid combination! Add to result.
 *      - Loop candidate i from idx to n - 1:
 *        - Pruning: Since A is sorted, if A[i] > remaining_target, ALL subsequent candidates 
 *          will also be > remaining_target! Break loop immediately.
 *        - Choice: Add A[i] to current_combo.
 *        - Recurse: backtrack(i, remaining_target - A[i], current_combo)
 *          *** Passing `i` (not `i + 1`) allows unlimited reuse of element A[i]! ***
 *        - Backtrack: current_combo.pop_back().
 */

class Solution {
    void backtrack(int idx, int remaining, const vector<int>& A, 
                   vector<int>& current, vector<vector<int>>& result) {
        // Base case: Exact target reached
        if (remaining == 0) {
            result.push_back(current);
            return;
        }

        for (int i = idx; i < (int)A.size(); i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Pruning: Since array is sorted, no subsequent element can fit into remaining target
            if (A[i] > remaining) {
                break;
            }

            current.push_back(A[i]);

            // *** CRUCIAL LINE: Recurse passing index `i` (allows element reuse) ***
            backtrack(i, remaining - A[i], A, current, result);

            // Backtrack: Remove candidate to explore alternative branch
            current.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& A, int B) {
        // Step 1: Sort and deduplicate input array
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());

        vector<vector<int>> result;
        vector<int> current;

        backtrack(0, B, A, current, result);
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> A = {2, 4, 6, 8};
    int B = 8;

    vector<vector<int>> combinations = sol.combinationSum(A, B);
    cout << "Combinations summing to " << B << ":\n";
    for (const auto& combo : combinations) {
        cout << "  ( ";
        for (int x : combo) cout << x << " ";
        cout << ")\n";
    }
    // Expected:
    // ( 2 2 2 2 )
    // ( 2 2 4 )
    // ( 2 6 )
    // ( 4 4 )
    // ( 8 )

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(2^(Target / min_element) * N). The maximum recursion depth is Target / min(A).
 *   Sorted break pruning eliminates subtrees whose sums exceed target instantly.
 * - Space Complexity: O(Target / min_element) recursion stack depth and temporary combination buffer.
 */
