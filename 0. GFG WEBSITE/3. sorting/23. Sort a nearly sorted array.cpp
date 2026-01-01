vector<int> sortNearlySorted(vector<int>& arr, int k) {
    /*
    Problem:
    Sort a nearly sorted (k-sorted) array.
    Each element is at most k positions away from its correct position.

    Approach (Min-Heap of size k+1):
    1. Use a min-heap (priority queue).
    2. Push the first (k+1) elements into the heap.
    3. For remaining elements:
       - Extract the minimum from heap and place it in result.
       - Push the next element from array into heap.
    4. After processing all elements, extract remaining heap elements.

    Why it works:
    - The correct element for any position i must be within next k elements.

    Time: O(n log k)
    Space: O(k)
    */

    priority_queue<int, vector<int>, greater<int>> minHeap;
    vector<int> result;

    int n = arr.size();

    // Step 1: push first k+1 elements
    for (int i = 0; i <= k && i < n; i++) {
        minHeap.push(arr[i]);
    }

    int index = k + 1;

    // Step 2: process remaining elements
    while (index < n) {
        result.push_back(minHeap.top());
        minHeap.pop();

        minHeap.push(arr[index]);
        index++;
    }

    // Step 3: empty heap
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    return result;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/nearly-sorted-1587115620/1

LeetCode:
https://leetcode.com/problems/sort-an-array/ 
(Note: nearly-sorted variant commonly discussed, heap-based solution expected)
*/
