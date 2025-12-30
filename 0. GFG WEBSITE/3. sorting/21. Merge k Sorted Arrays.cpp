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
    int n = mat.size();
    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>
    > pq;
    
    // push first element of all the arr in mat
    for(int i = 0; i < n; i++){
        if(mat[i].size()){
            int val = mat[i][0];
            int x = i;
            int y = 0;
            
            pq.push({val, x, y});
        }
    }
    
    while(pq.size()){
        auto [val, x, y] = pq.top();
        pq.pop();
        result.push_back(val);
        if(y + 1 < mat[x].size()){
            pq.push({mat[x][y +  1], x, y + 1});
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
