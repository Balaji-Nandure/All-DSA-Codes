/**
 * Problem: Find the Next Greater Element
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Brute force scans O(N) ahead for every element yielding an inefficient O(N^2) complexity.
 * - Here, we introduce the fundamental Monotonic Stack technique: maintaining a stack of elements
 *   in strictly decreasing order so that every element immediately finds its closest larger successor.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Right-to-Left Monotonic Stack:
 *   - Traverse array from right to left (index N-1 down to 0).
 *   - Any element in the stack smaller than or equal to `arr[i]` can NEVER be the next greater element
 *     for any item to the left of `arr[i]` because `arr[i]` is both taller and closer!
 *   - Hence, pop all elements `<= arr[i]`.
 *   - If stack is not empty, `st.top()` is the next greater element; otherwise, -1.
 *   - Push `arr[i]` onto the stack.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each element is pushed onto the stack exactly once and popped at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the monotonic stack.
 */

#include <iostream>
#include <vector>
#include <stack>

std::vector<long long> nextLargerElement(const std::vector<long long>& arr, int n) {
    std::vector<long long> nge(n);
    std::stack<long long> st;

    // Traverse from right to left
    for (int i = n - 1; i >= 0; i--) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Eliminate all smaller or equal elements that are shadowed by arr[i].
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }

        // Top element is now the first greater element to the right
        nge[i] = st.empty() ? -1 : st.top();

        // Push current element for left-side queries
        st.push(arr[i]);
    }

    return nge;
}

int main() {
    std::vector<long long> arr = {6, 8, 0, 1, 3};
    int n = arr.size();
    std::vector<long long> result = nextLargerElement(arr, n);

    std::cout << "Next Greater Elements: ";
    for (long long x : result) {
        std::cout << x << " ";
    }
    std::cout << "\n"; // Output: 8 -1 1 3 -1

    return 0;
}
