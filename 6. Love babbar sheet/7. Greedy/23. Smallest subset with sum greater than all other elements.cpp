#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

/**
 * Problem: Smallest subset with sum greater than all other elements
 * 
 * Given an array of non-negative integers, find the minimum number of elements 
 * (the smallest subset size) such that the sum of these elements is strictly greater 
 * than the sum of all remaining elements in the array.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In fractional knapsack or subset sum, we might optimize value per weight or reach an exact sum.
 * - Here, we want to minimize CARDINALITY (subset count) subject to a sum inequality:
 *   subset_sum > total_sum - subset_sum  <=>  2 * subset_sum > total_sum.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy by Largest Elements First:
 *   To reach the threshold (total_sum / 2) with the MINIMUM number of elements,
 *   each selected element must contribute as much sum as possible.
 *   Therefore, we must greedily pick the largest elements first.
 * - Sort the array in descending order.
 * - Keep adding elements from largest down until:
 *   current_sum > total_sum - current_sum (i.e. 2 * current_sum > total_sum).
 * - Return the number of elements picked.
 */

class Solution {
public:
    int minSubset(vector<int>& Arr, int N) {
        long long total_sum = 0;
        for (int x : Arr) {
            total_sum += x;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sort descending so each picked element contributes maximum possible sum
        sort(Arr.begin(), Arr.end(), greater<int>());

        long long current_subset_sum = 0;
        int count = 0;

        for (int i = 0; i < N; i++) {
            current_subset_sum += Arr[i];
            count++;

            // *** CRUCIAL LINE: Check if subset sum strictly dominates the remaining elements ***
            if (current_subset_sum > total_sum - current_subset_sum) {
                return count;
            }
        }

        return count;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {2, 17, 7, 3};
    int N1 = arr1.size();
    cout << "Min subset size 1: " << sol.minSubset(arr1, N1) << "\n";
    // Total sum = 29. Half = 14.5.
    // Sorted descending: 17, 7, 3, 2.
    // Pick 17: sum = 17 > (29 - 17 = 12). Count = 1.

    vector<int> arr2 = {20, 12, 18, 4};
    int N2 = arr2.size();
    cout << "Min subset size 2: " << sol.minSubset(arr2, N2) << "\n";
    // Total sum = 54. Half = 27.
    // Sorted descending: 20, 18, 12, 4.
    // Pick 20: 20 <= 34.
    // Pick 18: 20 + 18 = 38 > 16. Count = 2.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting.
 * - Space Complexity: O(1) auxiliary space.
 */
