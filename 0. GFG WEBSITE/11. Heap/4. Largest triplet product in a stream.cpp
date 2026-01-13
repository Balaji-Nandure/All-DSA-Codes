/*
Problem:
Largest Triplet Product in a Stream

Given a stream of integers, after reading each element,
print the product of the largest three elements seen so far.
If fewer than three elements have been read, print -1.

Rules:
- Stream is processed from left to right.
- After each insertion, output result for current prefix.

Example:
Input:
arr = [1, 2, 3, 4, 5]

Output:
-1
-1
6
24
60

Explanation:
After 1 → less than 3 elements → -1
After 2 → less than 3 elements → -1
After 3 → 1*2*3 = 6
After 4 → 2*3*4 = 24
After 5 → 3*4*5 = 60

Approach (Optimal – Min Heap of Size 3):
- Maintain a min-heap of size at most 3.
- For each incoming element:
  - Push it into the heap.
  - If heap size exceeds 3, remove the smallest element.
- When heap size == 3:
  - Multiply all elements in heap to get answer.
- This keeps track of the largest 3 elements efficiently.

Why this works:
- The 3 largest elements determine the maximum triplet product.
- Min heap ensures smallest among top 3 is discarded first.

GeeksforGeeks:
https://www.geeksforgeeks.org/largest-triplet-product-stream/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N log 3) ≈ O(N)

Space Complexity:
O(1)
*/

vector<int> largestTripletProducts(vector<int>& arr) {
    priority_queue<int> pq;
    vector<int> result;
    
    for (int i = 0; i < arr.size(); i++) {
        pq.push(arr[i]);

        // If there are less than 3 elements, push -1
        if (pq.size() < 3) {
            result.push_back(-1);
        } else {
            // Extract top 3 elements
            int first = pq.top(); pq.pop();
            int second = pq.top(); pq.pop();
            int third = pq.top(); pq.pop();

            result.push_back(first * second * third);

            // Push them back
            pq.push(first);
            pq.push(second);
            pq.push(third);
        }
    }
    return result;
}