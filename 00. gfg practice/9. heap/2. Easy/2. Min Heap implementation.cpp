/*
GeeksforGeeks: Min Heap implementation
Difficulty: Easy

Problem:
Implement a class minHeap that supports the following operations:
push(x) – push element x into the heap
pop() – remove the top element from the heap
peek() – return top element from the heap, if empty return -1
size() - return the no of elements in the heap.

Examples :
Input: q = 5, queries[][] = [[1, 3], [1, 7], [3], [1, 2], [3]]
Output: [3, 2]
Explanation:
push(3): heap is [3]
push(7): heap is [3, 7]
peek(): return top element 3
push(2): heap is [2, 3, 7]
peek(): return top element 2

Input: q = 6, queries[][] = [[1, 4], [1, 8], [1, 7], [2], [3], [4]]
Output: [7, 2]
Explanation:
push(4): heap is [4]
push(8): heap is [4, 8]
push(7): heap is [4, 7, 8]
pop(): remove top element 4, now heap is [7, 8]
peek(): return top element 7
size(): return no of elements in the heap

Core Idea:
Instead of building a heap from scratch using an array and managing the `heapifyUp` and `heapifyDown` logic ourselves, we can simply use the C++ Standard Template Library (STL).
C++ provides `std::priority_queue`. By default, it's a Max-Heap. 
To make it a Min-Heap, we provide `vector<int>` as the underlying container and `greater<int>` as the comparator.
This takes away all the hard work and wraps it in a perfectly optimized, easy-to-read class.

Approach:
1. Declare an internal `priority_queue<int, vector<int>, greater<int>> pq`.
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

GFG Link: https://www.geeksforgeeks.org/problems/min-heap-implementation/1
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class minHeap {
private:
    // STL Min-Heap declaration
    priority_queue<int, vector<int>, greater<int>> pq;

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
   pq state (min-heap): [3]

2. push(7)
   pq state (min-heap): [3, 7]

3. peek()
   pq is not empty. Returns pq.top() which is 3.

4. push(2)
   pq state (min-heap): [2, 3, 7]

5. peek()
   pq is not empty. Returns pq.top() which is 2.
   
Output of peeks: [3, 2]
*/
