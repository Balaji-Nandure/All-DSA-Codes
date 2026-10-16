/**
 * Problem: Sum of minimum and maximum elements of all subarrays of size "k"
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "First negative integer in every window of size k", a standard FIFO queue was sufficient because
 *   we only cared about the earliest negative number.
 * - Here, we simultaneously query the EXTREMA (both minimum and maximum) of dynamic sliding windows.
 *   This necessitates two parallel MONOTONIC DEQUES to maintain extrema in amortized O(1) time per window.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Dual Monotonic Deques (Sliding Window Min & Max):
 *   - `dqMax`: Maintains indices in descending order of values (`dqMax.front()` is max of window).
 *   - `dqMin`: Maintains indices in ascending order of values (`dqMin.front()` is min of window).
 *   - For each element at index `i`:
 *     1. Evict expired indices: while front index `<= i - k`, pop from front.
 *     2. Maintain monotonicity:
 *        - Pop from back of `dqMax` while `arr[i] >= arr[dqMax.back()]`.
 *        - Pop from back of `dqMin` while `arr[i] <= arr[dqMin.back()]`.
 *     3. Push `i` to back of both deques.
 *     4. Once `i >= k - 1`, add `arr[dqMax.front()] + arr[dqMin.front()]` to total sum.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each index enters and leaves each deque at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(K) for the two deques storing at most K indices.
 */

#include <iostream>
#include <vector>
#include <deque>

long long sumOfMinAndMax(const std::vector<int>& arr, int n, int k) {
    std::deque<int> dqMax; // Stores indices of maximum candidates
    std::deque<int> dqMin; // Stores indices of minimum candidates
    long long totalSum = 0;

    for (int i = 0; i < n; i++) {
        // Step 1: Remove indices that are out of current window [i - k + 1, i]
        while (!dqMax.empty() && dqMax.front() <= i - k) dqMax.pop_front();
        while (!dqMin.empty() && dqMin.front() <= i - k) dqMin.pop_front();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Maintain descending order in dqMax and ascending order in dqMin by popping inferior elements from the back.
        while (!dqMax.empty() && arr[i] >= arr[dqMax.back()]) dqMax.pop_back();
        while (!dqMin.empty() && arr[i] <= arr[dqMin.back()]) dqMin.pop_back();

        dqMax.push_back(i);
        dqMin.push_back(i);

        // Step 2: Accumulate answer once the first full window of size k is formed
        if (i >= k - 1) {
            totalSum += arr[dqMax.front()] + arr[dqMin.front()];
        }
    }

    return totalSum;
}

int main() {
    std::vector<int> arr = {2, 5, -1, 7, -3, -1, -2};
    int n = arr.size();
    int k = 4;

    // Windows of size 4:
    // [2, 5, -1, 7]   -> max: 7, min: -1  -> sum = 6
    // [5, -1, 7, -3]  -> max: 7, min: -3  -> sum = 4
    // [-1, 7, -3, -1] -> max: 7, min: -3  -> sum = 4
    // [7, -3, -1, -2] -> max: 7, min: -3  -> sum = 4
    // Total sum = 6 + 4 + 4 + 4 = 18

    std::cout << "Total sum of min and max in windows of size " << k << ": " 
              << sumOfMinAndMax(arr, n, k) << "\n"; // 18

    return 0;
}
