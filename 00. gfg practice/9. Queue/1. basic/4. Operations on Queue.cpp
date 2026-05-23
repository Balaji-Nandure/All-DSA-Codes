/*
Problem: Operations on Queue

GFG: https://www.geeksforgeeks.org/problems/operations-on-queue/1

Description:
Implement a class myQueue that supports:
- enqueue(x): Insert element x at end of queue
- dequeue(): Remove element from front
- getFront(): Return front element
- getRear(): Return rear element
- isEmpty(): Return true if queue empty else false
- size(): Return number of elements in queue

The driver processes queries in numeric form:
1 x -> enqueue(x)
2   -> dequeue()
3   -> getFront()
4   -> getRear()
5   -> isEmpty()
6   -> size()

Examples:
Input: queries = [[1 1], [1 7], [1 8], [2], [3], [4], [5], [6]]
Output: [7, 8, false, 2]

Input: queries = [[5], [1 3], [1 6], [4]]
Output: [true, 6]

Constraints:
1 ≤ q ≤ 1000
1 ≤ x ≤ 1000

Approach:
Use a deque<int> as the underlying container to support O(1) front and
rear operations. Deque provides push_back, pop_front, front, back, empty,
and size all in O(1).

Time Complexity: O(1) per operation
Space Complexity: O(n) where n is the number of elements in the queue
*/

#include <bits/stdc++.h>
using namespace std;

class myQueue {
  private:
    deque<int> dq;

  public:
    void enqueue(int x) {
        dq.push_back(x);
    }

    void dequeue() {
        if (!dq.empty()) {
            dq.pop_front();
        }
    }

    int getFront() {
        if (dq.empty()) return -1;
        return dq.front();
    }

    int getRear() {
        if (dq.empty()) return -1;
        return dq.back();
    }

    bool isEmpty() {
        return dq.empty();
    }

    int size() {
        return dq.size();
    }
};
