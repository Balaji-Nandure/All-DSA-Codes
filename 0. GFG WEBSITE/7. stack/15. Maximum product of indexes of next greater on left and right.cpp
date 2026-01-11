/*
Problem:
Maximum Product of Indexes of Next Greater on Left and Right

Given an array of integers, for each element find:
- Nearest Greater Element on the Left (NGL)
- Nearest Greater Element on the Right (NGR)

Compute the product:
(index of NGL) * (index of NGR)

Return the maximum such product.
Indexes are 1-based.
If no greater element exists on a side, its index is taken as 0.

Example:
Input:
arr = [5, 4, 3, 4, 5]

Output:
8

Explanation:
For element 3 (index 3):
NGL = 5 at index 1
NGR = 5 at index 5
Product = 1 * 5 = 5
Maximum product obtained is 8.

Approach:
- Use monotonic decreasing stacks.
- First pass (left to right) to compute NGL indices.
- Second pass (right to left) to compute NGR indices.
- For each position, compute product and track maximum.

GeeksforGeeks:
https://www.geeksforgeeks.org/maximum-product-of-indexes-of-next-greater-on-left-and-right/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
public:
    long long maxIndexProduct(vector<int>& arr) {

        int n = arr.size();
        vector<long long> left(n, 0), right(n, 0);
        stack<int> st;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] <= arr[i]) {
                st.pop();
            }
            if (!st.empty()) left[i] = st.top() + 1;
            st.push(i);
        }

        while (!st.empty()) st.pop();

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] <= arr[i]) {
                st.pop();
            }
            if (!st.empty()) right[i] = st.top() + 1;
            st.push(i);
        }

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, left[i] * right[i]);
        }

        return ans;
    }
};
    