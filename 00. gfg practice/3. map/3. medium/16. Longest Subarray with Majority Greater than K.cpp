/*
    Problem Name: Longest Subarray with Majority Greater than K
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array arr[] and an integer k, the task is to find the length of the longest subarray in which the count of elements greater than k is more than the count of elements less than or equal to k.

    Expected Complexities:
    Time Complexity: O(N), where N is the size of the array. We iterate through the array once and use a hash map.
    Space Complexity: O(N) to store the prefix sums in the map.

    Love Babbar Style Approach:
    1. We want to find the longest subarray where `(count of elements > k) > (count of elements <= k)`.
    2. We can transform this into a prefix sum problem! Treat every element `> k` as `+1`, and every element `<= k` as `-1`. 
       Now the problem simply becomes: "Find the longest subarray with a strictly positive sum (> 0)".
    3. We keep a running `prefix_sum`. At any index `i`:
       - If `prefix_sum > 0`: The entire subarray from index `0` to `i` has a positive sum! The length is `i + 1`.
       - If `prefix_sum <= 0`: We want to find the earliest previous index where the prefix sum was strictly less than our current `prefix_sum`. 
    4. Since our prefix sum only changes by +1 or -1 at each step, the absolute earliest time it was strictly less than `prefix_sum` is EXACTLY the very first time it was `prefix_sum - 1`.
    5. We simply use an `unordered_map` to store the very first index we see each prefix sum. Whenever `prefix_sum <= 0`, we check if `prefix_sum - 1` exists in our map. If it does, we calculate the length and update our maximum length!
    
    Dry Run:
    arr = [1, 2, 3, 4, 1], k = 2
    Transformed: [-1, -1, 1, 1, -1]
    
    i=0: val=-1, pfx=-1. map[-1] = 0. Want -2. Not in map. max_len=0.
    i=1: val=-1, pfx=-2. map[-2] = 1. Want -3. Not in map. max_len=0.
    i=2: val=1, pfx=-1. Want -2. map[-2] is 1. Length = 2 - 1 = 1. max_len=1.
    i=3: val=1, pfx=0. Want -1. map[-1] is 0. Length = 3 - 0 = 3. max_len=3.
    i=4: val=-1, pfx=-1. Want -2. map[-2] is 1. Length = 4 - 1 = 3. max_len=3.
    
    Result = 3. Matches Expected Output!
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& arr, int k) {
        int n = arr.size();
        int max_len = 0;
        int pfx = 0;
        
        // Map to store the very first index we see a specific prefix sum
        unordered_map<int, int> first_occ;
        
        for (int i = 0; i < n; i++) {
            // Transform element: +1 if > k, -1 if <= k
            int val = (arr[i] > k) ? 1 : -1;
            pfx += val;
            
            if (pfx > 0) {
                // Entire prefix from 0 to i is valid (sum > 0)
                max_len = max(max_len, i + 1);
            } else {
                // Record the first time we see this exact prefix sum
                if (first_occ.find(pfx) == first_occ.end()) {
                    first_occ[pfx] = i;
                }
                
                // We want the earliest prefix sum that is strictly less than pfx,
                // which is exactly (pfx - 1). Check if it exists in the map!
                if (first_occ.find(pfx - 1) != first_occ.end()) {
                    max_len = max(max_len, i - first_occ[pfx - 1]);
                }
            }
        }
        
        return max_len;
    }
};

int main() {
    int t;
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n >> k;
            
            vector<int> arr(n);
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            
            Solution ob;
            cout << ob.longestSubarray(arr, k) << "\n";
        }
    }
    return 0;
}
