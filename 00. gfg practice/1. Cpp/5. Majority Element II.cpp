/*
Majority Element II

Difficulty: Medium

Given an array of integers, find all elements that appear more than n/3 times.
Return the elements in sorted order. If no such element exists, return {-1}.

Examples:

Input: nums = [3, 2, 3]
Output: [3]
Explanation: 3 appears 2 times which is more than 3/3 = 1

Input: nums = [1, 1, 1, 3, 3, 2, 2, 2]
Output: [1, 2]
Explanation: 1 and 2 both appear 3 times which is more than 8/3 = 2

Input: nums = [1, 2, 3]
Output: [-1]
Explanation: No element appears more than 3/3 = 1 time
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> findMajority(vector<int>& nums) {
    int n = nums.size();
    int candidate1 = 0, candidate2 = 0;
    int count1 = 0, count2 = 0;
    
    // Boyer-Moore Voting Algorithm for finding up to 2 candidates
    for (int num : nums) {
        if (num == candidate1) {
            count1++;
        } else if (num == candidate2) {
            count2++;
        } else if (count1 == 0) {
            candidate1 = num;
            count1 = 1;
        } else if (count2 == 0) {
            candidate2 = num;
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }
    
    // Verify the candidates
    count1 = 0;
    count2 = 0;
    for (int num : nums) {
        if (num == candidate1) count1++;
        else if (num == candidate2) count2++;
    }
    
    vector<int> result;
    int threshold = n / 3;
    
    if (count1 > threshold) result.push_back(candidate1);
    if (count2 > threshold) result.push_back(candidate2);
    
    sort(result.begin(), result.end());
    return result;
}




