/**
 * Problem: Largest Rectangular Area in Histogram
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Next Greater Element looked for the first LARGER element.
 * - Here, the span of any histogram bar is bounded by the first SMALLER element to its left AND right.
 * - Instead of calculating previous and next smaller elements in two separate passes, this can be solved
 *   in an elegant, cache-optimal SINGLE PASS using a monotonic increasing index stack.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Monotonic Increasing Stack (Single Pass):
 *   - Stack stores indices of bars in strictly non-decreasing heights.
 *   - When encountering a bar `i` with height strictly less than the bar at `st.top()`:
 *     - The bar at `st.top()` can no longer expand rightwards! Its right boundary is index `i`.
 *     - Pop `st.top()` as `height = arr[mid]`.
 *     - Its left boundary is the new `st.top()` (or -1 if stack is empty).
 *     - Width = `st.empty() ? i : (i - st.top() - 1)`.
 *     - Update `maxArea = max(maxArea, height * width)`.
 *   - Adding a dummy height of 0 at index N cleanly flushes all remaining bars from the stack.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each index is pushed and popped at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the stack.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

long long getMaxArea(const std::vector<long long>& arr, int n) {
    std::stack<int> st;
    long long maxArea = 0;

    for (int i = 0; i <= n; i++) {
        // Use a dummy height 0 at index n to force flush all remaining bars from stack
        long long currentHeight = (i == n) ? 0 : arr[i];

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // When current bar is lower, top of stack has found its right boundary (index i) and left boundary (st.top() after pop).
        while (!st.empty() && currentHeight < arr[st.top()]) {
            long long height = arr[st.top()];
            st.pop();

            long long width = st.empty() ? i : (i - st.top() - 1);
            maxArea = std::max(maxArea, height * width);
        }

        st.push(i);
    }

    return maxArea;
}

int main() {
    std::vector<long long> hist = {6, 2, 5, 4, 5, 1, 6};
    int n = hist.size();
    std::cout << "Maximum area in histogram: " << getMaxArea(hist, n) << "\n"; // 12 (bars 5, 4, 5 with height 4 -> 4*3 = 12)

    return 0;
}
