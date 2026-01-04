/*
Problem:
Find Pairs with Given Sum in a Sorted Doubly Linked List

Given the head of a sorted doubly linked list (non-decreasing order)
and an integer target sum,
find all pairs of nodes (a, b) such that:
- a.data + b.data == target
- a appears before b in the list

Important:
- The list is SORTED.
- Do NOT modify the list.
- Return or print all valid pairs.
- Each pair should be reported once.

Examples:
Input:
List : 1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9
Sum  : 7
Output:
(1, 6), (2, 5)

Input:
List : 1 <-> 2 <-> 3 <-> 4
Sum  : 10
Output:
No pair found


-----------------------------------
Approach (Expected / Optimal – Two Pointers):
-----------------------------------
1. Set two pointers:
   - left  → head of the list
   - right → tail of the list
2. While left != right and left comes before right:
   - currentSum = left->data + right->data
   - If currentSum == target:
       • Record the pair
       • Move both pointers inward
   - If currentSum < target:
       • Move left forward
   - If currentSum > target:
       • Move right backward
3. Stop when pointers meet or cross.

Why this works:
- Sorted order allows two-pointer optimization.
- Each node is visited at most once.
- No extra space is required.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-pairs-given-sum-doubly-linked-list/

LeetCode:
No direct equivalent problem.
(Related to two-sum with two pointers)
*/


// Definition for Doubly Linked List Node
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int x) {
        data = x;
        next = NULL;
        prev = NULL;
    }
};


vector<pair<int,int>> findPairsWithSum(Node* head, int target) {

    vector<pair<int,int>> result;

    // Edge case: empty or single node list
    if (head == NULL || head->next == NULL) {
        return result;
    }

    // Step 1: Find tail of the list
    Node* left = head;
    Node* right = head;
    while (right->next != NULL) {
        right = right->next;
    }

    // Step 2: Two-pointer traversal
    while (left != right && right->next != left) {

        int sum = left->data + right->data;

        if (sum == target) {
            result.push_back({left->data, right->data});
            left = left->next;
            right = right->prev;
        }
        else if (sum < target) {
            left = left->next;
        }
        else {
            right = right->prev;
        }
    }

    return result;
}
