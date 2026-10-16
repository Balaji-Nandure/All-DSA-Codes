#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

/**
 * Problem: Find maximum sum possible equal sum of three stacks
 * 
 * Given three stacks of positive numbers S1, S2, and S3 (represented as vectors where index 0 
 * is the top of the stack). We can only pop elements from the top of each stack.
 * Find the maximum possible equal sum of the three stacks. If no non-zero sum is possible, return 0.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is a multi-pointer monotonic descent problem.
 * - Unlike problems where we build up from bottom (min-heap), here we start from the maximum possible 
 *   total heights and prune monotonically until all three heights align.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy Height Equalization:
 *   1. Calculate initial total sum of each stack: sum1, sum2, sum3.
 *   2. Maintain 3 pointers top1, top2, top3 pointing to the top of each stack.
 *   3. Invariant: Since all elements are positive, popping an element strictly REDUCES the sum of that stack.
 *      To make all three sums equal, a stack whose sum is strictly larger than another can NEVER match 
 *      the others without popping from it.
 *   4. Therefore, at each step:
 *      - If sum1 == sum2 && sum2 == sum3: Found maximal equal sum! Return sum1.
 *      - Otherwise, identify the stack with the maximum sum and pop its top element:
 *        - If sum1 is largest: sum1 -= S1[top1++];
 *        - If sum2 is largest: sum2 -= S2[top2++];
 *        - If sum3 is largest: sum3 -= S3[top3++];
 *   5. If any stack becomes exhausted (top >= N), the only possible equal sum remaining is 0.
 */

class Solution {
public:
    int maxEqualSum(int N1, int N2, int N3, vector<int>& S1, vector<int>& S2, vector<int>& S3) {
        long long sum1 = 0, sum2 = 0, sum3 = 0;

        for (int x : S1) sum1 += x;
        for (int x : S2) sum2 += x;
        for (int x : S3) sum3 += x;

        int top1 = 0, top2 = 0, top3 = 0;

        while (top1 < N1 && top2 < N2 && top3 < N3) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If all three stack sums are identical, this is the maximal feasible equal sum
            if (sum1 == sum2 && sum2 == sum3) {
                return sum1;
            }

            // *** CRUCIAL LINE: Greedily pop the top element from the stack with the largest sum ***
            if (sum1 >= sum2 && sum1 >= sum3) {
                sum1 -= S1[top1++];
            } else if (sum2 >= sum1 && sum2 >= sum3) {
                sum2 -= S2[top2++];
            } else {
                sum3 -= S3[top3++];
            }
        }

        return 0; // If any stack is fully emptied
    }
};

int main() {
    Solution sol;
    vector<int> S1 = {3, 2, 1, 1, 1}; // sum = 8
    vector<int> S2 = {4, 3, 2};       // sum = 9
    vector<int> S3 = {1, 1, 4, 1};    // sum = 7

    int N1 = S1.size(), N2 = S2.size(), N3 = S3.size();
    cout << "Max Equal Sum: " << sol.maxEqualSum(N1, N2, N3, S1, S2, S3) << "\n";
    // S2 pops 4 -> sum2 = 5
    // S1 pops 3 -> sum1 = 5
    // S3 pops 1, 1 -> sum3 = 5
    // All equal to 5!

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N1 + N2 + N3). In each step, at least one element is popped from one of the stacks.
 * - Space Complexity: O(1) auxiliary space (using indices top1, top2, top3).
 */
