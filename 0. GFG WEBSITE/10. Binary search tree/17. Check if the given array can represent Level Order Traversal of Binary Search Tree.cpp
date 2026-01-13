/*
Problem:
Check if the given array can represent Level Order Traversal of a BST

Approach (Optimal – Queue with Ranges):
- First element is the root.
- Maintain a queue of pairs: (minRange, maxRange).
- For each element:
  - Check if it fits the front range.
  - If not, pop ranges until a valid range is found.
  - If no valid range exists → return false.
  - Once placed, push its left and right child ranges.
*/

class Solution {
public:
    bool checkBST(vector<int>& arr) {

        if (arr.empty()) return true;

        queue<pair<int,int>> q;
        q.push({INT_MIN, INT_MAX});

        int i = 0;

        while (i < arr.size()) {

            bool placed = false;

            while (!q.empty()) {

                auto range = q.front();
                q.pop();

                int low = range.first;
                int high = range.second;

                if (arr[i] > low && arr[i] < high) {

                    q.push({low, arr[i]});
                    q.push({arr[i], high});

                    placed = true;
                    i++;
                    break;
                }
            }

            if (!placed) return false;
        }

        return true;
    }
};
    