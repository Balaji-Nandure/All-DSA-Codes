/**
 * Problem: Oliver and the Game (Subtree & Ancestor Queries on Trees)
 * Category: Graphs
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - We need to answer multiple queries in an unweighted tree asking whether a target node lies on the path from the current node towards the root or away from the root.
 * - Naive traversal per query takes O(N), leading to O(Q * N) TLE for Q = 500,000.
 * - Using Euler Tour entry and exit timestamps, ancestor queries can be answered in O(1) time per query.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Euler Tour Subtree Timestamps (tin / tout):
 *   - Root the tree at node 1 (the King's mansion).
 *   - Run DFS from the root, recording entry time `tin[u]` and exit time `tout[u]`.
 *   - Crucial Property: Node `u` is an ancestor of node `v` IF AND ONLY IF:
 *     `tin[u] <= tin[v] && tout[u] >= tout[v]`
 *   - Query Types:
 *     - Type 0: Oliver moves towards the King (root). Oliver finds Bob if Bob is an ancestor of Oliver (Bob lies on the path to root).
 *       => Check if `isAncestor(Bob, Oliver)`.
 *     - Type 1: Oliver moves away from the King (down into subtree). Oliver finds Bob if Oliver is an ancestor of Bob.
 *       => Check if `isAncestor(Oliver, Bob)`.
 * 
 * TIME COMPLEXITY:
 * - Preprocessing: O(N) single DFS.
 * - Query: O(1) per query => Total O(N + Q).
 * 
 * SPACE COMPLEXITY:
 * - O(N) for tree adjacency list and tin/tout timestamp arrays.
 */

#include <iostream>
#include <vector>

class OliverAndGame {
    int timer;
    std::vector<int> tin, tout;

    void dfs(int u, int p, const std::vector<std::vector<int>>& adj) {
        tin[u] = ++timer;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, adj);
            }
        }
        tout[u] = ++timer;
    }

public:
    OliverAndGame(int n, const std::vector<std::vector<int>>& adj) {
        timer = 0;
        tin.assign(n + 1, 0);
        tout.assign(n + 1, 0);
        // Preprocess Euler tour timestamps rooted at node 1
        dfs(1, 0, adj);
    }

    // u is ancestor of v if u enters before v and exits after v
    bool isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    bool canFind(int type, int X, int Y) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Type 0: Moving towards root -> Y must be an ancestor of X.
        // Type 1: Moving away from root -> X must be an ancestor of Y.
        if (type == 0) {
            return isAncestor(Y, X);
        } else {
            return isAncestor(X, Y);
        }
    }
};

int main() {
    int n = 9;
    std::vector<std::vector<int>> adj(n + 1);

    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(1, 2);
    addEdge(1, 3);
    addEdge(2, 6);
    addEdge(2, 7);
    addEdge(6, 9);
    addEdge(7, 8);
    addEdge(3, 4);
    addEdge(3, 5);

    OliverAndGame game(n, adj);

    // Query 1: type 0 (towards root), X = 9 (Oliver), Y = 2 (Bob) -> Bob is ancestor of Oliver: YES
    std::cout << "Query 1 (type 0, X=9, Y=2): " << (game.canFind(0, 9, 2) ? "YES" : "NO") << "\n"; // YES

    // Query 2: type 0, X = 9, Y = 3 -> Bob is NOT ancestor of Oliver: NO
    std::cout << "Query 2 (type 0, X=9, Y=3): " << (game.canFind(0, 9, 3) ? "YES" : "NO") << "\n"; // NO

    // Query 3: type 1 (away from root), X = 2, Y = 9 -> Oliver is ancestor of Bob: YES
    std::cout << "Query 3 (type 1, X=2, Y=9): " << (game.canFind(1, 2, 9) ? "YES" : "NO") << "\n"; // YES

    return 0;
}
