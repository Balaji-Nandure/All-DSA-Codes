#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Weighted Job Scheduling (Maximum Profit in Job Scheduling)
 * 
 * Given N jobs where each job has a start time, finish time, and profit.
 * Find the maximum profit subset of jobs such that no two selected jobs overlap in time.
 * (A job can start at the exact same moment another job ends).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Greedy: Activity Selection Problem", all jobs had equal weight, so greedy finish time 
 *   was optimal.
 * - In "24. Max Length Chain of Pairs", weights were also equal (1 per pair).
 * - Here, jobs have ARBITRARY PROFITS (weights). Greedy choice fails because a long job 
 *   can have a massive profit that outweighs multiple short jobs.
 * - Combining Finish-Time Sorting + Dynamic Programming + Binary Search yields optimal O(N log N).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - DP with Binary Search Predecessor Query in O(N log N) Time:
 *   1. Sort all jobs by FINISH TIME ascending:
 *      jobs[0].finish <= jobs[1].finish <= ... <= jobs[n-1].finish.
 *   
 *   2. State Definition:
 *      Let dp[i] be the maximum profit achievable considering a subset of the first i jobs (1-indexed).
 *      Base Case: dp[0] = 0.
 *   
 *   3. Decisions for job i:
 *      - Option A: EXCLUDE job i: profit = dp[i - 1].
 *      - Option B: INCLUDE job i:
 *        We earn profit[i] PLUS the maximum profit from all non-overlapping predecessor jobs!
 *        The latest non-overlapping predecessor is the job p with finish[p] <= start[i].
 *        Using binary search on finish times, p is found in O(log N) time!
 *        profit = profit[i] + dp[p].
 *      
 *      dp[i] = max(dp[i - 1], jobs[i-1].profit + dp[p])
 */

struct Job {
    int start;
    int finish;
    int profit;
};

class Solution {
    // Binary search to find the latest job (1-indexed) finishing <= target_start
    int findLatestNonConflicting(const vector<Job>& jobs, int i) {
        int low = 0, high = i - 1;
        int target = jobs[i].start;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (jobs[mid].finish <= target) {
                ans = mid;
                low = mid + 1; // Try to find a later compatible job
            } else {
                high = mid - 1;
            }
        }

        return ans + 1; // Return 1-based index (0 means no compatible predecessor)
    }

public:
    static bool compareJobs(const Job& a, const Job& b) {
        return a.finish < b.finish;
    }

    int maximumProfit(vector<Job>& jobs) {
        int n = jobs.size();
        if (n == 0) return 0;

        // Step 1: Sort jobs by finish time ascending
        sort(jobs.begin(), jobs.end(), compareJobs);

        // dp[i] stores max profit considering a subset of first i jobs (1-indexed)
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            // Option 1: Exclude current job i
            int exclude_profit = dp[i - 1];

            // Option 2: Include current job i
            int include_profit = jobs[i - 1].profit;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Binary search the latest compatible predecessor in O(log N)
            int p = findLatestNonConflicting(jobs, i - 1);
            if (p != 0) {
                include_profit += dp[p];
            }

            // *** CRUCIAL LINE: Pick optimal between including and excluding job i ***
            dp[i] = max(exclude_profit, include_profit);
        }

        return dp[n];
    }
};

int main() {
    Solution sol;
    vector<Job> jobs = {
        {1, 2, 50},
        {3, 5, 20},
        {6, 19, 100},
        {2, 100, 200}
    };

    cout << "Max Profit from Weighted Jobs: " << sol.maximumProfit(jobs) << "\n";
    // Job 1 (1-2, 50) + Job 4 (2-100, 200) = 250. Expected: 250.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N). Sorting takes O(N log N). For each of the N jobs, 
 *   binary search takes O(log N). Total = O(N log N).
 * - Space Complexity: O(N) for the 1D dp array.
 */
