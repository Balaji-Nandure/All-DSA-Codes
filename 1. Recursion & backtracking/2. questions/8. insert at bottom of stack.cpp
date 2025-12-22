/*
 * Problem: Insert Element at Bottom of Stack
 *
 * Insert an element at the bottom of a stack using recursion.
 * Cannot use extra data structures (except call stack).
 *
 * Example: stack = [1,2,3,4,5] (5 is at top)
 * After insertAtBottom(stack, 0): stack = [0,1,2,3,4,5]
 *
 * Time: O(n) - where n is stack size
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Insert element x at bottom of stack using recursion
void insertAtBottom(stack<int>& st, int x) {
    // Base case: stack is empty, push x (now at bottom)
    if(st.empty()) {
        st.push(x);
        return;
    }
    // Remove top element temporarily
    int topElem = st.top();
    st.pop();
    // Recurse to insert x in remaining stack
    insertAtBottom(st, x);
    // After recursion, push back the removed element
    // This restores original order with x at bottom
    st.push(topElem);
}

// Helper function to print stack in the order in which elements are removed (top to bottom)
void printStack(stack<int> st) {
    // Elements are printed in order they are popped: top to bottom
    while(!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}

int main() {
    stack<int> st;
    // Example: stack from bottom 1,2,3,4,5 (top is 5)
    for(int i=1; i<=5; i++)
        st.push(i);

    cout << "Original stack (removed order, top to bottom): ";
    printStack(st);

    // Reinitialize since stack was emptied by printStack
    for(int i=1; i<=5; i++)
        st.push(i);

    int x = 0;
    insertAtBottom(st, x);

    cout << "After inserting " << x << " at bottom (removed order, top to bottom): ";
    printStack(st);

    return 0;
}
