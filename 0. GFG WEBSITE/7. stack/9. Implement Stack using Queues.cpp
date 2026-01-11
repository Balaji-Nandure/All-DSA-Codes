/*
Problem:
Implement Stack using Queues

Implement a stack using queue data structure.
Stack should support the following operations:
- push(x)
- pop()
- top()
- empty()

Rules:
- Only standard queue operations are allowed.
- Stack must follow LIFO order.

Example:
push(1)
push(2)
top()  → 2
pop()  → 2
empty() → false

Approach:
- Use a single queue.
- For push(x):
  - Push x into queue.
  - Rotate the queue elements so that x comes to front.
- pop():
  - Dequeue front element.
- top():
  - Return front element.
- empty():
  - Check if queue is empty.

GeeksforGeeks:
https://www.geeksforgeeks.org/implement-stack-using-queue/

LeetCode:
https://leetcode.com/problems/implement-stack-using-queues/

Time Complexity:
push  → O(N)
pop   → O(1)
top   → O(1)
empty → O(1)

Space Complexity:
O(N)
*/

class MyStack {
    private:
        queue<int> q;
    
    public:
        MyStack() {}
    
        void push(int x) {
            q.push(x);
            int sz = q.size() - 1;
            while (sz--) {
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
    
        int top() {
            if (q.empty()) return -1;
            return q.front();
        }
    
        bool empty() {
            return q.empty();
        }
    };
    