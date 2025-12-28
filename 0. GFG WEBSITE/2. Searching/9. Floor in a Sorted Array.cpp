#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    // Returns the index of the floor of x in sorted array arr
    // Floor of x is the greatest element <= x
    // Returns -1 if no floor exists (i.e., x < arr[0])
    int findFloor(vector<int>& arr, int x) {
        int n = arr.size();
        int l = 0, r = n - 1;
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] <= x) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};