/*
    Problem Name: Stack using Queue
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 225

    Problem Statement:
    Implement a Stack using Queue data structure. This stack has no fixed capacity
    and can grow dynamically until memory is available.
    The Stack must support the following operations:
    (i)   push(x): Insert an element x at the top of the stack.
    (ii)  pop(): Remove the element from the top of the stack, if stack is empty do nothing.
    (iii) top(): Return top element if not empty, else -1.
    (iv)  size(): Return the number of elements currently in the stack.

    Queries:
    1 x: Call push(x)
    2: Call pop()
    3: Call top()
    4: Call size()

    Examples:
    Input: q = 6, queries = [[1, 5], [1, 3], [1, 4], [3], [2], [4]]
    Output: [4, 2]
    Explanation:
    - push(5): Stack = [5]
    - push(3): Stack = [5, 3]
    - push(4): Stack = [5, 3, 4]
    - top(): returns 4
    - pop(): removes 4, Stack = [5, 3]
    - size(): returns 2

    Input: q = 4, queries = [[4], [3], [1, 10], [3]]
    Output: [0, -1, 10]
    Explanation:
    - size(): returns 0
    - top(): empty stack, returns -1
    - push(10): Stack = [10]
    - top(): returns 10

    Constraints:
    1 <= queries.size <= 1000
    0 <= x <= 10^4

    Expected Complexities:
    Push: O(N) (Single Queue) or O(1) amortized
    Pop: O(1)
    Top: O(1)
    Size: O(1)
    Space Complexity: O(N)

    Approach 1: Using Two Queues (Push Costly)
    Approach 2: Using Single Queue (Optimal - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Queue is FIFO (First-In, First-Out), while Stack is LIFO (Last-In, First-Out).
    2. To simulate LIFO behavior using a single queue `q`:
       - When pushing a new element `x`:
         * Note the current size `s = q.size()`.
         * Enqueue `x` into `q`.
         * Rotate the previous `s` elements by dequeueing each from the front and enqueueing to the back.
         * Now, `x` is at the FRONT of the queue!
       - `pop()`:
         * Simply dequeue from the front: `q.pop()`. (O(1))
       - `top()`:
         * Front of the queue is the top of the stack: `q.front()`. (O(1))
       - `size()`:
         * Return `q.size()`. (O(1))

    DRY RUN:
    Operations: push(5), push(3), push(4), top(), pop(), size()
    - push(5):
      * size before = 0, push 5 -> q = [5]
      * rotate 0 times -> q = [5]
    - push(3):
      * size before = 1, push 3 -> q = [5, 3]
      * rotate 1 time: pop 5, push 5 -> q = [3, 5]
    - push(4):
      * size before = 2, push 4 -> q = [3, 5, 4]
      * rotate 2 times:
        pop 3, push 3 -> q = [5, 4, 3]
        pop 5, push 5 -> q = [4, 3, 5]
    - top(): q.front() = 4
    - pop(): q.pop() -> q = [3, 5]
    - size(): q.size() = 2
*/

#include <iostream>
#include <queue>

using namespace std;

// ============================================================================
// Approach 2: Using Single Queue (Optimal O(N) Push, O(1) Pop, O(1) Top/Size)
// ============================================================================
class StackSingleQueue {
private:
    queue<int> q;

public:
    void push(int x) {
        int s = q.size();
        q.push(x);

        // Rotate the previous elements to place the new element at the front
        for (int i = 0; i < s; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    void pop() {
        if (!q.empty()) {
            q.pop();
        }
    }

    int top() {
        if (q.empty()) return -1;
        return q.front();
    }

    int size() {
        return q.size();
    }
};

// ============================================================================
// Default Class for GFG Submission
// ============================================================================
class Stack {
private:
    StackSingleQueue impl;

public:
    void push(int x) {
        impl.push(x);
    }

    void pop() {
        impl.pop();
    }

    int top() {
        return impl.top();
    }

    int size() {
        return impl.size();
    }
};

// Alias in case platform expects MyStack or QueueStack
typedef Stack MyStack;
typedef Stack QueueStack;
