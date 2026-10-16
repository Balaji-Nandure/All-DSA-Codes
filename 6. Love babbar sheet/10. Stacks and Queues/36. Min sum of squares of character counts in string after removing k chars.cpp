/**
 * Problem: Minimum sum of squares of character counts in string after removing k chars (Game with String)
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previous problems processed data with monotonic queues or BFS queues.
 * - Here, we optimize a convex non-linear objective function `sum(f_i^2)` where each removal operation
 *   must be assigned to whichever character gives the highest marginal reduction.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Max-Priority Queue (Greedy reduction):
 *   - The marginal decrease in square sum when reducing frequency `f` by 1 is:
 *     `f^2 - (f - 1)^2 = 2f - 1`.
 *   - This difference is strictly monotonically increasing with `f`!
 *   - Therefore, to maximize reduction at every step, we MUST ALWAYS decrement the current LARGEST frequency.
 *   - Algorithm:
 *     1. Count frequencies of all lowercase characters into an array of size 26.
 *     2. Push all non-zero frequencies into a Max-Heap (`std::priority_queue<int>`).
 *     3. For K iterations:
 *        - Pop the largest frequency `top`.
 *        - Decrement `top = top - 1`.
 *        - Push `top` back into the heap if `top > 0`.
 *     4. Compute `sum(f^2)` for all elements remaining in the heap.
 * 
 * TIME COMPLEXITY:
 * - O(N + K log(26)) = O(N + K): Alphabet size is bounded by 26, making heap operations effectively O(1).
 * 
 * SPACE COMPLEXITY:
 * - O(1): Frequency array and priority queue size <= 26.
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>

int minValue(const std::string& s, int k) {
    if (k >= (int)s.length()) return 0;

    std::vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    std::priority_queue<int> pq;
    for (int count : freq) {
        if (count > 0) pq.push(count);
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Greedily reduce the highest frequency at each step to maximize the marginal reduction (2f - 1).
    while (k > 0 && !pq.empty()) {
        int top = pq.top();
        pq.pop();
        top--;
        if (top > 0) pq.push(top);
        k--;
    }

    long long sumOfSquares = 0;
    while (!pq.empty()) {
        int val = pq.top();
        pq.pop();
        sumOfSquares += 1LL * val * val;
    }

    return sumOfSquares;
}

int main() {
    std::string s1 = "abccc";
    int k1 = 1;
    std::cout << "Min sum of squares for " << s1 << " (k=" << k1 << "): " 
              << minValue(s1, k1) << "\n"; // 'c' goes from 3->2: 1^2 + 1^2 + 2^2 = 6

    std::string s2 = "aabcbcbcabcc";
    int k2 = 3;
    std::cout << "Min sum of squares for " << s2 << " (k=" << k2 << "): " 
              << minValue(s2, k2) << "\n";

    return 0;
}
