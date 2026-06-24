/*
    Problem Name: Union of Two Linked Lists
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two singly linked lists, create a new linked list that contains the union of elements present in both lists. Each element should appear only once in the resulting list. The order should first strictly follow the first list's elements, then the remaining unique elements from the second list in their original order.

    Expected Complexities:
    Time Complexity: O(N + M), where N and M are the lengths of the two linked lists. We traverse both lists exactly once. Searching and inserting into the `unordered_set` takes O(1) on average.
    Space Complexity: O(N + M) to store the unique elements in the hash set and to create the new linked list nodes.

    Love Babbar Style Approach:
    1. Hash Set for Uniqueness: We use an `unordered_set` to keep track of which elements have already been added to our resulting union list. This allows us to instantly O(1) check for duplicates.
    2. Dummy Node: We use a dummy node to easily construct the new linked list without worrying about empty list edge cases for the `head`. We maintain a `tail` pointer to append new nodes in O(1) time.
    3. Traverse First List: We loop through `head1`. For each node:
       - If its data is NOT in the set: insert it into the set, create a new node with this data, and append it to our `tail`.
       - If it IS in the set: skip it.
    4. Traverse Second List: We loop through `head2`. For each node, we perform the exact same uniqueness check and append process.
    5. Result: We return `dummy->next` which points to the actual start of our newly constructed union linked list.

    Dry Run:
    Input: head1 = 1->5->1->2, head2 = 4->5->6->1
    - Initialize set = {}, dummy node.
    - List 1:
      - '1': Not in set. Add to set. Append '1'. set={1}
      - '5': Not in set. Add to set. Append '5'. set={1, 5}
      - '1': In set! Skip.
      - '2': Not in set. Add to set. Append '2'. set={1, 5, 2}
    - List 2:
      - '4': Not in set. Add to set. Append '4'. set={1, 5, 2, 4}
      - '5': In set! Skip.
      - '6': Not in set. Add to set. Append '6'. set={1, 5, 2, 4, 6}
      - '1': In set! Skip.
    Result Linked List: 1 -> 5 -> 2 -> 4 -> 6
*/

#include <iostream>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list.
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
    Node* makeUnion(Node* head1, Node* head2) {
        unordered_set<int> seen;
        Node* dummy = new Node(0);
        Node* tail = dummy;
        
        // Traverse the first list
        Node* curr = head1;
        while (curr != NULL) {
            if (seen.find(curr->data) == seen.end()) {
                seen.insert(curr->data);
                tail->next = new Node(curr->data);
                tail = tail->next;
            }
            curr = curr->next;
        }
        
        // Traverse the second list
        curr = head2;
        while (curr != NULL) {
            if (seen.find(curr->data) == seen.end()) {
                seen.insert(curr->data);
                tail->next = new Node(curr->data);
                tail = tail->next;
            }
            curr = curr->next;
        }
        
        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// Helper function to print list
void printList(Node* node) {
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << "\n";
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n, m;
            cin >> n >> m;
            Node* head1 = NULL;
            Node* tail1 = NULL;
            for (int i = 0; i < n; i++) {
                int val;
                cin >> val;
                if (head1 == NULL) {
                    head1 = new Node(val);
                    tail1 = head1;
                } else {
                    tail1->next = new Node(val);
                    tail1 = tail1->next;
                }
            }
            
            Node* head2 = NULL;
            Node* tail2 = NULL;
            for (int i = 0; i < m; i++) {
                int val;
                cin >> val;
                if (head2 == NULL) {
                    head2 = new Node(val);
                    tail2 = head2;
                } else {
                    tail2->next = new Node(val);
                    tail2 = tail2->next;
                }
            }
            
            Solution ob;
            Node* res = ob.makeUnion(head1, head2);
            printList(res);
        }
    }
    return 0;
}
