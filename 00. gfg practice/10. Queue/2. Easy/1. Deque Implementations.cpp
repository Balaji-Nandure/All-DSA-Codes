/*
GeeksforGeeks: Deque Implementations
Difficulty: Easy

Problem:
A deque is a double-ended queue that allows enqueue and dequeue operations from both ends.
Given a deque and q queries. The task is to perform some operation on dequeue according to the queries as given below:
1. pb: query to push back the element x.
2. pf: query to push element x to the front of the deque.
3. pp_b(): query to delete element from the back of the deque.
4. f: query to return a front element from the deque. If the deque is empty return -1.

Examples:
Input: queries = [[ pf 5 ],[ pf 10 ],[ pb 6 ],[ f ],[ pp_b ]]
Output: 10
Explanation: 
1. After push front deque will be [5]
2. After push front deque will be [10, 5]
3. After push back deque will be [10, 5, 6]
4. Return front element which is 10
5. After pop back deque will be [10, 5]

Input: queries = [[ pf 5 ],[ f ]]
Output: 5 
Explanation:
1. After push front deque will be [5]
2. Return front element which is 5

Core Idea:
A Deque (Double Ended Queue) natively supports O(1) insertions and deletions at both the front and the back.
In C++, the standard template library (STL) provides the `std::deque` container which perfectly maps to these operations.
We just need to use the built-in functions: `push_back()`, `push_front()`, `pop_back()`, and `front()`.
We also must ensure to check if the deque is empty before performing pop or front operations to avoid runtime errors (like trying to pop from an empty container).

Approach:
1. `push_back_pb(deque<int> &dq, int x)`: Directly call `dq.push_back(x)`.
2. `push_front_pf(deque<int> &dq, int x)`: Directly call `dq.push_front(x)`.
3. `pop_back_ppb(deque<int> &dq)`: Check `if (!dq.empty())`, then call `dq.pop_back()`.
4. `front_dq(deque<int> &dq)`: Check `if (dq.empty()) return -1;`, otherwise return `dq.front()`.

Time Complexity: O(1) for all operations.
Space Complexity: O(1) auxiliary space, as we are only manipulating the given deque.

GFG Link: https://www.geeksforgeeks.org/problems/deque-implementations/1
*/

#include <iostream>
#include <deque>

using namespace std;

// Function to push element x to the back of the deque.
void push_back_pb(deque<int> &dq, int x) {
    dq.push_back(x);
}

// Function to pop element from back of the deque.
void pop_back_ppb(deque<int> &dq) {
    if (!dq.empty()) {
        dq.pop_back();
    }
}

// Function to return element from front of the deque.
int front_dq(deque<int> &dq) {
    if (dq.empty()) {
        return -1;
    }
    return dq.front();
}

// Function to push element x to the front of the deque.
void push_front_pf(deque<int> &dq, int x) {
    dq.push_front(x);
}

/*
Dry Run — Example 1:
Queries: [[pf 5], [pf 10], [pb 6], [f], [pp_b]]

1. pf 5  -> push_front_pf(dq, 5)
   dq = [5]
   
2. pf 10 -> push_front_pf(dq, 10)
   dq = [10, 5]
   
3. pb 6  -> push_back_pb(dq, 6)
   dq = [10, 5, 6]
   
4. f     -> front_dq(dq)
   dq is not empty. Returns dq.front() which is 10.
   
5. pp_b  -> pop_back_ppb(dq)
   dq is not empty. dq.pop_back().
   dq = [10, 5]
   
Outputs: 10
*/
