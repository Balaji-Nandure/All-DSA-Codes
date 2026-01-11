/*
Problem:
Delete Middle Element of a Stack

Given a stack of size N, delete its middle element.
For even N, delete the lower middle element.
Indexing is 0-based.

Approaches required:
1) Using Vector            → O(N) Time, O(N) Space
2) Using Recursion         → O(N) Time, O(N) Space
3) Using Auxiliary Stack   → O(N) Time, O(N) Space

Example:
Input stack (top → bottom):
5  4  3  2  1
N = 5

Output stack:
5  4  2  1

GeeksforGeeks:
https://www.geeksforgeeks.org/delete-middle-element-of-a-stack/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(N)
*/

class Solution {
    public:
    
        /* -------- Approach 1: Using Vector -------- */
        void deleteMiddle_Vector(stack<int>& st, int n) {
            vector<int> temp;
            int k = n / 2;
            for (int i = 0; i < k; i++) {
                temp.push_back(st.top());
                st.pop();
            }
            st.pop();
            for (int i = temp.size() - 1; i >= 0; i--) {
                st.push(temp[i]);
            }
        }
        
    
    
        /* -------- Approach 2: Using Recursion -------- */
        void solveRec(stack<int>& st, int k) {
            if (k == 1) {
                st.pop();
                return;
            }
    
            int temp = st.top();
            st.pop();
            solveRec(st, k - 1);
            st.push(temp);
        }
    
        void deleteMiddle_Recursion(stack<int>& st, int n) {
            int k = (n / 2) + 1;
            solveRec(st, k);
        }
    
    
        /* -------- Approach 3: Using Auxiliary Stack -------- */
        void deleteMiddle_Stack(stack<int>& st, int n) {
    
            stack<int> temp;
            int mid = n / 2;
    
            for (int i = 0; i < n; i++) {
                if (i == mid) {
                    st.pop();
                } else {
                    temp.push(st.top());
                    st.pop();
                }
            }
    
            while (!temp.empty()) {
                st.push(temp.top());
                temp.pop();
            }
        }
    };
    