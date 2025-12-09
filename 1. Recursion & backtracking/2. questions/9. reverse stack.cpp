/*
Question: Reverse a stack using recursion (without using any extra data structures except recursion stack).
For example: stack = [1,2,3,4,5] (5 at top), after reverseStack(stack), stack = [5,4,3,2,1] (1 at bottom, 5 at top).

Approach:
- To reverse stack recursively:
    1. Remove top element, recursively reverse rest of stack.
    2. Insert the removed element at the bottom of the reversed stack.

We'll use the previous problem's logic for "insertAtBottom".
*/

#include <bits/stdc++.h>
using namespace std;

// Helper: insert element x at bottom of stack
void insertAtBottom(stack<int> &st, int x) {
    if(st.empty()) {
        st.push(x);
        return;
    }
    int t = st.top();
    st.pop();
    insertAtBottom(st, x);
    st.push(t);
}

// Main function to reverse stack
void reverseStack(stack<int> &st) {
    if(st.empty()) return;
    int t = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, t);
}

// Helper for printing: prints (top to bottom)
void printStack(stack<int> st) {
    while(!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

int main() {
    stack<int> st;
    // Example: stack has 1,2,3,4,5 (top is 5)
    for(int i=1; i<=5; i++)
        st.push(i);

    cout << "Original stack (top to bottom): ";
    printStack(st);

    // Need to re-fill stack since it was emptied by printStack
    for(int i=1; i<=5; i++)
        st.push(i);

    reverseStack(st);

    cout << "Reversed stack (top to bottom): ";
    printStack(st);

    return 0;
}
