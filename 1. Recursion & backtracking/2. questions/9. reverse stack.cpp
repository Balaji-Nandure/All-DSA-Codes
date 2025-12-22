/*
 * Problem: Reverse Stack using Recursion
 *
 * Reverse a stack using recursion without extra data structures (except call stack).
 *
 * Example: stack = [1,2,3,4,5] (5 at top)
 * After reverse: stack = [5,4,3,2,1] (5 at top)
 *
 * Approach:
 * 1. Remove top element, recursively reverse rest of stack
 * 2. Insert removed element at bottom of reversed stack
 *
 * Time: O(n²) - each insertAtBottom is O(n), called n times
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Helper: Insert element x at bottom of stack
void insertAtBottom(stack<int> &st, int x) {
    // Base case: stack empty, push x (now at bottom)
    if(st.empty()) {
        st.push(x);
        return;
    }
    // Remove top temporarily
    int t = st.top();
    st.pop();
    // Recurse to insert x in remaining stack
    insertAtBottom(st, x);
    // Push back removed element
    st.push(t);
}

// Reverse stack recursively
void reverseStack(stack<int> &st) {
    // Base case: empty stack is already reversed
    if(st.empty()) return;
    // Remove top element
    int t = st.top();
    st.pop();
    // Recursively reverse remaining stack
    reverseStack(st);
    // Insert removed element at bottom of reversed stack
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
