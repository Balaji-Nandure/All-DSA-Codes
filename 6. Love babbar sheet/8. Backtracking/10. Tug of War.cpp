#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <numeric>

using namespace std;

/**
 * Problem: Tug of War
 * 
 * Given a set of N integers, divide them into two subsets of sizes n/2 and (n - n/2) 
 * such that the absolute difference between the sums of the two subsets is minimized.
 * Print the two balanced subsets.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "8. Subset Sum Problem", subsets could have ANY cardinality (any number of elements).
 * - In Tug of War, there is a STRICT cardinality constraint: one subset must have EXACTLY 
 *   floor(N / 2) elements, and the other must have ceil(N / 2) elements.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Backtracking with Cardinality Pruning:
 *   1. Calculate total sum of all elements.
 *   2. For each element at index `idx`:
 *      - Option A: Include arr[idx] in subset 1.
 *        Allowed only if subset 1 currently has fewer than n/2 elements:
 *        curr_elements.push_back(arr[idx]);
 *        backtrack(idx + 1, curr_count + 1, curr_sum + arr[idx]);
 *        curr_elements.pop_back(); // Backtrack
 *      - Option B: Exclude arr[idx] from subset 1 (place in subset 2).
 *        Allowed only if the remaining elements (N - 1 - idx) plus current count 
 *        is AT LEAST n/2: (N - 1 - idx >= n/2 - curr_count).
 *        *** This cardinality pruning cuts off dead-end branches immediately! ***
 *   3. When curr_count == n / 2:
 *      Difference = |total_sum - 2 * curr_sum|.
 *      Update min_diff and save best subset configuration.
 */

class Solution {
    int min_diff = INT_MAX;
    vector<int> best_subset1;

    void backtrack(int idx, int curr_count, int curr_sum, int target_size, int total_sum, 
                   const vector<int>& arr, vector<int>& current_selected) {
        // Base case: Exactly target_size (n / 2) elements selected
        if (curr_count == target_size) {
            int subset2_sum = total_sum - curr_sum;
            int diff = abs(curr_sum - subset2_sum);

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Check if current split achieves a smaller discrepancy between the two teams
            if (diff < min_diff) {
                min_diff = diff;
                best_subset1 = current_selected;
            }
            return;
        }

        // If we ran out of elements to consider
        if (idx == (int)arr.size()) {
            return;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Cardinality Pruning: If remaining elements cannot fulfill the required team size, prune!
        int remaining_available = (int)arr.size() - idx;
        int needed = target_size - curr_count;
        if (remaining_available < needed) {
            return;
        }

        // Choice 1: Include arr[idx] in subset 1
        current_selected.push_back(arr[idx]);
        backtrack(idx + 1, curr_count + 1, curr_sum + arr[idx], target_size, total_sum, arr, current_selected);
        current_selected.pop_back(); // Backtrack

        // Choice 2: Exclude arr[idx] from subset 1 (place in subset 2)
        backtrack(idx + 1, curr_count, curr_sum, target_size, total_sum, arr, current_selected);
    }

public:
    void tugOfWar(vector<int>& arr) {
        int n = arr.size();
        int total_sum = accumulate(arr.begin(), arr.end(), 0);
        int target_size = n / 2;

        min_diff = INT_MAX;
        best_subset1.clear();
        vector<int> current_selected;

        backtrack(0, 0, 0, target_size, total_sum, arr, current_selected);

        // Derive subset 2 from elements not in best_subset1
        vector<int> subset1 = best_subset1;
        vector<int> subset2;
        vector<bool> in_sub1(n, false);

        vector<int> temp_sub1 = subset1;
        for (int x : arr) {
            auto it = find(temp_sub1.begin(), temp_sub1.end(), x);
            if (it != temp_sub1.end()) {
                temp_sub1.erase(it);
            } else {
                subset2.push_back(x);
            }
        }

        int sum1 = accumulate(subset1.begin(), subset1.end(), 0);
        int sum2 = accumulate(subset2.begin(), subset2.end(), 0);

        cout << "Subset 1 (size " << subset1.size() << ", sum " << sum1 << "): [ ";
        for (int x : subset1) cout << x << " ";
        cout << "]\n";

        cout << "Subset 2 (size " << subset2.size() << ", sum " << sum2 << "): [ ";
        for (int x : subset2) cout << x << " ";
        cout << "]\n";

        cout << "Minimum Difference: " << min_diff << "\n";
    }
};

int main() {
    Solution sol;
    vector<int> arr = {23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4};
    sol.tugOfWar(arr);
    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(C(N, N/2)). Generating all combinations of choosing N/2 from N elements.
 *   Cardinality pruning eliminates unnecessary paths outside the valid size window.
 * - Space Complexity: O(N) for recursion stack and subset buffers.
 */
