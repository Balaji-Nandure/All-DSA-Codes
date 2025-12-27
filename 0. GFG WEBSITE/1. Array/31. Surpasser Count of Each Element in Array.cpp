/*
 * Problem: Surpasser Count of Each Element in Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-surpasser-count-of-each-element-in-array/
 * 
 * Given an array of integers, find the surpasser count of each element.
 * The surpasser count of an element is the number of elements to its right 
 * that are greater than it.
 * 
 * Example 1:
 * Input: arr[] = {2, 7, 5, 3, 0, 8, 1}
 * Output: [4, 1, 1, 1, 2, 0, 0]
 * Explanation:
 * - For 2: elements to right greater than 2 are {7, 5, 3, 8} = 4
 * - For 7: elements to right greater than 7 are {8} = 1
 * - For 5: elements to right greater than 5 are {8} = 1
 * - For 3: elements to right greater than 3 are {8} = 1
 * - For 0: elements to right greater than 0 are {8, 1} = 2
 * - For 8: no elements to right greater than 8 = 0
 * - For 1: no elements to right = 0
 * 
 * Example 2:
 * Input: arr[] = {4, 6, 3, 9, 7, 10}
 * Output: [4, 2, 3, 1, 1, 0]
 * 
 * Constraints:
 * - 1 <= n <= 10^5
 * - -10^9 <= arr[i] <= 10^9
 * 
 * Approach:
 * - Method 1: Merge Sort (Optimal) - O(n log n) time, O(n) space
 *   Similar to counting inversions, count elements greater during merge
 *   Process elements from right to left during merge
 * 
 * - Method 2: Self-Balancing BST (AVL Tree) - O(n log n) time, O(n) space
 *   Insert elements from right to left, count greater elements
 * 
 * - Method 3: Brute Force - O(n^2) time, O(1) space
 *   For each element, count elements to right that are greater
 * 
 * Time: O(n log n) - merge sort approach (optimal method)
 * Space: O(n) - auxiliary arrays for merge sort
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    void merge(vector<pair<int,int>>& a, int l, int m, int r, vector<int>& res) {

        vector<pair<int,int>> temp;
        int i = l, j = m + 1;
        int rightCount = r - (m + 1) + 1;

        while (i <= m && j <= r) {
            if (a[i].first < a[j].first) {
                res[a[i].second] += rightCount;
                temp.push_back(a[i++]);
            } else {
                temp.push_back(a[j++]);
                rightCount--;
            }
        }

        while (i <= m) {
            res[a[i].second] += rightCount;
            temp.push_back(a[i++]);
        }

        while (j <= r) {
            temp.push_back(a[j++]);
        }

        for (int k = l; k <= r; k++) {
            a[k] = temp[k - l];
        }
    }

    void mergeSort(vector<pair<int,int>>& a, int l, int r, vector<int>& res) {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeSort(a, l, m, res);
        mergeSort(a, m + 1, r, res);
        merge(a, l, m, r, res);
    }

    vector<int> findSurpasser(vector<int>& arr) {
        int n = arr.size();
        vector<pair<int,int>> a;
        vector<int> res(n, 0);

        for (int i = 0; i < n; i++)
            a.push_back({arr[i], i});

        mergeSort(a, 0, n - 1, res);
        return res;
    }
};
    