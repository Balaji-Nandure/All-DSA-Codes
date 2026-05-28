/*
GeeksforGeeks: Minimum Depth of a Binary Tree
Difficulty: Easy

Problem:
Find minimum depth of binary tree.

Minimum depth =
number of nodes from root
to nearest LEAF node.

Leaf node:
node having no children.

Example:

        1
       / \
      3   2
     /
    4

Paths:
1->3->4 = depth 3
1->2    = depth 2

Answer = 2

Important Observation:
We CANNOT directly use:

1 + min(left, right)

Why?

Example:

        1
       /
      2

left depth  = 1
right depth = 0

min(1,0)=0

But answer is NOT 1.
Correct answer is 2.

So:
If one subtree is missing,
we MUST take the other subtree.

Approach:
1. If node is NULL -> 0
2. If leaf -> 1
3. If one child missing:
      return 1 + depth(other child)
4. Else:
      return 1 + min(left, right)

Time Complexity: O(N)
Space Complexity: O(H)

(H = tree height)

GFG Link:
https://www.geeksforgeeks.org/problems/minimum-depth-of-a-binary-tree/1
*/

class Solution {
public:

    int minDepth(Node *root) {

        // empty tree
        if(!root)
            return 0;

        // leaf node
        if(!root->left && !root->right)
            return 1;

        // left missing
        if(!root->left)
            return 1 + minDepth(root->right);

        // right missing
        if(!root->right)
            return 1 + minDepth(root->left);

        // both children exist
        return 1 + min(minDepth(root->left),
                       minDepth(root->right));
    }
};

/*
Dry Run:

        1
       /
      2

Node 1:
left exists
right missing

So:
1 + minDepth(2)

Node 2:
leaf => 1

Answer:
1 + 1 = 2

Final Summary:
1. Leaf node gives depth 1
2. If one subtree missing,
   use other subtree only
3. Otherwise take minimum
*/