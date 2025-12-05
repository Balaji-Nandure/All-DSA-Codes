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
        if (sum == k) {
            for (int x : ds) cout << x << " ";
            cout << endl;
            return true;  // stop
        }
        return false;
    }

    // TAKE
    ds.push_back(a[i]);
    sum += a[i];
    if (printOne(i + 1, a, ds, sum, k)) {
        ds.pop_back();
        sum -= a[i];
        return true;
    }
    ds.pop_back();
    sum -= a[i];

    // NOT TAKE
    if (printOne(i + 1, a, ds, sum, k)) return true;

    return false;
}


// PRINT COUNT OF SUBSEQUENCES WITH SUM = K
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
