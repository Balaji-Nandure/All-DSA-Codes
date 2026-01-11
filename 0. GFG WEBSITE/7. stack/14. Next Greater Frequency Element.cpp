/*
Problem:
Next Greater Frequency Element

Given an array of integers, for each element find the next element
to its right whose frequency in the array is strictly greater than
the frequency of the current element.
If no such element exists, output -1.

Rules:
- Frequency is calculated over the entire array.
- Next element must lie to the right.
- Comparison is based on frequency, not value.

Example:
Input:
arr = [1, 1, 2, 3, 4, 2, 1]

Output:
[-1, -1, 1, 2, 2, 1, -1]

Approach:
- Compute frequency of each element using hashmap.
- Use a monotonic stack holding elements.
- Traverse array from right to left.
- While stack top has frequency <= current element frequency, pop.
- Top of stack (if any) is the answer for current element.
- Push current element into stack.

GeeksforGeeks:
https://www.geeksforgeeks.org/next-greater-frequency-element/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
    public:
        vector<int> nextGreaterFrequency(vector<int>& arr) {
    
            unordered_map<int,int> freq;
            for (int x : arr) freq[x]++;
    
            int n = arr.size();
            vector<int> ans(n);
            stack<int> st;
    
            for (int i = n - 1; i >= 0; i--) {
    
                while (!st.empty() && freq[st.top()] <= freq[arr[i]]) {
                    st.pop();
                }
    
                if (st.empty()) ans[i] = -1;
                else ans[i] = st.top();
    
                st.push(arr[i]);
            }
    
            return ans;
        }
    };
    