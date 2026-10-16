/**
 * ============================================================================
 * Problem: Job Sequencing Problem (with Deadlines and Profits)
 * Category: Greedy / Disjoint Set Union (DSU)
 * 
 * Problem Statement:
 * Given a set of N jobs where every job `i` has a deadline and associated profit.
 * Each job takes 1 unit of time to complete and only one job can be scheduled
 * at any time slot. A job earns its profit if and only if it is completed on 
 * or before its deadline.
 * 
 * Find:
 *   1. The maximum number of jobs that can be scheduled.
 *   2. The maximum total profit earned.
 * 
 * Example 1:
 * Input:
 *   Jobs: (1, 4, 20), (2, 1, 10), (3, 1, 40), (4, 1, 30)
 *   Format: (Job_id, Deadline, Profit)
 * Output: Count = 2, Profit = 60
 * Explanation:
 *   Job 3 (profit 40, deadline 1) runs at slot [0, 1].
 *   Job 1 (profit 20, deadline 4) runs at slot [3, 4].
 *   Total Profit = 40 + 20 = 60.
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 1 <= Deadline <= 10^5
 * 1 <= Profit <= 10^5
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Activity Selection (Problem 1) vs Job Sequencing:
 *    - In Activity Selection, jobs had fixed start and end intervals `[start, end]`.
 *    - In Job Sequencing, jobs only have a DEADLINE. A job can be scheduled in
 *      ANY available 1-unit time slot in the range `[1, deadline]`.
 * 2. Slot Choice Heuristic (Delay as Late as Possible):
 *    - To maximize freedom for other jobs with tighter deadlines, every selected
 *      job should be scheduled as LATE as possible (at `deadline`, or the latest
 *      free slot preceding `deadline`).
 * 3. Linear Scan O(N * D) vs DSU Path Compression O(N log N):
 *    - Scanning backwards from `deadline` down to 1 takes O(D) time per job,
 *      resulting in O(N * D) worst-case time (TLE for N, D = 10^5).
 *    - Disjoint Set Union (DSU) path compression maintains the latest available
 *      free slot in O(alpha(D)) ≈ O(1) time!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy by Profit + DSU for O(1) Slot Assignment:
 *   - Step 1: Sort all jobs in descending order of their profit.
 *   - Step 2: Initialize DSU `parent` array up to `maxDeadline`:
 *       `parent[i] = i` (each slot i represents that slot i is available).
 *   - Step 3: For each job in sorted order:
 *       - Find latest available slot `availableSlot = find(job.deadline)`.
 *       - If `availableSlot > 0`:
 *           - Assign job to this slot!
 *           - Increment total jobs and add profit.
 *           - Union `availableSlot` with `availableSlot - 1`:
 *               `parent[availableSlot] = find(availableSlot - 1)`.
 *   - Total Time: O(N log N) for sorting + O(N * alpha(D)) for DSU operations.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Job {
    int id;
    int dead;
    int profit;
};

// Disjoint Set Union helper with Path Compression
class DisjointSet {
private:
    vector<int> parent;

public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    void unite(int u, int v) {
        parent[u] = v;
    }
};

class Solution {
public:
    /**
     * Solves Job Sequencing Problem in O(N log N) using Greedy + DSU.
     * @param arr Array of jobs.
     * @param n Number of jobs.
     * @return Pair {count of jobs scheduled, maximum profit earned}.
     */
    pair<int, int> JobScheduling(Job arr[], int n) {
        if (n == 0) return {0, 0};

        // Step 1: Sort jobs in descending order of profit
        sort(arr, arr + n, [](const Job& a, const Job& b) {
            return a.profit > b.profit;
        });

        // Step 2: Find maximum deadline
        int maxDeadline = 0;
        for (int i = 0; i < n; ++i) {
            maxDeadline = max(maxDeadline, arr[i].dead);
        }

        // Step 3: Initialize DSU with slots [0...maxDeadline]
        DisjointSet dsu(maxDeadline);

        int countJobs = 0;
        int maxProfit = 0;

        for (int i = 0; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // DSU path compression finds the latest empty slot <= arr[i].dead in O(1) time.
            // When slot 'availableSlot' is filled, it is linked to find(availableSlot - 1).
            int availableSlot = dsu.find(arr[i].dead);

            if (availableSlot > 0) {
                countJobs++;
                maxProfit += arr[i].profit;
                // Re-route this filled slot to the previous available slot
                dsu.unite(availableSlot, dsu.find(availableSlot - 1));
            }
        }

        return {countJobs, maxProfit};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case:
    // Job 1: (id: 1, dead: 4, profit: 20)
    // Job 2: (id: 2, dead: 1, profit: 10)
    // Job 3: (id: 3, dead: 1, profit: 40)
    // Job 4: (id: 4, dead: 1, profit: 30)
    Job arr[] = {
        {1, 4, 20},
        {2, 1, 10},
        {3, 1, 40},
        {4, 1, 30}
    };
    int n = sizeof(arr) / sizeof(arr[0]);

    pair<int, int> result = solver.JobScheduling(arr, n);
    cout << "Test 1: Jobs Scheduled = " << result.first 
         << ", Max Profit = " << result.second 
         << " (Expected: Jobs = 2, Profit = 60)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting jobs by profit: O(N log N).
 *   - N iterations of DSU `find` and `unite`: O(N * alpha(maxDeadline)) ≈ O(N).
 *   - Total Time: O(N log N) strictly.
 *   - Avoids the O(N * D) worst case of naive array scanning.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(maxDeadline) for DSU parent array.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Always delay a job as close to its deadline as possible to leave earlier
 *    slots open for jobs with smaller deadlines.
 * 2. DSU with path compression is the optimal data structure to track dynamically
 *    exhausted contiguous resource slots in O(1) time.
 */
