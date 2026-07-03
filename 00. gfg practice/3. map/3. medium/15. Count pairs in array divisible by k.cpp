/*
    Problem Name: Count pairs in array divisible by k
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array arr[] and positive integer k, count total number of pairs in the array whose sum is divisible by k.

    Expected Complexities:
    Time Complexity: O(N + K), where N is the number of elements in the array and K is the divisor. We traverse the array once to compute remainder frequencies, and then loop up to K/2 to calculate pairs.
    Space Complexity: O(K), for the remainder frequency array.

    Love Babbar Style Approach:
    1. A pair `(a, b)` has a sum perfectly divisible by `k` if `(a % k + b % k) % k == 0`.
    2. We can compute the remainder of each element when divided by `k` and store their frequencies in an array of size `k`.
       For example, `rem[x % k]++`.
    3. Now we simply count the valid pairs using combinations!
       - Case 1 (Remainder 0): Numbers perfectly divisible by `k` can only form valid pairs with other numbers perfectly divisible by `k`. Using nCr combinations, Number of pairs = `rem[0] * (rem[0] - 1) / 2`.
       - Case 2 (Remainder i and k-i): Numbers leaving remainder `i` can form valid pairs with numbers leaving remainder `k-i`. Because they are completely distinct groups, Number of pairs = `rem[i] * rem[k - i]`. We check this for `i` from `1` to `(k - 1) / 2`.
       - Case 3 (Remainder k/2): If `k` is even, numbers leaving exactly remainder `k/2` form pairs with other numbers leaving remainder `k/2`. Number of pairs = `rem[k/2] * (rem[k/2] - 1) / 2`.
    4. Sum all these pairs up and return the result. Use `long long` to definitively prevent integer overflow when multiplying large frequency values.

    Dry Run:
    Input: arr = [2, 2, 1, 7, 5, 3], k = 4
    Remainders mapped:
    - 2 % 4 = 2 -> rem[2]++
    - 2 % 4 = 2 -> rem[2]++
    - 1 % 4 = 1 -> rem[1]++
    - 7 % 4 = 3 -> rem[3]++
    - 5 % 4 = 1 -> rem[1]++
    - 3 % 4 = 3 -> rem[3]++
    
    rem array: [0, 2, 2, 2] (indices 0 to 3)
    
    Counting pairs:
    - i = 0: rem[0] = 0. Pairs = 0 * -1 / 2 = 0
    - i = 1 (and 4-1 = 3): rem[1] = 2, rem[3] = 2. Pairs = 2 * 2 = 4
    - i = 2 (k/2 exactly): rem[2] = 2. Pairs = 2 * 1 / 2 = 1
    
    Total pairs = 0 + 4 + 1 = 5. Matches Expected Output!
*/

#include <iostream>
#include <vector>

using namespace std;

/*
    Time Complexity: O(N + K)
    Space Complexity: O(K)
*/
class Solution {
public:
    long long countKdivPairs(vector<int>& arr, int k) {
        // Array to store frequencies of remainders
        vector<long long> rem(k, 0);
        
        // Count remainder frequencies
        for (int i = 0; i < arr.size(); i++) {
            rem[arr[i] % k]++;
        }
        
        long long count = 0;
        
        // Pairs with remainder 0
        count += (rem[0] * (rem[0] - 1)) / 2;
        
        // Pairs with remainders i and k-i
        for (int i = 1; i <= k / 2; i++) {
            if (i == k - i) {
                // When k is even, elements with remainder k/2 form pairs with each other
                count += (rem[i] * (rem[i] - 1)) / 2;
            } else {
                // Distinct remainders
                count += (rem[i] * rem[k - i]);
            }
        }
        
        return count;
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
            cout << ob.countKdivPairs(arr, k) << "\n";
        }
    }
    return 0;
}
