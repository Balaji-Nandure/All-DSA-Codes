/*
 * Problem: Print All Subsequences with Sum K
 *
 * Find and print all subsequences of an array that sum to exactly K.
 * Uses backtracking: try including/excluding each element.
 *
 * Time: O(2^n * n) - 2^n subsequences, each printed in O(n)
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Method 1: Pick and Not Pick approach
void printAll(int i, vector<int> &a, vector<int> &curr, int &sum, int k) {
    // Base case: processed all elements
    if (i == (int)a.size()) {
        // If current sum equals k, print the subsequence
        if (sum == k) {
            for (int x : curr) cout << x << " ";
            cout << endl;
        }
        return;
    }

    // TAKE: Include a[i] in subsequence
    curr.push_back(a[i]);
    sum += a[i];
    printAll(i + 1, a, curr, sum, k);

    // BACKTRACK: Remove a[i] to try without it
    curr.pop_back();
    sum -= a[i];

    // NOT TAKE: Skip a[i] and continue
    printAll(i + 1, a, curr, sum, k);
}

// Method 2: Loop-based approach (similar to generating combinations)
void printAll_loop(int start, vector<int> &a, vector<int> &curr, int sum, int k) {
    // Check if current sum equals k (print if found)
    if (sum == k) {
        for (int x : curr) cout << x << " ";
        cout << endl;
        // Note: Don't return here if array has negative numbers
        // If all elements are positive, can return early to prune
    }

    // Base case: processed all elements
    if (start == (int)a.size()) return;

    // Try each element from start to end
    for (int i = start; i < (int)a.size(); i++) {
        curr.push_back(a[i]);
        // Recursively try with a[i] included
        printAll_loop(i + 1, a, curr, sum + a[i], k);
        // For repetition allowed: use i instead of i+1
        // printAll_loop(i, a, curr, sum + a[i], k);
        curr.pop_back(); // Backtrack
    }
}


// Print only ONE subsequence with sum = K (early termination)
// Method 1: Pick and Not Pick with boolean return
bool printOne(int i, vector<int> &a, vector<int> &ds, int &sum, int k) {
    // Base case: processed all elements
    if (i == a.size()) {
        // If sum equals k, print and return true to stop recursion
        if (sum == k) {
            for (int x : ds) cout << x << " ";
            cout << endl;
            return true;  // Found one, stop searching
        }
        return false; // Not found, continue searching
    }

    // TAKE: Try including a[i]
    ds.push_back(a[i]);
    sum += a[i];
    // If found in this path, return true immediately (stop recursion)
    if (printOne(i + 1, a, ds, sum, k)) {
        return true;
    }
    // BACKTRACK: Remove a[i] if not found
    ds.pop_back();
    sum -= a[i];

    // NOT TAKE: Try without a[i]
    if (printOne(i + 1, a, ds, sum, k)) return true;

    // Neither path found a solution
    return false;
}

// Method 2: Loop-based with early termination
bool printOne_loop(int start, vector<int> &a, vector<int> &curr, int sum, int k) {
    // If sum equals k, print and return true (found one)
    if (sum == k) {
        for (int x : curr) cout << x << " ";
        cout << endl;
        return true; // Found one, stop searching
    }
    // Base case: no more elements
    if (start == (int)a.size()) return false;

    // Try each element from start
    for (int i = start; i < (int)a.size(); i++) {
        curr.push_back(a[i]);
        // If found in this path, propagate true upward
        if (printOne_loop(i + 1, a, curr, sum + a[i], k)) return true;
        curr.pop_back(); // Backtrack
    }
    return false; // Not found in this path
}

// Count total subsequences with sum = K
// Note: No need to maintain curr vector, only track sum
// Method 1: Pick and Not Pick
int countWays(int i, vector<int> &a, int &sum, int k) {
    // Early pruning: if sum exceeds k and all elements are positive
    // This optimization only works if array has positive numbers only
    if(sum > k) return 0;
    
    // Base case: processed all elements
    if (i == a.size()) {
        return (sum == k); // Return 1 if sum equals k, else 0
    }

    // TAKE: Count ways including a[i]
    sum += a[i];
    int take = countWays(i + 1, a, sum, k);
    sum -= a[i]; // Backtrack

    // NOT TAKE: Count ways excluding a[i]
    int not_take = countWays(i + 1, a, sum, k);

    // Total ways = ways with a[i] + ways without a[i]
    return take + not_take;
}

// Method 2: Loop-based counting
int countWays_loop(int start, vector<int> &a, int sum, int k) {
    // Base case: if sum equals k or processed all elements
    if (sum == k || start == (int)a.size()) {
        return sum == k; // Return 1 if sum equals k, else 0
    }

    int ways = 0;
    // Try each element from start
    for (int i = start; i < (int)a.size(); i++) {
        // Add ways from including a[i]
        ways += countWays_loop(i + 1, a, sum + a[i], k);
    }
    return ways;
}

int main() {

    vector<int> a = {1, 2, 3, 4, 5};
    int k = 5;

    cout << "All subsequences with sum " << k << " (pick/not-pick):\n";
    vector<int> curr;
    int sum = 0;
    printAll(0, a, curr, sum, k);

    cout << "\nAll subsequences with sum " << k << " (loop):\n";
    curr.clear();
    printAll_loop(0, a, curr, 0, k);

    cout << "\nAny one subsequence with sum " << k << " (pick/not-pick):\n";
    curr.clear();
    sum = 0;
    bool found = printOne(0, a, curr, sum, k);
    if (!found) cout << "None found.\n";

    cout << "\nAny one subsequence with sum " << k << " (loop):\n";
    curr.clear();
    found = printOne_loop(0, a, curr, 0, k);
    if (!found) cout << "None found.\n";

    cout << "\nCount of subsequences with sum " << k << " (pick/not-pick): ";
    sum = 0; // needs to be passed by reference
    cout << countWays(0, a, sum, k) << endl;

    cout << "Count of subsequences with sum " << k << " (loop): ";
    cout << countWays_loop(0, a, 0, k) << endl;

    return 0;
}

