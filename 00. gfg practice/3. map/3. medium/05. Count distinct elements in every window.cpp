/*
    Problem Name: Count distinct elements in every window
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given an integer array arr[] and a number k. Find the count of distinct elements in every window of size k in the array.

    Expected Complexities:
    Time Complexity: O(N), where N is the size of the array. We visit each element at most twice (once entering the window, once leaving). Hash map operations take O(1) on average.
    Space Complexity: O(K), to store the frequencies of the elements in the current window of size k.

    Love Babbar Style Approach:
    1. Sliding Window & Hash Map: Since we are querying contiguous subarrays of fixed size `k`, this is a classic Sliding Window problem. To count distinct elements efficiently, a Hash Map (`unordered_map`) is the perfect data structure as its size intrinsically represents the count of distinct elements.
    2. First Window Initialization: We first process the elements from index `0` to `k-1` by inserting them into the hash map and updating their frequencies. After adding `k` elements, the size of our map is our first answer.
    3. Sliding the Window: We iterate from index `k` to the end of the array. For each step:
       - Entering Element: We include the new element `arr[i]` into our map by incrementing its frequency.
       - Leaving Element: We exclude the element that just left the window, which is `arr[i-k]`, by decrementing its frequency.
       - Map Cleanup: If the frequency of the leaving element drops to 0, we completely `erase` it from the map. This ensures the map size accurately reflects the number of distinct elements.
    4. Result Accumulation: At each step of the slide, the size of the map gives us the distinct elements count for the current window. We push this into our result array.
    5. Result: Return the populated result array.

    Dry Run:
    Input: arr = [1, 2, 1, 3, 4, 2, 3], k = 4
    - First Window (i=0 to 3): [1, 2, 1, 3]
      - Map: {1: 2, 2: 1, 3: 1}. Distinct count = 3.
      - Result = [3]
    - Slide 1 (i=4): Add 4, Remove arr[0]=1.
      - Map after add: {1: 2, 2: 1, 3: 1, 4: 1}
      - Map after remove: {1: 1, 2: 1, 3: 1, 4: 1}. Distinct count = 4.
      - Result = [3, 4]
    - Slide 2 (i=5): Add 2, Remove arr[1]=2.
      - Map after add: {1: 1, 2: 2, 3: 1, 4: 1}
      - Map after remove: {1: 1, 2: 1, 3: 1, 4: 1}. Distinct count = 4.
      - Result = [3, 4, 4]
    - Slide 3 (i=6): Add 3, Remove arr[2]=1.
      - Map after add: {1: 1, 2: 1, 3: 2, 4: 1}
      - Map after remove 1: freq of 1 is 0 -> erase 1! Map: {2: 1, 3: 2, 4: 1}. Distinct count = 3.
      - Result = [3, 4, 4, 3]
    Output: [3, 4, 4, 3]
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    vector<int> countDistinct(vector<int>& arr, int k) {
        vector<int> res;
        unordered_map<int, int> freq;
        int n = arr.size();
        
        // Edge case: if k is larger than the array size
        if (k > n) return res;
        
        // Process the first window
        for (int i = 0; i < k; i++) {
            freq[arr[i]]++;
        }
        res.push_back(freq.size());
        
        // Slide the window for the rest of the array
        for (int i = k; i < n; i++) {
            // Add the new element entering the window
            freq[arr[i]]++;
            
            // Remove the old element leaving the window
            int leaving_element = arr[i - k];
            freq[leaving_element]--;
            
            // If the leaving element's frequency drops to 0, completely erase it
            if (freq[leaving_element] == 0) {
                freq.erase(leaving_element);
            }
            
            // Record the number of distinct elements in the current window
            res.push_back(freq.size());
        }
        
        return res;
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
            vector<int> res = ob.countDistinct(arr, k);
            for (int x : res) {
                cout << x << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
