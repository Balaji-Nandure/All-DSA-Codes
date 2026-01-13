/*
Problem:
Heap Sort using priority_queue

Approach:
- Push all elements into a priority_queue (Max Heap).
- Repeatedly extract the top element and place it from back to front.
- priority_queue in C++ is a Max Heap by default.

Time Complexity:
O(N log N)

Space Complexity:
O(N)   // because priority_queue uses extra space
*/

class Solution {
    public:
        void heapSort(vector<int>& arr) {
    
            priority_queue<int> pq;
    
            // Insert all elements into max heap
            for (int x : arr) {
                pq.push(x);
            }
    
            // Extract max and place from end
            for (int i = arr.size() - 1; i >= 0; i--) {
                arr[i] = pq.top();
                pq.pop();
            }
        }
    };
    