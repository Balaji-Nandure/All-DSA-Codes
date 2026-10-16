// Problem: Given an Array of Size N and Number K, Find All Elements That Appear More Than N/K Times
// Link (Article): https://www.geeksforgeeks.org/dsa/given-an-array-of-of-size-n-finds-all-the-elements-that-appear-more-than-nk-times/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/count-element-occurences/1
// Link (LeetCode 229 - Majority Element II for k = 3): https://leetcode.com/problems/majority-element-ii/
// Difficulty: Medium / Hard
// Topic: Array, Hash Table, Boyer-Moore Voting Algorithm

/*
Problem Statement:
Given an array `arr[]` of size `n` and an integer `k`. Find all elements in the array that appear 
strictly more than `n / k` times.

Note:
By mathematical pigeonhole principle, there can be AT MOST `k - 1` such elements!
(If there were k elements each appearing > n/k times, total count > k * (n/k) = n, a contradiction!).

Example 1:
Input: arr = [3, 1, 2, 2, 1, 2, 3, 3], k = 4
Output: [2, 3]
Explanation: n = 8, n / k = 8 / 4 = 2. Elements appearing > 2 times are 2 (appears 3 times) and 3 (appears 3 times).

Example 2:
Input: arr = [2, 3, 3, 2], k = 3
Output: [2, 3]
Explanation: n = 4, n / 3 = 1. Elements appearing > 1 time are 2 and 3.

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^9
- 1 <= k <= arr.size()
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 18: We used hash maps to find pairs summing to target.
// - In Problem 25:
//   * We are finding HEAVY HITTERS (majority elements).
//   * While a standard hash map takes O(N) space, the Boyer-Moore Voting Algorithm allows us
//     to solve this in O(1) extra space for k=2 or k=3, and O(K) space for arbitrary K!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Hash Map (O(N) Time, O(N) Space - Direct & Practical)
//   - Count frequencies using `unordered_map<int, int>`.
//   - Filter elements where `count > n / k`.
//
// Approach 2: Generalized Boyer-Moore Voting Algorithm (O(N * K) Time, O(K) Space - THEORETICAL OPTIMUM)
//   - There can be at most `k - 1` candidates.
//   - Maintain an array of `k - 1` candidate elements with their respective counts.
//   - Step 1 (Candidate Elimination):
//     * For each element `x` in `arr`:
//       - If `x` matches an existing candidate: increment its count.
//       - Else if an empty candidate slot exists: insert `x` with count = 1.
//       - Else: Decrement counts of ALL `k - 1` candidates by 1!
//         (This represents discarding a set of `k` distinct elements together).
//   - Step 2 (Verification Pass):
//     * Boyer-Moore only provides potential candidates. We must do a second pass to verify
//       their true counts exceed `n / k`.
//   - Complexity: O(N * K) time, O(K) space! When K is small (e.g., k=2, k=3), space is O(1)!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Method 1: Hash Map Method (Fast & General - O(N) Time, O(N) Space)
    // -------------------------------------------------------------------------
    vector<int> countOccurenceHashMap(vector<int>& arr, int k) {
        int n = arr.size();
        int threshold = n / k;
        unordered_map<int, int> freq;
        vector<int> result;

        for (int x : arr) {
            freq[x]++;
        }

        for (const auto& [val, count] : freq) {
            if (count > threshold) {
                result.push_back(val);
            }
        }

        return result;
    }

    // -------------------------------------------------------------------------
    // Method 2: Generalized Boyer-Moore Voting Algorithm (O(N * K) Time, O(K) Space)
    // Optimal when memory is strictly bounded by O(K)
    // -------------------------------------------------------------------------
    vector<int> countOccurenceBoyerMoore(vector<int>& arr, int k) {
        int n = arr.size();
        if (k <= 1) return arr;

        int numCandidates = k - 1;
        // candidates[i] stores {value, count}
        vector<pair<int, int>> candidates(numCandidates, {0, 0});

        // Pass 1: Voting and Cancellation
        for (int x : arr) {
            bool matched = false;

            // Check if x matches an existing candidate
            for (int i = 0; i < numCandidates; i++) {
                if (candidates[i].second > 0 && candidates[i].first == x) {
                    candidates[i].second++;
                    matched = true;
                    break;
                }
            }

            if (matched) continue;

            // Check if there is an empty slot for a new candidate
            bool placed = false;
            for (int i = 0; i < numCandidates; i++) {
                if (candidates[i].second == 0) {
                    candidates[i] = {x, 1};
                    placed = true;
                    break;
                }
            }

            if (placed) continue;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If x does not match any candidate AND all (k - 1) candidate slots are full,
            // we have found a group of 'k' distinct elements (the k-1 candidates + current element x)!
            // Discarding a group of k distinct elements CANNOT alter the fact that elements
            // appearing > n/k times will still survive!
            // Hence, decrement counts of ALL candidates by 1!
            for (int i = 0; i < numCandidates; i++) {
                candidates[i].second--;
            }
        }

        // Pass 2: Verification Pass
        vector<int> result;
        int threshold = n / k;

        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].second > 0) {
                int actualCount = 0;
                for (int x : arr) {
                    if (x == candidates[i].first) actualCount++;
                }
                if (actualCount > threshold) {
                    result.push_back(candidates[i].first);
                }
                // Clear to avoid duplicate checks if same value was picked twice
                candidates[i].second = 0;
            }
        }

        return result;
    }
};

/*
Time Complexity:
- Method 1 (Hash Map): O(N) average time.
- Method 2 (Boyer-Moore): O(N * K) — for each of the N elements, we iterate through K - 1 candidates.
  * For fixed K (like LeetCode 169 k=2 or LeetCode 229 k=3), O(N * K) is strictly O(N) linear time!

Space Complexity:
- Method 1: O(N) Auxiliary Space for hash table.
- Method 2: O(K) Auxiliary Space for storing K - 1 candidates. (O(1) auxiliary space when k is constant!).

Key Insights:
1. Mathematical Cancellation Property:
   - If an element appears > N / k times, it CANNOT be completely eliminated by groups of k distinct elements,
     because there are at most N / k such complete groups!
   - This proves the candidate is guaranteed to survive into the second pass.
*/
