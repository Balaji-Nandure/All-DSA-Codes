/*
 * Problem: 491. Non-decreasing Subsequences
 * 
 * Given an integer array nums, return all the different possible non-decreasing 
 * subsequences of the given array with at least two elements. You may return 
 * the answer in any order.
 * 
 * Example 1:
 * Input: nums = [4,6,7,7]
 * Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
 * 
 * Example 2:
 * Input: nums = [4,4,3,2,1]
 * Output: [[4,4]]
 * 
 * Constraints:
 * - 1 <= nums.length <= 15
 * - -100 <= nums[i] <= 100
 */

#include <bits/stdc++.h>
using namespace std;

// Backtracking approach to find all non-decreasing subsequences
void backtrack(int start, vector<int>& nums, vector<int>& curr, 
               set<vector<int>>& result) {
    if (curr.size() >= 2) {
        result.insert(curr);
    }
    if (start == (int)nums.size()) {
        return;
    }
    for (int end = start; end < (int)nums.size(); end++) {
        if (curr.empty() || nums[end] >= curr.back()) {
            curr.push_back(nums[end]);
            backtrack(end + 1, nums, curr, result);
            curr.pop_back();
        }
    }
}


vector<vector<int>> findSubsequences(vector<int>& nums) {
    set<vector<int>> result;
    vector<int> curr;
    backtrack(0, nums, curr, result);
    return vector<vector<int>>(result.begin(), result.end());
}

// "Pick and not pick" approach to find all non-decreasing subsequences
void pickNotPick(int idx, vector<int>& nums, vector<int>& curr, set<vector<int>>& result) {
    if (idx == (int)nums.size()) {
        if (curr.size() >= 2)
            result.insert(curr);
        return;
    }
    // Pick the current element if it forms a non-decreasing subsequence
    if (curr.empty() || nums[idx] >= curr.back()) {
        curr.push_back(nums[idx]);
        pickNotPick(idx + 1, nums, curr, result);
        curr.pop_back();
    }
    // Not pick, but skip duplicate not-pick calls for the same value as previous if previous was not picked
    pickNotPick(idx + 1, nums, curr, result);
}

// Optional: Unused, but for illustration you could also use pickNotPick in an alternative function
vector<vector<int>> findSubsequencesPickNotPick(vector<int>& nums) {
    set<vector<int>> result;
    vector<int> curr;
    pickNotPick(0, nums, curr, result);
    return vector<vector<int>>(result.begin(), result.end());
}

// Helper function to print result
void printResult(vector<vector<int>>& result) {
    cout << "[";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << "[";
        for (int j = 0; j < (int)result[i].size(); j++) {
            cout << result[i][j];
            if (j < (int)result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < (int)result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    // Test case 1
    vector<int> nums1 = {4, 6, 7, 7};
    cout << "Test case 1:" << endl;
    cout << "Input: [4,6,7,7]" << endl;

    vector<int> nums1_copy = nums1;
    vector<vector<int>> result1 = findSubsequences(nums1_copy);
    cout << "Output: ";
    printResult(result1);
    cout << "Expected: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]" << endl;
    cout << endl;

    // Test case 2
    vector<int> nums2 = {4, 4, 3, 2, 1};
    cout << "Test case 2:" << endl;
    cout << "Input: [4,4,3,2,1]" << endl;

    vector<int> nums2_copy = nums2;
    vector<vector<int>> result2 = findSubsequences(nums2_copy);
    cout << "Output: ";
    printResult(result2);
    cout << "Expected: [[4,4]]" << endl;
    cout << endl;

    // Test case 3
    vector<int> nums3 = {1, 2, 3, 4};
    cout << "Test case 3:" << endl;
    cout << "Input: [1,2,3,4]" << endl;

    vector<int> nums3_copy = nums3;
    vector<vector<int>> result3 = findSubsequences(nums3_copy);
    cout << "Output: ";
    printResult(result3);
    cout << endl;

    return 0;
}
