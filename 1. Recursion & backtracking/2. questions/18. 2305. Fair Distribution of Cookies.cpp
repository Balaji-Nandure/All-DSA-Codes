/*
 * Problem: 2305. Fair Distribution of Cookies
 *
 * You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith bag, and an integer k, the number of children.
 * You should distribute all cookies to k children such that each child gets at least one bag. The unfairness of a distribution is defined as the maximum total cookies obtained by a single child.
 * Return the minimum unfairness possible of all distributions.
 *
 * Example:
 * Input: cookies = [8,15,10,20,8], k = 2
 * Output: 31
 * Explanation: One optimal distribution is [8,15,8] and [10,20], unfairness = max(31,30) = 31.
 */

#include <bits/stdc++.h>
using namespace std;

// Backtracking function: tries all possible distributions
void backtrack(int idx, vector<int>& cookies, vector<int>& children, int& res) {
    int k = children.size();
    if (idx == (int)cookies.size()) {
        int unfairness = *max_element(children.begin(), children.end());
        // int unfairness = max({children.begin(), children.end()}); // ❌❌❌
        res = min(res, unfairness);
        return;
    }
    for (int i = 0; i < k; ++i) {
        children[i] += cookies[idx];
        backtrack(idx + 1, cookies, children, res);
        children[i] -= cookies[idx];
        // Pruning: if current child has no cookies before, don't try other children at this position (avoid duplicates)
        if (children[i] == 0) break;
    }
}

int distributeCookies(vector<int>& cookies, int k) {
    vector<int> children(k, 0);
    int res = INT_MAX;
    backtrack(0, cookies, children, res);
    return res;
}

// Helper to print result
void printResult(int res) {
    cout << "Minimum unfairness: " << res << endl;
}

int main() {
    // Example 1
    vector<int> cookies1 = {8, 15, 10, 20, 8};
    int k1 = 2;
    cout << "Test case 1: cookies = [8,15,10,20,8], k = 2" << endl;
    printResult(distributeCookies(cookies1, k1)); // Expected: 31

    // Example 2
    vector<int> cookies2 = {6,1,3,2,2,4,1,2};
    int k2 = 3;
    cout << "Test case 2: cookies = [6,1,3,2,2,4,1,2], k = 3" << endl;
    printResult(distributeCookies(cookies2, k2)); // Expected: 7

    // Example 3 (edge case)
    vector<int> cookies3 = {5,9,7,3};
    int k3 = 4;
    cout << "Test case 3: cookies = [5,9,7,3], k = 4" << endl;
    printResult(distributeCookies(cookies3, k3)); // Expected: 9

    return 0;
}
