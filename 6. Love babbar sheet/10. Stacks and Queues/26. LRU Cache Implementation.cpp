/**
 * Problem: LRU Cache Implementation
 * Category: Stacks and Queues
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - A standard queue eviction always drops the oldest element in arrival order (FIFO).
 * - An LRU cache evicts the item that has not been ACCESSED (neither read nor written) for the longest time.
 * - Whenever any item is accessed (`get` or `put`), its priority is refreshed to the front in O(1) time.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Hash Map + Doubly Linked List (DLL):
 *   - Why Hash Map? Provides O(1) lookup to find the node corresponding to any key.
 *   - Why DLL? Allows O(1) removal of any node from its arbitrary current position and O(1) insertion at the head.
 *   - Architecture:
 *     - Dummy `head` and `tail` nodes eliminate edge cases for empty/single-node lists.
 *     - Head represents Most Recently Used (MRU).
 *     - Tail represents Least Recently Used (LRU).
 *     - On `get(key)`: If found, detach node from its current spot and reinsert right after `head`.
 *     - On `put(key, value)`:
 *       - If key exists, update value and move to head.
 *       - If key does not exist and cache is at capacity, delete node immediately preceding `tail` (`tail->prev`),
 *         remove its key from hash map, and insert the new node after `head`.
 * 
 * TIME COMPLEXITY:
 * - get(key): O(1)
 * - put(key, value): O(1)
 * 
 * SPACE COMPLEXITY:
 * - O(Capacity) auxiliary space for DLL nodes and hash map.
 */

#include <iostream>
#include <unordered_map>

class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    std::unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void addNode(Node* node) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Insert node right after dummy head (marking it Most Recently Used in O(1))
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Unlink node from DLL in O(1) without iterating through the list
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    Node* popTail() {
        Node* res = tail->prev;
        removeNode(res);
        return res;
    }

public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        Node* node = cache[key];
        moveToHead(node); // Refresh recency
        return node->value;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            if ((int)cache.size() >= capacity) {
                Node* lru = popTail();
                cache.erase(lru->key);
                delete lru;
            }
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addNode(newNode);
        }
    }
};

int main() {
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    std::cout << "get(1): " << lru.get(1) << "\n"; // 1 (1 is now MRU, 2 is LRU)
    lru.put(3, 3); // evicts key 2
    std::cout << "get(2): " << lru.get(2) << "\n"; // -1 (not found)
    lru.put(4, 4); // evicts key 1
    std::cout << "get(1): " << lru.get(1) << "\n"; // -1 (not found)
    std::cout << "get(3): " << lru.get(3) << "\n"; // 3
    std::cout << "get(4): " << lru.get(4) << "\n"; // 4

    return 0;
}
