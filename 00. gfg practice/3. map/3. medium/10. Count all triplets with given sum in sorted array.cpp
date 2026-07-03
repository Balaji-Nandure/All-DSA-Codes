/*
    Problem Name: Count all triplets with given sum in sorted array
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a sorted array arr[] and a target value, the task is to count triplets (i, j, k) of valid indices, such that arr[i] + arr[j] + arr[k] = target and i < j < k.

    Expected Complexities:
    Time Complexity: O(N^2), where N is the length of the array. We use a nested loop; the outer loop fixes the first element and the inner loop uses the two-pointer approach which traverses the rest of the array.
    Space Complexity: O(1), as we are using constant extra space.

    Love Babbar Style Approach:
    1. Loop through the array with `i` from 0 to n-3. This fixes the first element of our triplet.
    2. For each `i`, initialize two pointers: `left = i + 1` and `right = n - 1`. The goal is to find pairs in the remaining array that sum up to `target - arr[i]`.
    3. While `left < right`:
        a. Calculate `sum = arr[left] + arr[right]`.
        b. If `sum == target - arr[i]`:
            - We found a valid triplet. Now we need to handle duplicates carefully.
            - If `arr[left] == arr[right]`, all elements from `left` to `right` are identical. The number of ways to pick 2 elements from `right - left + 1` identical elements is `n * (n - 1) / 2`. Add this to count and break the inner loop.
            - If `arr[left] != arr[right]`, count how many times `arr[left]` repeats and how many times `arr[right]` repeats.
              Let `countLeft = 1`, `countRight = 1`.
              While `left + 1 < right` and `arr[left] == arr[left + 1]`, increment `left` and `countLeft`.
              While `right - 1 > left` and `arr[right] == arr[right - 1]`, decrement `right` and `countRight`.
              Add `countLeft * countRight` to the total count. Move `left` forward and `right` backward.
        c. If `sum < target - arr[i]`, increment `left` to increase the sum.
        d. If `sum > target - arr[i]`, decrement `right` to decrease the sum.
    4. Return the total count.

    Dry Run:
    Input: arr[] = [-3, -1, -1, 0, 1, 2], target = -2
    - i = 0, arr[i] = -3, target_sum = -2 - (-3) = 1. left = 1 (-1), right = 5 (2)
      - arr[1] + arr[5] = -1 + 2 = 1. Matches!
      - arr[left] != arr[right]. countLeft = 2 (since arr[1]==arr[2]), countRight = 1 (arr[5]). 
      - add 2 * 1 = 2 to count. (Triplets: [-3, -1(idx1), 2], [-3, -1(idx2), 2])
      - left becomes 3 (0), right becomes 4 (1).
      - arr[3] + arr[4] = 0 + 1 = 1. Matches!
      - arr[left] != arr[right]. countLeft = 1, countRight = 1.
      - add 1 * 1 = 1 to count. count = 3.
      - left becomes 4, loop terminates.
    - i = 1, arr[i] = -1, target_sum = -2 - (-1) = -1. left = 2 (-1), right = 5 (2)
      - arr[left] + arr[right] = -1 + 2 = 1 > -1. right = 4.
      - arr[2] + arr[4] = -1 + 1 = 0 > -1. right = 3.
      - arr[2] + arr[3] = -1 + 0 = -1. Matches!
      - countLeft = 1, countRight = 1. Add 1 to count. count = 4.
    - i = 2 ... similarly no more valid triplets are found.
    Result = 4.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int countTriplets(vector<int>& arr, int target) {
        int n = arr.size();
        int count = 0;
        
        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;
            int remaining_target = target - arr[i];
            
            while (left < right) {
                int sum = arr[left] + arr[right];
                
                if (sum == remaining_target) {
                    if (arr[left] == arr[right]) {
                        // All elements between left and right are same
                        int num_elements = right - left + 1;
                        count += (num_elements * (num_elements - 1)) / 2;
                        break;
                    } else {
                        int countLeft = 1;
                        int countRight = 1;
                        
                        // Count occurrences of arr[left]
                        while (left + 1 < right && arr[left] == arr[left + 1]) {
                            left++;
                            countLeft++;
                        }
                        
                        // Count occurrences of arr[right]
                        while (right - 1 > left && arr[right] == arr[right - 1]) {
                            right--;
                            countRight++;
                        }
                        
                        count += (countLeft * countRight);
                        left++;
                        right--;
                    }
                } else if (sum < remaining_target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return count;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n, target;
            cin >> n >> target;
            vector<int> arr(n);
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            
            Solution ob;
            cout << ob.countTriplets(arr, target) << "\n";
        }
    }
    return 0;
}
