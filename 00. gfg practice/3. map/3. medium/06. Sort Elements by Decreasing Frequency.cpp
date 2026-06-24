/*
    Problem Name: Sort Elements by Decreasing Frequency
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an array of integers arr[], sort the array according to the frequency of elements, i.e. elements that have higher frequency comes first. If the frequencies of two elements are the same, then the smaller number comes first.

    Expected Complexities:
    Time Complexity: O(N log N), where N is the number of elements. We use standard sorting algorithms, which take O(N log N) time, while counting frequencies takes O(N).
    Space Complexity: O(N) to store the frequencies in a hash map.

    Love Babbar Style Approach:
    1. Frequency Map: The first step is to count how many times each element appears in the array. We use an `unordered_map<int, int>` to efficiently store the mapping of `element -> frequency`.
    2. Custom Sorting logic: We can sort the original array in-place, but we need to tell the `sort` function *how* to compare two elements `a` and `b`. 
    3. Lambda Function: We pass a custom lambda function to `std::sort` which captures our frequency map by reference `[&]`.
    4. Sorting Rules:
       - Compare the frequencies: `freq[a]` vs `freq[b]`.
       - If `freq[a] != freq[b]`, the element with the higher frequency should come first (return `freq[a] > freq[b]`).
       - If `freq[a] == freq[b]`, the elements have the same frequency. In this case, the smaller number should come first (return `a < b`).
    5. Result: The array `arr` is now sorted exactly as required. We just return it.

    Dry Run:
    Input: arr[] = [5, 5, 4, 6, 4]
    - Frequency Map: {5: 2, 4: 2, 6: 1}
    - During sorting:
      - Compare 5 and 4: Both have frequency 2. Since frequencies are equal, we check values: is 5 < 4? False. So 4 comes before 5.
      - Compare 4 and 6: freq(4)=2, freq(6)=1. 2 > 1? True. So 4 comes before 6.
      - Compare 5 and 6: freq(5)=2, freq(6)=1. 2 > 1? True. So 5 comes before 6.
    - Final sorted array: [4, 4, 5, 5, 6]
    Result: [4, 4, 5, 5, 6]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
  public:
    vector<int> sortByFreq(vector<int>& arr) {
        unordered_map<int, int> freq;
        
        // Count frequencies of each element
        for (int num : arr) {
            freq[num]++;
        }
        
        // Sort the array using a custom comparator
        // What is [&] and why do we use it?
        // [&] is a capture clause in a lambda function that tells it to "capture all local variables by reference".
        // We use it here so the lambda function can access the 'freq' map (declared outside) efficiently without copying it.
        sort(arr.begin(), arr.end(), [&](int a, int b) {
            // If frequencies are different, higher frequency comes first
            if (freq[a] != freq[b]) {
                return freq[a] > freq[b];
            }
            // If frequencies are same, smaller element comes first
            return a < b;
        });
        
        return arr;
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
            vector<int> res = ob.sortByFreq(arr);
            for (int x : res) {
                cout << x << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
