/*
 * Problem: Design Browser History (LeetCode 1472)
 * 
 * You have a browser of one tab where you start on the homepage and you can 
 * visit another url, get back in the history number of steps or move forward 
 * in the history number of steps.
 * 
 * Implement the BrowserHistory class:
 * - BrowserHistory(string homepage) Initializes the object with the homepage 
 *   of the browser.
 * - void visit(string url) Visits url from the current page. It clears up all 
 *   the forward history.
 * - string back(int steps) Move steps back in history. If you can only return 
 *   x steps in the history and steps > x, you will return only x steps. 
 *   Return the current url after moving back in history at most steps.
 * - string forward(int steps) Move steps forward in history. If you can only 
 *   forward x steps in the history and steps > x, you will forward only x steps. 
 *   Return the current url after forwarding in history at most steps.
 * 
 */

#include <bits/stdc++.h>
using namespace std;

// ========== METHOD 1: Doubly Linked List (Optimal) ==========
// Time Complexity: O(1) for all operations, Space Complexity: O(n)
class BrowserHistory {
private:
    struct Node {
        string url;
        Node* prev;
        Node* next;
        
        Node(string url) {
            this->url = url;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };
    
    Node* current;

public:
    BrowserHistory(string homepage) {
        current = new Node(homepage);
    }
        
    void visit(string url) {
        // Clear forward history (delete all nodes after current)
        Node* temp = current->next;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        
        // Create new node and link it
        Node* newNode = new Node(url);
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    
    string back(int steps) {
        while (steps > 0 && current->prev) {
            current = current->prev;
            steps--;
        }
        return current->url;
    }
    
    string forward(int steps) {
        while (steps > 0 && current->next) {
            current = current->next;
            steps--;
        }
        return current->url;
    }
};

// ========== METHOD 2: Using Vector/Array ==========
// Time Complexity: O(1) for visit, O(steps) for back/forward, Space Complexity: O(n)
class BrowserHistoryVector {
private:
    vector<string> history;
    int currentIndex;
    int lastIndex;  // Last valid index (for clearing forward history)

public:
    BrowserHistoryVector(string homepage) {
        history.push_back(homepage);
        currentIndex = 0;
        lastIndex = 0;
    }
    
    void visit(string url) {
        // Clear forward history by updating lastIndex
        currentIndex++;
        if (currentIndex < history.size()) {
            history[currentIndex] = url;
        } else {
            history.push_back(url);
        }
        lastIndex = currentIndex;
    }
    
    string back(int steps) {
        currentIndex = max(0, currentIndex - steps);
        return history[currentIndex];
    }
    
    string forward(int steps) {
        currentIndex = min(lastIndex, currentIndex + steps);
        return history[currentIndex];
    }
};
