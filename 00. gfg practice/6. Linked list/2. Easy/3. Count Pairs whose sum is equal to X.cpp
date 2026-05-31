/*
GeeksforGeeks: Count Pairs whose sum is equal to X
Difficulty: Easy

Problem:
Given two linked lists head1 and head2 with distinct elements, determine the count of all distinct pairs from both lists whose sum equals the given value x.
Note: A valid pair would be in the form (x, y) where x is from the first linked list and y is from the second linked list. (1, 3) and (3, 1) are considered different. All elements in each linked list are unique.

Example 1:
Input: head1 = 1->2->3->4->5->6, head2 = 11->12->13, x = 15
Output: 3
Explanation: There are total 3 pairs whose sum is 15 : (4,11) , (3,12) and (2,13)

Example 2:
Input: head1 = 7->5->1->3, head2 = 3->5->2->8, x = 10
Output: 2
Explanation: There are total 2 pairs whose sum is 10 : (7,3) and (5,5)

Core Idea:
To optimize from the brute force O(N*M) time, we can use a Hash Set. 
Since we are looking for pairs (a, b) such that `a + b = x`, we can say `a = x - b`.
If we store all the elements of the first linked list in an unordered set, we can then iterate through the second linked list. For every element `b` in the second list, we check if `x - b` exists in the set. If it does, we have found a valid pair.

Approach:
1. Initialize an `unordered_set<int>` to store the elements of the first linked list.
2. Initialize a `count` variable to 0.
3. Traverse the first linked list (`head1`) and insert each node's data into the set.
4. Traverse the second linked list (`head2`). For each node's `data`:
   a. Check if `(x - data)` is present in the set.
   b. If it is present, increment the `count`.
5. Return the `count`.

Time Complexity: O(N + M) where N is the length of head1 and M is the length of head2. We traverse each list once. Lookups and insertions in an unordered set take O(1) time on average.
Space Complexity: O(N) where N is the length of head1, to store its elements in the set.

GFG Link:
https://www.geeksforgeeks.org/problems/count-pairs-whose-sum-is-equal-to-x/1
*/

#include <iostream>
#include <unordered_set>

using namespace std;

struct Node {
    int data;
    struct Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    // your task is to complete this function
    int countPairs(struct Node* head1, struct Node* head2, int x) {
        unordered_set<int> elements;
        int count = 0;
        
        // Store all elements of head1 in a set
        Node* curr1 = head1;
        while (curr1 != NULL) {
            elements.insert(curr1->data);
            curr1 = curr1->next;
        }
        
        // Traverse head2 and find matching pairs
        Node* curr2 = head2;
        while (curr2 != NULL) {
            if (elements.find(x - curr2->data) != elements.end()) {
                count++;
            }
            curr2 = curr2->next;
        }
        
        return count;
    }
};

/*
Dry Run — Example 1:
Input: head1 = 1->2->3->4->5->6, head2 = 11->12->13, x = 15

Initial state:
head1: [1] -> [2] -> [3] -> [4] -> [5] -> [6] -> NULL
head2: [11] -> [12] -> [13] -> NULL
x = 15
count = 0
elements = {}

Step 1 (Traverse head1):
- Insert 1: elements = {1}
- Insert 2: elements = {1, 2}
- Insert 3: elements = {1, 2, 3}
- Insert 4: elements = {1, 2, 3, 4}
- Insert 5: elements = {1, 2, 3, 4, 5}
- Insert 6: elements = {1, 2, 3, 4, 5, 6}

Step 2 (Traverse head2):
- curr2 is at 11. `x - 11 = 15 - 11 = 4`.
  Is 4 in elements? Yes. count becomes 1.
  
- curr2 is at 12. `x - 12 = 15 - 12 = 3`.
  Is 3 in elements? Yes. count becomes 2.
  
- curr2 is at 13. `x - 13 = 15 - 13 = 2`.
  Is 2 in elements? Yes. count becomes 3.

Loop finishes as curr2 becomes NULL.

Return count (3).
*/
