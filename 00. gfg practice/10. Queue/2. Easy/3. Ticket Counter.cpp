/*
GeeksforGeeks: Ticket Counter
Difficulty: Easy

Problem:
N people from 1 to N are standing in the queue at a movie ticket counter. 
It is a weird counter, as it distributes tickets to the first K people and then the last K people and again first K people and so on.
Once a person gets a ticket, they move out of the queue. 
The task is to find the last person to get the ticket.

Examples:
Input: N = 9, K = 3
Output: 6
Explanation:
Starting queue: [1, 2, 3, 4, 5, 6, 7, 8, 9]. 
After 1st distribution (front 3): [4, 5, 6, 7, 8, 9].
After 2nd distribution (back 3): [4, 5, 6]. 
Last person to get the ticket is 6.

Input: N = 5, K = 1
Output: 3
Explanation:
Queue starts as [1, 2, 3, 4, 5] -> [2, 3, 4, 5] -> [2, 3, 4] -> [3, 4] -> [3]
Last person to get ticket will be 3.

Core Idea:
While this problem is categorized under Queues/Deques, simulating the process using a literal `std::deque` would take O(N) time and O(N) memory to populate the structure.
We can heavily optimize this to O(N/K) Time and O(1) Space using a Two-Pointer approach. These pointers (`left` and `right`) conceptually represent the front and back of our queue!
- We maintain a `left` pointer starting at 1 and a `right` pointer starting at N.
- We maintain a boolean `frontTurn` to toggle between the front distribution and the back distribution.
- If the remaining people (`right - left + 1`) are greater than `K`, we shrink the conceptual queue by moving the corresponding pointer inward by `K` and flip the turn.
- If the remaining people are `<= K`, the last person to get a ticket depends on whose turn it is:
  - If it's the front's turn, tickets are handed out left-to-right, meaning the very last person to receive one is `right`.
  - If it's the back's turn, tickets are handed out right-to-left, meaning the very last person to receive one is `left`.

Approach:
1. Initialize `left = 1`, `right = N`, and `frontTurn = true`.
2. Loop while `left < right`:
   - Calculate remaining elements `rem = right - left + 1`.
   - If `rem <= K`, break out of the loop. All remaining people will get their tickets in this final turn.
   - If `frontTurn` is true, increment `left` by `K`.
   - If `frontTurn` is false, decrement `right` by `K`.
   - Toggle `frontTurn`.
3. Return `right` if it's `frontTurn`, otherwise return `left`.

Time Complexity: O(N / K) because we reduce the remaining pool by K in each step. This loop is incredibly fast and easily passes the constraints.
Space Complexity: O(1) auxiliary space, purely mathematical pointers.

GFG Link: https://www.geeksforgeeks.org/problems/ticket-counter-2731/1
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int ticketCounter(int N, int K) {
        int left = 1;
        int right = N;
        bool frontTurn = true;
        
        while (left < right) {
            int rem = right - left + 1;
            
            // If the remaining people can be covered in a single turn, we stop.
            if (rem <= K) {
                break;
            }
            
            // Distribute K tickets to either front or back
            if (frontTurn) {
                left += K;
            } else {
                right -= K;
            }
            
            // Switch turns
            frontTurn = !frontTurn;
        }
        
        // If it's the front's turn, it processes left-to-right, making `right` the last one.
        // If it's the back's turn, it processes right-to-left, making `left` the last one.
        return frontTurn ? right : left;
    }
};

/*
Dry Run — Example 1:
Input: N = 9, K = 3
Variables: left = 1, right = 9, frontTurn = true

1. Loop 1:
   rem = 9 - 1 + 1 = 9
   9 > 3, so we don't break.
   frontTurn is true: left = 1 + 3 = 4.
   frontTurn becomes false.
   
2. Loop 2:
   rem = 9 - 4 + 1 = 6
   6 > 3, so we don't break.
   frontTurn is false: right = 9 - 3 = 6.
   frontTurn becomes true.
   
3. Loop 3:
   rem = 6 - 4 + 1 = 3
   3 <= 3, so we BREAK.
   
4. Return:
   frontTurn is true, so return right (which is 6).
   
Output: 6
*/
