/*
    Problem Name: Duplicate rows in a binary matrix
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a boolean matrix mat[][] of size n x m, where each element is either 0 or 1, identify all rows
    that are duplicates of a previously occurring row.
    Return the 0-based indices of such duplicate rows in the order they occur.

    Examples:
    Input: mat[][] = [[1, 0],
                      [1, 0]]
    Output: [1]
    Explanation: Row 1 is a duplicate of Row 0.

    Input: mat[][] = [[1, 0, 0],
                      [1, 0, 0],
                      [0, 0, 0],
                      [0, 0, 0]]
    Output: [1, 3]
    Explanation: Row 1 and Row 3 are duplicates of Row 0 and Row 2 respectively.

    Input: mat[][] = [[1, 1],
                      [0, 0],
                      [0, 0],
                      [1, 1],
                      [1, 1]]
    Output: [2, 3, 4]
    Explanation: Row 2 is duplicate of Row 1; Rows 3 and 4 are duplicates of Row 0.

    Constraints:
    1 <= n, m <= 1000
    mat[i][j] = {0, 1}

    Expected Complexities:
    Time Complexity: O(N * M), inserting each row of length M into Trie / Set.
    Space Complexity: O(N * M), for Trie nodes / Set storage.

    Approach 1: Binary Trie Data Structure (Optimal O(N * M) - Striver & Love Babbar)
    Approach 2: HashSet / Map of Rows (O(N * M) - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Binary Trie Approach (Optimal):
       - Build a Binary Trie where each node has 2 children (0 and 1).
       - For each row `i` from `0` to `n - 1`:
         * Insert the binary values of row `i` bit-by-bit into the Trie.
         * If the leaf node corresponding to the end of row `i` ALREADY has `isEnd == true`, then row `i`
           is a DUPLICATE -> append index `i` to `ans`.
         * Else: mark `isEnd = true` (first occurrence of this row).
    2. Set Approach:
       - Maintain `set<vector<int>> seen`.
       - For each row `i`, if `seen.count(mat[i])` is true, add `i` to duplicate indices; else insert `mat[i]`.
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Trie Node for Binary Matrix Rows
struct TrieNode {
    TrieNode* children[2];
    bool isEnd;

    TrieNode() {
        children[0] = children[1] = NULL;
        isEnd = false;
    }
};
// ============================================================================
// Approach 2: HashSet of Rows (O(N * M) - Striver & Love Babbar)
// ============================================================================
class SolutionSet {
public:
    vector<int> repeatedRows(vector<vector<int>>& mat, int n, int m) {
        set<vector<int>> seen;
        vector<int> duplicates;

        for (int i = 0; i < n; i++) {
            if (seen.count(mat[i])) {
                duplicates.push_back(i);
            } else {
                seen.insert(mat[i]);
            }
        }

        return duplicates;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    vector<int> repeatedRows(vector<vector<int>>& mat, int n, int m) {
        SolutionTrie solver;
        return solver.repeatedRows(mat, n, m);
    }

    vector<int> repeatedRows(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        return repeatedRows(mat, n, m);
    }
};

// Helper function to print vector
void printVector(const vector<int>& vec) {
    cout << "[ ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << "]\n";
}

int main() {
    // Example 1:
    // Expected Output: [ 1 ]
    vector<vector<int>> mat1 = {
        {1, 0},
        {1, 0}
    };
    int n1 = 2, m1 = 2;

    SolutionTrie solver1;
    cout << "Example 1 Duplicate Row Indices (Trie): ";
    printVector(solver1.repeatedRows(mat1, n1, m1));

    // Example 2:
    // Expected Output: [ 1 3 ]
    vector<vector<int>> mat2 = {
        {1, 0, 0},
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int n2 = 4, m2 = 3;

    cout << "Example 2 Duplicate Row Indices (Trie): ";
    printVector(solver1.repeatedRows(mat2, n2, m2));

    // Example 3:
    // Expected Output: [ 2 3 4 ]
    vector<vector<int>> mat3 = {
        {1, 1},
        {0, 0},
        {0, 0},
        {1, 1},
        {1, 1}
    };
    int n3 = 5, m3 = 2;

    SolutionSet solver2;
    cout << "Example 3 Duplicate Row Indices (Set): ";
    printVector(solver2.repeatedRows(mat3, n3, m3));

    return 0;
}
