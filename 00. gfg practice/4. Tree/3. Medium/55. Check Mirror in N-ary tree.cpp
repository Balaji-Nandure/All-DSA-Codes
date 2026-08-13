/*
    Problem Name: Check Mirror in N-ary tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two N-ary trees represented by e edges and two 1D arrays t1[] and t2[].
    Each pair (u, v) in the arrays (consecutive elements t1[2*i] and t1[2*i+1]) represents an edge
    from parent node u to child node v.
    Check whether the second tree is a mirror image of the first tree.

    Examples:
    Input: e = 2, t1[] = [1, 2, 1, 3], t2[] = [1, 3, 1, 2]
    Output: true (or 1)
    Explanation:
    - Tree 1: Children of 1 are [2, 3] (left to right).
    - Tree 2: Children of 1 are [3, 2] (left to right).
    Since [3, 2] is the reverse of [2, 3], the second tree is a mirror image of the first tree!

    Input: e = 2, t1[] = [1, 2, 1, 3], t2[] = [1, 2, 1, 3]
    Output: false (or 0)
    Explanation: Both trees have children [2, 3] in identical order, so they are not mirror images.

    Constraints:
    1 <= e <= 10^5

    Expected Complexities:
    Time Complexity: O(e), where e is the number of edges.
    Space Complexity: O(e), for the hash map of stacks.

    Love Babbar Style Approach:
    Map of Stacks for LIFO Child Comparison:

    1. INTUITION:
       - In a mirror image of an N-ary tree:
         * For every parent node `u`, its children in Tree 1 appear in LEFT-TO-RIGHT order.
         * Its children in Tree 2 must appear in REVERSE (RIGHT-TO-LEFT) order.
       - A `stack<int>` inherently reverses insertion order!
       - If we store Tree 1's children for node `u` in `unordered_map<int, stack<int>> mp`:
         * The top of `mp[u]` will be the LAST inserted child of `u` in Tree 1.
         * When processing Tree 2's children of `u`, the first child in Tree 2 MUST equal `mp[u].top()`.
       - If any child in Tree 2 fails to match `mp[u].top()`, return `0` / `false`.

    2. ALGORITHM:
       - `unordered_map<int, stack<int>> mp;`
       - Traverse `t1[]` (step by 2): `mp[t1[i]].push(t1[i + 1]);`
       - Traverse `t2[]` (step by 2):
         * `int u = t2[i], v = t2[i + 1];`
         * `if (mp[u].empty() || mp[u].top() != v) return 0;`
         * `mp[u].pop();`
       - Return `1` / `true`.

    Dry Run:
    e = 2, t1 = [1, 2, 1, 3], t2 = [1, 3, 1, 2]

    1. Build map from t1:
       - (1, 2) -> mp[1] = [2]
       - (1, 3) -> mp[1] = [2, 3] (top = 3)

    2. Validate against t2:
       - (1, 3) -> mp[1].top() is 3 == 3 ✓ -> pop 3. mp[1] = [2]
       - (1, 2) -> mp[1].top() is 2 == 2 ✓ -> pop 2. mp[1] = []

    Result: 1 (true) ✓
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
public:
    // GFG Signature - Map of Stacks Strategy
    int checkMirrorTree(int n, int e, int t1[], int t2[]) {
        unordered_map<int, stack<int>> mp;

        // Step 1: Push all edges of Tree 1 into stacks corresponding to each parent node
        for (int i = 0; i < 2 * e; i += 2) {
            int u = t1[i];
            int v = t1[i + 1];
            mp[u].push(v);
        }

        // Step 2: Compare children of Tree 2 against the top of the stack for each parent node
        for (int i = 0; i < 2 * e; i += 2) {
            int u = t2[i];
            int v = t2[i + 1];

            // If node u has no remaining children or top does not match v, not a mirror
            if (mp[u].empty() || mp[u].top() != v) {
                return 0;
            }

            mp[u].pop();
        }

        return 1;
    }

    // Overload for vector signature
    int checkMirrorTree(int e, vector<int>& t1, vector<int>& t2) {
        return checkMirrorTree(e + 1, e, t1.data(), t2.data());
    }
};

int main() {
    Solution ob;

    // Example 1:
    // e = 2, t1 = [1, 2, 1, 3], t2 = [1, 3, 1, 2]
    // Expected Output: 1 (true)
    int e1 = 2;
    int t1_1[] = {1, 2, 1, 3};
    int t2_1[] = {1, 3, 1, 2};

    cout << "Example 1 Check Mirror: " << ob.checkMirrorTree(3, e1, t1_1, t2_1) << "\n";

    // Example 2:
    // e = 2, t1 = [1, 2, 1, 3], t2 = [1, 2, 1, 3]
    // Expected Output: 0 (false)
    int e2 = 2;
    int t1_2[] = {1, 2, 1, 3};
    int t2_2[] = {1, 2, 1, 3};

    cout << "Example 2 Check Mirror: " << ob.checkMirrorTree(3, e2, t1_2, t2_2) << "\n";

    return 0;
}
