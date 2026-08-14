/*
    Problem Name: Tree Transformation
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given a tree containing N nodes represented by an array p[] where p[i] represents
    the parent of the i-th node, and p[0] = -1 (rooted at node 0).
    In one move, you can merge any two adjacent nodes.
    Calculate the minimum number of moves required to turn the tree into a Star Tree.

    Definitions:
    - Merging adjacent nodes deletes the edge between them and combines them into a single node.
    - A Star Tree is a tree with a single central node, and all other nodes are leaves connected
      directly to that central node.

    Examples:
    Input: N = 5, p[] = {-1, 0, 0, 1, 1}
    Output: 1
    Explanation:
    Node 1 has degree > 1. Merging node 1 into node 0 (1 move) connects all leaves directly to node 0.

    Input: N = 8, p[] = {-1, 0, 0, 0, 0, 2, 2, 5}
    Output: 2
    Explanation:
    Nodes 2 and 5 have degree > 1. Merging node 5 and node 2 requires 2 operations.

    Input: N = 3, p[] = {-1, 0, 1}
    Output: 1
    Explanation:
    Node 1 has degree 2. Merging node 1 into 0 turns it into a Star Tree.

    Constraints:
    1 <= N <= 10^5
    0 <= p[i] < N
    p[0] = -1

    Expected Complexities:
    Time Complexity: O(N), single pass over the parent array.
    Space Complexity: O(N), for node degree counts.

    Love Babbar Style Approach:
    Internal Child Node Degree Counting:

    1. INTUITION:
       - To transform any tree into a Star Tree:
         * Leaf nodes (nodes with `degree == 1`) do not need to be merged.
         * The root node (node 0) and the last node (node N-1) serve as endpoints.
         * Any intermediate child node `i` (where `1 <= i <= N - 2`) that has `degree > 1`
           represents an internal branching node that MUST be merged into its parent.
       - Therefore, the minimum number of moves required equals the count of nodes `i`
         in the range `1 <= i <= N - 2` such that `degree[i] > 1`!

    2. ALGORITHM:
       - `vector<int> deg(N, 0);`
       - For `i = 1` to `N - 1`: `deg[i]++`, `deg[p[i]]++`.
       - `int ans = 0;`
       - For `i = 1` to `N - 2`:
         * `if (deg[i] > 1) ans++;`
       - Return `ans`.

    Dry Run:
    N = 3, p = {-1, 0, 1}
    - Edges: (0,1), (1,2)
    - Degrees: deg[0]=1, deg[1]=2, deg[2]=1
    - Loop i = 1 (to N-2 = 1):
      * i = 1: deg[1] = 2 > 1 -> ans = 1.
    - Return 1 ✓
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // GFG Signature
    int solve(int N, vector<int> p) {
        vector<int> deg(N, 0);

        // Step 1: Calculate the degree of every node
        for (int i = 1; i < N; i++) {
            deg[i]++;
            deg[p[i]]++;
        }

        // Step 2: Count internal child nodes (range 1 to N-2) with degree > 1
        int ans = 0;
        for (int i = 1; i < N - 1; i++) {
            if (deg[i] > 1) {
                ans++;
            }
        }

        return ans;
    }
};

int main() {
    Solution ob;

    // Testcase Fail Fix:
    // N = 3, p[] = {-1, 0, 1} --> Expected Output: 1
    int N0 = 3;
    vector<int> p0 = {-1, 0, 1};
    cout << "Testcase N=3 p={-1,0,1} Min Moves: " << ob.solve(N0, p0) << "\n";

    // Example 1:
    // N = 5, p[] = {-1, 0, 0, 1, 1} --> Expected Output: 1
    int N1 = 5;
    vector<int> p1 = {-1, 0, 0, 1, 1};
    cout << "Example 1 Min Moves: " << ob.solve(N1, p1) << "\n";

    // Example 2:
    // N = 8, p[] = {-1, 0, 0, 0, 0, 2, 2, 5} --> Expected Output: 2
    int N2 = 8;
    vector<int> p2 = {-1, 0, 0, 0, 0, 2, 2, 5};
    cout << "Example 2 Min Moves: " << ob.solve(N2, p2) << "\n";

    return 0;
}
