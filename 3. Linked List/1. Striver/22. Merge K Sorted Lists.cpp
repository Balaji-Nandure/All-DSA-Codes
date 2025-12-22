/*
 * Problem: Merge k Sorted Lists (LeetCode 23)
 * 
 * You are given an array of k linked-lists lists, each linked-list is sorted 
 * in ascending order.
 * 
 * Merge all the linked-lists into one sorted linked-list and return it.
 * 
 * Example 1:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 * Explanation: The linked-lists are:
 * [
 *   1->4->5,
 *   1->3->4,
 *   2->6
 * ]
 * merging them into one sorted list: 1->1->2->3->4->4->5->6
 * 
 */

#include <bits/stdc++.h>
using namespace std;

// Node class represents a node in the linked list
class Node {
public:
    int data;     // Data value
    Node* next;   // Pointer to next node

    // Constructor with data and next
    Node(int data, Node* next) {
        this->data = data;
        this->next = next;
    }

    // Constructor with only data
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

// Helper function to convert array to linked list
Node* arrayToLinkedList(const vector<int>& arr) {
    if (arr.size() == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* curr = head;
    for (int i = 1; i < arr.size(); ++i) {
        curr->next = new Node(arr[i]);
        curr = curr->next;
    }
    return head;
}

// Helper function to print linked list
void printLinkedList(Node* head) {
    Node* curr = head;
    while(curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

// Helper function to merge two sorted linked lists
Node* mergeTwoLists(Node* list1, Node* list2) {
    Node* dummy = new Node(0);
    Node* tail = dummy;
    
    while (list1 && list2) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    
    if (list1) tail->next = list1;
    if (list2) tail->next = list2;
    
    Node* result = dummy->next;
    delete dummy;
    return result;
}

/*
 * Problem: Merge k Sorted Lists
 *
 * LeetCode 23: Merge k Sorted Lists
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/merge-k-sorted-linked-lists/1
 *
 * Merge k sorted linked lists into one sorted list.
 * Example: [[1,4,5],[1,3,4],[2,6]] -> [1,1,2,3,4,4,5,6]
 *
 * Time: O(n * log k) - where n is total nodes, k is number of lists
 * Space: O(1) for divide-conquer, O(k) for heap
 */

// Method 1: Divide and Conquer / Merge Pairs (Optimal)
// Merge pairs of lists iteratively until one remains
Node* mergeKLists(vector<Node*>& lists) {
    if (lists.empty()) return nullptr;
    
    int k = lists.size();
    
    // Merge pairs of lists until only one remains
    while (k > 1) {
        int newK = 0; // Count of merged lists in this round
        
        // Merge pairs: lists[i] and lists[i+1]
        for (int i = 0; i < k; i += 2) {
            if (i + 1 < k) {
                // Merge two lists
                lists[newK] = mergeTwoLists(lists[i], lists[i + 1]);
            } else {
                // Odd number: keep the last list as is
                lists[newK] = lists[i];
            }
            newK++;
        }
        
        k = newK; // Update count for next round
    }
    
    return lists[0]; // Final merged list
}

// ========== METHOD 2: Merge One by One ==========
// Time Complexity: O(k * n), Space Complexity: O(1)
// where n is average length of lists, k is number of lists
Node* mergeKListsOneByOne(vector<Node*>& lists) {
    if (lists.empty()) return nullptr;
    
    Node* result = lists[0];
    
    // Merge each subsequent list with the result
    for (int i = 1; i < lists.size(); i++) {
        result = mergeTwoLists(result, lists[i]);
    }
    
    return result;
}

// Method 3: Priority Queue / Min Heap
// Use min heap to always get the smallest element
Node* mergeKListsHeap(vector<Node*>& lists) {
    if (lists.empty()) return nullptr;
    
    // Min heap: stores (value, node) pairs
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> minHeap;
    
    // Push head of each non-empty list into heap
    for (Node* list : lists) {
        if (list) {
            minHeap.push({list->data, list});
        }
    }
    
    // Create dummy node to build result
    Node* dummy = new Node(0);
    Node* tail = dummy;
    
    // Extract minimum and add to result
    while (!minHeap.empty()) {
        auto [minValue, minNode] = minHeap.top();
        minHeap.pop();
        
        // Add minimum node to result
        tail->next = minNode;
        tail = tail->next;
        
        // Push next node from the same list (if exists)
        if (minNode->next) {
            minHeap.push({minNode->next->data, minNode->next});
        }
    }
    
    Node* result = dummy->next;
    delete dummy;
    return result;
}
