#include <bits/stdc++.h>
using namespace std;

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

// PRINT ONLY ONE SUBSEQUENCE WITH SUM = K

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


// PRINT COUNT OF SUBSEQUENCES WITH SUM = K
// here no need to maintain the curr vector because we are not printing the subsequences
// and just maintaining the sum if more than sufficient.
int countWays(int i, vector<int> &a, int &sum, int k) {

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


int main() {

    vector<int> a = {1, 2, 3, 4, 5};
    int k = 5;

    vector<int> curr;
    int sum = 0;
    printAll(0, a, curr, sum, k);

    return 0;
}
