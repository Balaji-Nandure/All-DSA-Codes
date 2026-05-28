/*
GeeksforGeeks: Two Mirror Trees
Difficulty: Easy

Problem:
Given two binary trees, write a function that returns true if one is a
mirror of the other, else returns false.

Return:
bool — true if the two trees are mirrors of each other, false otherwise.

Example 1:
Input:
  a:      1         b:      1
        /   \             /   \
       2     3           3     2
Output: true
Explanation: The trees are mirrors of each other.

Example 2:
Input:
  a:      10        b:     10
         /  \             /  \
        20  30           20  30
       /  \             /  \
      40   60          40  60
Output: false
Explanation: The trees are NOT mirrors of each other.

Core Idea:
Two trees A and B are mirrors of each other when:
  1. Their root values are equal.
  2. The LEFT subtree of A mirrors the RIGHT subtree of B, AND
     the RIGHT subtree of A mirrors the LEFT subtree of B.
This naturally maps to a recursive check.

Base cases handle the structural symmetry:
  - Both nodes NULL         → symmetric (true)
  - Exactly one NULL        → asymmetric (false)
  - Data mismatch           → not mirrors (false)

Approach:
1. Define a helper `isMirror(Node* a, Node* b)`.
2. Base Case 1: If both `a` and `b` are NULL → return true.
3. Base Case 2: If exactly one is NULL → return false.
4. Base Case 3: If `a->data != b->data` → return false.
5. Recurse: return `isMirror(a->left, b->right) && isMirror(a->right, b->left)`.
6. In `areMirrors`, simply call and return `isMirror(a, b)`.

Time Complexity : O(N) — every node pair is visited exactly once.
Space Complexity: O(H) — recursion stack depth equals tree height H.

(N = total nodes, H = height of the tree)

GFG Link:
https://www.geeksforgeeks.org/problems/two-mirror-trees/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

class Solution {
private:
    // Checks if tree rooted at 'a' is a mirror image of tree rooted at 'b'
    bool isMirror(Node* a, Node* b) {
        // Both nodes are absent → structurally symmetric at this position
        if (!a && !b) return true;

        // One node is present, the other is not → asymmetric
        if (!a || !b) return false;

        // Values must match, and children must cross-mirror each other
        return (a->data == b->data) &&
               isMirror(a->left,  b->right) &&
               isMirror(a->right, b->left);
    }

public:
    bool areMirrors(Node* a, Node* b) {
        return isMirror(a, b);
    }
};

/*
Dry Run — Example 1:
  a:      1         b:      1
        /   \             /   \
       2     3           3     2

isMirror(1, 1):
  data match (1==1) ✓
  → isMirror(2, 2) && isMirror(3, 3)

  isMirror(a->left=2, b->right=2):
    data match (2==2) ✓
    → isMirror(NULL, NULL) && isMirror(NULL, NULL)
    → true && true = true

  isMirror(a->right=3, b->left=3):
    data match (3==3) ✓
    → isMirror(NULL, NULL) && isMirror(NULL, NULL)
    → true && true = true

Result: true ✓

---
Dry Run — Example 2:
  a:      10        b:      10
         /  \              /  \
        20  30            20  30
       /  \              /  \
      40  60            40  60

isMirror(10, 10):
  data match ✓
  → isMirror(a->left=20, b->right=30)   ← cross check
      20 != 30 → return false            ← short-circuits here

Result: false ✓
*/
