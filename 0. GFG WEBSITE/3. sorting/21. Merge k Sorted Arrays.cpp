vector<int> mergeKSortedArrays(vector<vector<int>>& arrays) {
    /*
    Problem:
    Merge k sorted arrays into a single sorted array.

    Approach (Min-Heap / K-way Merge):
    1. Each array is already sorted.
    2. Use a min-heap to always extract the smallest current element.
    3. Heap stores a tuple:
       (value, array_index, index_in_that_array)
    4. Push the first element of each non-empty array into heap.
    5. Repeat until heap is empty:
       - Pop the smallest element and add it to result.
       - From the same array, push the next element (if exists).

    Time:
    - Let total elements = N, number of arrays = k
    - O(N log k)

    Space:
    - O(k) for heap (excluding output)
    */

    vector<int> result;

    // We use tuple<int, int, int> in the min-heap because:
    //   - First int:   the actual element value (for heap order)
    //   - Second int:  array index (which array this value came from)
    //   - Third int:   index within that array (position of value)
    // This is necessary so that after popping the smallest element, we can 
    // efficiently find and insert the "next" element from the same array.
    // If we stored only the int value in the heap: we would lose track of 
    // which array and position it came from, so could not know what to push next.
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
    > minHeap;

    // Push first element of each array
    for (int i = 0; i < arrays.size(); i++) {
        if (!arrays[i].empty()) {
            minHeap.push({arrays[i][0], i, 0});
        }
    }

    // K-way merge
    while (!minHeap.empty()) {
        auto [val, arrIdx, idx] = minHeap.top();
        minHeap.pop();

        result.push_back(val);

        if (idx + 1 < arrays[arrIdx].size()) {
            minHeap.push({arrays[arrIdx][idx + 1], arrIdx, idx + 1});
        }
    }

    return result;
}

/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/merge-k-sorted-arrays/1

LeetCode:
https://leetcode.com/problems/merge-k-sorted-lists/
(conceptually equivalent problem)
*/
