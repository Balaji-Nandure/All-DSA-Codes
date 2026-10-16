/**
 * ============================================================================
 * Problem: Weighted Job Scheduling in O(N log N) Time
 * Category: Searching and Sorting / Dynamic Programming
 * 
 * Problem Statement:
 * Given N jobs where every job is represented by following three elements:
 *   1. Start Time
 *   2. Finish Time
 *   3. Profit Associated
 * 
 * Find the maximum profit subset of jobs such that no two jobs in the subset
 * overlap. Two jobs can be scheduled if one ends before or at the time the other
 * starts (i.e. start >= finish).
 * 
 * Constraints:
 * 1 <= N <= 100,000
 * 1 <= startTime < finishTime <= 10^9
 * 1 <= profit <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Unweighted vs Weighted Scheduling:
 *    - In classic unweighted interval scheduling, greedy sorting by finish time
 *      and picking the first compatible job is optimal.
 *    - With weights (profits), greedy completely fails because a single job with
 *      huge profit might overlap with multiple smaller profit jobs.
 * 2. Combining Dynamic Programming with Binary Search:
 *    - Standard DP checks all previous non-overlapping jobs, resulting in O(N^2)
 *      time, which is far too slow for N = 100,000.
 *    - By sorting by finish time, finish times become strictly non-decreasing.
 *    - This allows us to find the latest non-conflicting job in O(log N) time
 *      using Binary Search, bringing total time to optimal O(N log N).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Data Structure:
 *    - Represent each job as struct {start, finish, profit}.
 * 2. Sorting:
 *    - Sort all jobs in non-decreasing order of finish time.
 * 3. Recurrence Relation:
 *    - For job i (0-indexed):
 *        Option A: Don't include job i -> max profit = dp[i - 1].
 *        Option B: Include job i -> profit[i] + dp[p], where p is the index of
 *                  the latest job that finishes <= job[i].start.
 *        dp[i] = max(Option A, Option B)
 * 4. Finding p via Binary Search:
 *    - We search for the largest index `idx < i` such that `job[idx].finish <= job[i].start`.
 *    - Can be done with a custom binary search or `upper_bound`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    long long start;
    long long finish;
    long long profit;
};

class Solution {
private:
    /**
     * Binary search to find the latest job (before index 'currentIndex')
     * whose finish time <= jobs[currentIndex].start.
     * Returns -1 if no such job exists.
     */
    int findLatestNonConflicting(const vector<Job>& jobs, int currentIndex) {
        int low = 0, high = currentIndex - 1;
        int nonConflictIdx = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (jobs[mid].finish <= jobs[currentIndex].start) {
                nonConflictIdx = mid; // Candidate found, try finding an even later one
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return nonConflictIdx;
    }

public:
    /**
     * Computes the maximum profit for weighted job scheduling in O(N log N).
     * @param jobs Vector of Job structs.
     * @return Maximum total profit attainable.
     */
    long long maxWeightedProfit(vector<Job>& jobs) {
        int n = jobs.size();
        if (n == 0) return 0;

        // Step 1: Sort jobs by finish time in non-decreasing order
        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.finish < b.finish;
        });

        // Step 2: dp[i] stores the maximum profit considering a subset of jobs from jobs[0...i]
        vector<long long> dp(n, 0);
        dp[0] = jobs[0].profit;

        for (int i = 1; i < n; ++i) {
            // Option 1: Exclude the current job
            long long inclProfit = jobs[i].profit;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Binary search replaces an O(N) backward linear scan with O(log N) lookup,
            // finding the most recent job that does not overlap with jobs[i].start.
            int l = findLatestNonConflicting(jobs, i);
            if (l != -1) {
                inclProfit += dp[l];
            }

            // Option 2: Exclude current job (dp[i - 1]) vs Include current job (inclProfit)
            dp[i] = max(dp[i - 1], inclProfit);
        }

        return dp[n - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1:
    // Job 1: (1, 2, 50)
    // Job 2: (3, 5, 20)
    // Job 3: (6, 19, 100)
    // Job 4: (2, 100, 200)
    // Optimal: Job 1 + Job 4 = 50 + 200 = 250 (since Job 4 starts at 2, compatible with Job 1 ending at 2)
    vector<Job> jobs1 = {
        {1, 2, 50},
        {3, 5, 20},
        {6, 19, 100},
        {2, 100, 200}
    };
    cout << "Test 1: Max Profit = " << solver.maxWeightedProfit(jobs1) << " (Expected: 250)\n";

    // Test Case 2:
    // Job 1: (3, 10, 20)
    // Job 2: (1, 2, 50)
    // Job 3: (6, 19, 100)
    // Job 4: (2, 100, 200)
    vector<Job> jobs2 = {
        {3, 10, 20},
        {1, 2, 50},
        {6, 19, 100},
        {2, 100, 200}
    };
    cout << "Test 2: Max Profit = " << solver.maxWeightedProfit(jobs2) << " (Expected: 250)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting jobs by finish time: O(N log N).
 *   - DP computation: N iterations. Each iteration performs one binary search of O(log N).
 *   - Total Time Complexity: O(N log N).
 *   - Efficiently handles N = 10^5 in < 0.05 seconds.
 * 
 * Space Complexity:
 *   - DP array of size N: O(N).
 *   - Total Space Complexity: O(N).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Sorting intervals by endpoint enables monotonicity for earlier intervals.
 * 2. Any interval-DP problem where state transition depends on non-overlapping
 *    predecessors can be accelerated from O(N^2) to O(N log N) via Binary Search.
 */
