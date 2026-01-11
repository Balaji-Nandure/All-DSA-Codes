/*
Problem:
Stock Span Problem

Given an array of stock prices where prices[i] represents the price of a stock
on the i-th day, find the stock span for each day.

The stock span is defined as the number of consecutive days (including today)
just before the current day for which the price was less than or equal to
today's price.

Rules:
- Span always includes the current day.

Example:
Input:
prices = [100, 80, 60, 70, 60, 75, 85]

Output:
[1, 1, 1, 2, 1, 4, 6]

Approach:
- Use a monotonic decreasing stack storing indices.
- Traverse the array from left to right.
- For each day:
  - Pop indices while their price <= current price.
  - If stack is empty, span = i + 1
  - Else, span = i - stack.top()
- Push current index onto stack.

GeeksforGeeks:
https://www.geeksforgeeks.org/the-stock-span-problem/

LeetCode:
https://leetcode.com/problems/online-stock-span/

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
public:
    vector<int> calculateSpan(vector<int>& prices) {

        int n = prices.size();
        vector<int> span(n);
        stack<int> st;

        for (int i = 0; i < n; i++) {

            while (!st.empty() && prices[st.top()] <= prices[i]) {
                st.pop();
            }

            if (st.empty()) span[i] = i + 1;
            else span[i] = i - st.top();

            st.push(i);
        }

        return span;
    }
};