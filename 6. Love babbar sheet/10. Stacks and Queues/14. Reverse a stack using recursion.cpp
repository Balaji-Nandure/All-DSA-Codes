/**
 * Problem: Reverse a Stack Using Recursion
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Reverse a String using Stack", we used an auxiliary stack.
 * - Here, we are forbidden from using ANY explicit auxiliary data structure or iterative loops.
 * - We build directly upon Problem 13 ("Insert an element at bottom of stack") by chaining two recursive functions.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Divide and Conquer Recursion:
 *   1. Pop top element `temp = st.top()`.
 *   2. Recursively reverse the remaining sub-stack of size (N - 1).
 *   3. Insert `temp` at the BOTTOM of the already reversed sub-stack using `insertAtBottom`.
 * - By mathematical induction, inserting each top element at the bottom reverses the entire sequence.
 * 
 * TIME COMPLEXITY:
 * - O(N^2): Reversing N elements calls `insertAtBottom` (which takes O(N) work) N times.
 * 
 * SPACE COMPLEXITY:
 * - O(N) call stack recursion depth.
 */

#include <iostream>
#include <stack>

// Helper from Problem 13
void insertAtBottom(std::stack<int>& st, int x) {
    if (st.empty()) {
        st.push(x);
        return;
    }
    int temp = st.top();
    st.pop();
    insertAtBottom(st, x);
    st.push(temp);
}

void reverseStack(std::stack<int>& st) {
    // Base Case
    if (st.empty()) return;

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Hold top element, recursively invert the rest, then push held element to the bottom.
    int temp = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, temp);
}

void printStack(std::stack<int> s) {
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "\n";
}

int main() {
    std::stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4); // Top is 4, bottom is 1

    std::cout << "Original stack (top to bottom): ";
    printStack(st); // 4 3 2 1

    reverseStack(st);

    std::cout << "Reversed stack (top to bottom): ";
    printStack(st); // 1 2 3 4

    return 0;
}
