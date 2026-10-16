#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

/**
 * Problem: Shortest Job First (SJF) CPU Scheduling (Non-preemptive)
 * 
 * Given an array of burst times of N processes that all arrive at time t = 0.
 * Calculate the average waiting time using Non-preemptive Shortest Job First (SJF) scheduling.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an optimal queuing/scheduling metric problem.
 * - Each process's wait time directly delays ALL subsequent processes.
 * - An early executed process's burst time is added into the waiting time of every single process after it.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Mathematical Derivation:
 *   Let the execution order of burst times be b[0], b[1], ..., b[N-1].
 *   Wait time for process 0: 0
 *   Wait time for process 1: b[0]
 *   Wait time for process 2: b[0] + b[1]
 *   Wait time for process i: sum_{j=0}^{i-1} b[j]
 *   
 *   Total Waiting Time = sum_{i=0}^{N-1} (N - 1 - i) * b[i]
 *                      = (N-1)*b[0] + (N-2)*b[1] + ... + 1*b[N-2] + 0*b[N-1]
 *   Notice the multipliers: (N-1) > (N-2) > ... > 0 are strictly decreasing.
 *   By the Rearrangement Inequality, to minimize the sum of products of two sequences,
 *   the sequence b[i] MUST be sorted in strictly ASCENDING order.
 * - This proves that executing the shortest jobs first minimizes average waiting time universally.
 */

class Solution {
public:
    long long solve(vector<int>& bt) {
        int n = bt.size();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sort burst times in ascending order to minimize cumulative delay multipliers
        sort(bt.begin(), bt.end());

        long long total_waiting_time = 0;
        long long current_time = 0;

        for (int i = 0; i < n; i++) {
            // Process i waited for all preceding processes to finish
            total_waiting_time += current_time;
            // *** CRUCIAL LINE: Advance the clock by the current job's burst time ***
            current_time += bt[i];
        }

        // Return average waiting time (integer division as required by standard GFG)
        return total_waiting_time / n;
    }

    double averageWaitingTimeAccurate(vector<int>& bt) {
        int n = bt.size();
        sort(bt.begin(), bt.end());

        long long total_waiting_time = 0;
        long long current_time = 0;

        for (int i = 0; i < n; i++) {
            total_waiting_time += current_time;
            current_time += bt[i];
        }

        return (double)total_waiting_time / n;
    }
};

int main() {
    Solution sol;
    vector<int> bt1 = {4, 3, 7, 1, 2};
    cout << "Floor Average Waiting Time: " << sol.solve(bt1) << "\n"; // Expected: 4
    cout << "Accurate Average Waiting Time: " << fixed << setprecision(2) << sol.averageWaitingTimeAccurate(bt1) << "\n";
    // Sorted: 1, 2, 3, 4, 7
    // Wait times:
    // P1: 0
    // P2: 1
    // P3: 1 + 2 = 3
    // P4: 1 + 2 + 3 = 6
    // P5: 1 + 2 + 3 + 4 = 10
    // Total wait time = 0 + 1 + 3 + 6 + 10 = 20
    // Average = 20 / 5 = 4.0

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) for sorting the burst times.
 * - Space Complexity: O(1) auxiliary space.
 */
