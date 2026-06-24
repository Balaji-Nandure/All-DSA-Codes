/*
    Problem Name: Subarray with 0 sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array of integers, arr[]. Find if there is a subarray (of size at least one) with 0 sum. Return true/false depending upon whether there is a subarray present with 0-sum or not. 

    Expected Complexities:
    Time Complexity: O(N), where N is the size of the array. Inserting and searching in an unordered_set takes O(1) time on average.
    Space Complexity: O(N), to store the prefix sums in the unordered_set.

    Love Babbar Style Approach:
    1. Prefix Sum Concept: We can keep a running sum (prefix sum) as we traverse the array. If a subarray has a sum of 0, it means the prefix sum before that subarray and the prefix sum after that subarray must be exactly the same.
    2. Hash Set: We use an `unordered_set` to store all the prefix sums we encounter. We use `long long` to prevent integer overflow as the running sum can get very large or small.
    3. Traversal: We iterate through the array and add each element to our running `sum`.
    4. Checking Conditions: At each step, we check two critical things:
       - Is the current `sum` equal to 0? If yes, the subarray from index 0 to the current index has a sum of 0.
       - Does the current `sum` already exist in our hash set? If yes, it means the subarray between the previous occurrence of this sum and the current index has a sum of exactly 0.
       If any of these are true, return `true`.
    5. Result: If we finish traversing the array without finding any of these conditions, it means no 0-sum subarray exists, so we return `false`.

    Dry Run:
    Input: arr[] = [4, 2, -3, 1, 6]
    - Initial values: sum = 0, hashSet = {}
    - i = 0, arr[0] = 4: sum = 4. Set doesn't have 4. hashSet = {4}
    - i = 1, arr[1] = 2: sum = 6. Set doesn't have 6. hashSet = {4, 6}
    - i = 2, arr[2] = -3: sum = 3. Set doesn't have 3. hashSet = {4, 6, 3}
    - i = 3, arr[3] = 1: sum = 4. Set HAS 4! This means the sum from index 1 to 3 is 0 (2 - 3 + 1 = 0). We return true.
    Result: true
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
  public:
    // Function to check whether there is a subarray present with 0-sum or not.
    bool subArrayExists(vector<int>& arr) {
        unordered_set<long long> prefixSums;
        long long sum = 0;
        
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            
            // If the current sum is 0, or if we have seen this sum before
            if (sum == 0 || prefixSums.find(sum) != prefixSums.end()) {
                return true;
            }
            
            // Insert the current sum into the set
            prefixSums.insert(sum);
        }
        
        return false;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; i++) cin >> arr[i];
            Solution ob;
            if (ob.subArrayExists(arr)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
    }
    return 0;
}
