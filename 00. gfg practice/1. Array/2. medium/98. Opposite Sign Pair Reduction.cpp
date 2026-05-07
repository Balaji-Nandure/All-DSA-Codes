/*
Problem: Opposite Sign Pair Reduction

GFG: https://www.geeksforgeeks.org/problems/opposite-sign-pair-reduction/

Description:
Given an array arr[], return the final array by repeatedly applying the following operation from left to right until no more valid operations can be performed.

If two adjacent elements have opposite signs:

If their absolute values are different, remove both elements and insert one with the greater absolute value, preserving its sign.
If their absolute values are equal, remove both elements without inserting any new element.

Examples:

Input: arr[] = [10, -5, -8, 2, -5]
Output: [10]
Explanation: 
At Index 0: Element 10 has positive sign.
At Index 1: -5 has lesser absolute value than 10. Replace both of them with 10.
At Index 2: -8 has lesser absolute value than 10. Replace both of them with 10.
At Index 3: 2 has positive sign. So it will be in the array.
At Index 4: -5 has greater absolute value than 2. Replace both of them with 5.
Now -5 has lesser absolute value than 10. Replace both of them with 10.

Input: arr[] = [5, -5, -2, -10]
Output: [-2, -10]
Explanation: 1st and 2nd element gets discarded because both elements have same values but opposite sign. 3rd and 4th elements have same sign. So, both will be in the array.

Input: arr[] = [-20, 1, 20]
Output: []
Explanation: 1st and 2nd elements are removed, and -20 is inserted since it has larger absolute value. Then, the remaining elements [-20, 20] are removed (equal absolute values, opposite signs).

Constraints:
1 ≤ arr.size() ≤ 10^5
-10000 ≤ arr[i] ≤ 10000
arr[i] != 0

Approach (Stack-based Simulation):
This is a classic stack-based reduction problem where we simulate the pair reduction process.

Key insight:
- Use stack to store surviving elements
- For each element, check collisions with stack top
- Remove weaker element(s) based on absolute values
- Continue until no more collisions possible

Algorithm:
1. Initialize empty stack
2. For each element in array:
   - While stack not empty and current element has opposite sign with stack top
   - Compare absolute values:
     - If stack top has greater absolute value: current element dies
     - If current element has greater absolute value: pop stack top
     - If equal absolute values: both die (pop stack, current dies)
   - If current survives all collisions, push to stack
3. Return stack as final array

Time Complexity: O(n²) in worst case (each element may collide with multiple stack elements)
Space Complexity: O(n)

Pattern: Stack-based Pair Reduction
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
STACK SIMULATION
=====================================================

TC: O(n²) worst case
SC: O(n)

🔥 STACK-BASED APPROACH
- Use stack to store surviving elements
- Simulate collision process from left to right
- Handle all collision scenarios

🧠 KEY INSIGHT:
Stack represents elements that have survived
all previous collisions.
Current element must survive collisions
with all stack elements to be added.

🎯 ALGORITHM:
1. For each element:
   - Check collisions with stack top
   - Apply reduction rules based on absolute values
   - Push survivors to stack
2. Return stack as final array

⚡ COLLISION RULES:
- Opposite signs: collision occurs
- Different absolute values: weaker dies
- Equal absolute values: both die
- Same sign: no collision
*/

class Solution {
public:

    vector<int> OppositeSignPairReduction(vector<int>& arr) {
        
        vector<int> st; // Acts as a stack to store surviving elements
        
        for (int x : arr) {
            
            bool survived = true;
            
            // While stack top and current element have opposite signs
            while (!st.empty() && ((st.back() > 0) != (x > 0))) {
                
                if (abs(st.back()) > abs(x)) {
                    
                    // Stack element is stronger: current element is destroyed
                    survived = false;
                    break;
                } 
                else if (abs(st.back()) < abs(x)) {
                    
                    // Current element is stronger: pop stack and continue checking
                    st.pop_back();
                } 
                else {
                    
                    // Equal strength: both are destroyed
                    st.pop_back();
                    survived = false;
                    break;
                }
            }
            
            // If current element survived all collisions, push it to stack
            if (survived) {
                st.push_back(x);
            }
        }
        
        return st;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    PAIR REDUCTION with RULES

Think immediately:
    STACK SIMULATION

-----------------------------------------------------

KEY OBSERVATIONS:

Stack represents:
- Elements that survived previous collisions
- Processing order matters (left to right)

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling equal absolute values correctly
2. Forgetting opposite sign condition
3. Wrong comparison of absolute values
4. Not processing all stack collisions

-----------------------------------------------------

SIMILAR PROBLEMS

- Reduce Array Size
- Gas Station Problem
- Collision Detection Algorithms
- Stack-based Reductions

-----------------------------------------------------
*/
