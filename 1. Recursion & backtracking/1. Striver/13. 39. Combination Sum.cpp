/*
 * Problem: Combination Sum
 * 
 * LeetCode 39: Combination Sum
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/combination-sum/0
 *
 * Find all unique combinations where candidate numbers sum to target.
 * The same number may be reused unlimited times.
 *
 * Time: O(2^target) - exponential in worst case
 * Space: O(target) - recursion stack depth
 */

#include <bits/stdc++.h>
using namespace std;

// Method 1: Pick / Not Pick approach
void findCombinations(int idx, vector<int>& candidates, int target,
                      vector<int>& current, vector<vector<int>>& result) {
    // Base case: target achieved, add current combination
    if (target == 0) {
        result.push_back(current);
        return;
    }
    // Base case: no more candidates or target becomes negative
    if (idx == candidates.size() || target < 0) {
        return;
    }

    // PICK: Include candidates[idx] (reuse allowed, so stay at idx)
    if (target - candidates[idx] >= 0) {
        current.push_back(candidates[idx]);
        // Stay at idx to allow reuse of same element
        findCombinations(idx, candidates, target - candidates[idx], current, result);
        current.pop_back(); // Backtrack
    }

    // NOT PICK: Skip candidates[idx] and move to next index
    findCombinations(idx + 1, candidates, target, current, result);
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> current;
    findCombinations(0, candidates, target, current, result);
    return result;
}


// Method 2: Loop-based approach (generally faster)
void dfsLoop(int start, vector<int>& a, int target,
             vector<int>& curr, vector<vector<int>>& ans) {
    // Base case: target achieved, add combination
    if (target == 0) {
        ans.push_back(curr);
        return;
    }
    // Pruning: if target becomes negative, no solution possible
    if (target < 0) return;

    // Try each candidate from start position
    for (int i = start; i < (int)a.size(); i++) {
        // Pruning: if sorted and a[i] > target, skip rest (all larger)
        // if (a[i] > target) break;

        curr.push_back(a[i]);
        // Stay at i to allow reuse of same element
        dfsLoop(i, a, target - a[i], curr, ans);
        curr.pop_back(); // Backtrack
    }
}

vector<vector<int>> combinationSumLoop(vector<int>& candidates, int target) {
    // sort(candidates.begin(), candidates.end());   // good for pruning
    vector<vector<int>> ans;
    vector<int> curr;
    dfsLoop(0, candidates, target, curr, ans);
    return ans;
}


// -------------------------------------------------------
// MAIN FUNCTION
// -------------------------------------------------------
int main() {
    vector<int> candidates = {4, 5, 6, 7, 8, 9, 10};
    int target = 12;

    cout << "Using Pick/Not-Pick Method:\n";
    vector<vector<int>> res1 = combinationSum(candidates, target);
    for (auto& comb : res1) {
        cout << "[ ";
        for (int x : comb) cout << x << " ";
        cout << "]\n";
    }

    cout << "\nUsing Loop Method:\n";
    vector<vector<int>> res2 = combinationSumLoop(candidates, target);
    for (auto& comb : res2) {
        cout << "[ ";
        for (int x : comb) cout << x << " ";
        cout << "]\n";
    }

    return 0;
}
