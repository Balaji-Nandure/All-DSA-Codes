/**
 * Problem: First negative integer in every window of size "k"
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A naive scan of every window takes O(N * K) time.
 * - Here, we maintain a sliding FIFO queue storing only the indices of NEGATIVE numbers, achieving
 *   linear O(N) time with O(1) query time per window.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Sliding Window Queue of Negative Indices:
 *   - Storing indices rather than values allows instant validation of whether an element falls inside
 *     the active window `[i - K + 1, i]`.
 *   - Step 1: Enqueue indices of negative numbers in the first window of size K.
 *   - Step 2: For subsequent windows (from index K to N-1):
 *     - Evict from the front of the queue any index that is `<= i - K` (out of window).
 *     - If `arr[i] < 0`, enqueue index `i`.
 *     - The first negative integer of the current window is `arr[q.front()]` (or 0 if queue is empty).
 * 
 * TIME COMPLEXITY:
 * - O(N): Each index is enqueued and dequeued at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(K) for the queue storing indices within the current window.
 */

#include <iostream>
#include <vector>
#include <queue>

std::vector<long long> printFirstNegativeInteger(const std::vector<long long>& arr, int n, int k) {
    std::queue<int> q; // Stores indices of negative numbers
    std::vector<long long> ans;

    // Process first window of size k
    for (int i = 0; i < k; i++) {
        if (arr[i] < 0) {
            q.push(i);
        }
    }

    // Answer for first window
    ans.push_back(q.empty() ? 0 : arr[q.front()]);

    // Process remaining windows
    for (int i = k; i < n; i++) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Expel indices that fall outside the sliding window boundary [i - k + 1, i].
        while (!q.empty() && q.front() <= i - k) {
            q.pop();
        }

        if (arr[i] < 0) {
            q.push(i);
        }

        ans.push_back(q.empty() ? 0 : arr[q.front()]);
    }

    return ans;
}

int main() {
    std::vector<long long> arr = {-8, 2, 3, -6, 10};
    int n = arr.size();
    int k = 2;

    std::vector<long long> result = printFirstNegativeInteger(arr, n, k);
    std::cout << "First negative integer in each window of size " << k << ": ";
    for (long long x : result) {
        std::cout << x << " ";
    }
    std::cout << "\n"; // -8 0 -6 -6

    return 0;
}
