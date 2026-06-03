/*
GeeksforGeeks: Deque deletion
Difficulty: Easy

Problem:
Given a Deque deq containing non-negative integers.
Complete below functions depending type of query as mentioned and provided to you (indexing starts from 0):
1. eraseAt(x): this function should remove the element from specified position x in deque.
2. eraseInRange(start, end): this function should remove the elements in range start (inclusive), end (exclusive) specified in the argument of the function.
Note: If start is equal to end then simply return.
3. eraseAll(): remove all the elements from the deque.

Examples:
Input: deq = [1 2 4 5 6], query = [1 2]
Output: 1 2 5 6 
Explanation: Here the query type is 1 and the position is 2. So we remove element at position 2. The element at position 2 is 1 2 4 5 6. So, we remove 4 and get 1 2 5 6.

Input: deq = [1 2 3 4], query = [2 1 3]
Output: 1 4 
Explanation: Here the query type is 2 and the range is [1, 3). So we need to delete 1 2 3 4. Remember that end is exclusive. So the updated dequeue is 1 4.

Input: deq = [1 2 3], query = [3]
Output: Empty
Explanation: Here the query is of type 3 so we remove all the elements of dequeue.

Core Idea:
In C++, the Standard Template Library (STL) `std::deque` natively supports random-access iterators and built-in deletion methods.
- `deq.erase(iterator)` removes the element pointed to by the iterator.
- `deq.erase(start_iterator, end_iterator)` removes a range of elements `[start, end)`.
- `deq.clear()` removes all elements from the deque entirely.
Since `std::deque` allows random access (unlike `std::queue` or `std::stack`), we can simply do `deq.begin() + position` to get the iterator for any position in O(1) time.

Approach:
1. `eraseAt(deq, X)`: Call `deq.erase(deq.begin() + X)`.
2. `eraseInRange(deq, start, end)`: Call `deq.erase(deq.begin() + start, deq.begin() + end)`.
3. `eraseAll(deq)`: Call `deq.clear()`.
*Note: I've included safety checks (valid bounds) before erasing to avoid runtime iterator bounds errors.*

Time Complexity:
- `eraseAt`: O(N) because elements after the erased position must be shifted inward.
- `eraseInRange`: O(N) because elements after the erased range must be shifted inward.
- `eraseAll`: O(N) since internally it destroys all elements (though practically it's just a swift block deallocation).
Space Complexity: O(1) auxiliary space as we modify the existing deque.

GFG Link: https://www.geeksforgeeks.org/problems/deque-deletion/1
*/

#include <iostream>
#include <deque>

using namespace std;

// Function to erase the element from specified position X in deque.
void eraseAt(deque<int> &deq, int X) {
    if (X >= 0 && X < deq.size()) {
        deq.erase(deq.begin() + X);
    }
}

// Function to erase the elements in range start (inclusive), end (exclusive).
void eraseInRange(deque<int> &deq, int start, int end) {
    if (start < end && start >= 0 && end <= deq.size()) {
        deq.erase(deq.begin() + start, deq.begin() + end);
    }
}

// Function to erase all the elements in the deque.
void eraseAll(deque<int> &deq) {
    deq.clear();
}

/*
Dry Run — Example 1:
deq = [1, 2, 4, 5, 6], query = [1, 2] (Type 1, position 2)

1. eraseAt(deq, 2) is called.
2. deq.begin() + 2 points to the element '4'.
3. deq.erase() removes '4'.
4. Elements after '4' (which are '5' and '6') are shifted left.
5. deq becomes [1, 2, 5, 6].

Output: 1 2 5 6
*/
