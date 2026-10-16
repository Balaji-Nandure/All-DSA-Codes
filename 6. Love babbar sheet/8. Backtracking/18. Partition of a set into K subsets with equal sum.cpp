#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/**
 * Problem: Partition of a set into K subsets with equal sum
 * 
 * Given an integer array arr of N elements and an integer K, determine if it is possible 
 * to partition the array into K non-empty subsets such that the sum of elements in each subset is identical.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "8. Subset Sum" and "10. Tug of War", we partitioned into K = 2 subsets.
 * - Here, K can be arbitrary (up to N). This is the NP-Complete Bin Packing / Multi-way Number Partitioning.
 * - Without aggressive symmetry breaking and pruning, K-branching explores K^N states (blows up).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Descending Backtracking with Bucket Symmetry Breaking:
 *   1. Early Rejections:
 *      - If total_sum % K != 0: return false (cannot partition into equal integer parts).
 *      - Let target = total_sum / K.
 *      - If max_element(arr) > target: return false.
 *   
 *   2. Descending Sort:
 *      Sort arr descending so the largest elements are placed first.
 *      Large elements have the fewest placement possibilities, triggering pruning near the root.
 *   
 *   3. Symmetry Breaking (The Magic Pruning):
 *      Maintain an array of bucket sums: `bucket_sum[0 ... K-1]`.
 *      For element arr[idx], try placing it into bucket j (0 <= j < K):
 *      - Prune 1: If bucket_sum[j] + arr[idx] > target, continue.
 *      - Prune 2 (Identical Buckets): If bucket_sum[j] == 0:
 *        If placing arr[idx] into this empty bucket fails to find a solution,
 *        DO NOT try placing arr[idx] into any other empty bucket!
 *        All empty buckets are indistinguishable/symmetric. Testing another empty bucket 
 *        is 100% redundant work.
 *      - Apply choice, recurse for idx + 1, and backtrack.
 */

class Solution {
    bool backtrack(int idx, int n, int target, int K, const vector<int>& arr, vector<int>& bucket_sums) {
        // Base case: All elements successfully distributed into valid buckets
        if (idx == n) {
            return true;
        }

        int curr_val = arr[idx];

        for (int j = 0; j < K; j++) {
            // Check if current value fits in bucket j
            if (bucket_sums[j] + curr_val <= target) {
                bucket_sums[j] += curr_val;

                // Recurse to place next element
                if (backtrack(idx + 1, n, target, K, arr, bucket_sums)) {
                    return true;
                }

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Backtrack: Remove element from bucket j
                bucket_sums[j] -= curr_val;

                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Symmetry Breaking: If the bucket was empty before, failing here means
                // placing curr_val into ANY other currently empty bucket will also fail.
                if (bucket_sums[j] == 0) {
                    break;
                }
            }
        }

        return false;
    }

public:
    bool isKPartitionPossible(vector<int>& arr, int K) {
        int n = arr.size();
        if (K == 1) return true;
        if (n < K) return false;

        int total_sum = accumulate(arr.begin(), arr.end(), 0);
        if (total_sum % K != 0) return false;

        int target = total_sum / K;

        // Sort descending to place largest elements first
        sort(arr.begin(), arr.end(), greater<int>());

        if (arr[0] > target) return false;

        vector<int> bucket_sums(K, 0);
        return backtrack(0, n, target, K, arr, bucket_sums);
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {2, 1, 4, 5, 6};
    int K1 = 3;
    cout << "Partition possible 1: " << (sol.isKPartitionPossible(arr1, K1) ? "YES" : "NO") << "\n";
    // Total sum = 18. Target = 6. Subsets: {6}, {5, 1}, {4, 2}. Expected: YES.

    vector<int> arr2 = {2, 1, 5, 5, 6};
    int K2 = 3;
    cout << "Partition possible 2: " << (sol.isKPartitionPossible(arr2, K2) ? "YES" : "NO") << "\n";
    // Total sum = 19 (not divisible by 3). Expected: NO.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(K^(N - K)) with worst-case search, but descending sort + bucket symmetry breaking 
 *   prunes redundant permutations, running nearly instantaneously for N <= 16.
 * - Space Complexity: O(K) for bucket sums and O(N) for recursion stack.
 */
