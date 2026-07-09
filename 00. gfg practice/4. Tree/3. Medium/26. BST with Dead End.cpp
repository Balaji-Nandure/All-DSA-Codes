/*
    Problem Name: BST with Dead End
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a BST with unique positive integers (> 0), determine whether the BST contains
    a "dead end" — a leaf node where no new integer can be inserted while maintaining
    the BST property and the constraint that all values must be > 0.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once.
    Space Complexity: O(H), where H is the height of the BST, for the recursion stack.

    Love Babbar Style Approach:
    The KEY insight — every node in a BST has a VALID RANGE of values that can exist
    below it. As we go deeper, this range gets TIGHTER and TIGHTER!

    We pass [minVal, maxVal] as the valid range for each node:
    - Go LEFT:  range becomes [minVal, node->data - 1]  (values must be < node)
    - Go RIGHT: range becomes [node->data + 1, maxVal]  (values must be > node)

    A DEAD END happens when a LEAF node's range has COLLAPSED completely:
        minVal == maxVal  → there's NO integer left to insert!

    WHY? If minVal == maxVal == node->data, then:
    - To insert LEFT:  need a value in [minVal, node-1] = [minVal, minVal-1] → EMPTY!
    - To insert RIGHT: need a value in [node+1, maxVal] = [maxVal+1, maxVal] → EMPTY!
    - DEAD END!

    IMPORTANT: We start with minVal = 0 (not 1!) because the constraint says values > 0,
    so 0 acts as the lower boundary. If a leaf node has value 1, its range is [0+1, ?] 
    going right and [0, 1-1]=[0,0] going left — but it's a leaf so we check: min==max? 
    Actually, we pass min=0 initially, and when we reach leaf 1 with range [1,1], 
    minVal==maxVal → dead end!

    Dry Run:
    BST:        8
               / \
              5   9
             /
            2
           /
          1

    - solve(8, min=0, max=INT_MAX):
        - solve(5, min=0, max=7):
            - solve(2, min=0, max=4):
                - solve(1, min=0, max=1):
                    - leaf! min=0+1? No wait, let's track correctly.
                    - Actually when we go left from 2: range = [0, 1]
                    - solve(1, min=0, max=1): 
                      - Go left: solve(NULL, min=0, max=0) → false
                      - Go right: solve(NULL, min=2, max=1) → false
                      - It's a LEAF! Check: min == max? → 0 == 1? NO...
                      
    Hmm, let me reconsider. The range means: the valid values in this subtree 
    are (min, max) exclusive. When we reach a leaf, the node itself occupies its 
    value. So for leaf node with value v, the range is [min, max] and v is there.
    Dead end if min == max (no room for anything else).

    Let me re-trace with corrected logic:
    - solve(8, min=0, max=INT_MAX): go left with [0, 7], go right with [9, INT_MAX]
        - solve(5, min=0, max=7): go left with [0, 4], go right with [6, 7]
            right is NULL → ok
            - solve(2, min=0, max=4): go left with [0, 1], go right with [3, 4]
                right is NULL → ok
                - solve(1, min=0, max=1): LEAF! min=0, max=1 → max-min=1, node=1
                  min == max? 0 == 1? NO... but node 1 IS a dead end!
    
    The trick: at a leaf, dead end if (max - min == 1) — wait no. 
    Let me think again. Actually the right way: if we pass the range as the 
    EXCLUSIVE boundaries (like BST validation), then for a leaf with value v and
    range (low, high), if low == v-1 and high == v+1, then no integer fits.
    Equivalently: high - low == 2 and v = low+1.
    
    Or simpler: pass inclusive range. Start with [1, INT_MAX] (since all values > 0).
    Go left: [min, node-1]. Go right: [node+1, max].
    At a leaf: if min == max, then no room. Since min==max==node->data, there's 
    no integer in [min, node-1] (empty) or [node+1, max] (empty).

    Let me re-trace:
    - solve(8, min=1, max=INT_MAX): 
        left → [1, 7], right → [9, INT_MAX]
        - solve(5, min=1, max=7):
            left → [1, 4], right → [6, 7]
            - solve(2, min=1, max=4):
                left → [1, 1], right → [3, 4]
                - solve(1, min=1, max=1): LEAF! min==max==1 → DEAD END! ✓
    
    YES! Starting with min=1 works perfectly.
</thinking>

Let me reconsider the range logic carefully before writing.

<function_calls>
<invoke name="write_to_file">
<parameter name="CodeContent">/*
    Problem Name: BST with Dead End
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a BST with unique positive integers (> 0), determine whether the BST contains
    a "dead end" — a leaf node where no new integer can be inserted while maintaining
    the BST property and the constraint that all values must be positive integers (> 0).

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once.
    Space Complexity: O(H), where H is the height of the BST, for the recursion stack.

    Love Babbar Style Approach:
    The KEY insight — every node in a BST lives within a VALID RANGE of values.
    As we go deeper, this range gets TIGHTER. A dead end is when the range COLLAPSES
    at a leaf node — no room to insert ANYTHING!

    We pass [minVal, maxVal] as the INCLUSIVE range of valid values for each subtree:
    - Start with [1, INT_MAX] (since all values must be > 0, minimum possible is 1).
    - Go LEFT:  range becomes [minVal, node->data - 1]  (must be strictly less than node)
    - Go RIGHT: range becomes [node->data + 1, maxVal]  (must be strictly greater than node)

    DEAD END condition at a LEAF node:
        minVal == maxVal
        This means the leaf's value is the ONLY integer in its range.
        - LEFT insertion needs a value in [minVal, node-1] → EMPTY (node == minVal)!
        - RIGHT insertion needs a value in [node+1, maxVal] → EMPTY (node == maxVal)!
        - No room at all → DEAD END!

    Dry Run:
    BST:        8
               / \
              5   9
             /
            2
           /
          1

    - solve(8, min=1, max=INT_MAX):
        - Left: solve(5, min=1, max=7)
            - Left: solve(2, min=1, max=4)
                - Left: solve(1, min=1, max=1)
                    - LEAF! min==max==1 → DEAD END! ✓
                    - WHY? Node 1 can't have a left child (would need value in [1,0] → empty!)
                           Node 1 can't have a right child (would need value in [2,1] → empty!)
                    - return TRUE!

    Dry Run 2:
    BST:        8
               / \
              7   10
             /   /  \
            2   9   13

    - solve(8, min=1, max=INT_MAX):
        - Left: solve(7, min=1, max=7)
            - Left: solve(2, min=1, max=6)
                - Leaf! min=1, max=6 → 1 ≠ 6 → NOT dead end. Can still insert values.
            - Right: NULL → false
        - Right: solve(10, min=9, max=INT_MAX)
            - Left: solve(9, min=9, max=9)
                - LEAF! min==max==9 → DEAD END! ✓
                - WHY? Node 9 is squeezed between 8 and 10. No integer fits!
            - return TRUE!
*/

#include <iostream>
#include <climits>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
private:
    bool solve(Node* root, int minVal, int maxVal) {
        // Base Case: Fell off the tree — no dead end found on this path
        if (root == NULL) return false;

        // LEAF NODE CHECK: If the range has collapsed to a single value,
        // this leaf has NO room for any new insertion → DEAD END!
        if (root->left == NULL && root->right == NULL) {
            if (minVal == maxVal) {
                return true;  // Dead end found!
            }
            return false;
        }

        // Recurse into left and right subtrees with tightened ranges
        // LEFT:  valid values are [minVal, node - 1]
        // RIGHT: valid values are [node + 1, maxVal]
        return solve(root->left,  minVal, root->data - 1) ||
               solve(root->right, root->data + 1, maxVal);
    }

public:
    // GFG Signature
    bool isDeadEnd(Node* root) {
        // Start with range [1, INT_MAX] since all values must be > 0
        return solve(root, 1, INT_MAX);
    }
};

int main() {
    // Example 1:
    //         8
    //        / \
    //       5   9
    //      /
    //     2
    //    /
    //   1
    // Expected: true (Node 1 is a dead end — squeezed at minimum boundary)

    Node* root1 = new Node(8);
    root1->left              = new Node(5);
    root1->right             = new Node(9);
    root1->left->left        = new Node(2);
    root1->left->left->left  = new Node(1);

    Solution ob;
    // Output: true
    cout << "Has Dead End (Example 1): " << (ob.isDeadEnd(root1) ? "true" : "false") << "\n";

    // Example 2:
    //         8
    //        / \
    //       7   10
    //      /   /  \
    //     2   9   13
    // Expected: true (Node 9 is a dead end — squeezed between 8 and 10)

    Node* root2 = new Node(8);
    root2->left         = new Node(7);
    root2->right        = new Node(10);
    root2->left->left   = new Node(2);
    root2->right->left  = new Node(9);
    root2->right->right = new Node(13);

    // Output: true
    cout << "Has Dead End (Example 2): " << (ob.isDeadEnd(root2) ? "true" : "false") << "\n";

    // Example 3: No dead end
    //     5
    //    / \
    //   3   7
    // Leaf 3: range [1, 4] → 1 ≠ 4 → NOT dead end
    // Leaf 7: range [6, INT_MAX] → NOT dead end
    // Expected: false

    Node* root3 = new Node(5);
    root3->left  = new Node(3);
    root3->right = new Node(7);

    // Output: false
    cout << "Has Dead End (Example 3): " << (ob.isDeadEnd(root3) ? "true" : "false") << "\n";

    return 0;
}
