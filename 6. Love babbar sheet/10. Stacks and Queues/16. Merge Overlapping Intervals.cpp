/**
 * Problem: Merge Overlapping Intervals
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In Greedy scheduling, we selected non-overlapping intervals (e.g. N meetings in one room).
 * - Here, overlapping intervals must not be discarded, but fused into single composite spans.
 *   Using a stack gives an intuitive mechanism to compare each new interval with the current merged frontier.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Sort + Stack-Based Merging:
 *   1. Sort intervals by start time `intervals[i][0]`.
 *   2. Push the first interval onto the stack.
 *   3. For each subsequent interval `[start, end]`:
 *      - If `start <= top.end`: They overlap! Merge by setting `top.end = max(top.end, end)`.
 *      - Otherwise: No overlap; push the current interval as a new independent segment onto the stack.
 * 
 * TIME COMPLEXITY:
 * - O(N log N) dominated by sorting. Stack pass is strictly O(N).
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the stack / output intervals.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

struct Interval {
    int start, end;
};

bool compareInterval(const Interval& a, const Interval& b) {
    return a.start < b.start;
}

std::vector<Interval> mergeIntervals(std::vector<Interval>& intervals) {
    if (intervals.empty()) return {};

    // Sort intervals by ascending start times
    std::sort(intervals.begin(), intervals.end(), compareInterval);

    std::stack<Interval> st;
    st.push(intervals[0]);

    for (int i = 1; i < (int)intervals.size(); i++) {
        Interval& top = st.top();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If current interval starts before or at the end of the top interval, expand top.end.
        if (intervals[i].start <= top.end) {
            top.end = std::max(top.end, intervals[i].end);
        } else {
            st.push(intervals[i]);
        }
    }

    // Transfer from stack to result vector
    std::vector<Interval> result(st.size());
    for (int i = (int)st.size() - 1; i >= 0; i--) {
        result[i] = st.top();
        st.pop();
    }

    return result;
}

int main() {
    std::vector<Interval> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    std::vector<Interval> merged = mergeIntervals(intervals);

    std::cout << "Merged intervals: ";
    for (const auto& it : merged) {
        std::cout << "[" << it.start << ", " << it.end << "] ";
    }
    std::cout << "\n"; // [1, 6] [8, 10] [15, 18]

    return 0;
}
