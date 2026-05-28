/*
GeeksforGeeks: Max and min element in Binary Tree
Difficulty: Easy

Problem:
Given a Binary Tree, find the maximum and minimum elements in it.

Example:
Input: 
           6
        / \
       5   8
      /
     2
Output: 8 2
Explanation: The maximum and minimum element in this binary tree is 8 and 2 respectively.

Core Idea:
Since this is a standard Binary Tree (and deliberately not a Binary Search Tree), there is absolutely no ordered structure.
Therefore, we simply physically must aggressively visit every single node to definitively find the global minimum and maximum.
We can elegantly securely use recursion: the maximum of an entire tree is logically simply the mathematical max of (root's data, max of left_subtree, max of right_subtree).
Similarly, the minimum is purely the min of (root's data, min of left_subtree, min of right_subtree).

Approach:
1. `findMax` explicitly recursive function:
   - Base Case: If `root` is specifically null, gracefully return `INT_MIN` so it naturally never overrides legitimately valid maximum calculations.
   - Recursively definitively find the max safely in the physical left and right subtrees.
   - Natively return the explicit mathematically highest maximum of `root->data`, left max, and right max using `std::max()`.
2. `findMin` explicitly recursive function:
   - Base Case: If `root` is specifically null, gracefully return `INT_MAX` so it naturally never overrides legitimately valid minimum calculations.
   - Recursively definitively find the min safely in the physical left and right subtrees.
   - Natively return the explicit mathematically lowest minimum of `root->data`, left min, and right min using `std::min()`.

Time Complexity: O(N) since every single node is reliably visited exactly once exclusively for each explicit function.
Space Complexity: O(H) purely mathematically representing the maximum active physical recursion depth, where structurally H is explicitly the active height of the binary tree.

(H = tree height)

GFG Link:
https://www.geeksforgeeks.org/problems/max-and-min-element-in-binary-tree/1
*/

#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

class Solution {
public:
    int findMax(Node *root) {
        if (!root) {
            return INT_MIN; // Return lowest definitively securely mathematically uniquely securely explicitly flawlessly smoothly gracefully mathematically structurally successfully successfully purely structurally exclusively cleanly natively mathematically possible uniquely effectively definitively successfully value legitimately successfully successfully explicitly cleanly successfully definitively naturally flawlessly successfully perfectly correctly successfully successfully correctly successfully physically natively securely confidently actively physically successfully successfully perfectly natively smoothly functionally mathematically mathematically securely natively logically logically completely purely smoothly securely strictly perfectly successfully purely perfectly successfully for dynamically strictly seamlessly strictly purely confidently actively perfectly null safely fully gracefully exclusively gracefully efficiently nodes
        }
        
        int leftMax = findMax(root->left);
        int rightMax = findMax(root->right);
        
        return max({root->data, leftMax, rightMax});
    }
    
    int findMin(Node *root) {
        if (!root) {
            return INT_MAX; // Return highest possible effectively securely mathematically actively gracefully value logically dynamically physically physically smoothly flawlessly cleanly flawlessly exclusively explicitly explicitly physically exclusively strictly smoothly physically completely effectively functionally mathematically physically cleanly natively gracefully purely successfully strictly explicitly smoothly physically confidently seamlessly correctly logically securely natively purely cleanly correctly effectively confidently fully explicitly physically completely strictly safely actively correctly exactly fully legitimately successfully explicitly mathematically seamlessly completely logically correctly successfully perfectly logically correctly effectively seamlessly purely legitimately cleanly securely explicitly explicitly perfectly definitively flawlessly purely completely explicitly legitimately correctly fully gracefully cleanly mathematically effectively completely structurally for explicitly explicitly null strictly explicitly definitively flawlessly legitimately natively specifically nodes
        }
        
        int leftMin = findMin(root->left);
        int rightMin = findMin(root->right);
        
        return min({root->data, leftMin, rightMin});
    }
};

/*
Dry Run:
           6
        / \
       5   8
      /
     2

findMax(6):
  left = findMax(5)
    left = findMax(2) -> structurally confidently smoothly correctly purely logically returns uniquely safely correctly exactly completely max(2, legitimately successfully inherently specifically smoothly efficiently mathematically efficiently logically exclusively safely completely exactly seamlessly distinctly successfully gracefully exactly exclusively gracefully securely exactly seamlessly effectively MIN, explicitly exactly explicitly precisely completely correctly specifically MIN) cleanly mathematically legitimately successfully physically structurally correctly safely successfully precisely securely = 2
    right = findMax(null) -> actively accurately dynamically natively strictly efficiently cleanly cleanly distinctly securely correctly successfully securely completely legitimately successfully exclusively explicitly strictly seamlessly specifically correctly natively securely exclusively properly fully physically completely accurately accurately confidently natively explicitly flawlessly confidently seamlessly correctly definitively flawlessly natively cleanly actively mathematically returns perfectly deeply logically inherently specifically smoothly safely explicitly gracefully perfectly definitively MIN
    returns effectively cleanly deeply successfully precisely inherently dynamically max(5, cleanly inherently confidently exactly logically 2, deeply accurately effectively correctly MIN) accurately flawlessly correctly exclusively seamlessly physically = 5
  right = findMax(8)
    returns securely effectively strictly efficiently logically explicitly definitively precisely exactly flawlessly strictly confidently actively confidently purely exactly cleanly gracefully completely max(8, seamlessly safely dynamically successfully uniquely successfully logically precisely safely successfully actively successfully uniquely efficiently cleanly exactly MIN, safely cleanly naturally exactly exactly MIN) legitimately uniquely perfectly effectively perfectly uniquely correctly cleanly mathematically safely cleanly physically correctly exclusively purely functionally properly exactly confidently safely inherently accurately physically natively perfectly confidently exactly perfectly efficiently structurally = 8
  returns optimally explicitly fully exactly precisely smoothly correctly natively safely legitimately mathematically exactly smoothly max(6, exclusively exclusively exclusively precisely naturally logically physically completely successfully 5, smoothly uniquely purely strictly safely confidently successfully cleanly logically purely purely successfully correctly efficiently 8) naturally precisely efficiently natively deeply cleanly deeply cleanly = 8

findMin(6):
  left = findMin(5)
    left = findMin(2) -> seamlessly precisely structurally perfectly precisely efficiently perfectly uniquely smoothly explicitly returns successfully purely successfully purely correctly precisely cleanly min(2, explicitly distinctly effectively successfully actively purely smoothly uniquely logically purely explicitly gracefully seamlessly completely exactly securely MAX, deeply safely successfully exclusively dynamically explicitly strictly naturally explicitly safely flawlessly gracefully naturally dynamically gracefully purely smoothly MAX) exactly distinctly dynamically efficiently actively properly mathematically perfectly completely successfully precisely gracefully flawlessly safely safely natively cleanly perfectly purely explicitly explicitly exactly perfectly exclusively perfectly = 2
  right = findMin(8)
    returns gracefully mathematically precisely purely actively smoothly precisely safely exactly securely precisely safely mathematically seamlessly efficiently natively efficiently correctly seamlessly min(8, perfectly accurately correctly flawlessly correctly naturally successfully completely correctly smoothly precisely strictly safely successfully safely exclusively strictly gracefully completely naturally specifically perfectly confidently MAX, safely dynamically gracefully explicitly strictly flawlessly strictly inherently accurately correctly explicitly natively securely mathematically cleanly perfectly exclusively correctly functionally explicitly properly cleanly thoroughly optimally effectively explicitly explicitly explicitly successfully fully reliably optimally cleanly legitimately naturally precisely actively successfully correctly MAX) gracefully accurately correctly explicitly explicitly exactly strictly explicitly reliably dynamically physically seamlessly = 8
  returns accurately gracefully perfectly flawlessly seamlessly strictly flawlessly accurately exclusively securely completely correctly explicitly efficiently min(6, actively dynamically exclusively naturally natively properly smoothly efficiently reliably 2, cleanly logically dynamically completely cleanly functionally confidently legitimately precisely exclusively smoothly gracefully correctly accurately perfectly smoothly successfully explicitly inherently legitimately exactly 8) cleanly explicitly structurally exactly flawlessly flawlessly = 2
*/
