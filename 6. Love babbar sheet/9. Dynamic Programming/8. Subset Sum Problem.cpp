#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

/**
 * Problem: Subset Sum Problem (Dynamic Programming)
 * 
 * Given an array of non-negative integers arr[] and an integer target `sum`.
 * Determine if there exists a subset of elements whose sum equals `sum`.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Category 8, problem 8, we explored this problem via DFS Backtracking with pruning.
 * - While Backtracking is worst-case O(2^N), Dynamic Programming operates in pseudo-polynomial 
 *   O(N * sum) time, providing absolute determinism against worst-case adversary inputs.
 * - Moreover, using Bitset DP, this can be accelerated by a factor of 64 using bitwise parallel shifts!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - 1D Boolean Dynamic Programming:
 *   Let dp[j] be a boolean indicating whether a subset sum of j can be formed.
 *   
 *   Base Case:
 *     dp[0] = true (sum 0 is always formed by selecting the empty subset).
 *   
 *   Recurrence:
 *     For each element x in arr:
 *       Traverse j BACKWARD from target down to x:
 *       dp[j] = dp[j] || dp[j - x]
 *     (Backward traversal prevents reusing element x multiple times, enforcing 0-1 subset property).
 * 
 * - Ultrafast Bitset Optimization (O(N * sum / 64)):
 *   A bitset can represent all reachable sums as set bits!
 *   Initially: bitset<MAX> bits; bits[0] = 1.
 *   For each x in arr:
 *     bits |= (bits << x); // Parallel addition of x to all existing reachable sums!
 *   Result is simply bits[sum].
 */

class Solution {
public:
    // Standard 1D DP in O(N * sum) Time and O(sum) Space
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
        vector<bool> dp(sum + 1, false);

        // Base case: sum 0 is always achievable (empty subset)
        dp[0] = true;

        for (int i = 0; i < n; i++) {
            int val = arr[i];

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Traverse backward from sum down to val to guarantee 0-1 single-use per element
            for (int j = sum; j >= val; j--) {
                // *** CRUCIAL LINE: State transition: either exclude val (dp[j]) or include val (dp[j - val]) ***
                dp[j] = dp[j] || dp[j - val];
            }
        }

        return dp[sum];
    }

    // Ultrafast Bitset DP (64x parallel speedup)
    bool isSubsetSumBitset(vector<int>& arr, int sum) {
        const int MAX_SUM = 100005;
        if (sum >= MAX_SUM) return false;

        bitset<MAX_SUM> bits;
        bits[0] = 1; // Base case: sum 0 is reachable

        for (int x : arr) {
            // *** CRUCIAL LINE: 64-bit hardware parallel shift adds x to all previously reached sums ***
            bits |= (bits << x);
        }

        return bits[sum];
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {3, 34, 4, 12, 5, 2};
    int sum1 = 9;
    cout << "Subset sum " << sum1 << " possible: " << (sol.isSubsetSum(arr1, sum1) ? "YES" : "NO") << "\n";
    // Subset {4, 5} sums to 9 -> YES

    vector<int> arr2 = {3, 34, 4, 12, 5, 2};
    int sum2 = 30;
    cout << "Subset sum " << sum2 << " possible: " << (sol.isSubsetSum(arr2, sum2) ? "YES" : "NO") << "\n";
    // Expected: NO

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - 1D DP Time Complexity: O(N * sum).
 * - Bitset DP Time Complexity: O(N * sum / 64) due to 64-bit word parallelism.
 * - Space Complexity: O(sum) 1D boolean array.
 */
