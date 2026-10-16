#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximize the sum of arr[i]*i
 * 
 * Given an array of N integers, find the maximum value of sum(arr[i] * i) for 0 <= i < N
 * by rearranging the elements of the array. Return the answer modulo 10^9 + 7.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - Here the objective function has positional weighting: element at index `i` is multiplied by its index `i`.
 * - The weights are monotonically increasing strictly: 0, 1, 2, ..., N-1.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Rearrangement Inequality:
 *   For any two sequences x_1 <= x_2 <= ... <= x_n and y_1 <= y_2 <= ... <= y_n,
 *   the dot product sum(x_i * y_sigma(i)) is strictly MAXIMIZED when the sequences 
 *   are sorted in the same monotonic order (x_i paired with y_i).
 * - Since the indices are strictly increasing: 0 < 1 < 2 < ... < N - 1,
 *   the array elements MUST be sorted in strictly ascending order: arr[0] <= arr[1] <= ... <= arr[N-1].
 * - Pairing smaller numbers with smaller multipliers (0, 1) and largest numbers with largest multipliers 
 *   guarantees the global maximum.
 */

class Solution {
    const long long MOD = 1e9 + 7;
public:
    int Maximize(vector<int>& arr) {
        int n = arr.size();

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // By the Rearrangement Inequality, sorting both sequences in ascending order maximizes dot product.
        sort(arr.begin(), arr.end());

        long long total_sum = 0;
        for (long long i = 0; i < n; i++) {
            // *** CRUCIAL LINE: Assign smaller weight to smaller value, larger weight to larger value ***
            total_sum = (total_sum + (arr[i] * i)) % MOD;
        }

        return total_sum;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {5, 3, 2, 4, 1};
    cout << "Max sum 1: " << sol.Maximize(arr1) << "\n"; // Sorted: 1,2,3,4,5 -> 1*0 + 2*1 + 3*2 + 4*3 + 5*4 = 0+2+6+12+20 = 40

    vector<int> arr2 = {1, 2, 3};
    cout << "Max sum 2: " << sol.Maximize(arr2) << "\n"; // 1*0 + 2*1 + 3*2 = 8

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) for sorting the array.
 * - Space Complexity: O(1) auxiliary space.
 */
