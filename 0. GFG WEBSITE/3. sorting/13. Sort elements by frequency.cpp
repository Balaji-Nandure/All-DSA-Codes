// hashmap and heap method
vector<int> sortByFreq(vector<int> &arr) {
    int n = arr.size();

    // hash map to store the 
    // frequency of each element
    unordered_map<int, int> mp;

    // store the frequency of each element
    for(int i = 0; i < n; i++) {
        mp[arr[i]]++;
    }

    // to store the frequency 
    // in descending order
    priority_queue<vector<int>> pq;

    // store the frequency and the element
    for(auto i : mp) {

        // storing the negative of element
        // to sort the elements with same
        // frequency in ascending order
        pq.push({i.second, -i.first});
    }

    // to store the answer
    vector<int> ans;

    // push the elements in the answer array
    while(!pq.empty()) {
        int freq = pq.top()[0];
        int ele = -pq.top()[1];
        pq.pop();
        for(int i = 0; i < freq; i++) {
            ans.push_back(ele);
        }
    }

    return ans;
}


vector<int> sortByFrequency(vector<int>& nums) {
    /*
    Problem:
    Sort elements by frequency.
    - Elements with higher frequency come first.
    - If frequencies are equal, smaller element comes first (GFG standard).

    Approach:
    1. Count frequency of each element using hashmap.
    2. Store elements in a vector.
    3. Sort the vector using custom comparator:
       - Primary: frequency (descending)
       - Secondary: value (ascending)
    4. Rebuild the result using sorted order and frequencies.

    Time: O(n log n)
    Space: O(n)
    */

    unordered_map<int, int> freq;
    for (int x : nums) {
        freq[x]++;
    }

    sort(nums.begin(), nums.end(), [&](int a, int b) {
        if (freq[a] != freq[b])
            return freq[a] > freq[b];   // higher frequency first
        return a < b;                   // smaller value first
    });

    return nums;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/sort-elements-by-frequency/1

LeetCode:
https://leetcode.com/problems/sort-array-by-increasing-frequency/
(Note: LeetCode version sorts by increasing frequency; comparator is reversed there)
*/
