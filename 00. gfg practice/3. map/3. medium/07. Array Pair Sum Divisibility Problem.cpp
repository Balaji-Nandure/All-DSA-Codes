/*
    Problem Name: Array Pair Sum Divisibility Problem
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array of integers arr and a number k, write a function that returns true if the given array can be divided into pairs such that the sum of every pair is divisible by k.

    Expected Complexities:
    Time Complexity: O(N), where N is the length of the array. We iterate through the array once to calculate remainders and once through the remainders up to k/2.
    Space Complexity: O(K), where K is the given divisor, to store the frequency of each remainder.

    Love Babbar Style Approach:
    1. Odd Length Check: If the array length is odd, we can't possibly form pairs for every element. Return `false` immediately.
    2. Remainder Frequency Map: When checking if the sum of two numbers `a` and `b` is divisible by `k`, the math translates to: `(a % k + b % k) % k == 0`. We can use an array `freq` of size `k` to store the frequency of each remainder `arr[i] % k`.
    3. Pairing Logic: We check if every remainder can be perfectly paired up:
       - Remainder 0: Elements with remainder 0 must pair with other elements with remainder 0. Hence, `freq[0]` must be an even number.
       - Remainder `k/2` (if `k` is even): Elements with remainder `k/2` must pair with themselves. Hence, `freq[k/2]` must be an even number.
       - Other Remainders `r`: An element with remainder `r` must pair with an element with remainder `k - r`. Therefore, `freq[r]` must exactly equal `freq[k - r]`.
    4. Validation: We iterate from `r = 1` to `k/2`. If any of the conditions fail, we return `false`. If we pass all checks, we return `true`.

    Dry Run:
    Input: arr = [9, 5, 7, 3], k = 6
    - Calculate Remainders:
      - 9 % 6 = 3 -> freq[3] = 1
      - 5 % 6 = 5 -> freq[5] = 1
      - 7 % 6 = 1 -> freq[1] = 1
      - 3 % 6 = 3 -> freq[3] = 2
    - Check Conditions:
      - freq[0] is 0 (even). Valid.
      - r = 1: freq[1] == freq[6-1] -> freq[1] == freq[5] -> 1 == 1. Valid.
      - r = 2: freq[2] == freq[6-2] -> freq[2] == freq[4] -> 0 == 0. Valid.
      - r = 3 (which is k/2): freq[3] is 2 (even). Valid.
    Result: true
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    bool canPair(vector<int> nums, int k) {
        // If the number of elements is odd, perfect pairing is impossible
        if (nums.size() % 2 != 0) {
            return false;
        }
        
        // Array to store the frequency of remainders
        vector<int> freq(k, 0);
        
        // Count frequencies of remainders
        for (int num : nums) {
            // using ((num % k) + k) % k to handle potential negative numbers
            // even though the constraints say 1 <= arr[i], it's a good generic practice
            int remainder = ((num % k) + k) % k;
            freq[remainder]++;
        }
        
        // Check if pairs can be formed
        if (freq[0] % 2 != 0) return false;
        
        for (int i = 1; i <= k / 2; i++) {
            // Special case for middle element when k is even
            if (i == k - i) {
                if (freq[i] % 2 != 0) return false;
            } 
            // For other remainders, freq of i must match freq of k-i
            else {
                if (freq[i] != freq[k - i]) return false;
            }
        }
        
        return true;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n >> k;
            vector<int> nums(n);
            for (int i = 0; i < n; i++) cin >> nums[i];
            Solution ob;
            if (ob.canPair(nums, k)) cout << "true\n";
            else cout << "false\n";
        }
    }
    return 0;
}
