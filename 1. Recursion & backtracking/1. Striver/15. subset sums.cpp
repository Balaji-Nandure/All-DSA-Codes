/*
 * Problem: Subset Sums
 * 
 * Given a list(Arr) of N integers, print sums of all subsets in it.
 * Output should be printed in increasing order of sums.
 * 
 * Example:
 * Input: N = 2, Arr = [2, 3]
 * Output: 0 2 3 5
 * Explanation:
 * - When no elements are taken, the Sum = 0.
 * - When only 2 is taken, the Sum = 2.
 * - When only 3 is taken, the Sum = 3.
 * - When elements 2 and 3 are taken, the Sum = 2 + 3 = 5.
 */

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// METHOD 1: Pick / Not Pick
// -------------------------------------------------------
void findSubsetSums(int i, vector<int>& arr, int sum, vector<int>& result) {
    // Base case: reached end of array
    if (i == (int)arr.size()) {
        result.push_back(sum);
        return;
    }

    // PICK: include arr[i] in the sum
    findSubsetSums(i + 1, arr, sum + arr[i], result);

    // NOT PICK: don't include arr[i] in the sum
    findSubsetSums(i + 1, arr, sum, result);
}

vector<int> subsetSums_pickNotPick(vector<int>& arr) {
    vector<int> result;
    findSubsetSums(0, arr, 0, result);
    sort(result.begin(), result.end()); // sort in increasing order
    return result;
}

// -------------------------------------------------------
// METHOD 2: Loop Method
// -------------------------------------------------------
void findSubsetSums_loop(int start, vector<int>& arr, int sum, vector<int>& result) {
    // Add current sum to result
    // here we are adding the sum to the result before the base case because we want to add the sum of the empty subset.
    result.push_back(sum);
    
    // Base case: reached end
    // even if we comment this base case, it will still work
    // dry run the code to understand why it works.
    // if (start == (int)arr.size()) {
    //     return;
    // }

    // Try all elements from start to end
    for (int i = start; i < (int)arr.size(); i++) {
        findSubsetSums_loop(i + 1, arr, sum + arr[i], result);
    }
}

vector<int> subsetSums_loop(vector<int>& arr) {
    vector<int> result;
    findSubsetSums_loop(0, arr, 0, result);
    sort(result.begin(), result.end()); // sort in increasing order
    return result;
}

// -------------------------------------------------------
// MAIN FUNCTION
// -------------------------------------------------------
int main() {
    vector<int> arr = {1, 2, 3};
    int n = arr.size();

    cout << "Input: N = " << n << ", Arr = [";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]\n\n";

    cout << "Using Pick/Not-Pick Method:\n";
    vector<int> res1 = subsetSums_pickNotPick(arr);
    for (int x : res1) cout << x << " ";
    cout << "\n\n";

    cout << "Using Loop Method:\n";
    vector<int> res2 = subsetSums_loop(arr);
    for (int x : res2) cout << x << " ";
    cout << "\n\n";

    // // Another test case
    // cout << "Test case 2:\n";
    // vector<int> arr2 = {1, 2, 3};
    // cout << "Input: N = 3, Arr = [1, 2, 3]\n";
    // vector<int> res3 = subsetSums_pickNotPick(arr2);
    // cout << "Output: ";
    // for (int x : res3) cout << x << " ";
    // cout << "\n";

    return 0;
}

