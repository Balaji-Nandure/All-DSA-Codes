/*
    Problem Name: Subarrays with sum K
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an unsorted array arr[] of integers, find the number of subarrays whose sum exactly equal to a given number k.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of elements in the array. Inserting and searching in an `unordered_map` takes O(1) average time.
    Space Complexity: O(N) to store the prefix sums and their frequencies in the hash map.

    Love Babbar Style Approach:
    1. Prefix Sum & Hash Map: The naive approach of checking all subarrays takes O(N^2) time. To optimize this to O(N), we use the Prefix Sum concept combined with a Hash Map (`unordered_map`).
    2. The Logic: At any index `i`, if our running prefix sum is `P`, we are looking for a previous prefix sum equal to `P - k`. Why? Because if the sum from index 0 to `j` is `P - k`, and the sum from 0 to `i` is `P`, then the sum of the subarray from `j+1` to `i` must be exactly `k`.
    3. Initialization: We initialize an `unordered_map<int, int>` to store the frequencies of prefix sums. We add `{0: 1}` to the map initially. This handles the case where the prefix sum itself is exactly equal to `k` (meaning the valid subarray starts from index 0).
    4. Traversal: We traverse the array maintaining a running `sum`.
       - For each element, we add it to `sum`.
       - We check if `sum - k` exists in our map. If it does, we add its frequency to our total `count`. This signifies the number of valid subarrays ending at the current index.
       - Finally, we add the current `sum` to our map (increment its frequency) so it can be paired with future elements.
    5. Result: Return the final `count`.

    Dry Run:
    Input: arr[] = [10, 2, -2, -20, 10], k = -10
    - Initialize map = {0: 1}, sum = 0, count = 0
    - i=0, arr[0]=10: sum = 10. target = 10 - (-10) = 20. Map has no 20. map[10] = 1.
    - i=1, arr[1]=2: sum = 12. target = 12 - (-10) = 22. Map has no 22. map[12] = 1.
    - i=2, arr[2]=-2: sum = 10. target = 10 - (-10) = 20. Map has no 20. map[10] becomes 2.
    - i=3, arr[3]=-20: sum = -10. target = -10 - (-10) = 0. Map HAS 0 (freq 1)! count += 1 = 1. map[-10] = 1.
    - i=4, arr[4]=10: sum = 0. target = 0 - (-10) = 10. Map HAS 10 (freq 2)! count += 2 = 3. map[0] becomes 2.
    Result: 3
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    int countSubarrays(vector<int>& arr, int k) {
        unordered_map<int, int> prefixCounts;
        
        // Base case: to handle subarrays that start from index 0
        prefixCounts[0] = 1;
        
        int count = 0;
        int sum = 0;
        
        for (int num : arr) {
            sum += num;
            
            int target = sum - k;
            
            // If (sum - k) exists in the map, add its frequency to our count
            if (prefixCounts.find(target) != prefixCounts.end()) {
                count += prefixCounts[target];
            }
            
            // Add the current prefix sum to the map
            prefixCounts[sum]++;
        }
        
        return count;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n >> k;
            vector<int> arr(n);
            for (int i = 0; i < n; i++) cin >> arr[i];
            Solution ob;
            cout << ob.countSubarrays(arr, k) << "\n";
        }
    }
    return 0;
}
