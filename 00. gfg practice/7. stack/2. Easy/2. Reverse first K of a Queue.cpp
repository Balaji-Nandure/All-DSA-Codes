/*
GeeksforGeeks: Reverse first K of a Queue
Difficulty: Easy

Problem:
Given an integer k and a queue of integers, we need to reverse the order of the first k elements of the queue, leaving the other elements in the same relative order.
"If the size of queue is smaller than the given k, then return the original queue."

Example 1:
Input: q = [1, 2, 3, 4, 5], k = 3
Output: [3, 2, 1, 4, 5]
Explanation: After reversing the first 3 elements from the given queue the resultant queue will be 3 2 1 4 5

Example 2:
Input: q = [4, 3, 2, 1], k = 4
Output: [1, 2, 3, 4] 
Explanation: After reversing the first 4 elements from the given queue the resultant queue will be 1 2 3 4 

Core Idea:
A stack naturally reverses the order of elements because of its Last-In-First-Out (LIFO) property. 
To reverse the first `k` elements of a queue:
1. We can dequeue the first `k` elements and push them onto a stack.
2. Then, we pop the elements from the stack and enqueue them back to the queue. This puts the reversed `k` elements at the back of the queue.
3. Finally, to restore the correct order, we dequeue the remaining `N - k` elements (where N is the original size of the queue) from the front and enqueue them directly back to the rear of the queue.

Approach:
1. Check if the queue is empty, or if `k <= 0`, or if `k > q.size()`. If so, return the queue unchanged.
2. Create an empty stack `s`.
3. Loop `k` times:
   - Pop the front element from the queue `q` and push it onto the stack `s`.
4. Loop `k` times (or until the stack is empty):
   - Pop the top element from the stack `s` and push it to the back of the queue `q`.
5. At this point, the reversed `k` elements are at the back of the queue. The remaining `N - k` elements are at the front.
6. Loop `q.size() - k` times:
   - Pop the front element from the queue `q` and push it directly back to the rear of the queue `q`.
7. Return the modified queue `q`.

Time Complexity: O(N) where N is the total number of elements in the queue. We process the first k elements twice and the remaining N-k elements once.
Space Complexity: O(k) for the stack used to reverse the first k elements.

GFG Link:
https://www.geeksforgeeks.org/problems/reverse-first-k-elements-of-queue/1
*/

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
    // Function to reverse first k elements of a queue.
    queue<int> modifyQueue(queue<int> q, int k) {
        // If k is greater than the size of the queue, return the original queue
        if (k > q.size() || k <= 0) {
            return q;
        }

        stack<int> s;
        int n = q.size();

        // Step 1: Dequeue the first k elements and push them onto a stack
        for (int i = 0; i < k; i++) {
            s.push(q.front());
            q.pop();
        }

        // Step 2: Pop from the stack and enqueue back to the queue
        // This will put the reversed k elements at the end of the queue
        while (!s.empty()) {
            q.push(s.top());
            s.pop();
        }

        // Step 3: Dequeue the remaining (n - k) elements and enqueue them back
        // to move them behind the reversed k elements
        for (int i = 0; i < n - k; i++) {
            q.push(q.front());
            q.pop();
        }

        return q;
    }
};

/*
Dry Run — Example 1:
Input: q = [1, 2, 3, 4, 5], k = 3

Initial State:
q = [1, 2, 3, 4, 5] (front is 1, rear is 5)
n = 5, k = 3

Step 1: Push first 3 elements to stack
- push 1 to stack, pop from q -> q = [2, 3, 4, 5], s = [1]
- push 2 to stack, pop from q -> q = [3, 4, 5], s = [1, 2]
- push 3 to stack, pop from q -> q = [4, 5], s = [1, 2, 3] (top is 3)

Step 2: Pop from stack and push back to queue
- pop 3 from stack, push to q -> q = [4, 5, 3], s = [1, 2]
- pop 2 from stack, push to q -> q = [4, 5, 3, 2], s = [1]
- pop 1 from stack, push to q -> q = [4, 5, 3, 2, 1], s = []

Step 3: Move remaining (5 - 3 = 2) elements to the back
- front is 4. push 4 to back, pop front -> q = [5, 3, 2, 1, 4]
- front is 5. push 5 to back, pop front -> q = [3, 2, 1, 4, 5]

Final Output: [3, 2, 1, 4, 5]
*/
