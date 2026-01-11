/*
Problem:
Largest Rectangular Area in a Histogram

Given an array of integers heights[], where heights[i] represents
the height of a histogram bar of width 1, find the area of the
largest rectangle that can be formed in the histogram.

Rules:
- Bars are adjacent.
- Rectangle must be formed using contiguous bars.

Example:
Input:
heights = [2, 1, 5, 6, 2, 3]

Output:
10

Explanation:
The largest rectangle is formed using bars of height 5 and 6.
Area = 2 * 5 = 10

// Approach (Monotonic Stack, with logic):
// - Use a stack to store indices of bars in increasing height order.
// - For each bar:
//     * If it is taller than stack top, push its index.
//     * If it is shorter, pop indices until heights increase, each time computing area with popped bar as smallest (width = current index - new stack top - 1).
// - This finds the max area for each potential rectangle efficiently.
// - After traversing all bars, process any remaining indices in the stack the same way.
// - Overall logic: always maintain stack of indices with increasing heights; whenever a bar is lower than stack top, resolve rectangles for taller bars just popped.

GeeksforGeeks:
https://www.geeksforgeeks.org/largest-rectangle-under-histogram/

LeetCode:
https://leetcode.com/problems/largest-rectangle-in-histogram/

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
public:
    long long getMaxArea(vector<int>& heights) {

        int n = heights.size();
        stack<int> st;
        long long maxArea = 0;

        for (int i = 0; i <= n; i++) {

            int currHeight = (i == n ? 0 : heights[i]);

            while (!st.empty() && currHeight < heights[st.top()]) {

                int h = heights[st.top()];
                st.pop();

                int width;
                if (st.empty()) {
                    width = i;
                } else {
                    width = i - st.top() - 1;
                }

                maxArea = max(maxArea, (long long)h * width);
            }

            st.push(i);
        }

        return maxArea;
    }
};