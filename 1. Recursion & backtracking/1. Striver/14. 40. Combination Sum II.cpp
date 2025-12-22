/*
 * Problem: Combination Sum II
 * 
 * LeetCode 40: Combination Sum II
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/combination-sum-part-2/0
 *
 * Find all unique combinations where candidate numbers sum to target.
 * Each number may only be used once. Array may contain duplicates.
 *
 * Time: O(2^n) - exponential
 * Space: O(target) - recursion stack depth
 */

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Loop-based backtracking
void backtrack(vector<int>& a, int target, int index, vector<int>& curr, vector<vector<int>>& ans) {
    // Base case: target achieved
    if (target == 0) {
        ans.push_back(curr);
        return;
    }

    // Try each candidate from index
    for (int i = index; i < (int)a.size(); ++i) {
        // Skip duplicates at same level to avoid duplicate combinations
        // Only skip if it's not the first occurrence at this level
        if (i > index && a[i] == a[i - 1]) continue;
        // Pruning: if sorted and current element > target, skip rest
        if (a[i] > target) break;

        curr.push_back(a[i]);
        // Move to i+1 (no reuse allowed)
        backtrack(a, target - a[i], i + 1, curr, ans);
        curr.pop_back(); // Backtrack
    }
}

// Approach 2: Pick / Not Pick (more intuitive)
void solve(int i, vector<int>& a, int target, vector<int>& curr, vector<vector<int>>& ans) {
    // Base case: target achieved
    if (target == 0) {
        ans.push_back(curr);
        return;
    }
    // Base case: no more elements or target negative
    if (i >= (int)a.size() || target < 0) return;

    // PICK: Include a[i] in combination
    curr.push_back(a[i]);
    solve(i + 1, a, target - a[i], curr, ans);
    curr.pop_back(); // Backtrack

    // NOT PICK: Skip a[i] and all its duplicates
    // Jump to first index with different value to avoid duplicate combinations
    int next = i + 1;
    while (next < (int)a.size() && a[next] == a[i]) next++;
    solve(next, a, target, curr, ans);
}

vector<vector<int>> combinationSum2_backtrack(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end()); // sort to group duplicates
    vector<vector<int>> ans;
    vector<int> curr;
    backtrack(candidates, target, 0, curr, ans);
    return ans;
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans;
    vector<int> curr;
    solve(0, candidates, target, curr, ans);
    return ans;
}

int main() {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    cout << "Using pick/not-pick style:\n";
    auto res1 = combinationSum2(candidates, target);
    for (auto& comb : res1) {
        cout << "[ ";
        for (int x : comb) cout << x << " ";
        cout << "]\n";
    }

    cout << "\nUsing for-loop backtracking style:\n";
    auto res2 = combinationSum2_backtrack(candidates, target);
    for (auto& comb : res2) {
        cout << "[ ";
        for (int x : comb) cout << x << " ";
        cout << "]\n";
    }

    return 0;
}