#include <bits/stdc++.h>
using namespace std;

// Approach 1: for-loop backtracking

void backtrack(vector<int>& a, int target, int index,
               vector<int>& curr, vector<vector<int>>& ans) {
    if (target == 0) {
        ans.push_back(curr);
        return;
    }

    for (int i = index; i < (int)a.size(); ++i) {
        if (i > index && a[i] == a[i - 1]) continue; // skip duplicates at this level
        if (a[i] > target) break;                    // pruning: array is sorted

        curr.push_back(a[i]);
        backtrack(a, target - a[i], i + 1, curr, ans);
        curr.pop_back();
    }
}

// Approach 2: pick / not-pick with duplicate skip in "not pick" branch
// this mehod is more intuitive and easy to understand.
void solve(int i, vector<int>& a, int target,
           vector<int>& curr, vector<vector<int>>& ans) {
    if (target == 0) {
        ans.push_back(curr);
        return;
    }
    if (i >= (int)a.size() || target < 0) return;

    // pick
    curr.push_back(a[i]);
    solve(i + 1, a, target - a[i], curr, ans);
    curr.pop_back();

    // not pick: jump over all equal values
    int next = i + 1; // move to first index with different value
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