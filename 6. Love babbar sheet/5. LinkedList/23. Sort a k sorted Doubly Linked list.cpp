/**
 * ============================================================================
 * Problem: Sort a K-Sorted Doubly Linked List
 * Category: LinkedList / Doubly Linked List / Heap
 * 
 * Problem Statement:
 * Given a Doubly Linked List where each node is at most K positions away from 
 * its sorted position. Sort the given doubly linked list in optimal time and space.
 * 
 * Example:
 * Input:  3 <-> 6 <-> 2 <-> 12 <-> 56 <-> 8 -> NULL, K = 2
 * Output: 2 <-> 3 <-> 6 <-> 8 <-> 12 <-> 56 -> NULL
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * 1 <= K <= Number of nodes
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N log K) time and O(K) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Exploiting the "Almost-Sorted" Invariant:
 *    - Standard Merge Sort (Problem 13) or QuickSort (Problem 14) takes O(N log N) time,
 *      completely ignoring the fact that elements are displaced by at most K positions.
 *    - For small K (e.g., K = 2 or K = 5), an O(N log K) algorithm performs almost
 *      in pure linear time O(N).
 * 2. Min-Heap Window over Node Pointers:
 *    - The next element in sorted order MUST be among the first (K + 1) nodes.
 *    - A priority queue of capacity (K + 1) continually yields the globally minimum
 *      remaining element in O(log K) operations.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Min-Heap Sliding Window:
 *   - Create a min-heap storing `Node*` pointers ordered by `node->data`.
 *   - Step 1: Push the first (K + 1) nodes of the DLL into the min-heap.
 *   - Step 2: Maintain pointers `newHead = nullptr` and `last = nullptr`.
 *   - Step 3: While min-heap is not empty:
 *       - Extract top node `minNode`.
 *       - If `newHead == nullptr`:
 *           `newHead = minNode;`
 *           `newHead->prev = nullptr;`
 *           `last = newHead;`
 *       - Else:
 *           `last->next = minNode;`
 *           `minNode->prev = last;`
 *           `last = minNode;`
 *       - If original list has remaining nodes (`head != nullptr`):
 *           Push `head` into heap, advance `head = head->next`.
 *   - Step 4: Terminate list: `last->next = nullptr;`.
 *   - Return `newHead`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// Comparator for Min-Heap based on node data
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }
};

class Solution {
public:
    /**
     * Sorts a K-sorted Doubly Linked List in O(N log K) time and O(K) space.
     * @param head Pointer to the head of the K-sorted DLL.
     * @param k Maximum displacement of any element.
     * @return Head of the sorted DLL.
     */
    Node* sortAKSortedDLL(Node* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0) {
            return head;
        }

        // Min-heap to store at most (K + 1) nodes
        priority_queue<Node*, vector<Node*>, CompareNode> minHeap;

        Node* newHead = nullptr;
        Node* last = nullptr;
        Node* curr = head;

        // Step 1: Push the first (K + 1) nodes into the min-heap
        for (int i = 0; curr != nullptr && i <= k; ++i) {
            minHeap.push(curr);
            curr = curr->next;
        }

        // Step 2: Continuously extract minimum and insert next node
        while (!minHeap.empty()) {
            Node* minNode = minHeap.top();
            minHeap.pop();

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The smallest element in the current (K + 1) window is guaranteed to be
            // the globally correct next node; rewire its bidirectional pointers to 'last'.
            if (newHead == nullptr) {
                newHead = minNode;
                newHead->prev = nullptr;
                last = newHead;
            } else {
                last->next = minNode;
                minNode->prev = last;
                last = minNode;
            }

            // Push next available element from original DLL
            if (curr != nullptr) {
                minHeap.push(curr);
                curr = curr->next;
            }
        }

        // Terminate the sorted list
        if (last != nullptr) {
            last->next = nullptr;
        }

        return newHead;
    }
};

void printDLL(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next) cout << " <-> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Create 2-sorted DLL: 3 <-> 6 <-> 2 <-> 12 <-> 56 <-> 8 -> NULL
    vector<int> values = {3, 6, 2, 12, 56, 8};
    Node* head = new Node(values[0]);
    Node* curr = head;

    for (size_t i = 1; i < values.size(); ++i) {
        Node* newNode = new Node(values[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }

    int K = 2;
    cout << "Original 2-Sorted DLL: ";
    printDLL(head);

    head = solver.sortAKSortedDLL(head, K);
    cout << "Fully Sorted DLL:      ";
    printDLL(head); // Expected: 2 <-> 3 <-> 6 <-> 8 <-> 12 <-> 56 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Building initial heap of size (K + 1): O(K log K).
 *   - Each of the remaining N nodes is pushed and popped from heap of size (K + 1):
 *     N * O(log K).
 *   - Total Time: O(N log K).
 *   - For K << N, this is effectively linear O(N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(K) to store (K + 1) pointers in the priority queue.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Whenever elements are bounded by displacement K, a sliding min-heap window
 *    of size K+1 guarantees global ordering.
 * 2. Don't forget to set `last->next = nullptr` at the end to prevent stale links.
 */
