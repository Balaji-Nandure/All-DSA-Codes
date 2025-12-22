/*
 * Problem: Subsets II
 * 
 * LeetCode 90: Subsets II
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/subsets-1587115621/1
 *
 * Given an integer array nums that may contain duplicates, return all possible subsets.
 * The solution set must not contain duplicate subsets.
 * 
 * Example: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 * Time: O(2^n * n) - 2^n subsets, each copied in O(n)
 * Space: O(n) - recursion stack depth
 */

#include <bits/stdc++.h>
using namespace std;

// Method 1: Pick / Not Pick with duplicate handling
void findSubsets(int i, vector<int>& nums, vector<int>& curr, vector<vector<int>>& result) {
    // Base case: processed all elements, add current subset
    if (i == (int)nums.size()) {
        result.push_back(curr);
        return;
    }

    // PICK: Include nums[i] in subset
    curr.push_back(nums[i]);
    findSubsets(i + 1, nums, curr, result);
    curr.pop_back(); // Backtrack

    // NOT PICK: Skip nums[i] and all its duplicates
    // Jump to first different value to avoid generating duplicate subsets
    int next = i + 1;
    while (next < (int)nums.size() && nums[next] == nums[i]) {
        next++;
    }
    findSubsets(next, nums, curr, result);
}

vector<vector<int>> subsetsWithDup_pickNotPick(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // sort to group duplicates together
    vector<vector<int>> result;
    vector<int> curr;
    findSubsets(0, nums, curr, result);
    return result;
}

// Method 2: Loop-based with duplicate handling
void findSubsets_loop(int start, vector<int>& nums, vector<int>& curr, vector<vector<int>>& result) {
    // Add current subset to result (captures all subsets formed so far)
    result.push_back(curr);

    // Base case: processed all elements
    if (start == (int)nums.size()) {
        return;
    }

    // Try each element from start position
    for (int i = start; i < (int)nums.size(); i++) {
        // Skip duplicates at same level to avoid duplicate subsets
        // Only skip if it's not the first occurrence at this level
        if (i > start && nums[i] == nums[i - 1]) {
            continue;
        }

        curr.push_back(nums[i]);
        findSubsets_loop(i + 1, nums, curr, result);
        curr.pop_back(); // Backtrack
    }
}

vector<vector<int>> subsetsWithDup_loop(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // sort to group duplicates together
    vector<vector<int>> result;
    vector<int> curr;
    findSubsets_loop(0, nums, curr, result);
    return result;
}

// -------------------------------------------------------
// MAIN FUNCTION
// -------------------------------------------------------
int main() {
    vector<int> nums = {1, 2, 2};
    int n = nums.size();

    cout << "Input: nums = [";
    for (int i = 0; i < n; i++) {
        cout << nums[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n\n";

    cout << "Using Pick/Not-Pick Method:\n";
    vector<vector<int>> res1 = subsetsWithDup_pickNotPick(nums);
    for (auto& subset : res1) {
        cout << "[";
        for (int i = 0; i < (int)subset.size(); i++) {
            cout << subset[i];
            if (i < (int)subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";

    cout << "Using Loop Method:\n";
    vector<vector<int>> res2 = subsetsWithDup_loop(nums);
    for (auto& subset : res2) {
        cout << "[";
        for (int i = 0; i < (int)subset.size(); i++) {
            cout << subset[i];
            if (i < (int)subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n\n";

    // Test case 2
    cout << "Test case 2:\n";
    vector<int> nums2 = {0};
    cout << "Input: nums = [0]\n";
    vector<vector<int>> res3 = subsetsWithDup_pickNotPick(nums2);
    cout << "Output: ";
    for (auto& subset : res3) {
        cout << "[";
        for (int i = 0; i < (int)subset.size(); i++) {
            cout << subset[i];
            if (i < (int)subset.size() - 1) cout << ",";
        }
        cout << "] ";
    }
    cout << "\n";

    return 0;
}

