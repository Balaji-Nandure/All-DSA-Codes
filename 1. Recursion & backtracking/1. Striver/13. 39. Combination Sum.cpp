/*
 * Problem: Combination Sum
 * 
 * LeetCode 39: Combination Sum
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/combination-sum/0
 */

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// METHOD 1: Pick / Not Pick (your original method)
// -------------------------------------------------------
void findCombinations(int idx, vector<int>& candidates, int target,
                      vector<int>& current, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    if (idx == candidates.size() || target < 0) {
        return;
    }

    // Pick the element at idx (reuse allowed)
    if (target - candidates[idx] >= 0) {
        current.push_back(candidates[idx]);
        findCombinations(idx, candidates, target - candidates[idx], current, result);
        current.pop_back();
    }

    // Not pick → move to next index
    findCombinations(idx + 1, candidates, target, current, result);
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> current;
    findCombinations(0, candidates, target, current, result);
    return result;
}


// Generally this method is faster.
// -------------------------------------------------------
// METHOD 2: Loop Method (also valid for LC-39)
// -------------------------------------------------------
void dfsLoop(int start, vector<int>& a, int target,
             vector<int>& curr, vector<vector<int>>& ans) {

    if (target == 0) { // found answer
        ans.push_back(curr);
        return;
    }
    if (target < 0) return; // no point continuing

    for (int i = start; i < (int)a.size(); i++) {
        // if (a[i] > target) break; // pruning if sorted // only if array is sorted

        curr.push_back(a[i]);
        dfsLoop(i, a, target - a[i], curr, ans);   // reuse allowed → stay at i
        curr.pop_back();
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
