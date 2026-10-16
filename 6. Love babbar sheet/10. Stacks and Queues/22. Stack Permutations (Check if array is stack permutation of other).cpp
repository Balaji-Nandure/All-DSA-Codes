/**
 * Problem: Stack Permutations (Check if array is stack permutation of other)
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Previously, we checked whether parentheses strings were balanced.
 * - Here, we test if a target sequence of elements can be produced by passing an input sequence
 *   through an intermediate LIFO stack (analogous to train switching yards / Knuth's permutation test).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Stack Simulation:
 *   - Iterate through each element of input array `A`:
 *     - Push `A[i]` onto an auxiliary stack `st`.
 *     - While stack is non-empty and `st.top() == B[j]` (the current required output element):
 *       - Pop from stack and advance pointer `j`.
 *   - Why Greedy works?
 *     - If the stack top matches the desired output element, we MUST pop it immediately; leaving it on the stack
 *       would bury it under future pushed elements, making it impossible to output it in the current required position.
 *   - If at the end all elements of `A` are processed and stack is empty, return 1; else 0.
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

int isStackPermutation(int n, const std::vector<int>& A, const std::vector<int>& B) {
    std::stack<int> st;
    int j = 0;

    for (int i = 0; i < n; i++) {
        st.push(A[i]);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Whenever stack top matches current expected output, greedily pop it immediately.
        while (!st.empty() && st.top() == B[j]) {
            st.pop();
            j++;
        }
    }

    return (st.empty() && j == n) ? 1 : 0;
}

int main() {
    std::vector<int> A = {1, 2, 3};
    std::vector<int> B = {2, 1, 3};
    std::vector<int> C = {3, 1, 2};

    std::cout << "B is stack permutation of A: " << isStackPermutation(3, A, B) << "\n"; // 1
    std::cout << "C is stack permutation of A: " << isStackPermutation(3, A, C) << "\n"; // 0

    return 0;
}
