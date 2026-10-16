/**
 * Problem: Sort a Stack using Recursion
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "Reverse a stack using recursion", elements were unconditionally inserted at the bottom.
 * - Here, we perform recursive Insertion Sort: inserting elements into their correct SORTED position
 *   relative to stack top, using solely the execution call stack.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive Insertion Sort:
 *   1. `sortStack(st)`:
 *      - Pop top element `temp`.
 *      - Recursively sort the remaining (N - 1) elements.
 *      - Insert `temp` into the sorted sub-stack using `sortedInsert`.
 *   2. `sortedInsert(st, x)`:
 *      - If stack is empty OR `x >= st.top()`, push `x` directly.
 *      - Otherwise, pop `st.top()`, recursively call `sortedInsert(st, x)`, then re-push the popped element.
 * 
 * TIME COMPLEXITY:
 * - O(N^2): Sorting N elements calls `sortedInsert` (which takes O(N) calls) N times.
 * 
 * SPACE COMPLEXITY:
 * - O(N) call stack recursion depth.
 */

#include <iostream>
#include <stack>

void sortedInsert(std::stack<int>& st, int x) {
    // Base Case: Insert if stack is empty or x is greater than top element
    if (st.empty() || x >= st.top()) {
        st.push(x);
        return;
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Hold top element in call stack, find position for x deeper down, then restore top upon return.
    int temp = st.top();
    st.pop();
    sortedInsert(st, x);
    st.push(temp);
}

void sortStack(std::stack<int>& st) {
    if (st.empty()) return;

    // Pop top element
    int temp = st.top();
    st.pop();

    // Recursively sort the remaining stack
    sortStack(st);

    // Insert held element into correct sorted position
    sortedInsert(st, temp);
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
    st.push(30);
    st.push(-5);
    st.push(18);
    st.push(14);
    st.push(-3);

    std::cout << "Original stack (top to bottom): ";
    printStack(st); // -3 14 18 -5 30

    sortStack(st);

    std::cout << "Sorted stack (top to bottom - largest at top): ";
    printStack(st); // 30 18 14 -3 -5

    return 0;
}
