/**
 * ============================================================================
 * Problem: Merge K Sorted Linked Lists (LeetCode 23)
 * Category: LinkedList / Heap / Divide and Conquer
 * 
 * Problem Statement:
 * You are given an array of K linked-lists, where each linked-list is sorted 
 * in ascending order.
 * 
 * Merge all the linked-lists into one sorted linked-list and return it.
 * 
 * Example:
 * Input:
 *   List 1: 1 -> 4 -> 5 -> NULL
 *   List 2: 1 -> 3 -> 4 -> NULL
 *   List 3: 2 -> 6 -> NULL
 * Output: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6 -> NULL
 * 
 * Constraints:
 * 0 <= K <= 10^4
 * 0 <= Total number of nodes (N) <= 10^5
 * -10^9 <= Node.val <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. 2-Way Merge vs K-Way Merge:
 *    - In Problem 13, we merged 2 sorted lists in O(N) time.
 *    - Merging K sorted lists sequentially (List 1 with List 2, then with List 3...)
 *      takes O(K * N) time, which causes TLE when K = 10^4.
 * 2. Logarithmic Scalability:
 *    - To scale efficiently, we either maintain a Min-Heap of size K (O(N log K)),
 *      or perform Divide and Conquer pairwise merging (O(N log K) with O(1) space).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Approach 1: Min-Heap / Priority Queue (O(N log K) Time, O(K) Space)
 *   - Push the head of each non-empty list into a min-heap.
 *   - Pop the minimum node, append it to `tail->next`.
 *   - If the popped node has a non-null `next`, push `minNode->next` into the heap.
 *   - Every node is inserted and extracted once -> O(N log K) time.
 * 
 * Approach 2: Divide and Conquer Merge (O(N log K) Time, O(1) Auxiliary Space)
 *   - Pair up lists and merge each pair using standard 2-way in-place merge.
 *   - After first round, K lists become K/2 lists, then K/4...
 *   - Total rounds: log2(K). In each round, all N nodes are visited.
 *   - Total Time: O(N log K). Space: strictly O(1) in-place!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

// Custom comparator for min-heap
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->val > b->val;
    }
};

class Solution {
private:
    /**
     * Helper to merge two sorted linked lists in O(1) space.
     */
    Node* mergeTwoLists(Node* l1, Node* l2) {
        Node dummy(0);
        Node* tail = &dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }

public:
    /**
     * Method 1: Min-Heap Approach (O(N log K) Time, O(K) Space)
     */
    Node* mergeKListsHeap(vector<Node*>& lists) {
        priority_queue<Node*, vector<Node*>, CompareNode> minHeap;

        // Push heads of all non-empty lists
        for (Node* head : lists) {
            if (head != nullptr) {
                minHeap.push(head);
            }
        }

        Node dummy(0);
        Node* tail = &dummy;

        while (!minHeap.empty()) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The root of the min-heap always contains the globally smallest
            // available node among all K lists in O(log K) extraction time.
            Node* smallest = minHeap.top();
            minHeap.pop();

            tail->next = smallest;
            tail = tail->next;

            if (smallest->next != nullptr) {
                minHeap.push(smallest->next);
            }
        }

        return dummy.next;
    }

    /**
     * Method 2: Divide and Conquer (O(N log K) Time, O(1) Auxiliary Space)
     */
    Node* mergeKListsDivideAndConquer(vector<Node*>& lists) {
        if (lists.empty()) return nullptr;

        int interval = 1;
        int k = lists.size();

        while (interval < k) {
            for (int i = 0; i + interval < k; i += interval * 2) {
                lists[i] = mergeTwoLists(lists[i], lists[i + interval]);
            }
            interval *= 2;
        }

        return lists[0];
    }
};

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->val;
        if (temp->next) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // List 1: 1 -> 4 -> 5
    Node* l1 = new Node(1);
    l1->next = new Node(4);
    l1->next->next = new Node(5);

    // List 2: 1 -> 3 -> 4
    Node* l2 = new Node(1);
    l2->next = new Node(3);
    l2->next->next = new Node(4);

    // List 3: 2 -> 6
    Node* l3 = new Node(2);
    l3->next = new Node(6);

    vector<Node*> lists = {l1, l2, l3};

    Node* merged = solver.mergeKListsHeap(lists);
    cout << "Merged K Sorted Lists: ";
    printList(merged); // Expected: 1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Min-Heap: N elements pushed and popped from heap of size K: O(N log K).
 *   - Divide and Conquer: log2(K) levels, each merging N nodes: O(N log K).
 *   - Both methods run in optimal O(N log K) time.
 * 
 * Space Complexity:
 *   - Min-Heap: O(K) auxiliary space.
 *   - Divide and Conquer: O(1) auxiliary space strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Divide and conquer pairwise merging achieves the exact same O(N log K) time
 *    as Min-Heap but eliminates the O(K) heap memory overhead.
 */
