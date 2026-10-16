/**
 * Problem: Insert an Element at Bottom of Stack without Auxiliary Data Structure
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A stack only natively supports inserting at the TOP.
 * - Inserting at the bottom normally requires an auxiliary stack or queue.
 * - Here, we are restricted to zero extra data structures, leveraging the implicit runtime call stack
 *   of recursion to temporarily hold all elements.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Recursive Unwinding:
 *   - Base Case: If the stack is empty, push `x` directly and return.
 *   - Recursive Step:
 *     1. Pop the top element `temp = st.top()`.
 *     2. Recursively call `insertAtBottom(st, x)`.
 *     3. Push `temp` back onto the stack as recursion unwinds.
 *   - This places `x` at the very bottom while preserving the exact relative order of all other elements!
 * 
 * TIME COMPLEXITY:
 * - O(N) where N is number of elements in the stack.
 * 
 * SPACE COMPLEXITY:
 * - O(N) implicit recursion call stack space.
 */

#include <iostream>
#include <stack>

void insertAtBottom(std::stack<int>& st, int x) {
    // Base Case: If stack becomes empty, insert x at the true bottom
    if (st.empty()) {
        st.push(x);
        return;
    }

    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
    // Hold top element in the call frame, drill down until bottom, then push back upon return.
    int temp = st.top();
    st.pop();
    insertAtBottom(st, x);
    st.push(temp);
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
    st.push(4); // Stack top is 4, bottom is 1

    std::cout << "Original stack (top to bottom): ";
    printStack(st); // 4 3 2 1

    insertAtBottom(st, 99);

    std::cout << "After inserting 99 at bottom: ";
    printStack(st); // 4 3 2 1 99

    return 0;
}
