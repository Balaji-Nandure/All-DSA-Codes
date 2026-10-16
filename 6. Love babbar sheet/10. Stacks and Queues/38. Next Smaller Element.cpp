/**
 * Problem: Next Smaller Element
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Find the next Greater element" (Problem 9), we maintained a monotonic decreasing stack to discard smaller elements.
 * - Here, we perform the exact mathematical inverse: finding the first strictly SMALLER element to the right
 *   using a monotonic INCREASING stack.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Right-to-Left Monotonic Increasing Stack:
 *   - Traverse array from right to left (index N-1 down to 0).
 *   - Any element in the stack greater than or equal to `arr[i]` can NEVER be the next smaller element
 *     for any index to the left of `i` because `arr[i]` is both smaller and closer.
 *   - Therefore, pop all elements `>= arr[i]`.
 *   - If the stack is not empty, `st.top()` is the next smaller element; otherwise, -1.
 *   - Push `arr[i]` onto the stack.
 * 
 * TIME COMPLEXITY:
 * - O(N): Each element is pushed and popped at most once.
 * 
 * SPACE COMPLEXITY:
 * - O(N) auxiliary space for the stack.
 */

#include <iostream>
#include <vector>
#include <stack>

std::vector<int> nextSmallerElement(const std::vector<int>& arr, int n) {
    std::vector<int> nse(n);
    std::stack<int> st;

    // Traverse from right to left
    for (int i = n - 1; i >= 0; i--) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Eliminate all elements greater than or equal to arr[i] since arr[i] shadows them for preceding queries.
        while (!st.empty() && st.top() >= arr[i]) {
            st.pop();
        }

        // Top element is the first smaller element to the right
        nse[i] = st.empty() ? -1 : st.top();

        // Push current element into monotonic stack
        st.push(arr[i]);
    }

    return nse;
}

int main() {
    std::vector<int> arr = {4, 8, 5, 2, 25};
    int n = arr.size();

    std::vector<int> result = nextSmallerElement(arr, n);

    std::cout << "Array: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\nNext Smaller Elements: ";
    for (int x : result) std::cout << x << " ";
    std::cout << "\n"; // Output: 2 5 2 -1 -1

    return 0;
}
