/*
 * Problem: Permutations II (with Duplicates)
 *
 * LeetCode 47: Permutations II
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/permutations-of-a-given-string/0
 *
 * Generate all unique permutations of an array that may contain duplicates.
 *
 * Three methods to handle duplicates:
 * 1. Used[] + Sort: Only pick duplicate if previous occurrence is used
 * 2. Map-based: Use frequency map to track available numbers
 * 3. Set in loop: Track used values at each recursion level
 *
 * Time: O(n! * n) - n! permutations, each copied in O(n)
 * Space: O(n) - recursion stack depth is n
 */

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>
using namespace std;

// Method 1: Used[] + Sort approach
void backtrack(vector<int>& nums, vector<bool>& used, vector<int>& curr, vector<vector<int>>& result) {
    // Base case: permutation complete
    if (curr.size() == nums.size()) {
        result.push_back(curr);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        // Skip if already used in current permutation
        if (used[i]) continue;

        // Key: For duplicates, only pick if previous occurrence is used
        // This ensures we always pick first occurrence before duplicates at same level
        // Prevents generating duplicate permutations
        if (i > 0 && nums[i] == nums[i-1] && !used[i-1])
            continue; // Skip duplicate before its previous copy is used

        // Pick nums[i] and recurse
        used[i] = true;
        curr.push_back(nums[i]);
        backtrack(nums, used, curr, result);
        // Backtrack: unmark and remove
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

// Method 2: Map-based (frequency map) - no sorting needed
void backtrack_map(unordered_map<int, int>& freq, vector<int>& curr, int n, vector<vector<int>>& result) {
    // Base case: permutation complete
    if (curr.size() == n) {
        result.push_back(curr);
        return;
    }
    // Try each unique number with count > 0
    for (auto& pair : freq) { 
        int num = pair.first;
        int& count = pair.second;
        if (count == 0) continue; // Skip if no more available

        // Pick number, decrement count, recurse
        curr.push_back(num);
        count--;
        backtrack_map(freq, curr, n, result);
        // Backtrack: restore count
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

// Method 3: Set in for loop - track used values at each level
void backtrack_setfor(vector<int>& nums, vector<bool>& used, vector<int>& curr, vector<vector<int>>& result) {
    // Base case: permutation complete
    if (curr.size() == nums.size()) {
        result.push_back(curr);
        return;
    }
    set<int> unique; // Track values used at this recursion level
    for (int i = 0; i < nums.size(); ++i) {
        if (used[i]) continue; // Skip if already used in permutation
        // Skip if this value already picked at current level (avoids duplicates)
        if (unique.count(nums[i])) continue;
        unique.insert(nums[i]); // Mark value as used at this level
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