#include <bits/stdc++.h>
using namespace std;

// method 1: pick and not pick
void printAll(int i, vector<int> &a, vector<int> &curr, int &sum, int k) {

    // Base case: reached end
    if (i == (int)a.size()) {
        if (sum == k) {
            for (int x : curr) cout << x << " ";
            cout << endl;
        }
        return;
    }

    // TAKE a[i]
    curr.push_back(a[i]);
    sum += a[i];
    printAll(i + 1, a, curr, sum, k);

    // BACKTRACK
    curr.pop_back();
    sum -= a[i];

    // NOT TAKE a[i]
    printAll(i + 1, a, curr, sum, k);
}

// method 2: loop
void printAll_loop(int start, vector<int> &a, vector<int> &curr, int sum, int k) {
    if (sum == k) {
        for (int x : curr) cout << x << " ";
        cout << endl;
        // NOTE: don't return here; there may be further elements (positive/negative)
        // If all a[i] > 0, you *can* return to prune.
    }

    if (start == (int)a.size()) return;

    for (int i = start; i < (int)a.size(); i++) {
        curr.push_back(a[i]);
        printAll_loop(i + 1, a, curr, sum + a[i], k);
        curr.pop_back();
    }
}


// PRINT ONLY ONE SUBSEQUENCE WITH SUM = K
// method 1: pick and not pick
bool printOne(int i, vector<int> &a, vector<int> &ds, int &sum, int k) {

    if (i == a.size()) {
        // if condition is satisfied then return true and stop the function
        if (sum == k) {
            for (int x : ds) cout << x << " ";
            cout << endl;
            return true;  // stop
        }
        // otherwise return false and continue the function
        return false;
    }

    // TAKE
    ds.push_back(a[i]);
    sum += a[i];
    // if true then immediate return true and stop the function
    // do this whenewer you are making a function call.
    if (printOne(i + 1, a, ds, sum, k)) {
        // stop further recursion calls
        return true;
    }

    ds.pop_back();
    sum -= a[i];

    // NOT TAKE
    // do this whenewer you are making a function call.
    if (printOne(i + 1, a, ds, sum, k)) return true;

    // if none of the aboce calls return true, then return false
    return false;
}

// method 2: loop
bool printOne_loop(int start, vector<int> &a, vector<int> &curr, int sum, int k) {
    if (sum == k) {
        for (int x : curr) cout << x << " ";
        cout << endl;
        return true;              // found one → stop
    }
    if (start == (int)a.size()) return false;

    for (int i = start; i < (int)a.size(); i++) {
        curr.push_back(a[i]);
        if (printOne_loop(i + 1, a, curr, sum + a[i], k)) return true; // propagate true
        curr.pop_back();
    }
    return false;
}



// PRINT COUNT OF SUBSEQUENCES WITH SUM = K
// here no need to maintain the curr vector because we are not printing the subsequences
// and just maintaining the sum if more than sufficient.
// method 1: pick and not pick
int countWays(int i, vector<int> &a, int &sum, int k) {
    // this can only be done if array contains positive numbers only.
    if(sum > k) return 0;
    if (i == a.size()) {
        return (sum == k);
    }

    // TAKE
    sum += a[i];
    int take = countWays(i + 1, a, sum, k);
    sum -= a[i];

    // NOT TAKE
    int not_take = countWays(i + 1, a, sum, k);

    return take + not_take;
}

// method 2: loop
int countWays_loop(int start, vector<int> &a, int sum, int k) {
    if (sum == k || start == (int)a.size()) {
        return sum == k;
    }

    int ways = 0;
    for (int i = start; i < (int)a.size(); i++) {
        ways += countWays_loop(i + 1, a, sum + a[i], k);
    }
    return ways;
}


int main() {

    vector<int> a = {1, 2, 3, 4, 5};
    int k = 5;

    cout << "All subsequences with sum " << k << ":\n";
    vector<int> curr;
    int sum = 0;
    printAll(0, a, curr, sum, k);

    cout << "\nAny one subsequence with sum " << k << ":\n";
    curr.clear();
    sum = 0;
    bool found = printOne(0, a, curr, sum, k);
    if (!found) cout << "None found.\n";

    cout << "\nCount of subsequences with sum " << k << " (pick/not-pick): ";
    sum = 0; // needs to be passed by reference
    cout << countWays(0, a, sum, k) << endl;

    cout << "Count of subsequences with sum " << k << " (loop): ";
    cout << countWays_loop(0, a, 0, k) << endl;

    return 0;
}


