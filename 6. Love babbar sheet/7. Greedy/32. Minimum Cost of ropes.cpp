#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * Problem: Minimum Cost of ropes
 * 
 * Given N ropes of different lengths, connect them into a single rope.
 * The cost to connect two ropes of length A and B is A + B.
 * Connect all ropes such that the total cost is minimized.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is isomorphic to Huffman Coding (problem 3) and optimal merge patterns.
 * - When two ropes are combined, their sum contributes to all future merges they participate in.
 * - If rope i is at depth d_i in the merge tree, it contributes (length_i * d_i) to the total cost.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy with Min-Heap (Priority Queue):
 *   To minimize sum(length_i * d_i), the largest lengths MUST have the smallest depth (merged late),
 *   and the smallest lengths MUST have the largest depth (merged early).
 *   
 *   1. Push all rope lengths into a min-priority queue.
 *   2. While more than one rope remains:
 *      - Pop the two smallest ropes: first = pq.top(), pq.pop(); second = pq.top(), pq.pop();
 *      - Merge them: cost = first + second.
 *      - Add cost to total cost.
 *      - Push the combined rope back into the min-heap: pq.push(cost).
 *   3. Continue until a single connected rope remains.
 */

class Solution {
public:
    long long minCost(vector<long long>& arr) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Min-heap to always extract the two shortest available ropes
        priority_queue<long long, vector<long long>, greater<long long>> pq;

        for (long long length : arr) {
            pq.push(length);
        }

        long long total_cost = 0;

        while (pq.size() > 1) {
            // Extract the two smallest ropes
            long long first = pq.top();
            pq.pop();
            long long second = pq.top();
            pq.pop();

            // *** CRUCIAL LINE: Cost incurred is the sum of the two smallest ropes ***
            long long merged_cost = first + second;
            total_cost += merged_cost;

            // Re-insert the combined rope into the pool
            pq.push(merged_cost);
        }

        return total_cost;
    }
};

int main() {
    Solution sol;
    vector<long long> arr1 = {4, 3, 2, 6};
    cout << "Min Cost 1: " << sol.minCost(arr1) << "\n";
    // Connect 2 and 3 -> cost 5, ropes: {4, 6, 5}
    // Connect 4 and 5 -> cost 9, ropes: {6, 9}
    // Connect 6 and 9 -> cost 15, ropes: {15}
    // Total cost = 5 + 9 + 15 = 29

    vector<long long> arr2 = {4, 2, 7, 6, 9};
    cout << "Min Cost 2: " << sol.minCost(arr2) << "\n"; // Expected: 62

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N). Building heap is O(N), and we perform N - 1 extractions and insertions, each taking O(log N).
 * - Space Complexity: O(N) to store elements in the priority queue.
 */
