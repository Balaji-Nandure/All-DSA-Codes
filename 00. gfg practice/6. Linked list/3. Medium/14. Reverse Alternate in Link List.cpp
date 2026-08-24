/*
    Problem Name: Reverse Alternate in Link List
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a singly linked list, perform the following in-place operations:
    1. Extract all alternate nodes starting from the second node (1st 1-indexed / odd positions).
    2. Reverse the extracted list of alternate nodes.
    3. Append the reversed list at the end of the remaining list.
    4. Return the head of the final modified list.

    Examples:
    Input: 12 -> 14 -> 16 -> 18 -> 20 -> nullptr
    Output: 12 -> 16 -> 20 -> 18 -> 14 -> nullptr
    Explanation: Alternate nodes from 2nd node: 14 -> 18.
                 Reversed: 18 -> 14.
                 Appended to remaining (12 -> 16 -> 20): 12 -> 16 -> 20 -> 18 -> 14.

    Input: 10 -> 4 -> 9 -> 1 -> 3 -> 5 -> 9 -> 4 -> nullptr
    Output: 10 -> 9 -> 3 -> 9 -> 4 -> 5 -> 1 -> 4 -> nullptr

    Constraints:
    1 <= size of linked list <= 10^6
    0 <= Node value <= 10^9

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Vector Storage & Value Copy (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: In-Place Extraction + Reverse + Append (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Traverse list, push even index node values to `mainVals` and odd index values to `altVals`.
       - Reverse `altVals` and concatenate to `mainVals`.
       - Overwrite node values.
       - Time: O(N), Space: O(N).

    2. Optimal In-Place Re-linking (Approach 2):
       - Step 1 (Extract Alternate Nodes): Traverse list with two pointers `mainPtr` and `altPtr`.
         Separate alternate nodes starting at `head->next` into a sublist `altHead`.
       - Step 2 (Reverse Sublist): Reverse the extracted `altHead` sublist in-place.
       - Step 3 (Append): Attach the reversed `altHead` list to the tail of the main list (`mainPtr->next = altHead`).
       - Time: O(N), Auxiliary Space: O(1).

    DRY RUN:
    Example: 12 -> 14 -> 16 -> 18 -> 20
    - Step 1 (Extract):
      Main List: 12 -> 16 -> 20 -> nullptr (mainPtr at node 20)
      Alt List: 14 -> 18 -> nullptr (altHead at node 14)
    - Step 2 (Reverse Alt List):
      Reversed Alt List: 18 -> 14 -> nullptr
    - Step 3 (Append):
      mainPtr(20)->next = altHead(18)
    - Result: 12 -> 16 -> 20 -> 18 -> 14.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Vector Storage & Value Copy (O(N) Time, O(N) Space)
// ============================================================================
class SolutionVector {
public:
    void rearrange(Node* head) {
        if (!head || !head->next) return;

        vector<int> mainVals, altVals;
        Node* curr = head;
        int idx = 0;

        while (curr != nullptr) {
            if (idx % 2 == 0) {
                mainVals.push_back(curr->data);
            } else {
                altVals.push_back(curr->data);
            }
            curr = curr->next;
            idx++;
        }

        reverse(altVals.begin(), altVals.end());

        curr = head;
        for (int val : mainVals) {
            curr->data = val;
            curr = curr->next;
        }
        for (int val : altVals) {
            curr->data = val;
            curr = curr->next;
        }
    }
};

// ============================================================================
// Approach 2: In-Place Extraction + Reverse + Append (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
private:
    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
    }

public:
    void rearrange(Node* head) {
        if (!head || !head->next || !head->next->next) return;

        Node* mainPtr = head;
        Node* altHead = head->next;
        Node* altPtr = altHead;

        // Step 1: Extract alternate nodes into altHead sublist
        while (mainPtr != nullptr && mainPtr->next != nullptr && mainPtr->next->next != nullptr) {
            mainPtr->next = mainPtr->next->next;
            mainPtr = mainPtr->next;

            if (mainPtr->next != nullptr) {
                altPtr->next = mainPtr->next;
                altPtr = altPtr->next;
            }
        }

        mainPtr->next = nullptr; // Terminate main list
        altPtr->next = nullptr;  // Terminate alternate list

        // Step 2: Reverse the alternate nodes list
        altHead = reverseList(altHead);

        // Step 3: Append reversed alternate list to the end of main list
        mainPtr->next = altHead;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    void rearrange(struct Node* odd) {
        SolutionOptimal solver;
        solver.rearrange(odd);
    }
};
