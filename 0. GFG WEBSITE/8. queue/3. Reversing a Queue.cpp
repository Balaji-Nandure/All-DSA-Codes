/*
Problem:
Reversing a Queue

Given a queue of integers, reverse the queue.

Rules:
- Use standard queue operations.
- Extra data structure is allowed.
- Return the reversed queue.

Example:
Input:
Queue = 1 2 3 4 5

Output:
5 4 3 2 1

Approach (Optimized – Using Stack):
- Use a stack to reverse order.
- Dequeue all elements from queue and push into stack.
- Pop elements from stack and enqueue back to queue.

GeeksforGeeks:
https://www.geeksforgeeks.org/reversing-a-queue/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
public:
    queue<int> rev(queue<int> q) {

        stack<int> st;

        while (!q.empty()) {
            st.push(q.front());
            q.pop();
        }

        while (!st.empty()) {
            q.push(st.top());
            st.pop();
        }

        return q;
    }
};


// Recursive
class Solution {
public:
    void reverseQueue(queue<int> &q) {
        if(q.empty()) return;
        
        int x = q.front();
        q.pop();
        reverseQueue(q);
        q.push(x);
        
    }
};
    