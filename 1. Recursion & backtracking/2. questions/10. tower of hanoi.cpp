/*
 * Problem: Tower of Hanoi
 *
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/tower-of-hanoi/0
 *
 * Move n disks from source rod to target rod using auxiliary rod.
 *
 * Rules:
 * - Only one disk can be moved at a time
 * - Only top disk of any rod can be moved
 * - Larger disk cannot be placed on top of smaller disk
 *
 * Approach: For n disks:
 * 1. Move (n-1) disks from source to auxiliary (using target as auxiliary)
 * 2. Move nth disk from source to target
 * 3. Move (n-1) disks from auxiliary to target (using source as auxiliary)
 *
 * Time: O(2^n) - exponential number of moves
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

// Solve Tower of Hanoi recursively
void towerOfHanoi(int n, char src, char aux, char dest, int &moveCount) {
    // Base case: no disks to move
    if(n == 0) return;
    
    // Step 1: Move n-1 disks from source to auxiliary (using dest as auxiliary)
    towerOfHanoi(n-1, src, dest, aux, moveCount);
    
    // Step 2: Move nth (largest) disk from source to destination
    cout << "Move disk " << n << " from rod " << src << " to rod " << dest << endl;
    moveCount++;
    
    // Step 3: Move n-1 disks from auxiliary to destination (using src as auxiliary)
    towerOfHanoi(n-1, aux, src, dest, moveCount);
}

int main() {
    int n = 3; // You can change for more disks
    int moveCount = 0;
    towerOfHanoi(n, 'A', 'B', 'C', moveCount);
    cout << "Total moves: " << moveCount << endl;
    return 0;
}
