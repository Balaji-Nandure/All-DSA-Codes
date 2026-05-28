/*
GeeksforGeeks: Leaves at Same Level or Not
Difficulty: Easy

Problem:
Check whether all leaf nodes
are present at the same level.

Return:
true  -> all leaves same level
false -> otherwise

Example:

        12
       /  \
      5    7
     /      \
    3        1

Leaf nodes:
3 -> level 2
1 -> level 2

Answer = true

Core Idea:
Store level of FIRST leaf.
Then compare every other leaf level with it.

If any mismatch found -> false

Approach:
1. DFS traversal
2. Whenever leaf found:
   - first leaf -> store level
   - next leaves -> compare level
3. If mismatch -> false

Time Complexity: O(N)
Space Complexity: O(H)

(H = tree height)

GFG Link:
https://www.geeksforgeeks.org/problems/leaf-at-same-level/1
*/

class Solution {
public:

    bool solve(Node* root, int level, int &leafLevel){

        if(!root)
            return true;

        // leaf node
        if(!root->left && !root->right){

            // first leaf found
            if(leafLevel == -1){

                leafLevel = level;
                return true;
            }

            // compare levels
            return leafLevel == level;
        }

        // check both subtrees
        return solve(root->left, level + 1, leafLevel) &&
               solve(root->right, level + 1, leafLevel);
    }

    bool check(Node *root) {

        int leafLevel = -1;

        return solve(root, 0, leafLevel);
    }
};

/*
Dry Run:

        1
       / \
      2   3
     /     \
    4       5

First leaf:
4 at level 2
store leafLevel = 2

Next leaf:
5 at level 2
matches

Answer = true

Final Summary:
1. Store first leaf level
2. Compare all other leaf levels
3. Any mismatch -> false
*/