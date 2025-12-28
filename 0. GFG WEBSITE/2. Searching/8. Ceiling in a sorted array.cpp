#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    // Returns the index of the ceiling of x in sorted array arr
    // Ceiling of x is the smallest element >= x
    // Returns -1 if no ceiling exists (i.e., x > arr[n-1])
    int findCeil(vector<int>& arr, int x) {
        int n = arr.size();
        int l = 0, r = n - 1;
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] >= x) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};