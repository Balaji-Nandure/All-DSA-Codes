// Problem: Find Majority Element (Boyer-Moore Voting Algorithm)
// Link (GFG): https://www.geeksforgeeks.org/problems/majority-element-1587115620/1
// Article: https://www.geeksforgeeks.org/dsa/majority-element/
// Difficulty: Medium
// Topic: Searching, Greedy, Boyer-Moore Majority Vote, Invariant Counting

/*
Problem Statement:
Given an array A of N elements. Find the majority element in the array.
A majority element in an array A of size N is an element that appears 
STRICTLY MORE THAN N / 2 times in the array.
If no such element exists, return -1.

Example 1:
Input: N = 3, A = [1, 2, 3]
Output: -1
Explanation: No element appears more than 3 / 2 = 1.5 times.

Example 2:
Input: N = 5, A = [3, 1, 3, 3, 2]
Output: 3
Explanation: 3 appears 3 times, which is > 5 / 2 = 2.5.

Constraints:
- 1 <= N <= 10^7
- 0 <= A[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Arrays Problem 25 (Elements Appearing More than N/K Times):
//   * We maintained K - 1 candidate slots using a generalized voting state machine.
// - In Problem 8 (Standard Majority Element > N/2):
//   * There can be AT MOST ONE such element because (N/2 + 1) * 2 > N!
//   * Robert S. Boyer and J Strother Moore's 1981 voting algorithm solves this 
//     with a single variable pair `{candidate, count}` in strictly O(1) memory!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Hash Map Frequency Count
//   - Count elements in `unordered_map<int, int>`.
//   - Complexity: O(N) time, O(N) auxiliary space.
//   - Why Suboptimal: For N = 10^7, allocating a 10M-entry hash map consumes hundreds 
//     of megabytes of RAM and triggers cache thrashing.
//
// Approach 2: Sorting
//   - Sort array: If a majority element exists, it MUST occupy the middle index `arr[N / 2]`.
//   - Complexity: O(N log N) time. Far too slow for N = 10^7.
//
// Approach 3: Boyer-Moore Voting Algorithm (Optimal & Chosen)
//   - Pass 1 (Candidate Elimination):
//       * If `count == 0`: Assign `candidate = arr[i]`, `count = 1`.
//       * If `arr[i] == candidate`: `count++`.
//       * If `arr[i] != candidate`: `count--` (pair-wise annihilation: 1 majority cancels with 1 non-majority).
//   - Pass 2 (Verification):
//       * Count actual occurrences of `candidate`. If `count > N / 2`, return it; else return -1.
//   - Complexity: O(N) time, O(1) auxiliary space!
//   - Why this approach: Theoretical minimum time and space; handles N = 10^7 in < 20 ms.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& a, int size) {
        int candidate = -1;
        int count = 0;

        // Pass 1: Find the predominant candidate via pairwise cancellation
        for (int i = 0; i < size; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // When count drops to 0, all previous elements have completely cancelled each other out.
            // Adopt the current element as the new prospective majority candidate.
            if (count == 0) {
                candidate = a[i];
                count = 1;
            } else if (a[i] == candidate) {
                count++;
            } else {
                count--; // Cancel this element against candidate
            }
        }

        // Pass 2: Verify if the candidate appears strictly more than N / 2 times
        int actualFreq = 0;
        for (int i = 0; i < size; ++i) {
            if (a[i] == candidate) {
                actualFreq++;
            }
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Strict inequality check: Majority element requires strictly > size / 2 occurrences.
        if (actualFreq > size / 2) {
            return candidate;
        }

        return -1; // No majority element exists
    }
};

int main() {
    Solution sol;
    vector<int> a1 = {3, 1, 3, 3, 2};
    cout << "Majority in a1: " << sol.majorityElement(a1, a1.size()) << "\n";

    vector<int> a2 = {1, 2, 3};
    cout << "Majority in a2: " << sol.majorityElement(a2, a2.size()) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N) = 2N total operations (Pass 1 candidate identification + Pass 2 verification).
- Space Complexity: O(1) auxiliary space (only 2 scalar variables: `candidate` and `count`).

Key Takeaways:
- Because the majority element appears more than N/2 times, even if all other N - (N/2 + 1)
  elements team up to cancel it, the majority element will still emerge victorious with count >= 1.
*/
