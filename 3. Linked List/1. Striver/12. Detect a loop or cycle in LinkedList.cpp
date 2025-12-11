/*
 * Problem: Linked List Cycle (LeetCode 141)
 * 
 * Given head, the head of a linked list, determine if the linked list has a cycle in it.
 * 
 * There is a cycle in a linked list if there is some node in the list that can be reached 
 * again by continuously following the next pointer. Internally, pos is used to denote the 
 * index of the node that tail's next pointer is connected to. Note that pos is not passed 
 * as a parameter.
 * 
 * Return true if there is a cycle in the linked list. Otherwise, return false.
 * 
 * Example 1:
 * Input: head = [3,2,0,-4], pos = 1
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
 * 
 * Example 2:
 * Input: head = [1,2], pos = 0
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
 * 
 * Example 3:
 * Input: head = [1], pos = -1
 * Output: false
 * Explanation: There is no cycle in the linked list.
 * 
 * Constraints:
 * - The number of the nodes in the list is in the range [0, 10^4]
 * - -10^5 <= Node.val <= 10^5
 * - pos is -1 or a valid index in the linked-list
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

// Helper function to print linked list (limited to avoid infinite loop)
void printLinkedList(Node* head, int maxNodes = 10) {
    Node* curr = head;
    int count = 0;
    while(curr && count < maxNodes) {
        cout << curr->data << " ";
        curr = curr->next;
        count++;
    }
    if (curr) cout << "... (cycle detected, stopping)";
    cout << endl;
}

// Helper function to create a cycle in linked list (for testing)
void createCycle(Node* head, int pos) {
    if (pos < 0 || !head) return;
    
    Node* tail = head;
    Node* cycleNode = nullptr;
    int index = 0;
    
    // Find tail and the node at position pos
    while (tail->next) {
        if (index == pos) {
            cycleNode = tail;
        }
        tail = tail->next;
        index++;
    }
    
    // If pos is 0, cycleNode should be head
    if (pos == 0) {
        cycleNode = head;
    }
    
    // Create cycle
    if (cycleNode) {
        tail->next = cycleNode;
    }
}

// ========== METHOD 1: Floyd's Cycle Detection (Tortoise and Hare) - Optimal ==========
// Time Complexity: O(n), Space Complexity: O(1)
bool hasCycle(Node* head) {
    if (!head || !head->next) return false;
    
    Node* slow = head;
    Node* fast = head;
    
    // Move slow pointer 1 step and fast pointer 2 steps
    // If there's a cycle, they will eventually meet
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;  // Cycle detected
        }
    }
    
    return false;  // No cycle
}

// ========== METHOD 2: Using HashSet ==========
// Time Complexity: O(n), Space Complexity: O(n)
bool hasCycleHashSet(Node* head) {
    if (!head) return false;
    
    unordered_set<Node*> visited;
    Node* curr = head;
    
    while (curr) {
        // If we've seen this node before, there's a cycle
        if (visited.find(curr) != visited.end()) {
            return true;
        }
        
        visited.insert(curr);
        curr = curr->next;
    }
    
    return false;  // No cycle
}

// ========== METHOD 3: Marking Nodes (Modifying List) ==========
// Time Complexity: O(n), Space Complexity: O(1) but modifies the list
// Note: This approach modifies the list, so it's not ideal
bool hasCycleMarking(Node* head) {
    if (!head) return false;
    
    // Use a special marker value or pointer
    // Since we can't modify node structure, we'll use a visited flag approach
    // For this to work, we'd need to add a visited flag to nodes
    // This is shown for educational purposes only
    
    Node* curr = head;
    while (curr) {
        // Check if node has been visited (would need visited flag in node)
        // For now, we'll use a different approach with temporary marking
        if (curr->next == (Node*)(-1)) {  // Using -1 as marker (not recommended)
            return true;
        }
        
        Node* next = curr->next;
        curr->next = (Node*)(-1);  // Mark as visited (destroys list structure)
        curr = next;
    }
    
    return false;
}

// Bonus: Find the starting node of the cycle (if cycle exists)
// This is LeetCode 142: Linked List Cycle II
Node* detectCycleStart(Node* head) {
    if (!head || !head->next) return nullptr;
    
    Node* slow = head;
    Node* fast = head;
    
    // Step 1: Detect if cycle exists
    bool cycleExists = false;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            cycleExists = true;
            break;
        }
    }
    
    if (!cycleExists) return nullptr;
    
    // Step 2: Find the start of the cycle
    // Move one pointer to head, keep other at meeting point
    // Move both one step at a time, they'll meet at cycle start
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;  // This is the start of the cycle
}

// Find the length of the cycle in a linked list (if it exists)
int cycleLength(Node* head) {
    if (!head || !head->next) return 0;

    Node* slow = head;
    Node* fast = head;
    // Detect cycle using Floyd's algorithm
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Cycle found; now find its length
            Node* temp = slow;
            int length = 1;
            temp = temp->next;
            while (temp != slow) {
                temp = temp->next;
                length++;
            }
            return length;
        }
    }
    return 0; // No cycle
}

int main() {
    cout << "========== METHOD 1: Floyd's Cycle Detection ==========" << endl;
    
    // Test case 1: [3,2,0,-4] with cycle at position 1
    vector<int> arr1 = {3, 2, 0, -4};
    Node* head1 = arrayToLinkedList(arr1);
    createCycle(head1, 1);
    
    cout << "\nTest case 1:" << endl;
    cout << "List: 3 2 0 -4 -> (cycle back to 2)" << endl;
    cout << "Has cycle: " << (hasCycle(head1) ? "true" : "false") << endl;
    cout << "Expected: true" << endl;
     
    return 0;
}

