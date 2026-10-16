// Problem: Sort Array According to Count of Set Bits
// Link (GFG): https://www.geeksforgeeks.org/problems/sort-by-set-bit-count1153/1
// Article: https://www.geeksforgeeks.org/dsa/sort-array-according-count-set-bits/
// Difficulty: Easy / Medium
// Topic: Sorting, Bit Manipulation, Stable Bucket Sort, Custom Comparator

/*
Problem Statement:
Given an array of integers, sort the array (in-place) in descending order of 
the count of set bits (1s in binary representation).
CRITICAL REQUIREMENT: The sort MUST BE STABLE!
If two numbers have the same number of set bits, their relative original order 
in the input array must be preserved!

Example 1:
Input: arr = [5, 2, 3, 9, 4, 6, 7, 15, 32]
Output: [15, 7, 5, 3, 9, 6, 2, 4, 32]
Explanation:
15 has 4 set bits.
7 has 3 set bits.
5, 3, 9, 6 have 2 set bits (their original relative order is preserved: 5, 3, 9, 6).
2, 4, 32 have 1 set bit (their original relative order is preserved: 2, 4, 32).

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In standard sorting (`std::sort`):
//   * Sorting is UNSTABLE (Introsort does not guarantee relative order for ties).
//   * Using `std::sort` fails test cases because elements with identical set bit counts 
//     get shuffled!
// - In Problem 16 (Stable Set Bit Sort):
//   * We must enforce STABILITY.
//   * Because the number of set bits for a 32-bit positive integer is bounded strictly 
//     between 0 and 31, we can use BUCKET SORT (Counting Sort) to achieve true O(N) linear 
//     time while naturally preserving 100% stability!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: `std::stable_sort` with Custom Lambda
//   - Call `stable_sort(arr, arr + n, [](int a, int b){ return __builtin_popcount(a) > __builtin_popcount(b); });`
//   - Complexity: O(N log N) time, O(N) internal buffer.
//
// Approach 2: 32-Bucket Stable Counting Sort (Optimal & Chosen)
//   - Any 32-bit integer has at most 31 set bits (values from 0 to 31).
//   - Maintain 32 buckets: `vector<int> bitBuckets[32]`.
//   - Scan `arr` from left to right:
//       * `int setBits = __builtin_popcount(arr[i]);`
//       * Append `arr[i]` into `bitBuckets[setBits]`.
//   - Collect back into `arr` by iterating buckets in DESCENDING order from 31 down to 0!
//   - Why Stability is Guaranteed: Elements within each bucket retain their exact insertion order.
//   - Complexity: O(N) time (32 is constant), O(N) auxiliary space.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Approach 2: O(N) Linear Time Stable Bucket Sort
    void sortBySetBitCount(int arr[], int n) {
        // 32 buckets corresponding to set bit counts from 0 to 31
        vector<int> bitBuckets[32];

        // Place elements in buckets based on their set bit count
        for (int i = 0; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // __builtin_popcount uses hardware instruction (POPCNT) to count 1s in O(1).
            // Pushing into the bucket preserves FIFO stability for equal set bit counts!
            int setBits = __builtin_popcount(arr[i]);
            bitBuckets[setBits].push_back(arr[i]);
        }

        // Reconstruct the array in descending order of set bit count (from 31 down to 0)
        int idx = 0;
        for (int b = 31; b >= 0; --b) {
            for (int val : bitBuckets[b]) {
                arr[idx++] = val;
            }
        }
    }
};

int main() {
    Solution sol;
    int arr[] = {5, 2, 3, 9, 4, 6, 7, 15, 32};
    int n = sizeof(arr) / sizeof(arr[0]);

    sol.sortBySetBitCount(arr, n);

    cout << "Sorted by set bit count (descending):\n";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N + 32) = O(N) strictly linear time.
  * Filling buckets: N operations with hardware popcount.
  * Emptying buckets: N operations.
- Space Complexity: O(N) auxiliary space to hold the 32 bucket lists.

Key Takeaways:
- When the sort key has a tiny bounded range (0 to 31), Bucket/Counting Sort 
  effortlessly beats comparison sorts (O(N) vs O(N log N)) while inherently guaranteeing stability.
*/
