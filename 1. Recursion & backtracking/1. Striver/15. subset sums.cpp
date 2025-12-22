/*
 * Problem: Subset Sums
 * 
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/subset-sums2234/1
 *
 * Given a list of N integers, print sums of all subsets.
 * Output should be printed in increasing order of sums.
 * 
 * Example: Arr = [2, 3]
 * Output: 0 2 3 5
 * (empty subset: 0, {2}: 2, {3}: 3, {2,3}: 5)
 *
 * Time: O(2^n) - generate all 2^n subsets
 * Space: O(n) - recursion stack depth
 */

#include <bits/stdc++.h>
using namespace std;

// Method 1: Pick / Not Pick approach
void findSubsetSums(int i, vector<int>& arr, int sum, vector<int>& result) {
    // Base case: processed all elements, add current sum
    if (i == (int)arr.size()) {
        result.push_back(sum);
        return;
    }

    // PICK: Include arr[i] in subset sum
    findSubsetSums(i + 1, arr, sum + arr[i], result);

    // NOT PICK: Exclude arr[i] from subset sum
    findSubsetSums(i + 1, arr, sum, result);
}

vector<int> subsetSums_pickNotPick(vector<int>& arr) {
    vector<int> result;
    findSubsetSums(0, arr, 0, result);
    sort(result.begin(), result.end()); // sort in increasing order
    return result;
}

// Method 2: Loop-based approach
void findSubsetSums_loop(int start, vector<int>& arr, int sum, vector<int>& result) {
    // Add current sum (represents subset from start to end)
    // This captures empty subset when start = 0, sum = 0
    result.push_back(sum);
    
    // Base case: processed all elements
    // Note: Even without this check, loop condition handles it

    // Try each element from start position
    for (int i = start; i < (int)arr.size(); i++) {
        // Recursively find sums including arr[i]
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

