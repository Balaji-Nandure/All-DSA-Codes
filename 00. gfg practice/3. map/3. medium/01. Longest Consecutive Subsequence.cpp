/*
    Problem Name: Longest Consecutive Subsequence
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array arr[] of non-negative integers. Find the length of the longest sub-sequence such that elements in the subsequence are consecutive integers, the consecutive numbers can be in any order.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of elements in the array. Inserting elements into the hash set takes O(N), and we only start searching for consecutive sequences from the start of a sequence, meaning each element is visited at most twice.
    Space Complexity: O(N) to store elements in the hash set.

    Love Babbar Style Approach:
    1. Hash Set: A naive sorting approach takes O(N log N) time, but we want O(N). To achieve this, we insert all elements of the array into an `unordered_set`. This allows O(1) average time complexity for checking the presence of any element.
    2. Finding Starting Elements: We iterate through the elements in the array (or the set). An element `x` can only be the starting point of a consecutive sequence if `x - 1` does NOT exist in the set.
    3. Expanding the Sequence: When we find a starting element `x`, we keep checking if `x + 1`, `x + 2`, etc., exist in the set. We increment our current sequence length for each consecutive element found.
    4. Maximizing: We update our `max_len` with the maximum length found across all sequences.
    5. Result: Return the `max_len`.

    Dry Run:
    Input: arr[] = [2, 6, 1, 9, 4, 5, 3]
    - Insert all into unordered_set: {1, 2, 3, 4, 5, 6, 9}
    - Loop through elements:
      - '2': '1' exists, so '2' is not a start.
      - '6': '5' exists, so '6' is not a start.
      - '1': '0' does not exist! It is a start.
        - Check 1, 2, 3, 4, 5, 6... all exist. Length becomes 6.
        - '7' doesn't exist. Stop. max_len = 6.
      - '9': '8' does not exist! It is a start.
        - Check 9. Length becomes 1.
        - '10' doesn't exist. Stop. max_len = max(6, 1) = 6.
      - '4': '3' exists, not a start.
      - '5': '4' exists, not a start.
      - '3': '2' exists, not a start.
    Result: 6
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int findLongestConseqSubseq(vector<int>& arr) {
        unordered_set<int> hashSet;
        for (int num : arr) {
            hashSet.insert(num);
        }

        int max_len = 0;

        for (int num : arr) {
            // Check if it's the start of a sequence
            if (hashSet.find(num - 1) == hashSet.end()) {
                int current_num = num;
                int current_len = 1;

                while (hashSet.find(current_num + 1) != hashSet.end()) {
                    current_num += 1;
                    current_len += 1;
                }

                max_len = max(max_len, current_len);
            }
        }

        return max_len;
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
            cout << ob.findLongestConseqSubseq(arr) << "\n";
        }
    }
    return 0;
}
