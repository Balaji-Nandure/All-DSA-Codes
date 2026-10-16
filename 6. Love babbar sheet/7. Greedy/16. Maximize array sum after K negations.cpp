#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

/**
 * Problem: Maximize array sum after K negations
 * 
 * Given an array of integers and an integer K, modify the array by negating an element 
 * (arr[i] = -arr[i]) exactly K times such that the final sum of the array is maximized.
 * An element can be negated multiple times.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "15. Maximum product subset", elements were multiplied and zeros played an absorption role.
 * - Here, we perform exactly K additive sign flips. Flipping a negative to positive gives a net gain of 
 *   +2*|x|, so we should greedily prioritize the most negative numbers first.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Strategy:
 *   1. Sort the array ascending so most negative elements appear first.
 *   2. For each element, while K > 0 and arr[i] < 0:
 *      arr[i] = -arr[i], K-- (Gives the maximum positive sum increase).
 *   3. If all negatives are exhausted and K remains > 0:
 *      - If K is even: We can flip the same number back and forth K times without altering any value.
 *      - If K is odd: Exactly one element must end up negated. To minimize the sum lost,
 *        we subtract 2 * (minimum element in the entire array).
 * - Why not always use a min-heap?
 *   A min-heap takes O(K log N). When K is very large (e.g. K = 10^9), min-heap TLEs.
 *   The sort + parity check takes strictly O(N log N) time regardless of K.
 */

class Solution {
public:
    long long maximizeSum(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());

        // Step 1: Flip all negative numbers to positive from smallest (most negative) up
        for (int i = 0; i < n && k > 0; i++) {
            if (arr[i] < 0) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                arr[i] = -arr[i]; // Flip largest negative to maximize immediate delta +2*|arr[i]|
                k--;
            }
        }

        // Step 2: Compute sum and find minimum element
        long long sum = 0;
        int min_val = INT_MAX;
        for (int x : arr) {
            sum += x;
            min_val = min(min_val, x);
        }

        // Step 3: If k is odd, we are forced to keep one element negated
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        if (k % 2 != 0) {
            sum -= 2LL * min_val; // Flip the smallest positive element to lose minimum sum
        }

        return sum;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 2, -3, 4, 5};
    int k1 = 1;
    cout << "Max sum 1: " << sol.maximizeSum(arr1, k1) << "\n"; // Flipping -3 gives 1+2+3+4+5 = 15

    vector<int> arr2 = {5, -2, 5, -4, 5, -12, 5, 5, 5, 20};
    int k2 = 5;
    cout << "Max sum 2: " << sol.maximizeSum(arr2, k2) << "\n"; // Flips -12, -4, -2; k=2 left (even, no change)

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) due to initial sort. O(N) linear scan afterwards.
 * - Space Complexity: O(1) auxiliary space (in-place modification).
 */
