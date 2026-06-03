/*
GeeksforGeeks: Maximum Diamonds
Difficulty: Easy

Problem:
There are N bags with diamonds in them. The i'th of these bags contains arr[i] diamonds. 
If you drop a bag with arr[i] diamonds, it changes to arr[i]/2 diamonds and you gain arr[i] diamonds. 
Dropping a bag takes 1 minute. Find the maximum number of diamonds that you can take if you are given k minutes.

Examples:
Input: arr[] = [2, 1, 7, 4, 2], k = 3
Output: 14
Explanation:
The state of bags is: 2 1 7 4 2
Take all diamonds from Third bag (7).
State of bags becomes: 2 1 3 4 2 
Take all diamonds from Fourth bag (4).
State of bags becomes: 2 1 3 2 2
Take all diamonds from Third bag (3).
State of bags becomes: 2 1 1 2 2 
Hence, number of Diamonds = 7 + 4 + 3 = 14.

Input: arr[] = [7, 1, 2], k = 2
Output: 10
Explanation:
Take all diamonds from First bag (7).
State of bags becomes: 3 1 2 
Take all diamonds from again First bag (3).
State of bags becomes: 1 1 2
You can take a maximum of 10 diamonds.

Core Idea:
To maximize the number of diamonds collected, we must greedily choose the bag with the maximum number of diamonds at every minute.
Since a bag's diamond count changes to `floor(diamonds / 2)` after we pick it, we need a data structure that can efficiently:
1. Find and remove the maximum element.
2. Insert a new element and maintain the order.
A Max-Heap (implemented as `std::priority_queue` in C++) is the perfect data structure for this, allowing extraction and insertion in O(log N) time.

Approach:
1. Initialize a max-heap (`priority_queue<int>`) and push all elements of the array into it.
2. Keep a variable `total_diamonds = 0` (use `long long` to prevent overflow, as the sum could be large).
3. Run a loop `k` times:
   - Pop the top element (which is the current maximum) from the priority queue.
   - Add this element to `total_diamonds`.
   - Push `element / 2` back into the priority queue.
4. Return `total_diamonds`.

Time Complexity: O(N + K log N). Building the priority queue from the array takes O(N) time (or O(N log N) if done by inserting one by one). Then, we perform K extractions and insertions, each taking O(log N) time.
Space Complexity: O(N) to store the elements in the priority queue.

GFG Link: https://www.geeksforgeeks.org/problems/maximum-diamonds2056/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    long long maxDiamonds(int arr[], int n, int k) {
        // Create a max-heap (priority queue) from the array elements
        // Passing the range to the constructor builds the heap in O(N) time
        priority_queue<int> pq(arr, arr + n);
        
        long long total_diamonds = 0;
        
        // Greedily take the maximum diamonds available 'k' times
        for (int i = 0; i < k; i++) {
            if (pq.empty()) break; // Edge case: if there are no bags left
            
            int top = pq.top();
            pq.pop();
            
            total_diamonds += top;
            
            // Push the remaining diamonds back into the queue
            pq.push(top / 2);
        }
        
        return total_diamonds;
    }
};

/*
Dry Run — Example 1:
Input: arr = [2, 1, 7, 4, 2], n = 5, k = 3

1. priority_queue initialization:
   pq pushes all elements: [7, 4, 2, 2, 1] (Conceptual max-heap order)
   total_diamonds = 0

2. Iteration 1 (k=1):
   - top = pq.top() = 7
   - pq.pop()
   - total_diamonds = 0 + 7 = 7
   - pq.push(7 / 2) -> pq.push(3)
   pq state: [4, 3, 2, 2, 1]

3. Iteration 2 (k=2):
   - top = pq.top() = 4
   - pq.pop()
   - total_diamonds = 7 + 4 = 11
   - pq.push(4 / 2) -> pq.push(2)
   pq state: [3, 2, 2, 2, 1]

4. Iteration 3 (k=3):
   - top = pq.top() = 3
   - pq.pop()
   - total_diamonds = 11 + 3 = 14
   - pq.push(3 / 2) -> pq.push(1)
   pq state: [2, 2, 2, 1, 1]

5. Loop ends since k iterations are done.

6. Return total_diamonds = 14.

Output: 14
*/
