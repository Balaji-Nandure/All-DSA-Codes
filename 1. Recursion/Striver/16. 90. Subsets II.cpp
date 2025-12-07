/*
 * Problem: 90. Subsets II
 * 
 * Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 * 
 * Example 1:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * 
 * Example 2:
 * Input: nums = [0]
 * Output: [[],[0]]
 */

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// METHOD 1: Pick / Not Pick with Duplicate Handling
// -------------------------------------------------------
void findSubsets(int i, vector<int>& nums, vector<int>& curr, vector<vector<int>>& result) {
    // Base case: reached end of array
    if (i == (int)nums.size()) {
        result.push_back(curr);
        return;
    }

    // PICK: include nums[i] in the subset
    curr.push_back(nums[i]);
    findSubsets(i + 1, nums, curr, result);
    curr.pop_back();

    // NOT PICK: skip nums[i] and all its duplicates
    // Jump over all consecutive duplicates to avoid duplicate subsets
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

// -------------------------------------------------------
// METHOD 2: Loop Method with Duplicate Handling
// -------------------------------------------------------
void findSubsets_loop(int start, vector<int>& nums, vector<int>& curr, vector<vector<int>>& result) {
    // Add current subset to result
    result.push_back(curr);

    // Base case: reached end
    if (start == (int)nums.size()) {
        return;
    }

    // Try all elements from start to end
    for (int i = start; i < (int)nums.size(); i++) {
        // Skip duplicates at the same level
        // Only skip if it's not the first occurrence at this level
        if (i > start && nums[i] == nums[i - 1]) {
            continue;
        }

        curr.push_back(nums[i]);
        findSubsets_loop(i + 1, nums, curr, result);
        curr.pop_back();
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

