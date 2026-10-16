/**
 * ============================================================================
 * Problem: First Non-Repeating Character in a Stream (Doubly Linked List + Hash Map)
 * Category: LinkedList / Queue / Design
 * 
 * Problem Statement:
 * Given an input stream of characters A of length N. While reading characters from 
 * the stream, you have to find the first non-repeating character at each instant.
 * If there is no non-repeating character at any moment, append '#' to the output.
 * 
 * Example 1:
 * Input:  A = "aabc"
 * Output: "a#bb"
 * Explanation:
 *   - 'a': first non-repeating is 'a'
 *   - 'aa': both 'a's repeat -> no non-repeating -> '#'
 *   - 'aab': 'b' is first non-repeating -> 'b'
 *   - 'aabc': 'b' is still first non-repeating -> 'b'
 * 
 * Example 2:
 * Input:  A = "zz"
 * Output: "z#"
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 'a' <= A[i] <= 'z'
 * Must process each incoming stream character in O(1) time.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Online Streaming vs Offline Batch Processing:
 *    - In Problem 7 (Remove duplicates), the entire static list was available at once.
 *    - In an online stream, characters arrive one-by-one indefinitely; we cannot
 *      restart scanning from the beginning for every incoming character without
 *      causing disastrous O(N^2) degradation.
 * 2. Doubly Linked List as an O(1) Removal Queue:
 *    - A standard FIFO queue can dequeue only from the front.
 *    - But in this problem, a character inside the queue might repeat later and
 *      must be removed from the MIDDLE of the queue in O(1) time!
 *    - A Doubly Linked List coupled with a direct node pointer lookup table
 *      allows O(1) deletion of arbitrary middle nodes.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Doubly Linked List + Direct Node Lookup Array:
 *   - Maintain:
 *       1. `inDLL[26]`: array of pointers to nodes currently in the DLL.
 *       2. `repeated[26]`: boolean array marking whether character has appeared >= 2 times.
 *       3. A Doubly Linked List storing unique characters in order of arrival.
 *   - When character `c` arrives:
 *       - Case 1: `repeated[c - 'a'] == true`:
 *           Character has already been marked as duplicate. Ignore it.
 *       - Case 2: `inDLL[c - 'a'] != nullptr`:
 *           Character has appeared for the second time!
 *           Mark `repeated[c - 'a'] = true`.
 *           Remove node `inDLL[c - 'a']` from the DLL in O(1) time!
 *           Set `inDLL[c - 'a'] = nullptr`.
 *       - Case 3: First time seeing `c`:
 *           Append `c` to the tail of the DLL in O(1) time.
 *           Record `inDLL[c - 'a'] = tail`.
 *       - Output:
 *           If DLL is empty: append '#'
 *           Else: append head of DLL (`head->data`)
 *   - Guarantees strictly O(1) time per stream event.
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Doubly Linked List Node
struct DLLNode {
    char data;
    DLLNode* next;
    DLLNode* prev;
    DLLNode(char val) : data(val), next(nullptr), prev(nullptr) {}
};

class Solution {
private:
    DLLNode* head;
    DLLNode* tail;

    void appendNode(DLLNode* node) {
        if (head == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    void removeNode(DLLNode* node) {
        if (node == nullptr) return;

        if (node == head) head = head->next;
        if (node == tail) tail = tail->prev;

        if (node->prev != nullptr) node->prev->next = node->next;
        if (node->next != nullptr) node->next->prev = node->prev;

        delete node;
    }

public:
    Solution() : head(nullptr), tail(nullptr) {}

    /**
     * Processes character stream and returns first non-repeating character at each step.
     * @param stream Input string representing stream of lowercase English characters.
     * @return Result string of characters.
     */
    string FirstNonRepeating(string stream) {
        head = nullptr;
        tail = nullptr;

        vector<DLLNode*> inDLL(26, nullptr);
        vector<bool> repeated(26, false);

        string result = "";

        for (char ch : stream) {
            int idx = ch - 'a';

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If the character hasn't repeated yet:
            // - If it's already in the DLL, this is its 2nd appearance -> remove from DLL in O(1)!
            // - Otherwise, this is its 1st appearance -> add to DLL in O(1).
            if (!repeated[idx]) {
                if (inDLL[idx] == nullptr) {
                    DLLNode* newNode = new DLLNode(ch);
                    appendNode(newNode);
                    inDLL[idx] = newNode;
                } else {
                    removeNode(inDLL[idx]);
                    inDLL[idx] = nullptr;
                    repeated[idx] = true;
                }
            }

            // Head of the DLL always maintains the earliest non-repeating character
            if (head != nullptr) {
                result += head->data;
            } else {
                result += '#';
            }
        }

        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: "aabc"
    // 'a' -> 'a'
    // 'a' -> '#'
    // 'b' -> 'b'
    // 'c' -> 'b'
    // Expected: "a#bb"
    string s1 = "aabc";
    cout << "Stream 1: " << s1 << "\n";
    cout << "Output:   " << solver.FirstNonRepeating(s1) << " (Expected: a#bb)\n\n";

    // Test Case 2: "zz"
    // Expected: "z#"
    string s2 = "zz";
    cout << "Stream 2: " << s2 << "\n";
    cout << "Output:   " << solver.FirstNonRepeating(s2) << " (Expected: z#)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each incoming character executes at most one O(1) DLL insertion or removal.
 *   - Total Time: O(N) for a stream of length N.
 * 
 * Space Complexity:
 *   - Alphabet size: 26 (fixed constant).
 *   - InDLL array: 26 pointers.
 *   - Repeated array: 26 booleans.
 *   - Auxiliary Space: O(1) strictly (O(26) alphabet space).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. A Doubly Linked List is the only queue-like structure that supports O(1)
 *    deletion of arbitrary internal elements when backed by direct node pointers.
 * 2. This identical DLL + Hash pattern forms the foundation of LRU Cache and LFU Cache.
 */
