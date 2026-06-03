/*
GeeksforGeeks: Max Heap implementation
Difficulty: Easy

Problem:
Implement a class maxHeap that supports the following operations:
push(x) – push element x into the heap
pop() – remove the top element from the heap
peek() – return top element from the heap, if empty return -1
size() - return the no of elements in the heap.

Examples :
Input: q = 5, queries[][] = [[1, 3], [1, 7], [3], [1, 2], [3]]
Output: [7, 7]
Explanation:
push(3): heap is [3]
push(7): heap is [7, 3]
peek(): return top element 7
push(2): heap is [7, 3, 2]
peek(): return top element 7

Input: q = 6, queries[][] = [[1, 4], [1, 8], [1, 7], [2], [3], [4]]
Output: [7, 2]
Explanation:
push(4): heap is [4]
push(8): heap is [8, 4]
push(7): heap is [8, 7, 4]
pop(): remove top element 8, now heap is [7, 4]
peek(): return top element 7
size(): return no of elements in the heap

Core Idea:
Just like the Min Heap, we can leverage the C++ Standard Template Library (STL) to implement a Max Heap.
C++ provides `std::priority_queue`, which by default is already a Max-Heap. 
We can simply wrap this STL container in our class to achieve an easy, bug-free, and perfectly optimal implementation, completely matching the approach you preferred for the Min Heap.

Approach:
1. Declare an internal `priority_queue<int> pq`.
2. `push(x)`: Call `pq.push(x)`.
3. `pop()`: If not empty, call `pq.pop()`.
4. `peek()`: If empty return `-1`, else return `pq.top()`.
5. `size()`: Return `pq.size()`.

Time Complexity: 
- `push`: O(log N)
- `pop`: O(log N)
- `peek`: O(1)
- `size`: O(1)
Space Complexity: O(N) to store elements inside the priority queue.

GFG Link: https://www.geeksforgeeks.org/problems/max-heap-implementation/1
*/

#include <iostream>
#include <queue>

using namespace std;

class maxHeap {
private:
    // STL Max-Heap declaration (Max-Heap is the default for priority_queue)
    priority_queue<int> pq;

public:
    // push element x into the heap
    void push(int x) {
        pq.push(x);
    }

    // remove the top element from the heap
    void pop() {
        if (!pq.empty()) {
            pq.pop();
        }
    }

    // return top element from the heap, if empty return -1
    int peek() {
        if (pq.empty()) {
            return -1;
        }
        return pq.top();
    }

    // return the no of elements in the heap
    int size() {
        return pq.size();
    }
};

/*
Dry Run — Example 1:
queries = [[1, 3], [1, 7], [3], [1, 2], [3]]

1. push(3)
   pq state (max-heap): [3]

2. push(7)
   pq state (max-heap): [7, 3]

3. peek()
   pq is not empty. Returns pq.top() which is 7.

4. push(2)
   pq state (max-heap): [7, 3, 2]

5. peek()
   pq is not empty. Returns pq.top() which is 7.
   
Output of peeks: [7, 7]
*/
