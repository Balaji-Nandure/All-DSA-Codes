/*
Problem:
Reversing the First K Elements of a Queue

Given a queue of integers and an integer K,
reverse the first K elements of the queue
while keeping the remaining elements in the same order.

Rules:
- Use queue and stack operations only.
- If K > size of queue, reverse the entire queue.

Example:
Input:
Queue = 1 2 3 4 5
K = 3

Output:
3 2 1 4 5

Approach:
- Push first K elements of the queue into a stack.
- Pop elements from stack and enqueue back to queue.
- Move the remaining (n - K) elements from front to back.

GeeksforGeeks:
https://www.geeksforgeeks.org/reversing-first-k-elements-queue/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(K)
*/

class Solution {
    public:
        queue<int> modifyQueue(queue<int> q, int k) {
    
            if (k <= 0 || q.empty()) return q;
    
            stack<int> st;
    
            int n = q.size();
            k = min(k, n);
    
            for (int i = 0; i < k; i++) {
                st.push(q.front());
                q.pop();
            }
    
            while (!st.empty()) {
                q.push(st.top());
                st.pop();
            }
    
            for (int i = 0; i < n - k; i++) {
                q.push(q.front());
                q.pop();
            }
    
            return q;
        }
    };
    