/*
Question:
Given two arrays: a[], an array of integers, and b[], an array of characters, both of length n.
Sort the array b[] in such a way that if we arrange the elements of a[] in sorted order, the corresponding 
arrangement of elements in b[] should be output.

Example:
Input: 
5
3 1 4 2 5
e a d c b

Output:
a c e d b

Approach:
1. Pair up each element of a[] with the corresponding character in b[].
2. Sort the pairs by the values of a[].
3. Output the sequence of characters from each sorted pair.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to sort b[] according to sorted order of a[]
void sortByOtherArray(const vector<int>& a, const vector<char>& b) {
    int n = a.size();
    vector<pair<int, char>> pairs(n);
    for (int i = 0; i < n; ++i) {
        pairs[i] = {a[i], b[i]};
    }
    sort(pairs.begin(), pairs.end());
    for (int i = 0; i < n; ++i) {
        cout << pairs[i].second;
        if (i != n - 1)
            cout << " ";
    }
    cout << endl;
}
