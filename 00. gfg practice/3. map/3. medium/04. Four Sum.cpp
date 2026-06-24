/*
    Problem Name: 4Sum
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array of integers and another number `target`. Find all the unique quadruplets from the given array that sums up to `target`.

    Expected Complexities:
    Time Complexity: O(N^3), where N is the length of the array. The array is sorted, and we use two nested loops to fix the first two elements and a two-pointer approach for the remaining two elements.
    Space Complexity: O(1) auxiliary space (excluding the output). 

    Love Babbar Style Approach:
    1. Sorting: First, sort the given array. Sorting helps in easily identifying duplicates and allows us to use the two-pointer approach effectively.
    2. Fixing First Two Elements: 
       - Iterate with a loop variable `i` from `0` to `n-3` to fix the first element. If `arr[i]` is the same as the previous element, continue to skip duplicates.
       - Iterate with a loop variable `j` from `i+1` to `n-2` to fix the second element. Again, if `arr[j]` is the same as the previous element, continue to skip duplicates.
    3. Two Pointers for Remaining Elements:
       - For the fixed `i` and `j`, use two pointers: `left = j + 1` and `right = n - 1`.
       - Calculate the sum of the four elements. Use `long long` to avoid integer overflow during the addition.
       - If `sum == target`, we have found a valid quadruplet. Add it to the answer.
       - Then, move both `left` and `right` pointers and skip any duplicate values to avoid duplicate quadruplets.
       - If `sum < target`, increment `left` to increase the sum.
       - If `sum > target`, decrement `right` to decrease the sum.
    4. Result: Return the list of unique quadruplets.

    Dry Run:
    Input: arr = [1, 0, -1, 0, -2, 2], target = 0
    - Sort arr: [-2, -1, 0, 0, 1, 2]
    - i = 0 (arr[0] = -2):
      - j = 1 (arr[1] = -1):
        - left = 2 (arr[2] = 0), right = 5 (arr[5] = 2)
        - sum = -2 + (-1) + 0 + 2 = -1 < 0 -> left++
        - left = 3 (arr[3] = 0), right = 5 (arr[5] = 2)
        - sum = -2 + (-1) + 0 + 2 = -1 < 0 -> left++
        - left = 4 (arr[4] = 1), right = 5 (arr[5] = 2)
        - sum = -2 + (-1) + 1 + 2 = 0 == 0 -> Found [-2, -1, 1, 2]. left++, right--
      - j = 2 (arr[2] = 0):
        - left = 3 (arr[3] = 0), right = 5 (arr[5] = 2)
        - sum = -2 + 0 + 0 + 2 = 0 == 0 -> Found [-2, 0, 0, 2]. left++, right--
    Result: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    vector<vector<int>> fourSum(vector<int> &arr, int target) {
        vector<vector<int>> ans;
        int n = arr.size();
        
        // Sort the array to easily handle duplicates and use two pointers
        sort(arr.begin(), arr.end());
        
        for (int i = 0; i < n - 3; i++) {
            // Skip duplicates for the first element
            if (i > 0 && arr[i] == arr[i - 1]) continue;
            
            for (int j = i + 1; j < n - 2; j++) {
                // Skip duplicates for the second element
                if (j > i + 1 && arr[j] == arr[j - 1]) continue;
                
                int left = j + 1;
                int right = n - 1;
                
                while (left < right) {
                    // Use long long to prevent integer overflow
                    long long sum = (long long)arr[i] + arr[j] + arr[left] + arr[right];
                    
                    if (sum == target) {
                        ans.push_back({arr[i], arr[j], arr[left], arr[right]});
                        
                        left++;
                        right--;
                        
                        // Skip duplicates for the third element
                        while (left < right && arr[left] == arr[left - 1]) {
                            left++;
                        }
                        
                        // Skip duplicates for the fourth element
                        while (left < right && arr[right] == arr[right + 1]) {
                            right--;
                        }
                    } else if (sum < target) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }
        
        return ans;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n, target;
            cin >> n >> target;
            vector<int> arr(n);
            for (int i = 0; i < n; i++) cin >> arr[i];
            Solution ob;
            vector<vector<int>> res = ob.fourSum(arr, target);
            for (auto &row : res) {
                for (int x : row) {
                    cout << x << " ";
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
