/*
GeeksforGeeks: Multiply two linked lists
Difficulty: Easy

Problem:
Given elements as nodes of the two singly linked lists. The task is to multiply these two linked lists, say L1 and L2.
Note: The output could be large, so take modulo 10^9+7.

Example 1:
Input: LinkedList L1 : 3->2 , LinkedList L2 : 2
Output: 64
Explanation: Multiplication of 32 and 2 gives 64.

Example 2:
Input: LinkedList L1: 1->0->0 , LinkedList L2 : 1->0
Output: 1000
Explanation: Multiplication of 100 and 10 gives 1000.

Core Idea:
To multiply the numbers represented by the two linked lists, we need to extract their integer values. Since the numbers can be very large (up to 10^5 digits), we cannot store them in standard integer types.
However, we only need the result modulo 10^9+7. By using the property of modular arithmetic `(A * B) % MOD = ((A % MOD) * (B % MOD)) % MOD`, we can compute the value of each linked list modulo 10^9+7 as we traverse them.
For each node, we shift the accumulated value left by one decimal place (multiply by 10) and add the current node's data.

Approach:
1. Define `MOD = 1000000007`.
2. Initialize `num1 = 0` and `num2 = 0` as `long long`.
3. Traverse the first linked list (L1). For each node:
   `num1 = (num1 * 10 + curr1->data) % MOD`
4. Traverse the second linked list (L2). For each node:
   `num2 = (num2 * 10 + curr2->data) % MOD`
5. Multiply `num1` and `num2`, take modulo `MOD`, and return the result as a `long long`.

Time Complexity: O(max(N, M)) where N and M are the lengths of the two linked lists. We traverse both lists exactly once.
Space Complexity: O(1) as we only use a few variables to store the intermediate values.

GFG Link:
https://www.geeksforgeeks.org/problems/multiply-two-linked-lists/1
*/

#include <iostream>

using namespace std;

/* Linked list node structure */
struct Node {
    int data;
    Node* next;
    
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    long long multiplyTwoLists(Node *first, Node *second) {
        long long MOD = 1000000007;
        long long num1 = 0;
        long long num2 = 0;
        
        // Compute value of first linked list modulo 10^9+7
        Node* curr1 = first;
        while (curr1 != NULL) {
            num1 = (num1 * 10 + curr1->data) % MOD;
            curr1 = curr1->next;
        }
        
        // Compute value of second linked list modulo 10^9+7
        Node* curr2 = second;
        while (curr2 != NULL) {
            num2 = (num2 * 10 + curr2->data) % MOD;
            curr2 = curr2->next;
        }
        
        // Return the product modulo 10^9+7
        return (num1 * num2) % MOD;
    }
};

/*
Dry Run — Example 1:
Input: LinkedList L1 : 3->2 , LinkedList L2 : 2

Initial state:
first: [3] -> [2] -> NULL
second: [2] -> NULL
MOD = 1000000007
num1 = 0, num2 = 0

Step 1 (Traverse first):
- curr1 is at 3. `num1 = (0 * 10 + 3) % MOD = 3`
- curr1 is at 2. `num1 = (3 * 10 + 2) % MOD = 32`
curr1 becomes NULL.

Step 2 (Traverse second):
- curr2 is at 2. `num2 = (0 * 10 + 2) % MOD = 2`
curr2 becomes NULL.

Step 3:
- Return `(num1 * num2) % MOD`
  `= (32 * 2) % 1000000007`
  `= 64 % 1000000007`
  `= 64`

Final Output: 64
*/
