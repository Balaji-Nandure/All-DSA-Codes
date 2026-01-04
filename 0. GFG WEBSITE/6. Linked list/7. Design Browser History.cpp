/*
Problem:
Design Browser History

Design a browser history system that supports the following operations:

1. BrowserHistory(homepage)
   - Initializes the browser with the given homepage.

2. visit(url)
   - Visits a new URL from the current page.
   - Clears all forward history.

3. back(steps)
   - Move back by at most "steps" in the history.
   - Return the current page after moving back.

4. forward(steps)
   - Move forward by at most "steps" in the history.
   - Return the current page after moving forward.


Examples:
BrowserHistory bh("leetcode.com");
bh.visit("google.com");
bh.visit("facebook.com");
bh.visit("youtube.com");
bh.back(1);        // facebook.com
bh.back(1);        // google.com
bh.forward(1);     // facebook.com
bh.visit("linkedin.com");
bh.forward(2);     // linkedin.com
bh.back(2);        // google.com
bh.back(7);        // leetcode.com


-----------------------------------
Approach (Expected / Optimal – Doubly Linked List Simulation):
-----------------------------------
1. Use a doubly linked list structure implicitly.
2. Maintain:
   - curr → pointer to current page
3. On visit(url):
   - Clear forward history
   - Add new node after curr
   - Move curr to new node
4. On back(steps):
   - Move curr backward while steps > 0 and prev exists
5. On forward(steps):
   - Move curr forward while steps > 0 and next exists

Why this works:
- Browser history naturally fits a doubly linked list.
- Back and forward operations are pointer moves.
- All operations are efficient and simple.

Time Complexity:
- visit  : O(1)
- back   : O(steps)
- forward: O(steps)

Space Complexity:
O(n)   (number of visited pages)


GeeksforGeeks:
https://www.geeksforgeeks.org/design-browser-history/

LeetCode:
https://leetcode.com/problems/design-browser-history/
*/


class BrowserHistory {
    private:
        struct Node {
            string url;
            Node* prev;
            Node* next;
    
            Node(string u) {
                url = u;
                prev = NULL;
                next = NULL;
            }
        };
    
        Node* curr;
    
    public:
        BrowserHistory(string homepage) {
            curr = new Node(homepage);
        }
    
        void visit(string url) {
            Node* newNode = new Node(url);
    
            // Clear forward history
            curr->next = NULL;
    
            // Link new node
            newNode->prev = curr;
            curr->next = newNode;
    
            // Move current pointer
            curr = newNode;
        }
    
        string back(int steps) {
            while (steps > 0 && curr->prev != NULL) {
                curr = curr->prev;
                steps--;
            }
            return curr->url;
        }
    
        string forward(int steps) {
            while (steps > 0 && curr->next != NULL) {
                curr = curr->next;
                steps--;
            }
            return curr->url;
        }
    };
    