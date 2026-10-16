/**
 * Problem: Implement Stack using Queue
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A Stack is LIFO while a Queue is FIFO.
 * - Previous problems simulated high-level algorithms using standard stacks.
 * - Here, we simulate LIFO semantics entirely on top of FIFO queue primitives.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Method 1 (Single Queue Rotation - Most Elegant):
 *   - Push `x` into queue `q`.
 *   - For each existing element previously in `q`, dequeue it from the front and re-enqueue it at the back!
 *   - Result: `x` ends up at the very front of the queue, perfectly emulating stack top.
 *   - `pop()` and `top()` become trivial O(1) queue operations!
 * - Method 2 (Two Queues):
 *   - Using `q1` and `q2`, push new element into `q2`, dump all elements from `q1` to `q2`, then swap names.
 * 
 * TIME COMPLEXITY:
 * - push(x): O(N) where N is current stack size.
 * - pop(): O(1)
 * - top(): O(1)
 * - empty(): O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(N) to store N elements. Single queue uses 0 extra queue buffers.
 */

#include <iostream>
#include <queue>

// Implementation using a Single Queue
class StackUsingSingleQueue {
private:
    std::queue<int> q;

public:
    void push(int x) {
        int sz = q.size();
        q.push(x);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Rotate all previous elements behind the newly inserted element so that x sits at front!
        for (int i = 0; i < sz; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        if (q.empty()) return -1;
        int val = q.front();
        q.pop();
        return val;
    }

    int top() const {
        if (q.empty()) return -1;
        return q.front();
    }

    bool empty() const {
        return q.empty();
    }

    int size() const {
        return q.size();
    }
};

int main() {
    StackUsingSingleQueue st;
    st.push(10);
    st.push(20);
    st.push(30);

    std::cout << "Top: " << st.top() << "\n";     // 30
    std::cout << "Popped: " << st.pop() << "\n"; // 30
    std::cout << "New Top: " << st.top() << "\n"; // 20
    std::cout << "Popped: " << st.pop() << "\n"; // 20
    std::cout << "Size: " << st.size() << "\n";   // 1

    return 0;
}
