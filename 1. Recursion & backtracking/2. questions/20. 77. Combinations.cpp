/*
 * Problem: 77. Combinations
 *
 * Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].
 * You may return the answer in any order.
 *
 * Example:
 * Input: n = 4, k = 2
 * Output:
 * [
 *   [1,2],
 *   [1,3],
 *   [1,4],
 *   [2,3],
 *   [2,4],
 *   [3,4]
 * ]
 *
 * Constraints:
 * - 1 <= n <= 20
 * - 1 <= k <= n
 */

#include <bits/stdc++.h>
using namespace std;

// Backtracking function to generate all combinations
void backtrack(int start, int n, int k, vector<int>& current, vector<vector<int>>& result) {
    if ((int)current.size() == k) {
        result.push_back(current);
        return;
    }
    // Prune: if not enough elements remaining, stop recursion early
    for (int i = start; i <= n - (k - current.size()) + 1; ++i) {
        current.push_back(i);
        backtrack(i + 1, n, k, current, result);
        current.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> current;
    backtrack(1, n, k, current, result);
    return result;
}

// Helper function to print combinations
void printCombinations(const vector<vector<int>>& combs) {
    cout << "[";
    for (int i = 0; i < (int)combs.size(); ++i) {
        cout << "[";
        for (int j = 0; j < (int)combs[i].size(); ++j) {
            cout << combs[i][j];
            if (j < (int)combs[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < (int)combs.size() - 1) cout << ",";
    }
    cout << "]";
    cout << endl;
}

int main() {
    int n1 = 4, k1 = 2;
    cout << "Test case 1: n = 4, k = 2" << endl;
    auto result1 = combine(n1, k1);
    printCombinations(result1);
    cout << "Expected: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]" << endl;
    cout << endl;

    int n2 = 5, k2 = 3;
    cout << "Test case 2: n = 5, k = 3" << endl;
    auto result2 = combine(n2, k2);
    printCombinations(result2);
    cout << endl;

    int n3 = 1, k3 = 1;
    cout << "Test case 3: n = 1, k = 1" << endl;
    auto result3 = combine(n3, k3);
    printCombinations(result3);
    cout << "Expected: [[1]]" << endl;
    cout << endl;

    return 0;
}
