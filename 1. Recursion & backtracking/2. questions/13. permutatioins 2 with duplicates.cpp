#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
using namespace std;

/*
    Generate all unique permutations of an array that may contain duplicates.

    Three methods:

    1. Used[] + sort:
       At each level (decision), DO NOT choose the second or later duplicate 
       before having chosen the first occurrence at that level.
       Only allow picking nums[i] if it is not used,
       and if it is a duplicate (same as previous value) only pick it
       if the previous copy has been used in this branch.

       This avoids permuting duplicate numbers in different order at the same recursion level,
       which would lead to duplicate permutations in the result.

    2. Map-based method:
       Use a frequency map (unordered_map<int, int>) to track available numbers.
       At each step, pick any unused number with count > 0, decrement count, recurse,
       then backtrack (restore count).
       No need to sort for the map-based method.

    3. Unordered_set in for loop:
       At each recursion level, use a set to record which numbers have been used
       at this level, so as to skip duplicate choices and ensure uniqueness
       without sorting. This avoids re-picking a duplicate at the same branch level.
*/

// ---------- Method 1: Used[] + Sort ----------
void backtrack(vector<int>& nums, vector<bool>& used, vector<int>& curr, vector<vector<int>>& result) {
    // Base case: current permutation is complete
    if (curr.size() == nums.size()) {
        result.push_back(curr);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        // Skip if already used in current permutation
        if (used[i]) continue;

        // IMPORTANT:
        // For duplicates: 
        // Only allow picking nums[i] if it's not a duplicate, 
        // OR if it's same as previous and previous occurrence has been used.
        // This ensures that we ALWAYS pick the first unused duplicate first at a given recursion level.
        // If we picked nums[1] before nums[0] when both are duplicates, they would generate identical subtrees.
        if (i > 0 && nums[i] == nums[i-1] && !used[i-1])
            continue; // skip using a duplicate before its previous copy at the same level

        // Mark as used and add to current permutation
        used[i] = true;
        curr.push_back(nums[i]);
        backtrack(nums, used, curr, result);
        // Backtrack: unmark and remove last
        curr.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> result;
    // Sort the array so that duplicates are adjacent
    sort(nums.begin(), nums.end());
    vector<bool> used(nums.size(), false);
    vector<int> curr;
    backtrack(nums, used, curr, result);
    return result;
}

// ---------- Method 2: Map-based method (frequency map) ----------
void backtrack_map(unordered_map<int, int>& freq, vector<int>& curr, int n, vector<vector<int>>& result) {
    // Base case: current permutation is complete
    if (curr.size() == n) {
        result.push_back(curr);
        return;
    }
    // Try picking any number with count > 0
    for (auto& pair : freq) { 
        int num = pair.first;
        int& count = pair.second;
        if (count == 0) continue;

        // Pick number, decrease count, recurse, then backtrack
        curr.push_back(num);
        count--;
        backtrack_map(freq, curr, n, result);
        count++;
        curr.pop_back();
    }
}

vector<vector<int>> permuteUnique_map(vector<int>& nums) {
    unordered_map<int, int> freq;
    for (int num : nums) freq[num]++;
    vector<vector<int>> result;
    vector<int> curr;
    backtrack_map(freq, curr, nums.size(), result);
    return result;
}

// ---------- Method 3: set in for loop (to avoid duplicates at each recursion level) ----------
void backtrack_setfor(vector<int>& nums, vector<bool>& used, vector<int>& curr, vector<vector<int>>& result) {
    if (curr.size() == nums.size()) {
        result.push_back(curr);
        return;
    }
    set<int> unique; // Only at this level
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) continue;
        if (unique.count(nums[i])) continue; // Skip if already picked this val at this level
        unique.insert(nums[i]);
        used[i] = true;
        curr.push_back(nums[i]);
        backtrack_setfor(nums, used, curr, result);
        curr.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permuteUnique_setfor(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> curr;
    vector<bool> used(nums.size(), false);
    backtrack_setfor(nums, used, curr, result);
    return result;
}

int main() {
    vector<int> nums = {1, 1, 2};

    // Method 1: used[] + sort
    cout << "Permutations using used[] method:" << endl;
    vector<vector<int>> ans = permuteUnique(nums);
    for (const auto& vec : ans) {
        for (int num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }

    // Method 2: map-based method
    cout << "\nPermutations using map-based method:" << endl;
    vector<vector<int>> ans2 = permuteUnique_map(nums);
    for (const auto& vec : ans2) {
        for (int num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }

    // Method 3: set-in-for-loop method
    cout << "\nPermutations using set-in-for-loop method:" << endl;
    vector<vector<int>> ans3 = permuteUnique_setfor(nums);
    for (const auto& vec : ans3) {
        for (int num : vec) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}